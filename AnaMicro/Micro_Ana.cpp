#define RAD2DEG  57.2958
#define VERBOSE 0
#define VERBOSE_PLOT 0
#define SAVE_MICRO 0

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
            
            // cout << "Set event "<<id_event<<endl;
        }//if
        
        if(id_fluka!=3&&id_fluka!=4){//skip e+e-
            
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
    Double_t x=0, y=0, z=0, px=0, py=0, pz=0, p=0, E=0, Ekin=0;
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
                        bt.SetPXYZ(px,py,pz);
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
            
            if (((Events.at(i)).GetMicroTrack(im)).GetFlukaID()==-2) cout << "bt: " << ((Events.at(i)).GetMicroTrack(im)).GetFlukaID() << endl;

            
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
    Int_t id_part = -99, id_layer=-99, id_parent=-99, id_fluka_part=-99, id_fluka_parent=-99, counttrack = 0;
    //Double_t linear_range=-99;
    //cout << "Events.size() " << Events.size() << endl;
    for(unsigned int i = 0; i<Events.size(); i++){
        
        counttrack=0;
        
        for(unsigned int ib = 0; ib<((Events.at(i)).GetBaseTracks()).size();ib++){
            //linear_range=0;
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
            else if(ib&&((id_fluka_part!=((Events.at(i)).GetBaseTrack(ib)).GetFlukaID()) ||(id_fluka_part==((Events.at(i)).GetBaseTrack(ib)).GetFlukaID()&&((Events.at(i)).GetBaseTrack(ib)).GetLayer()<=id_layer&&id_parent==((Events.at(i)).GetBaseTrack(ib)).GetParentIDPart())||(id_fluka_part==((Events.at(i)).GetBaseTrack(ib)).GetFlukaID()&&((Events.at(i)).GetBaseTrack(ib)).GetLayer()<=id_layer&&id_fluka_parent!=((Events.at(i)).GetBaseTrack(ib)).GetParentFlukaID()))){
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
                
              //  linear_range = sqrt(pow((vt.GetBaseTrack(lastbase).GetX()-vt.GetBaseTrack(0).GetX()),2)+pow((vt.GetBaseTrack(lastbase).GetY()-vt.GetBaseTrack(0).GetY()),2)+pow((vt.GetBaseTrack(lastbase).GetZ()-vt.GetBaseTrack(0).GetZ()),2));
                
                vt.SetP(((Events.at(i)).GetBaseTrack(ib)).GetP());
                vt.SetE(((Events.at(i)).GetBaseTrack(ib)).GetE());
                vt.SetEkin(((Events.at(i)).GetBaseTrack(ib)).GetEkin());
                
                vt.SetBaseTrack((Events.at(i)).GetBaseTrack(ib));
            }
            
            id_part = ((Events.at(i)).GetBaseTrack(ib)).GetIDPart();
            id_fluka_parent = ((Events.at(i)).GetBaseTrack(ib)).GetParentFlukaID();
            id_fluka_part = ((Events.at(i)).GetBaseTrack(ib)).GetFlukaID();
            id_parent = ((Events.at(i)).GetBaseTrack(ib)).GetParentIDPart();
            id_layer = ((Events.at(i)).GetBaseTrack(ib)).GetLayer();
            
            // } // chiudo if sugli elettroni e positroni
            
            if (id_fluka_part==-2) cout << "vt: " << id_fluka_part << endl;
            
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
    
    EventTree->Branch("event", &evt);
    
    //cout << "Events.size() " << Events.size() << endl;
    for(unsigned int i = 0; i<Events.size(); i++){
        evt.Clear();
        
        evt = Events.at(i);
        
//        for(unsigned int iv=0; iv<(evt.GetVolumeTracks()).size(); iv++){
//            vt.Clear();
//            lastbase=0;
//            linear_range=0;
//
//            vt=evt.GetVolumeTrack(iv);
//
//            v_vt->push_back(vt);
//
//            for(unsigned int ib=0; ib<(vt.GetBaseTracks()).size(); ib++){
//                bt.Clear();
//                bt = vt.GetBaseTrack(ib);
//                v_bt->push_back(bt);
//
//                if(SAVE_MICRO==1){
//                    for(unsigned int im=0; im<(bt.GetMicroTracks()).size(); im++){
//                        mt.Clear();
//                        mt = bt.GetMicroTrack(im);
//                        v_mt->push_back(mt);
//                    } //chiudo micro im
//                }
//            } // chiudo base ib
//        }//chiudo volume iv
        EventTree->Fill();
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






