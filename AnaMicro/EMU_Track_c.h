// EmuTrack.h - EmuTrack(s), EmuEvent classes
//last update 18/1/18

#ifndef ROOT_EMU_TRACK
#define ROOT_EMU_TRACK

#include <vector>
#include "TObject.h"

using namespace std;

//------------------------------------------
// Emulsion MicroTrack 

class EMU_MicroTrack : public TObject {
    
public:
    EMU_MicroTrack();
    virtual ~EMU_MicroTrack();
    
    void Clear();
    Int_t GetID()           {return fid_track;};
    Int_t GetEvent()        {return fid_event;};
    Int_t GetStack()        {return fid_stack;};
    Int_t GetLayer()        {return fid_layer;};
    Int_t GetIDPart()       {return fid_part;};
    Int_t GetFlukaID()      {return fid_fluka;};
    Int_t GetGrains()       {return fgrains;};
    long long int GetVPH()  {return fvph;};
    Int_t GetParentIDPart() {return fid_part_parent;};
    Int_t GetParentFlukaID(){return fid_fluka_parent;};
    Double_t GetX()         {return fpos[0];};
    Double_t GetY()         {return fpos[1];};
    Double_t GetZ()         {return fpos[2];};
    Double_t GetAngle()     {return fangle;};
    Double_t GetSX()        {return fslope[0];};
    Double_t GetSY()        {return fslope[1];};
    Double_t GetPX()        {return fp_coord[0];};
    Double_t GetPY()        {return fp_coord[1];};
    Double_t GetPZ()        {return fp_coord[2];};
    Double_t GetP()         {return fp;};
    Double_t GetE()         {return fE;};
    Double_t GetEkin()      {return fEkin;};
    
    void SetID(Int_t n)     {fid_track = n;};
    void SetEvent(Int_t n)  {fid_event = n;};
    void SetStack(Int_t n)  {fid_stack = n;};
    void SetLayer(Int_t n)  {fid_layer = n;};
    void SetIDpart(Int_t n) {fid_part = n;};
    void SetFlukaID(Int_t n){fid_fluka = n;};
    void SetParentIDPart(Int_t n)  {fid_part_parent = n;};
    void SetParentFlukaID(Int_t n) {fid_fluka_parent = n;};
    void SetGrains(Int_t n) {fgrains = n;};
    void SetVPH(long long int n) {fvph = n;};
    void SetXYZ(Double_t x,Double_t y,Double_t z) {fpos[0] = x; fpos[1] = y; fpos[2] = z;};
    void SetAngle(Double_t a) {fangle = a;};
    void SetSlopes(Double_t sx, Double_t sy) {fslope[0] = sx; fslope[1] = sy;};
    void SetPXYZ(Double_t px,Double_t py,Double_t pz) {fp_coord[0] = px; fp_coord[1] = py; fp_coord[2] = pz;};
    void SetP(Double_t p) {fp = p;};
    void SetE(Double_t E) {fE = E;};
    void SetEkin(Double_t E) {fEkin = E;};
    
private:
    
    Int_t fid_track;
    Int_t fid_event;
    Int_t fid_stack;
    Int_t fid_layer;
    Int_t fid_part;
    Int_t fid_fluka;
    Int_t fid_part_parent;
    Int_t fid_fluka_parent;
    Int_t fgrains;
    
    long long int fvph;
    
    Double_t fpos[3];
    Double_t fangle;
    Double_t fslope[2];
    Double_t fp_coord[3];
    Double_t fp;
    Double_t fE;
    Double_t fEkin;
    
protected:
    ClassDef(EMU_MicroTrack,1);
    
};
//------------------------------------------
// Emulsion BaseTrack 

class EMU_BaseTrack : public TObject {
    
public:
    EMU_BaseTrack();
    virtual ~EMU_BaseTrack();
    
    void Clear();
    Int_t GetID()           {return fid_track;};
    Int_t GetEvent()        {return fid_event;};
    Int_t GetStack()        {return fid_stack;};
    Int_t GetLayer()        {return fid_layer;};
    Int_t GetGrains()       {return fgrains;};
    long long int GetVPH()  {return fvph;};
    Int_t GetIDPart()       {return fid_part;};
    Int_t GetFlukaID()      {return fid_fluka;};
    Int_t GetParentIDPart() {return fid_part_parent;};
    Int_t GetParentFlukaID(){return fid_fluka_parent;};
    Double_t GetX()         {return fpos[0];};
    Double_t GetY()         {return fpos[1];};
    Double_t GetZ()         {return fpos[2];};
    Double_t GetAngle()     {return fangle;};
    Double_t GetSX()        {return fslope[0];};
    Double_t GetSY()        {return fslope[1];};
    Double_t GetPX()        {return fp_coord[0];};
    Double_t GetPY()        {return fp_coord[1];};
    Double_t GetPZ()        {return fp_coord[2];};
    Double_t GetP()         {return fp;};
    Double_t GetE()         {return fE;};
    Double_t GetEkin()      {return fEkin;};
    
    void SetID(Int_t n)     {fid_track = n;};
    void SetEvent(Int_t n)  {fid_event = n;};
    void SetStack(Int_t n)  {fid_stack = n;};
    void SetLayer(Int_t n)  {fid_layer = n;};
    void SetGrains(Int_t n) {fgrains = n;};
    void SetVPH(long long int n) {fvph = n;};
    void SetIDpart(Int_t n) {fid_part = n;};
    void SetFlukaID(Int_t n){fid_fluka = n;};
    void SetParentIDPart(Int_t n)  {fid_part_parent = n;};
    void SetParentFlukaID(Int_t n) {fid_fluka_parent = n;};
    void SetXYZ(Double_t x,Double_t y,Double_t z) {fpos[0] = x; fpos[1] = y; fpos[2] = z;};
    void SetSlopes(Double_t sx, Double_t sy) {fslope[0] = sx; fslope[1] = sy;};
    void SetAngle(Double_t a) {fangle = a;};
    void SetPXYZ(Double_t px,Double_t py,Double_t pz) {fp_coord[0] = px; fp_coord[1] = py; fp_coord[2] = pz;};
    void SetP(Double_t p) {fp = p;};
    void SetE(Double_t E) {fE = E;};
    void SetEkin(Double_t E) {fEkin = E;};
    
    void SetMicro(EMU_MicroTrack m)  {fmt.push_back(m);};
    vector<EMU_MicroTrack> GetMicroTracks() { return fmt;};
    EMU_MicroTrack GetMicroTrack(Int_t n)  { return fmt.at(n);};
    
private:
    Int_t fid_track;
    Int_t fid_event;
    Int_t fid_stack;
    Int_t fid_layer;
    Int_t fid_part;
    Int_t fid_fluka;
    Int_t fid_part_parent;
    Int_t fid_fluka_parent;
    Int_t fgrains;
    
    long long int fvph;
    
    Double_t fpos[3];
    Double_t fslope[2];
    Double_t fangle;
    Double_t fp_coord[3];
    Double_t fp;
    Double_t fE;
    Double_t fEkin;
    
    vector<EMU_MicroTrack> fmt;
    
protected:
    ClassDef(EMU_BaseTrack,1);
    
};
//------------------------------------------
// Emulsion VolumeTrack 

class EMU_VolumeTrack : public TObject {
    
public:
    EMU_VolumeTrack();
    virtual ~EMU_VolumeTrack();
    void Clear();
    Int_t GetEvent()        {return fid_event;};
    Int_t GetID()           {return fid_track;};
    Int_t GetIDPart()       {return fid_part;};
    Int_t GetParentIDPart() {return fid_part_parent;};
    Int_t GetStack()        {return fid_stack;};
    Double_t GetAngle()     {return fangle;};
    Int_t GetFlukaID()      {return fid_fluka;};
    Int_t GetParentFlukaID()      {return fid_fluka_parent;};
    Double_t GetX()         {return fpos[0];};
    Double_t GetY()         {return fpos[1];};
    Double_t GetZ()         {return fpos[2];};
    //Double_t GetLength()     {return flength;};
    //Double_t GetLinearRange()     {return flinearrange;};
    Double_t GetSX()        {return fslope[0];};
    Double_t GetSY()        {return fslope[1];};
    Double_t GetPX()         {return fp_coord[0];};
    Double_t GetPY()         {return fp_coord[1];};
    Double_t GetPZ()         {return fp_coord[2];};
    Double_t GetP()         {return fp;};
    Double_t GetE()         {return fE;};
    Double_t GetEkin()         {return fEkin;};
    
    vector<EMU_BaseTrack> GetBaseTracks(){return fbt;};
    EMU_BaseTrack GetBaseTrack(Int_t n)  {return fbt.at(n);};
    
    void SetID(Int_t n)     {fid_track = n;};
    void SetEvent(Int_t n)  {fid_event = n;};
    void SetStack(Int_t n)  {fid_stack = n;};
    void SetIDPart(Int_t n) {fid_part = n;};
    void SetFlukaID(Int_t n){fid_fluka = n;};
    void SetParentIDPart(Int_t n)  {fid_part_parent = n;};
    void SetParentFlukaID(Int_t n) {fid_fluka_parent = n;};
    void SetXYZ(Double_t x,Double_t y,Double_t z) {fpos[0] = x; fpos[1] = y; fpos[2] = z;};
    //void SetLength(Double_t a) {flength = a;};
    //void SetLinearRange(Double_t a) {flinearrange = a;};
    void SetSlopes(Double_t sx, Double_t sy) {fslope[0] = sx; fslope[1] = sy;};
    void SetAngle(Double_t a) {fangle = a;};
    void SetPXYZ(Double_t px,Double_t py,Double_t pz) {fp_coord[0] = px; fp_coord[1] = py; fp_coord[2] = pz;};
    void SetP(Double_t p) {fp = p;};
    void SetE(Double_t E) {fE = E;};
    void SetEkin(Double_t E) {fEkin = E;};
    
    void SetBaseTrack(EMU_BaseTrack b)   {fbt.push_back(b);};
    
private:
    Int_t fid_track;
    Int_t fid_event;
    Int_t fid_stack;
    Int_t fid_part;
    Int_t fid_fluka;
    Int_t fid_part_parent;
    Int_t fid_fluka_parent;
    
    Double_t fpos[3];
    Double_t fslope[2];
    Double_t fangle;
    //Double_t flength;
    Double_t fp_coord[3];
    Double_t fp;
    Double_t fE;
    Double_t fEkin;
    
    vector<EMU_BaseTrack> fbt;
    
protected:
    ClassDef(EMU_VolumeTrack,1);
    
};
//------------------------------------------
// Emulsion Event

class EMU_Event : public TObject {
    
public:
    EMU_Event();
    virtual ~EMU_Event();
    
    void Clear();
    Int_t GetID()           {return fid_event;};
    vector<EMU_MicroTrack> GetMicroTracks(){return fmt;};
    vector<EMU_BaseTrack> GetBaseTracks()  {return fbt;};
    vector<EMU_VolumeTrack> GetVolumeTracks(){return ft;};
    EMU_MicroTrack GetMicroTrack(Int_t n)  {return fmt.at(n);};
    EMU_BaseTrack GetBaseTrack(Int_t n)    {return fbt.at(n);};
    EMU_VolumeTrack GetVolumeTrack(Int_t n){return ft.at(n);};
    void SetID(Int_t n)     {fid_event = n;};
    void SetMicroTrack(EMU_MicroTrack t)  {fmt.push_back(t);};
    void SetBaseTrack(EMU_BaseTrack t)  {fbt.push_back(t);};
    void SetTrack(EMU_VolumeTrack t)  {ft.push_back(t);};
    
private:
    Int_t fid_event;
    
    vector<EMU_VolumeTrack> ft;
    vector<EMU_BaseTrack> fbt;
    vector<EMU_MicroTrack> fmt;
    
protected:
    ClassDef(EMU_Event,1);
    
};

#endif
