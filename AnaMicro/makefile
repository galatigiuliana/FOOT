# Makefile for the Micro_Ana program.
# last update 8/11/17, A.P.

CXX           =
ObjSuf        = o
SrcSuf        = cpp
ExeSuf        =
DllSuf        = so
OutPutOpt     = -o 

ROOTSYS      := $(shell root-config --prefix)
ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs)
ROOTGLIBS    := $(shell root-config --glibs)

# Linux with egcs, gcc 2.9x, gcc 3.x (>= RedHat 5.2)
CXX           = g++
CXXFLAGS      = -g -Wall -fPIC
CXXFLAGS     += $(ROOTCFLAGS) -I.
LD            = g++
LDFLAGS       = $(ROOTLIBS) $(ROOTGLIBS) -lm

LIBS          = $(ROOTLIBS) $(SYSLIBS)
GLIBS         = $(ROOTGLIBS) $(SYSLIBS)
MYLIBS        = $(ROOTLIBS) $(ROOTGLIBS) $(SYSLIBS)


#------------------------------------------------------------------------------
SRC   = EMU_Track_c.cpp Micro_AnaDict.cpp Micro_Ana.cpp
OBJ   = EMU_Track_c.o Micro_AnaDict.o
HEAD  = EMU_Track_c.h 
#------------------------------------------------------------------------------

all: Micro_Ana

Micro_Ana:  Micro_Ana.o $(OBJ) #$(HEAD) Micro_Ana.h
	$(LD) $(LDFLAGS) Micro_Ana.o $(OBJ) $(MYLIBS) -o Micro_Ana

Micro_AnaDict.cpp:  $(HEAD) Micro_AnaLinkDef.h
		@echo "Generating dictionary $@..." 
		@$(ROOTSYS)/bin/rootcint -f Micro_AnaDict.cpp -c -p $(HEAD) Micro_AnaLinkDef.h


clean:
	@rm -f *.o *Dict* Micro_Ana


