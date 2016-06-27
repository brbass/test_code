#include "Test_Trilinos.hh"

Test_Trilinos::
Test_Trilinos(int size,
              double dx,
              double sigma_a,
              double nu_sigma_f,
              double q,
              bool print):
    size_(size),
    dx_(dx),
    sigma_a_(sigma_a),
    nu_sigma_f_(nu_sigma_f),
    q_(q),
    print_(print)
{
    num_entries_per_row_.assign(size_, 3);
    num_entries_per_row_[0] = 2;
    num_entries_per_row_[size_ - 1] = 2;

    
}

// Same diffusion problem with Teuchos Serial classes
void Test_Trilinos::
test_dense()
{
    shared_ptr<SerialDenseMatrix> mat = make_shared<SerialDenseMatrix>(size_, size_);
    shared_ptr<SerialDenseVector> rhs = make_shared<SerialDenseVector>(size_);
    shared_ptr<SerialDenseVector> lhs = make_shared<SerialDenseVector>(size_);
    shared_ptr<SerialDenseSolver> sol = make_shared<SerialDenseSolver>();

    double on_diagonal = 2. / (dx_ * dx_) + sigma_a_;
    double off_diagonal = 1 / (dx_ * dx_);
    
    for (int i = 0; i < size_; ++i)
    {
        if (i != 0)
        {
            (*mat)(i, i - 1) = -off_diagonal;
        }
        (*mat)(i, i) = on_diagonal;
        if (i != size_ - 1)
        {
            (*mat)(i, i + 1) = - off_diagonal;
        }
        
        (*rhs)(i) = q_;
    }

    sol->setMatrix(rcp(mat));
    sol->setVectors(rcp(lhs), rcp(rhs));
    sol->factor();
    sol->solve();

    cout << endl << "Test_Trilinos: test2";
    cout << (*lhs) << endl;
}

// Simple diffusion problem with Belos and Tpetra
void Test_Trilinos::
test_steady()
{
    shared_ptr<Comm> comm = get_comm();
    shared_ptr<Map> map = get_map(comm);
    shared_ptr<CrsMatrix> mat = get_diffusion_matrix(map);
    shared_ptr<Vector> lhs = make_shared<Vector>(rcp(map));
    shared_ptr<Vector> rhs = get_rhs_steady(map);
    shared_ptr<LinearProblem> problem = get_steady_problem(mat,
                                                           lhs,
                                                           rhs);
    
    RCP<Teuchos::FancyOStream> ostr = Teuchos::VerboseObjectBase::getDefaultOStream();
    
    if (print_)
    {
        cout << endl << "Test 1: Belos and Tpetra" << endl << endl;
        rhs->describe((*ostr), Teuchos::EVerbosityLevel::VERB_EXTREME);
        mat->describe((*ostr), Teuchos::EVerbosityLevel::VERB_EXTREME);
    }
    
    shared_ptr<ParameterList> params = get_shared_ptr(parameterList());
    // params->set ("Num Blocks", 1);
    params->set("Maximum Iterations", 400);
    params->set("Convergence Tolerance", 1.0e-8);
    if (print_)
    {
        params->set("Verbosity", Belos::Debug + Belos::IterationDetails);
        params->set("Verbosity", Belos::Errors + Belos::Warnings + Belos::StatusTestDetails);
        int frequency=1;
        params->set("Output Frequency", frequency);
        params->set("Output Style", Belos::Brief);
    }
    
    shared_ptr<BelosSolverFactory> factory = make_shared<BelosSolverFactory>();
    shared_ptr<BelosSolverManager> solver = get_shared_ptr(factory->create("GMRES", rcp(params)));
    
    solver->setProblem(rcp(problem));
    
    solver->solve();

    if (print_)
    {
        lhs->describe(*ostr, Teuchos::EVerbosityLevel::VERB_EXTREME);
    }
    
    // ArrayRCP<const double> result = problem->getLHS()->getData(0);
}

// Eigenvalue problem with Anasazi and Tpetra
void Test_Trilinos::
test_eigenvalue(int num_eigenvalues)
{
    shared_ptr<Comm> comm = get_comm();
    shared_ptr<Map> map = get_map(comm);
    shared_ptr<MultiVector> vec = make_shared<MultiVector>(rcp(map), num_eigenvalues);
    shared_ptr<CrsMatrix> mat = get_diffusion_matrix(map);
    shared_ptr<CrsMatrix> fis = get_fission_matrix(map);
    shared_ptr<Eigenproblem> problem = get_eigenvalue_problem(mat,
                                                              fis,
                                                              vec,
                                                              num_eigenvalues);
    
    RCP<Teuchos::FancyOStream> ostr = Teuchos::VerboseObjectBase::getDefaultOStream();
    
    if (print_ && false)
    {
        cout << endl << "Test 3: Anasazi and Tpetra" << endl << endl;
        mat->describe((*ostr), Teuchos::EVerbosityLevel::VERB_EXTREME);
        fis->describe((*ostr), Teuchos::EVerbosityLevel::VERB_EXTREME);
    }
    
    shared_ptr<ParameterList> params = get_shared_ptr(parameterList());
    params->set("Maximum Iterations", 400);
    // params->set("Convergence Tolerance", 1.0e-8);
    if (print_)
    {
        // params->set("Verosity", Anasazi::TimingDetails + Anasazi::IterationDetails + Anasazi::Debug + Anasazi::FinalSummary);
        params->set("Verosity", Anasazi::Debug);
        int frequency=1;
        params->set("Output Frequency", frequency);
    }
    
    shared_ptr<AnasaziSolverManager> solver = make_shared<AnasaziSolverManager>(rcp(problem), *params);
    
    if (solver->solve() != Anasazi::ReturnType::Converged)
    {
        cout << "Eigenvalue solve did not converge" << endl;
    }
    
    cout << "Num iters: ";
    cout << solver->getNumIters() << endl;

    if (print_)
    {
        Eigensolution const solution = problem->getSolution();

        cout << "Eigenvalues: ";
        for (int i = 0; i < solution.numVecs; ++i)
        {
            cout << solution.Evals[i].realpart << " ";
        }
        cout << endl;
        solution.Evecs->describe(*ostr, Teuchos::EVerbosityLevel::VERB_EXTREME);
    }
    
}

shared_ptr<Comm> Test_Trilinos::
get_comm()
{
    return make_shared<MpiComm>(MPI_COMM_WORLD);
}

shared_ptr<Map> Test_Trilinos::
get_map(shared_ptr<Comm> comm)
{
    return make_shared<Map>(size_, index_base_, rcp(comm));
}

shared_ptr<CrsMatrix> Test_Trilinos::
get_diffusion_matrix(shared_ptr<Map> map)
{
    shared_ptr<CrsMatrix> mat = make_shared<CrsMatrix>(rcp(map), arcp(rcpFromRef(num_entries_per_row_)), Tpetra::ProfileType::StaticProfile);

    double on_diagonal = 2. / (dx_ * dx_) + sigma_a_;
    double off_diagonal = 1 / (dx_ * dx_);
    
    for (int i = 0; i < size_; ++i)
    {
        vector<int> cols;
        vector<double> vals;
        
        if (i != 0)
        {
            cols.push_back(i - 1);
            vals.push_back(-off_diagonal);
        }
        cols.push_back(i);
        vals.push_back(on_diagonal);
        if (i != size_ - 1)
        {
            cols.push_back(i + 1);
            vals.push_back(-off_diagonal);
        }
        
        mat->insertGlobalValues(i, arrayViewFromVector(cols), arrayViewFromVector(vals));
    }
    mat->fillComplete();

    return mat;
}

shared_ptr<Vector> Test_Trilinos::
get_rhs_steady(shared_ptr<Map> map)
{
    shared_ptr<Vector> rhs = make_shared<Vector>(rcp(map));

    for (int i = 0; i < size_; ++i)
    {
        rhs->replaceGlobalValue(i, q_);
    }

    return rhs;
}
shared_ptr<LinearProblem> Test_Trilinos::
get_steady_problem(shared_ptr<CrsMatrix> mat,
                   shared_ptr<Vector> lhs,
                   shared_ptr<Vector> rhs)
{
    shared_ptr<LinearProblem> problem = make_shared<LinearProblem>(rcp(mat), rcp(lhs), rcp(rhs));
    
    if (!problem->setProblem())
    {
        cout << "Linear problem not set up correctly" << endl;
    }
    
    return problem;
}

shared_ptr<CrsMatrix> Test_Trilinos::
get_fission_matrix(shared_ptr<Map> map)
{
    shared_ptr<CrsMatrix> mat = make_shared<CrsMatrix>(rcp(map), 1, Tpetra::ProfileType::StaticProfile);
    
    double on_diagonal = nu_sigma_f_;
    
    for (int i = 0; i < size_; ++i)
    {
        vector<int> cols = {i};
        vector<double> vals = {on_diagonal};
        
        mat->insertGlobalValues(i, arrayViewFromVector(cols), arrayViewFromVector(vals));
    }
    mat->fillComplete();
    
    return mat;
}

shared_ptr<Eigenproblem> Test_Trilinos::
get_eigenvalue_problem(shared_ptr<CrsMatrix> mat,
                       shared_ptr<CrsMatrix> fis,
                       shared_ptr<MultiVector> vec,
                       int nev)
{
    // shared_ptr<Eigenproblem> problem = make_shared<Eigenproblem>(rcp(mat), rcp(vec));
    shared_ptr<Eigenproblem> problem = make_shared<Eigenproblem>(rcp(fis), rcp(mat), rcp(vec));
    problem->setNEV(nev);
    
    if (!problem->setProblem())
    {
        cout << "Eigenvalue problem not set up correctly" << endl;
    }

    return problem;
}
