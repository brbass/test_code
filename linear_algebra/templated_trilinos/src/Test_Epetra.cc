#include "Test_Epetra.hh"

Test_Epetra::
Test_Epetra(int size,
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

void Test_Epetra::
test_eigenvalue(int num_eigenvalues)
{
    int block_size = 1;
    int num_blocks = ceil(size_ / 4);
    num_blocks = num_blocks < 3 ? 3 : num_blocks;
    string which = "LM";
    
    shared_ptr<Epetra_Comm> comm = get_comm();
    shared_ptr<Epetra_Map> map = get_map(comm);
    shared_ptr<Epetra_MultiVector> vec = make_shared<Epetra_MultiVector>(*map, block_size);
    shared_ptr<Epetra_CrsMatrix> mat = get_diffusion_matrix(map);
    shared_ptr<Epetra_CrsMatrix> fis = get_fission_matrix(map);
    shared_ptr<Anasazi_Eigenproblem> problem = get_eigenvalue_problem(mat,
                                                                      fis,
                                                                      vec,
                                                                      num_eigenvalues);
    
    RCP<Teuchos::FancyOStream> ostr = Teuchos::VerboseObjectBase::getDefaultOStream();
    
    if (print_ && false)
    {
        cout << endl << "Test 3: Anasazi and Tpetra" << endl << endl;
        // mat->describe((*ostr), Teuchos::EVerbosityLevel::VERB_EXTREME);
        // fis->describe((*ostr), Teuchos::EVerbosityLevel::VERB_EXTREME);
    }
    
    shared_ptr<ParameterList> params = get_shared_ptr(parameterList());
    params->set("Maximum Iterations", 400);
    params->set("Block Size", block_size);
    params->set("Num Blocks", num_blocks);
    params->set("Convergence Tolerance", 1.0e-6);
    params->set("Dynamic Extra NEV", false);
    params->set("Which", which);
    if (print_)
    {
        params->set("Verbosity", Anasazi::IterationDetails + Anasazi::TimingDetails + Anasazi::FinalSummary);
        int frequency=1;
        params->set("Output Frequency", frequency);
    }
    
    shared_ptr<Anasazi_SolverManager> solver = make_shared<Anasazi_SolverManager>(rcp(problem), *params);
    
    if (solver->solve() != Anasazi::ReturnType::Converged)
    {
        cout << "Eigenvalue solve did not converge" << endl;
    }
    
    cout << "Num iters: ";
    cout << solver->getNumIters() << endl;
    
    if (print_)
    {
        Anasazi_Eigensolution const solution = problem->getSolution();
        
        cout << "Eigenvalues: ";
        for (int i = 0; i < solution.numVecs; ++i)
        {
            cout << solution.Evals[i].realpart << " ";
        }
        cout << endl;
        // cout << *solution.Evecs << endl;
    }
}

shared_ptr<Epetra_Comm> Test_Epetra::
get_comm()
{
    return make_shared<Epetra_MpiComm>(MPI_COMM_WORLD);
}

shared_ptr<Epetra_Map> Test_Epetra::
get_map(shared_ptr<Epetra_Comm> comm)
{
    return make_shared<Epetra_Map>(size_, index_base_, *comm);
}

shared_ptr<Epetra_CrsMatrix> Test_Epetra::
get_diffusion_matrix(shared_ptr<Epetra_Map> map)
{
    shared_ptr<Epetra_CrsMatrix> mat = make_shared<Epetra_CrsMatrix>(Copy, *map, &num_entries_per_row_[0], true);

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
        
        mat->InsertGlobalValues(i, num_entries_per_row_[i], &vals[0], &cols[0]);
    }
    mat->FillComplete();

    return mat;
}

shared_ptr<Epetra_CrsMatrix> Test_Epetra::
get_fission_matrix(shared_ptr<Epetra_Map> map)
{
    shared_ptr<Epetra_CrsMatrix> mat = make_shared<Epetra_CrsMatrix>(Copy, *map, 1, true);
    
    double on_diagonal = nu_sigma_f_;
    
    for (int i = 0; i < size_; ++i)
    {
        vector<int> cols = {i};
        vector<double> vals = {on_diagonal};
        
        mat->InsertGlobalValues(i, 1, &vals[0], &cols[0]);
    }
    mat->FillComplete();
    
    return mat;
}

shared_ptr<Anasazi_Eigenproblem> Test_Epetra::
get_eigenvalue_problem(shared_ptr<Epetra_CrsMatrix> mat,
                       shared_ptr<Epetra_CrsMatrix> fis,
                       shared_ptr<Epetra_MultiVector> vec,
                       int nev)
{
    shared_ptr<Anasazi_Eigenproblem> problem = make_shared<Anasazi_Eigenproblem>(rcp(mat), rcp(vec));
    // shared_ptr<Anasazi_Eigenproblem> problem = make_shared<Anasazi_Eigenproblem>(rcp(mat), rcp(fis), rcp(vec));
    problem->setNEV(nev);
    
    
    if (!problem->setProblem())
    {
        cout << "Eigenvalue problem not set up correctly" << endl;
    }

    return problem;
}

