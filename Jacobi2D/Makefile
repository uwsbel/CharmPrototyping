CHARMC = $(CHARMDIR)/bin/charmc $(OPTS)


default: all
all: jacobi


##--- Executable ---##

jacobi : main.o jacobi.o
	$(CHARMC) -language charm++ -o jacobi main.o jacobi.o


##--- Main Chare ---##

main.o : main.cpp main.h main.decl.h main.def.h jacobi.decl.h common.h
	$(CHARMC) -o main.o main.cpp

main.h : jacobi.decl.h main.decl.h common.h

main.decl.h main.def.h : main.ci
	$(CHARMC) main.ci


##--- Jacobi Chare ---##

jacobi.o : jacobi.cpp jacobi.h main.h common.h jacobi.def.h 
	$(CHARMC) -o jacobi.o jacobi.cpp

jacobi.h : jacobi.decl.h common.h

jacobi.decl.h jacobi.def.h : jacobi.ci
	$(CHARMC) jacobi.ci


##--- Clean-up ---##

clean:
	rm -f main.decl.h main.def.h main.o
	rm -f jacobi.decl.h jacobi.def.h jacobi.o
	rm -f jacobi charmrun
