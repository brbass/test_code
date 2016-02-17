all: amesos

amesos: amesos.cc
	export OMPI_CXX=g++
	mpic++ \
		-std=c++11 -g -o3 \
		-lepetra -lamesos -laztecoo -lepetraext -ltriutils -lepetra -lteuchosremainder -lteuchosnumerics -lteuchoscomm -lteuchosparameterlist -lteuchoscore \
		-I/usr/cac/rhel6/trilinos/12.0.1/include \
		-L/usr/cac/rhel6/trilinos/12.0.1/lib \
		amesos.cc -o amesos
