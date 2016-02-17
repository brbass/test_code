Here's how I got Trilinos on Flux to work:

[brbass@flux-login2 amesos_test]$ module unload boost
[brbass@flux-login2 amesos_test]$ module unload openmpi
[brbass@flux-login2 amesos_test]$ module unload python
[brbass@flux-login2 amesos_test]$ module load gcc/4.7.2
[brbass@flux-login2 amesos_test]$ module load openmpi/1.6.5/gcc/4.7.2
[brbass@flux-login2 amesos_test]$ module load python/2.7.5
[brbass@flux-login2 amesos_test]$ module load mkl/11.2
[brbass@flux-login2 amesos_test]$ module load boost/1.54.0-gcc
[brbass@flux-login2 amesos_test]$ module load trilinos
[brbass@flux-login2 amesos_test]$ make 
export OMPI_CXX=g++
mpic++ \ 		-std=c++11 -g -o3 \ 		-lepetra -lamesos -laztecoo -lepetraext -ltriutils -lepetra -lteuchosremainder -lteuchosnumerics -lteuchoscomm -lteuchosparameterlist -lteuchoscore \ 		-I/usr/cac/rhel6/trilinos/12.0.1/include \ 		-L/usr/cac/rhel6/trilinos/12.0.1/lib \ 		amesos.cc -o amesos 
