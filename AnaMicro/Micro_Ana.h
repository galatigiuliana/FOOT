// Micro_Ana.h - main program header
#ifndef Micro_Ana_H
#define Micro_Ana_H

#ifdef __MAKECINT__
#pragma link C++ class std::vector<int>+;
#pragma link C++ class std::vector<float>+;
#pragma link C++ class std::vector < std::vector<float> >+;
#pragma link C++ class std::vector < std::vector<int> >+;
#endif

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <vector>
#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <TDirectory.h>
#include <TString.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TProfile.h>
#include "TH1.h"
#include "TF1.h"
#include "TH2.h"
#include <TStyle.h>
#include <TMath.h>
#include <TLatex.h>
#include <TLegend.h>
#include "TPaveStats.h"
#include "TGraphErrors.h"
#include "TLine.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

#include "EMU_Track_c.h"

using namespace std;

#define RAD2DEG  57.2958


//global variables
const char* filein;
//vector<EMU_MicroTrack> Micros;
vector<EMU_Event> Events;
TFile *fileout;
TTree *EventTree;


//functions
void SetStyle();

void ECC_DefineBaseTrack();
void ECC_DefineVolumeTrack();
Int_t ECC_ReadMicro(const char* filein, TFile *fileout);
void ECC_WriteData();

#endif
