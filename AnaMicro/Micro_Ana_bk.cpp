#define RAD2DEG  57.2958
#define VERBOSE 0
#define VERBOSE_PLOT 0

#include "Micro_Ana.h"

using namespace std;

//USAGE: make
//       ./Micro_Ana -in input.root

Int_t main(Int_t argc, char *argv[]){//last update 06/03/18
    
    //define input file
    for (Int_t i = 0; i < argc; i++){
        if(strcmp(argv[i],"-in") == 0) filein = argv[++i];   }//for i
    
    //define output
    fileout = new TFile("EMU_out.root","RECREATE");
    
    EventTree=new TTree("EventTree","EventTree");
    VolumeTree=new TTree("VolumeTree","VolumeTree");
    BaseTree=new TTree("BaseTree","BaseTree");
    MicroTree=new TTree("MicroTree","MicroTree");
    
    //load input file microtracks
    if(ECC_ReadMicro(filein, fileout)<=0) { cout <<"No events in the input file, please check!"<<endl<<"Exiting from ReadMicro ..."<<endl; fileout->Close(); return -1;}
    
    //define event tracks
    ECC_DefineBaseTrack();
    ECC_DefineVolumeTrack();
    
    ECC_WriteData();
    
    fileout->Write();
    fileout->Close();
    
    
    //draw plots
    //ECC_Draw_Data(fileout);
    
    return 0;
}

//-----------------------------------------------------------------------
Int_t ECC_ReadMicro(const char* filein, TFile *fileout){//last update 4/5/18, A.P.
    long long int nmicro = -1;
    if(!filein) { cout << "Input file not exists! Exiting ECC_ReadMicro .."<< endl; return nmicro;}
    
    TFile *fin = new TFile(filein);
    TTree *MicroTrackTree = (TTree*)fin->Get("MicroTrackTree");
    
    Int_t id_micro = -1, id_event = -1, id_stack = -1, id_layer = -1, grains = -1, id_particle = -1, id_parent = -1, id_fluka = -1, id_fluka_parent = -1;
    unsigned long long int VPH = -1;
    Double_t x_micro = .0, y_micro = .0, z_micro = .0, sx_micro = -99., sy_micro = -99., px_micro = -99., py_micro = -99., pz_micro = -99., p_micro = -99., E_micro = -99., Ekin_micro = -99.;
    
    MicroTrackTree->SetBranchAddress("id_micro",&id_micro);
    MicroTrackTree->SetBranchAddress("id_event",&id_event);
    MicroTrackTree->SetBranchAddress("id_stack",&id_stack);
    MicroTrackTree->SetBranchAddress("id_layer",&id_layer);
    MicroTrackTree->SetBranchAddress("id_particle",&id_particle);
    MicroTrackTree->SetBranchAddress("id_parentparticle",&id_parent);
    MicroTrackTree->SetBranchAddress("flukaid_micro",&id_fluka);
    MicroTrackTree->SetBranchAddress("flukaid_parent",&id_fluka_parent);
    MicroTrackTree->SetBranchAddress("grains_micro",&grains);
    MicroTrackTree->SetBranchAddress("x_micro",&x_micro);
    MicroTrackTree->SetBranchAddress("y_micro",&y_micro);
    MicroTrackTree->SetBranchAddress("z_micro",&z_micro);
    MicroTrackTree->SetBranchAddress("sx_micro",&sx_micro);
    MicroTrackTree->SetBranchAddress("sy_micro",&sy_micro);
    MicroTrackTree->SetBranchAddress("px_micro",&px_micro);
    MicroTrackTree->SetBranchAddress("py_micro",&py_micro);
    MicroTrackTree->SetBranchAddress("pz_micro",&pz_micro);
    MicroTrackTree->SetBranchAddress("p_micro",&p_micro);
    MicroTrackTree->SetBranchAddress("E_micro",&E_micro);
    MicroTrackTree->SetBranchAddress("Ekin_micro",&Ekin_micro);
    
    
    nmicro = MicroTrackTree->GetEntries();
    if(nmicro) printf("Nr MicroTracks %lld\n",nmicro);
    else return -1;
    
    EMU_Event evt;
    EMU_MicroTrack mt;
    long long int evt_id = -1;
    int nev=0;
    //read data and define events
    for(int i = 0; i<nmicro; i++){
        mt.Clear();
        MicroTrackTree->GetEntry(i);
        
        if(evt_id!=id_event){
            if(i) {
                Events.push_back(evt);
                evt.Clear();
                nev++;
            }
            
            evt.SetID(id_event);
        }//if
        
        if(id_fluka!=3&&id_fluka!=4){//skip e
            
            Double_t angle = acos(pz_micro/p_micro);
            angle *= RAD2DEG;
            
            mt.SetID(id_micro);
            mt.SetEvent(id_event);
            mt.SetStack(id_stack);
            mt.SetLayer(id_layer);
            mt.SetGrains(grains);
            mt.SetVPH(VPH);
            mt.SetIDpart(id_particle);
            mt.SetFlukaID(id_fluka);
            mt.SetParentIDPart(id_parent);
            mt.SetParentFlukaID(id_fluka_parent);
            mt.SetXYZ(x_micro,y_micro,z_micro);
            mt.SetAngle(angle);
            mt.SetSlopes(sx_micro,sy_micro);
            mt.SetPXYZ(px_micro,py_micro,pz_micro);
            mt.SetP(p_micro);
            mt.SetE(E_micro);
            mt.SetEkin(Ekin_micro);
            
            //Fill plots
            /*fileout->cd("ECC_MicroTracks");
             ((TH2D*)gDirectory->Get("hmicro_xy"))->Fill(x_micro,y_micro);
             fileout->cd("..");*/
            //end Fill
            
            evt.SetMicroTrack(mt);
        }
        //cout << id_event << "\t" << id_micro << " x: " << mt.GetX() << endl;
        evt_id = id_event;
        
    }//for i
    
    Events.push_back(evt);
    evt.Clear();
    nev++;
    
    printf("Nr saved Events %lu\n", Events.size());
    
    fin->Close();
    cout << " num events: " << nev << endl;
    
    return Events.size();
}
//-----------------------------------------------------------------------
void ECC_DefineBaseTrack(){//last update 18/1/18,AP
    
    if(!Events.size()) { cout << "None event to be processed!" << endl << "Exiting from ECC_DefineBaseTrack..."<<endl; return;}
    
    EMU_BaseTrack bt;
    Int_t idpart = -99, layer = -1, ngr = -1, countbase = 0;
    long long int nvph = -1;
    Double_t x, y, z, px, py, pz, p, E, Ekin;
    Double_t base_angle = .0;
    Int_t id_micro =0, id_event=0;
    
    
    //fileout->cd("ECC_BaseTracks");
    for(unsigned int i = 0; i<Events.size(); i++){
        countbase = 0;
        for(unsigned int im = 0; im<((Events.at(i)).GetMicroTracks()).size();im++){
            if(im&&layer==((Events.at(i)).GetMicroTrack(im)).GetLayer()&&idpart==((Events.at(i)).GetMicroTrack(im)).GetIDPart()){
                countbase++;
                bt.SetID(countbase);
                bt.SetEvent((Events.at(i)).GetID());
                bt.SetStack(((Events.at(i)).GetMicroTrack(im)).GetStack());
                bt.SetLayer(layer);
                bt.SetIDpart(idpart);
                bt.SetFlukaID(((Events.at(i)).GetMicroTrack(im)).GetFlukaID());
                bt.SetParentIDPart(((Events.at(i)).GetMicroTrack(im)).GetParentIDPart());
                bt.SetParentFlukaID(((Events.at(i)).GetMicroTrack(im)).GetParentFlukaID());
                bt.SetGrains(ngr+((Events.at(i)).GetMicroTrack(im)).GetGrains());
                bt.SetVPH(nvph+((Events.at(i)).GetMicroTrack(im)).GetVPH());
                bt.SetXYZ((x+((Events.at(i)).GetMicroTrack(im)).GetX())/2.,(y+((Events.at(i)).GetMicroTrack(im)).GetY())/2.,(z+((Events.at(i)).GetMicroTrack(im)).GetZ())/2.);
                if(z>((Events.at(i)).GetMicroTrack(im)).GetZ()){
                    bt.SetSlopes((x-((Events.at(i)).GetMicroTrack(im)).GetX())/(z-((Events.at(i)).GetMicroTrack(im)).GetZ()),(y-((Events.at(i)).GetMicroTrack(im)).GetY())/(z-((Events.at(i)).GetMicroTrack(im)).GetZ()));
                    bt.SetPXYZ(px,py,pz);
                    bt.SetP(p);
                    bt.SetE(E); bt.SetEkin(Ekin);    } else
                    { bt.SetSlopes((-x+((Events.at(i)).GetMicroTrack(im)).GetX())/(-z+((Events.at(i)).GetMicroTrack(im)).GetZ()),(-y+((Events.at(i)).GetMicroTrack(im)).GetY())/(-z+((Events.at(i)).GetMicroTrack(im)).GetZ()));
                        px = ((Events.at(i)).GetMicroTrack(im)).GetPX();
                        py = ((Events.at(i)).GetMicroTrack(im)).GetPY();
                        pz = ((Events.at(i)).GetMicroTrack(im)).GetPZ();
                        p = ((Events.at(i)).GetMicroTrack(im)).GetP();
                        E = ((Events.at(i)).GetMicroTrack(im)).GetE();
                        Ekin = ((Events.at(i)).GetMicroTrack(im)).GetEkin();
                        bt.SetPXYZ(px,py,px);
                        bt.SetP(p);
                        bt.SetE(E); bt.SetEkin(Ekin);
                    }
                base_angle = acos((-z+((Events.at(i)).GetMicroTrack(im)).GetZ())/sqrt(pow(-z+((Events.at(i)).GetMicroTrack(im)).GetZ(),2)+pow(-x+((Events.at(i)).GetMicroTrack(im)).GetX(),2)+pow(-y+((Events.at(i)).GetMicroTrack(im)).GetY(),2)));
                base_angle *= RAD2DEG;
                bt.SetAngle(base_angle);
                bt.SetMicro((Events.at(i)).GetMicroTrack(im-1));
                bt.SetMicro((Events.at(i)).GetMicroTrack(im));
                
                //Fill plots
                //((TH1D*)gDirectory->Get("hbase_angle"))->Fill(bt.GetAngle());
                //end Fill
                
                (Events.at(i)).SetBaseTrack(bt); bt.Clear();
            }//if
            
            id_event = (Events.at(i)).GetID();
            id_micro = ((Events.at(i)).GetMicroTrack(im)).GetID();
            layer = ((Events.at(i)).GetMicroTrack(im)).GetLayer();
            idpart = ((Events.at(i)).GetMicroTrack(im)).GetIDPart();
            ngr = ((Events.at(i)).GetMicroTrack(im)).GetGrains();
            nvph = ((Events.at(i)).GetMicroTrack(im)).GetVPH();
            x = ((Events.at(i)).GetMicroTrack(im)).GetX();
            y = ((Events.at(i)).GetMicroTrack(im)).GetY();
            z = ((Events.at(i)).GetMicroTrack(im)).GetZ();
            px = ((Events.at(i)).GetMicroTrack(im)).GetPX();
            py = ((Events.at(i)).GetMicroTrack(im)).GetPY();
            pz = ((Events.at(i)).GetMicroTrack(im)).GetPZ();
            p = ((Events.at(i)).GetMicroTrack(im)).GetP();
            E = ((Events.at(i)).GetMicroTrack(im)).GetE();
            Ekin = ((Events.at(i)).GetMicroTrack(im)).GetEkin();
            
        }//for im
        
        // cout <<"Event "<<(Events.at(i)).GetID()<<" nr of basetracks = "<<((Events.at(i)).GetBaseTracks()).size()<<endl;
        
    }//for i
    //fileout->cd("..");
    return ;
}
//-----------------------------------------------------------------------
void ECC_DefineVolumeTrack(){//last update 4/5/18, AP
    
    if(!Events.size()) { cout << "None event to be processed!" << endl << "Exiting from ECC_DefineVolumeTrack..."<<endl; return;}
    
    EMU_VolumeTrack vt;
    Int_t id_part = -99, id_layer=-99, id_parent=-99, id_fluka_part=-99, counttrack = 0;
    
    //cout << "Events.size() " << Events.size() << endl;
    for(unsigned int i = 0; i<Events.size(); i++){
        
        counttrack=0;
        
        for(unsigned int ib = 0; ib<((Events.at(i)).GetBaseTracks()).size();ib++){
            
            // if(((Events.at(i)).GetBaseTrack(ib)).GetFlukaID()!=3){
            
            if(ib==0) {
                vt.Clear();
                counttrack++; vt.SetID(counttrack);
                vt.SetEvent((Events.at(i)).GetID());
                vt.SetStack((Events.at(i)).GetBaseTrack(ib).GetStack());
                vt.SetIDPart(((Events.at(i)).GetBaseTrack(ib)).GetIDPart());
                vt.SetFlukaID(((Events.at(i)).GetBaseTrack(ib)).GetFlukaID());
                vt.SetParentIDPart(((Events.at(i)).GetBaseTrack(ib)).GetParentIDPart());
                vt.SetParentFlukaID(((Events.at(i)).GetBaseTrack(ib)).GetParentFlukaID());
                vt.SetBaseTrack((Events.at(i)).GetBaseTrack(ib));
                vt.SetXYZ(((Events.at(i)).GetBaseTrack(ib)).GetX(),((Events.at(i)).GetBaseTrack(ib)).GetY(),((Events.at(i)).GetBaseTrack(ib)).GetZ());
                vt.SetPXYZ(((Events.at(i)).GetBaseTrack(ib)).GetPX(),((Events.at(i)).GetBaseTrack(ib)).GetPY(),((Events.at(i)).GetBaseTrack(ib)).GetPZ());
                vt.SetSlopes(((Events.at(i)).GetBaseTrack(ib)).GetSX(),((Events.at(i)).GetBaseTrack(ib)).GetSY());
                vt.SetAngle(((Events.at(i)).GetBaseTrack(ib)).GetAngle());
                vt.SetP(((Events.at(i)).GetBaseTrack(ib)).GetP());
                vt.SetE(((Events.at(i)).GetBaseTrack(ib)).GetE());
                vt.SetEkin(((Events.at(i)).GetBaseTrack(ib)).GetEkin());
            }//if
            else if(ib&&id_fluka_part==((Events.at(i)).GetBaseTrack(ib)).GetFlukaID()&&id_parent==((Events.at(i)).GetBaseTrack(ib)).GetParentIDPart()&&((Events.at(i)).GetBaseTrack(ib)).GetLayer()>id_layer){
                
                vt.SetBaseTrack((Events.at(i)).GetBaseTrack(ib));
                
                if(ib==((Events.at(i)).GetBaseTracks()).size()-1){
                    (Events.at(i)).SetTrack(vt);
                    vt.Clear();
                }
            }
            else if(ib&&((id_fluka_part!=((Events.at(i)).GetBaseTrack(ib)).GetFlukaID()) ||(id_fluka_part==((Events.at(i)).GetBaseTrack(ib)).GetFlukaID()&&((Events.at(i)).GetBaseTrack(ib)).GetLayer()<=id_layer&&id_parent==((Events.at(i)).GetBaseTrack(ib)).GetParentIDPart() ))){
                (Events.at(i)).SetTrack(vt);
                vt.Clear();
                
                counttrack++; vt.SetID(counttrack);
                vt.SetEvent((Events.at(i)).GetID());
                vt.SetStack((Events.at(i)).GetBaseTrack(ib).GetStack());
                vt.SetIDPart(((Events.at(i)).GetBaseTrack(ib)).GetIDPart());
                vt.SetFlukaID(((Events.at(i)).GetBaseTrack(ib)).GetFlukaID());
                vt.SetParentIDPart(((Events.at(i)).GetBaseTrack(ib)).GetParentIDPart());
                vt.SetParentFlukaID(((Events.at(i)).GetBaseTrack(ib)).GetParentFlukaID());
                vt.SetXYZ(((Events.at(i)).GetBaseTrack(ib)).GetX(),((Events.at(i)).GetBaseTrack(ib)).GetY(),((Events.at(i)).GetBaseTrack(ib)).GetZ());
                vt.SetPXYZ(((Events.at(i)).GetBaseTrack(ib)).GetPX(),((Events.at(i)).GetBaseTrack(ib)).GetPY(),((Events.at(i)).GetBaseTrack(ib)).GetPZ());
                vt.SetSlopes(((Events.at(i)).GetBaseTrack(ib)).GetSX(),((Events.at(i)).GetBaseTrack(ib)).GetSY());
                vt.SetAngle(((Events.at(i)).GetBaseTrack(ib)).GetAngle());
                vt.SetP(((Events.at(i)).GetBaseTrack(ib)).GetP());
                vt.SetE(((Events.at(i)).GetBaseTrack(ib)).GetE());
                vt.SetEkin(((Events.at(i)).GetBaseTrack(ib)).GetEkin());
                
                vt.SetBaseTrack((Events.at(i)).GetBaseTrack(ib));
            }
            
            id_part = ((Events.at(i)).GetBaseTrack(ib)).GetIDPart();
            id_fluka_part = ((Events.at(i)).GetBaseTrack(ib)).GetFlukaID();
            id_parent = ((Events.at(i)).GetBaseTrack(ib)).GetParentIDPart();
            id_layer = ((Events.at(i)).GetBaseTrack(ib)).GetLayer();
            
            // } // chiudo if sugli elettroni e positroni
            
        }//for ib
        
        //        unsigned int nt = ((Events.at(i)).GetVolumeTracks()).size();
        //        cout <<"Event "<<(Events.at(i)).GetID()<<" nr of volumetracks = "<<nt<<endl;
        
        //        EMU_VolumeTrack vt1;
        //
        //        for(unsigned int j = 0; j<nt; j++){
        //            vt1.Clear();
        //            vt1=(Events.at(i)).GetVolumeTrack(j);
        //
        //            cout <<  vt1.GetID() << "\t" << (vt1.GetBaseTracks()).size() << endl;
        //            //            Fill volume tracks plot
        //            //             fileout->cd("ECC_VolumeTracks");
        //            //            ...
        //            //            fileout->cd("..");
        //            //            end fill
        //
        //        }//for j
        //}
        
    }//for i
    
    return ;
}
//-----------------------------------------------------------------------


//-----------------------------------------------------------------------
void ECC_WriteData(){ // 8/03/18 Gg
    
    if(!Events.size()) { cout << "None event to be processed!" << endl << "Exiting from ECC_DefineVolumeTrack..."<<endl; return;}
    
    EMU_Event evt;
    EMU_VolumeTrack vt;
    EMU_BaseTrack bt;
    EMU_MicroTrack mt;
    
    //EVENTO
    int id_event=0;
    int ev_nmicro=0;
    int ev_nbase=0;
    int ev_nvolumetrk=0;
    int ev_ncharged_vtrk=0;
    int ev_stack=0;
    EventTree->Branch("id_event",&id_event, "id_event/I");
    EventTree->Branch("nmicro",&ev_nmicro, "ev_nmicro/I");
    EventTree->Branch("nbase",&ev_nbase, "ev_nbase/I");
    EventTree->Branch("nvolumetrk",&ev_nvolumetrk, "ev_nvolumetrk/I");
    EventTree->Branch("ncharged_vtrk",&ev_ncharged_vtrk, "ev_ncharged_vtrk/I");
    //EventTree->Branch("stack",&ev_stack,"ev_stack/I");
    
    
    //VOLUME
    std::vector<int> *v_vt_id_event = NULL;
    std::vector<int> *v_vt_id = NULL;
    std::vector<int> *v_vt_id_stack = NULL;
    std::vector<int> *v_vt_id_particle = NULL;
    std::vector<int> *v_vt_id_parentparticle = NULL;
    std::vector<int> *v_vt_id_fluka = NULL;
    std::vector<int> *v_vt_id_flukaparent = NULL;
    std::vector<double> *v_vt_x = NULL;
    std::vector<double> *v_vt_y = NULL;
    std::vector<double> *v_vt_z = NULL;
    std::vector<int> *v_vt_firstbase = NULL;
    std::vector<int> *v_vt_firstlayer = NULL;
    std::vector<int> *v_vt_lastlayer = NULL;
    std::vector<double> *v_vt_linear_range = NULL;
    std::vector<double> *v_vt_sx = NULL;
    std::vector<double> *v_vt_sy = NULL;
    std::vector<double> *v_vt_angle = NULL;
    std::vector<double> *v_vt_px = NULL;
    std::vector<double> *v_vt_py = NULL;
    std::vector<double> *v_vt_pz = NULL;
    std::vector<double> *v_vt_p = NULL;
    std::vector<double> *v_vt_E = NULL;
    std::vector<double> *v_vt_Ekin = NULL;
    std::vector<double> *v_vt_Ekin_final = NULL;
    std::vector<int> *v_vt_nbase = NULL;
    
    VolumeTree->Branch("v_vt_id_event",&v_vt_id_event);
    VolumeTree->Branch("v_vt_id",&v_vt_id);
    VolumeTree->Branch("v_vt_id_stack",&v_vt_id_stack);
    VolumeTree->Branch("v_vt_id_particle",&v_vt_id_particle);
    VolumeTree->Branch("v_vt_id_parentparticle",&v_vt_id_parentparticle);
    VolumeTree->Branch("v_vt_id_fluka",&v_vt_id_fluka);
    VolumeTree->Branch("v_vt_id_flukaparent",&v_vt_id_flukaparent);
    VolumeTree->Branch("v_vt_x",&v_vt_x);
    VolumeTree->Branch("v_vt_y",&v_vt_y);
    VolumeTree->Branch("v_vt_z",&v_vt_z);
    VolumeTree->Branch("v_vt_firstbase",&v_vt_firstbase);
    VolumeTree->Branch("v_vt_firstlayer",&v_vt_firstlayer);
    VolumeTree->Branch("v_vt_lastlayer",&v_vt_lastlayer);
    VolumeTree->Branch("v_vt_linear_range",&v_vt_linear_range);
    VolumeTree->Branch("v_vt_sx",&v_vt_sx);
    VolumeTree->Branch("v_vt_sy",&v_vt_sy);
    VolumeTree->Branch("v_vt_angle",&v_vt_angle);
    VolumeTree->Branch("v_vt_px",&v_vt_px);
    VolumeTree->Branch("v_vt_py",&v_vt_py);
    VolumeTree->Branch("v_vt_pz",&v_vt_pz);
    VolumeTree->Branch("v_vt_p",&v_vt_p);
    VolumeTree->Branch("v_vt_E",&v_vt_E);
    VolumeTree->Branch("v_vt_Ekin",&v_vt_Ekin);
    VolumeTree->Branch("v_vt_Ekin_final",&v_vt_Ekin_final);
    VolumeTree->Branch("v_vt_nbase",&v_vt_nbase);
    
    //BASE
    std::vector<int> *v_bt_id_event = NULL;
    std::vector<int> *v_bt_id = NULL;
    std::vector<int> *v_bt_id_volume = NULL;
    std::vector<int> *v_bt_id_stack = NULL;
    std::vector<int> *v_bt_id_layer = NULL;
    std::vector<int> *v_bt_id_fluka = NULL;
    std::vector<int> *v_bt_id_particle = NULL;
    std::vector<int> *v_bt_id_parentparticle = NULL;
    std::vector<int> *v_bt_id_flukaparent = NULL;
    std::vector<int> *v_bt_grains = NULL;
    std::vector<double> *v_bt_x = NULL;
    std::vector<double> *v_bt_y = NULL;
    std::vector<double> *v_bt_z = NULL;
    std::vector<double> *v_bt_sx = NULL;
    std::vector<double> *v_bt_sy = NULL;
    std::vector<double> *v_bt_angle = NULL;
    std::vector<double> *v_bt_px = NULL;
    std::vector<double> *v_bt_py = NULL;
    std::vector<double> *v_bt_pz = NULL;
    std::vector<double> *v_bt_p = NULL;
    std::vector<double> *v_bt_E = NULL;
    std::vector<double> *v_bt_Ekin = NULL;
    std::vector<int> *v_bt_nmicro = NULL;
    
    BaseTree->Branch("v_bt_id_event",&v_bt_id_event);
    BaseTree->Branch("v_bt_id",&v_bt_id);
    BaseTree->Branch("v_bt_id_volume",&v_bt_id_volume);
    BaseTree->Branch("v_bt_id_stack",&v_bt_id_stack);
    BaseTree->Branch("v_bt_id_layer",&v_bt_id_layer);
    BaseTree->Branch("v_bt_id_particle",&v_bt_id_particle);
    BaseTree->Branch("v_bt_id_fluka",&v_bt_id_fluka);
    BaseTree->Branch("v_bt_id_parentparticle",&v_bt_id_parentparticle);
    BaseTree->Branch("v_bt_id_flukaparent",&v_bt_id_flukaparent);
    BaseTree->Branch("v_bt_grains",&v_bt_grains);
    BaseTree->Branch("v_bt_x",&v_bt_x);
    BaseTree->Branch("v_bt_y",&v_bt_y);
    BaseTree->Branch("v_bt_z",&v_bt_z);
    BaseTree->Branch("v_bt_sx",&v_bt_sx);
    BaseTree->Branch("v_bt_sy",&v_bt_sy);
    BaseTree->Branch("v_bt_angle",&v_bt_angle);
    BaseTree->Branch("v_bt_px",&v_bt_px);
    BaseTree->Branch("v_bt_py",&v_bt_py);
    BaseTree->Branch("v_bt_pz",&v_bt_pz);
    BaseTree->Branch("v_bt_p",&v_bt_p);
    BaseTree->Branch("v_bt_E",&v_bt_E);
    BaseTree->Branch("v_bt_Ekin",&v_bt_Ekin);
    BaseTree->Branch("v_bt_nmicro",&v_bt_nmicro);
    
    //MICRO
    std::vector<int> *v_mt_id_event = NULL;
    std::vector<int> *v_mt_id_stack = NULL;
    std::vector<int> *v_mt_id = NULL;
    std::vector<int> *v_mt_id_base = NULL;
    std::vector<int> *v_mt_id_volume = NULL;
    std::vector<int> *v_mt_id_layer = NULL;
    std::vector<int> *v_mt_id_particle = NULL;
    std::vector<int> *v_mt_id_parentparticle = NULL;
    std::vector<int> *v_mt_flukaid = NULL;
    std::vector<int> *v_mt_id_flukaparent = NULL;
    std::vector<int> *v_mt_grains = NULL;
    std::vector<double> *v_mt_x = NULL;
    std::vector<double> *v_mt_y = NULL;
    std::vector<double> *v_mt_z = NULL;
    std::vector<double> *v_mt_sx = NULL;
    std::vector<double> *v_mt_sy = NULL;
    std::vector<double> *v_mt_angle = NULL;
    std::vector<double> *v_mt_px = NULL;
    std::vector<double> *v_mt_py = NULL;
    std::vector<double> *v_mt_pz = NULL;
    std::vector<double> *v_mt_p = NULL;
    std::vector<double> *v_mt_E = NULL;
    std::vector<double> *v_mt_Ekin = NULL;
    
    MicroTree->Branch("v_mt_id_event",&v_mt_id_event);
    MicroTree->Branch("v_mt_id",&v_mt_id);
    MicroTree->Branch("v_mt_id_base",&v_mt_id_base);
    MicroTree->Branch("v_mt_id_volume",&v_mt_id_volume);
    MicroTree->Branch("v_mt_id_stack",&v_mt_id_stack);
    MicroTree->Branch("v_mt_id_layer",&v_mt_id_layer);
    MicroTree->Branch("v_mt_id_particle",&v_mt_id_particle);
    MicroTree->Branch("v_mt_id_parentparticle",&v_mt_id_parentparticle);
    MicroTree->Branch("v_mt_flukaid",&v_mt_flukaid);
    MicroTree->Branch("v_mt_id_flukaparent",&v_mt_id_flukaparent);
    MicroTree->Branch("v_mt_grains",&v_mt_grains);
    MicroTree->Branch("v_mt_x",&v_mt_x);
    MicroTree->Branch("v_mt_y",&v_mt_y);
    MicroTree->Branch("v_mt_z",&v_mt_z);
    MicroTree->Branch("v_mt_sx",&v_mt_sx);
    MicroTree->Branch("v_mt_sy",&v_mt_sy);
    MicroTree->Branch("v_mt_angle",&v_mt_angle);
    MicroTree->Branch("v_mt_px",&v_mt_px);
    MicroTree->Branch("v_mt_py",&v_mt_py);
    MicroTree->Branch("v_mt_pz",&v_mt_pz);
    MicroTree->Branch("v_mt_p",&v_mt_p);
    MicroTree->Branch("v_mt_E",&v_mt_E);
    MicroTree->Branch("v_mt_Ekin",&v_mt_Ekin);
    
    int lastbase=0;
    double linear_range=0;
    
    //cout << "Events.size() " << Events.size() << endl;
    for(unsigned int i = 0; i<Events.size(); i++){
        evt.Clear();
        ev_ncharged_vtrk=0;
        
        evt = Events.at(i);
        id_event=evt.GetID();
        //cout << "id_event\t" << id_event << "\t n trks " << (evt.GetVolumeTracks()).size() << endl;
        ev_nmicro=(evt.GetMicroTracks()).size();
        ev_nbase=(evt.GetBaseTracks()).size();
        ev_nvolumetrk=(evt.GetVolumeTracks()).size();
        ev_stack=evt.GetStack();
        //cout << "nvolume: " << ev_nvolumetrk << "\tnbase: " << ev_nbase << "\tnmicro: " << ev_nmicro << endl;
        
        for(unsigned int iv=0; iv<(evt.GetVolumeTracks()).size(); iv++){
            vt.Clear();
            lastbase=0;
            linear_range=0;
            
            vt=evt.GetVolumeTrack(iv);
            //cout << "\t\tid_track\t" << vt.GetID() << "\t n base " << (vt.GetBaseTracks()).size() << " x: " << vt.GetX() << endl;
            
            v_vt_id_event->push_back(vt.GetEvent());
            v_vt_id->push_back(vt.GetID());
            v_vt_id_stack->push_back(vt.GetStack());
            v_vt_id_particle->push_back(vt.GetIDPart());
            v_vt_id_parentparticle->push_back(vt.GetParentIDPart());
            v_vt_id_fluka->push_back(vt.GetFlukaID());
            v_vt_id_flukaparent->push_back(vt.GetParentFlukaID());
            v_vt_x->push_back(vt.GetX());
            v_vt_y->push_back(vt.GetY());
            v_vt_z->push_back(vt.GetZ());
            v_vt_sx->push_back(vt.GetSX());
            v_vt_sy->push_back(vt.GetSY());
            v_vt_angle->push_back(vt.GetAngle());
            v_vt_px->push_back(vt.GetPX());
            v_vt_py->push_back(vt.GetPY());
            v_vt_pz->push_back(vt.GetPZ());
            v_vt_p->push_back(vt.GetP());
            v_vt_E->push_back(vt.GetE());
            v_vt_Ekin->push_back(vt.GetEkin());
            v_vt_nbase->push_back((vt.GetBaseTracks()).size());
            lastbase=(vt.GetBaseTracks()).size();
            
            v_vt_firstbase->push_back((vt.GetBaseTrack(0)).GetID());
            v_vt_Ekin_final->push_back(vt.GetBaseTrack(lastbase-1).GetEkin());
            v_vt_firstlayer->push_back(vt.GetBaseTrack(0).GetLayer());
            v_vt_lastlayer->push_back(vt.GetBaseTrack(lastbase-1).GetLayer());
            
            linear_range = sqrt(pow((vt.GetBaseTrack(lastbase-1).GetX()-vt.GetBaseTrack(0).GetX()),2)+pow((vt.GetBaseTrack(lastbase-1).GetY()-vt.GetBaseTrack(0).GetY()),2)+pow((vt.GetBaseTrack(lastbase-1).GetZ()-vt.GetBaseTrack(0).GetZ()),2));
            v_vt_linear_range->push_back(linear_range);
            // cout << vt.GetBaseTrack(0).GetLayer() << "\t" << vt.GetBaseTrack(lastbase-1).GetLayer() << "\t" << linear_range << endl;
            
            
            if(v_vt_id_fluka->at(iv)!=7&&v_vt_id_fluka->at(iv)!=8) ev_ncharged_vtrk++; //non è fotone, non è neutrone
            
            for(unsigned int ib=0; ib<(vt.GetBaseTracks()).size(); ib++){
                bt.Clear();
                
                bt = vt.GetBaseTrack(ib);
                //cout << "\t\t\t\tid_base\t" << bt.GetID() << "\t n micro " << (bt.GetMicroTracks()).size() << endl;
                //cout << "\t\t\t\tx base\t" << bt.GetX() << endl;
                
                v_bt_id_event->push_back(bt.GetEvent());
                v_bt_id->push_back(bt.GetID());
                v_bt_id_volume->push_back(vt.GetID());
                v_bt_id_stack->push_back(bt.GetStack());
                v_bt_id_layer->push_back(bt.GetLayer());
                v_bt_id_particle->push_back(bt.GetIDPart());
                v_bt_id_fluka->push_back(bt.GetFlukaID());
                v_bt_id_parentparticle->push_back(bt.GetParentIDPart());
                v_bt_id_flukaparent->push_back(bt.GetParentFlukaID());
                v_bt_grains->push_back(bt.GetGrains());
                v_bt_x->push_back(bt.GetX());
                v_bt_y->push_back(bt.GetY());
                v_bt_z->push_back(bt.GetZ());
                v_bt_sx->push_back(bt.GetSX());
                v_bt_sy->push_back(bt.GetSY());
                v_bt_angle->push_back(bt.GetAngle());
                v_bt_px->push_back(bt.GetPX());
                v_bt_py->push_back(bt.GetPY());
                v_bt_pz->push_back(bt.GetPZ());
                v_bt_p->push_back(bt.GetP());
                v_bt_E->push_back(bt.GetE());
                v_bt_Ekin->push_back(bt.GetEkin());
                v_bt_nmicro->push_back((bt.GetMicroTracks()).size());
                
                for(unsigned int im=0; im<(bt.GetMicroTracks()).size(); im++){
                    mt.Clear();
                    
                    mt = bt.GetMicroTrack(im);
                    //cout << "\t\t\t\t\t\tid_micro\t" << mt.GetID() << " x: " << mt.GetX() << endl;
                    
                    v_mt_id_event->push_back(mt.GetEvent());
                    v_mt_id->push_back(mt.GetID());
                    v_mt_id_base->push_back(bt.GetID());
                    v_mt_id_volume->push_back(vt.GetID());
                    v_mt_id_stack->push_back(mt.GetStack());
                    v_mt_id_layer->push_back(mt.GetLayer());
                    v_mt_id_particle->push_back(mt.GetIDPart());
                    v_mt_id_parentparticle->push_back(mt.GetParentIDPart());
                    v_mt_flukaid->push_back(mt.GetFlukaID());
                    v_mt_id_flukaparent->push_back(mt.GetParentFlukaID());
                    v_mt_grains->push_back(mt.GetGrains());
                    v_mt_x->push_back(mt.GetX());
                    v_mt_y->push_back(mt.GetY());
                    v_mt_z->push_back(mt.GetZ());
                    v_mt_sx->push_back(mt.GetSX());
                    v_mt_sy->push_back(mt.GetSY());
                    v_mt_angle->push_back(mt.GetAngle());
                    v_mt_px->push_back(mt.GetPX());
                    v_mt_py->push_back(mt.GetPY());
                    v_mt_pz->push_back(mt.GetPZ());
                    v_mt_p->push_back(mt.GetP());
                    v_mt_E->push_back(mt.GetE());
                    v_mt_Ekin->push_back(mt.GetEkin());
                    
                } //chiudo micro im
                
                
                //clear MICRO
                mt.Clear();
                v_mt_id_event->clear();
                v_mt_id->clear();
                v_mt_id_base->clear();
                v_mt_id_volume->clear();
                v_mt_id_stack->clear();
                v_mt_id_layer->clear();
                v_mt_id_particle->clear();
                v_mt_id_parentparticle->clear();
                v_mt_flukaid->clear();
                v_mt_id_flukaparent->clear();
                v_mt_grains->clear();
                v_mt_x->clear();
                v_mt_y->clear();
                v_mt_z->clear();
                v_mt_sx->clear();
                v_mt_sy->clear();
                v_mt_angle->clear();
                v_mt_px->clear();
                v_mt_py->clear();
                v_mt_pz->clear();
                v_mt_p->clear();
                v_mt_E->clear();
                v_mt_Ekin->clear();
            } // chiudo base ib
            
            
            // BASE
            bt.Clear();
            v_bt_id_event->clear();
            v_bt_id->clear();
            v_bt_id_volume->clear();
            v_bt_id_stack->clear();
            v_bt_id_layer->clear();
            v_bt_id_particle->clear();
            v_bt_id_parentparticle->clear();
            v_bt_id_flukaparent->clear();
            v_bt_grains->clear();
            v_bt_x->clear();
            v_bt_y->clear();
            v_bt_z->clear();
            v_bt_sx->clear();
            v_bt_sy->clear();
            v_bt_angle->clear();
            v_bt_px->clear();
            v_bt_py->clear();
            v_bt_pz->clear();
            v_bt_p->clear();
            v_bt_E->clear();
            v_bt_Ekin->clear();
            v_bt_nmicro->clear();
            
            
        }//chiudo volume iv
        
        EventTree->Fill();//4/5/18, AP
        
        VolumeTree->Fill();
        
        BaseTree->Fill();
        
        //MicroTree->Fill();

        
        //clear VOLUME
        vt.Clear();
        v_vt_id_event->clear();
        v_vt_id->clear();
        v_vt_id_stack->clear();
        v_vt_id_particle->clear();
        v_vt_id_parentparticle->clear();
        v_vt_id_fluka->clear();
        v_vt_id_flukaparent->clear();
        v_vt_x->clear();
        v_vt_y->clear();
        v_vt_z->clear();
        v_vt_firstbase->clear();
        v_vt_firstlayer->clear();
        v_vt_lastlayer->clear();
        v_vt_linear_range->clear();
        v_vt_sx->clear();
        v_vt_sy->clear();
        v_vt_angle->clear();
        v_vt_px->clear();
        v_vt_py->clear();
        v_vt_pz->clear();
        v_vt_p->clear();
        v_vt_E->clear();
        v_vt_Ekin->clear();
        v_vt_Ekin_final->clear();
        v_vt_nbase->clear();
        
    }//for i
    
    
    return ;
}

//aggiungere ID MICRO alle base
//Micro -> id base
//base -> id volume
//Tree degli eventi -> numero delle tracce di volume, posizione del vtx primario (posizione ultimo segmento del parent, primo segmento del daughter)
//controllo traccia di volume: se la traccia è 1 si setta come vtx il primo segmento del dau, se è >1 si setta l'ultimo del parent

//Fluka ID:
//-7 = frammenti da evaporazione nucleone
//-6 = 4He
//-5 = 3He
//-4 = 3H = Trizio
//-3 = 2H = deuterio
//-2 = heavy ion
//
//1 = protone
//3 = elettrone
//4 = positrone
//7 = fotone
//8 = neutrone
//13 = pione+
//14 = pione-






