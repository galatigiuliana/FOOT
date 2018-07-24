// EmuTrack_c.cpp - implementation of functions for EmuTrack(s), EmuEvent classes
//last update 18/1/18, AP

#include "/Users/Giuliana/Desktop/PhD/FOOT/Git_FOOT/AnaMicro/EMU_Track_c.h"

ClassImp(EMU_MicroTrack);
ClassImp(EMU_BaseTrack);
ClassImp(EMU_VolumeTrack);
ClassImp(EMU_Event);

/*.........................................................................*/
EMU_MicroTrack::EMU_MicroTrack(){

  fid_track = -1;
  fid_event = -1;
  fid_stack = -1;
  fid_layer = -1;
  fid_part = -1;
  fid_fluka = -1;
  fid_part_parent = -1;
  fid_fluka_parent = -1;
  fgrains = -1;
  fvph = -1;
  fangle = -99.;
  
  for(int i=0;i<3;i++) { fpos[i]= -99.; fp_coord[i]= -99.;}
  for(int j=0; j<2;j++) fslope[j] = -99.;  

  fp = -99.;
  fE = -99.;
  fEkin = -99.;

  };
/*.........................................................................*/
EMU_MicroTrack::~EMU_MicroTrack(){  };
/*.........................................................................*/
void EMU_MicroTrack::Clear(){

  fid_track = -1;
  fid_event = -1;
  fid_stack = -1;
  fid_layer = -1;
  fid_part = -1;
  fid_fluka = -1;
  fid_part_parent = -1;
  fid_fluka_parent = -1;
  fgrains = -1;
  fvph = -1;
  fangle = -99.;
  
  for(int i=0;i<3;i++) { fpos[i]= -99.; fp_coord[i]= -99.;}
  for(int j=0; j<2;j++) fslope[j] = -99.;  

  fp = -99.;
  fE = -99.;
  fEkin = -99.;

  };
/*.........................................................................*/
EMU_BaseTrack::EMU_BaseTrack(){

  fid_track = -1;
  fid_event = -1;
  fid_stack = -1;
  fid_layer = -1;
  fid_part = -1;
  fid_fluka = -1;
  fid_part_parent = -1;
  fid_fluka_parent = -1;
  fgrains = -1;
  fvph = -1;
  fangle = -99.;
  
  for(int i=0;i<3;i++) { fpos[i]= -99.; fp_coord[i]= -99.;}
  for(int j=0; j<2;j++) fslope[j] = -99.;  

  fp = -99.;
  fE = -99.;
  fEkin = -99.;

  vector <EMU_MicroTrack> fmt;

  };
/*.........................................................................*/
void EMU_BaseTrack::Clear(){

  fid_track = -1;
  fid_event = -1;
  fid_stack = -1;
  fid_layer = -1;
  fid_part = -1;
  fid_fluka = -1;
  fid_part_parent = -1;
  fid_fluka_parent = -1;
  fgrains = -1;
  fvph = -1;
  fangle = -99.;
  
  for(int i=0;i<3;i++) { fpos[i]= -99.; fp_coord[i]= -99.;}
  for(int j=0; j<2;j++) fslope[j] = -99.;  

  fp = -99.;
  fE = -99.;
  fEkin = -99.;

  fmt.clear();

  };
/*.........................................................................*/
EMU_BaseTrack::~EMU_BaseTrack(){  };
/*.........................................................................*/
EMU_VolumeTrack::EMU_VolumeTrack(){

  fid_track = -1;
  fid_event = -1;
  fid_stack = -1;
  fid_part = -1;
  fid_fluka = -1;
  fid_part_parent = -1;
  fid_fluka_parent = -1;
  fangle = -99.;
  
  for(int i=0;i<3;i++) { fpos[i]= -99.; fp_coord[i]= -99.;}
  for(int j=0; j<2;j++) fslope[j] = -99.;  

  fp = -99.;
  fE = -99.;
  fEkin = -99.;

  vector <EMU_BaseTrack> fbt;

  };
/*.........................................................................*/
void EMU_VolumeTrack::Clear(){

  fid_track = -1;
  fid_event = -1;
  fid_stack = -1;
  fid_part = -1;
  fid_fluka = -1;
  fid_part_parent = -1;
  fid_fluka_parent = -1;
  fangle = -99.;
  
  for(int i=0;i<3;i++) { fpos[i]= -99.; fp_coord[i]= -99.;}
  for(int j=0; j<2;j++) fslope[j] = -99.;  

  fp = -99.;
  fE = -99.;
  fEkin = -99.;

  fbt.clear();

  };
/*.........................................................................*/
EMU_VolumeTrack::~EMU_VolumeTrack(){  };
/*.........................................................................*/
EMU_Event::EMU_Event(){

  fid_event = -1;
  fid_stack = -1;

  vector <EMU_VolumeTrack> ft;
  vector <EMU_BaseTrack> fbt;
  vector <EMU_MicroTrack> fmt;

  };
/*.........................................................................*/
void EMU_Event::Clear(){

  fid_event = -1;
  fid_stack = -1;

  ft.clear();
  fbt.clear();
  fmt.clear();

  };
/*.........................................................................*/
EMU_Event::~EMU_Event(){  };
/*.........................................................................*/
