all: amesos

amesos: amesos.cc
	g++ \
		-std=c++0x -g -o3 \
		-lepetra -lamesos -laztecoo -lepetraext -ltriutils -lepetra -lteuchosremainder -lteuchosnumerics -lteuchoscomm -lteuchosparameterlist -lteuchoscore \
		-I/usr/cac/rhel6/trilinos/12.0.1/include \
		-L/usr/cac/rhel6/trilinos/12.0.1/lib \
		amesos.cc -o amesos
