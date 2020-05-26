
// 2016/1/20 ----Created by herbertqiao
// 2018/4/15-----modified by  SONG Yunxuan
//2018/4/25----- Add set ROOT File Name by Siguang WANG ( siguang@pku.edu.cn)
//

#include <TTree.h>
#include "Run.hh"
#include <TTree.h>
#include "TVector3.h"
#include <TLorentzVector.h>
#include <TROOT.h>
#include <TRandom3.h>
#include "TClonesArray.h"
#include <iostream>
#include "RunMessenger.hh"
#include "G4SystemOfUnits.hh"

static Run*  instance = 0;

Run::Run()
//  :  fRunMessenger(0)
{
  rootFileName = "test.root";
  fRunMessenger = new RunMessenger(this);
  _energy =0;
}

Run::~Run() {
    //_file->Close();
   delete fRunMessenger;
}

Run*  Run::GetInstance()
{
  if (instance == 0 )
  {
    instance = new Run();
  }
  return instance;
}


void Run::initTree() {
    std::cout << "Init Tree File." << std::endl;
    _file = new TFile(rootFileName.c_str(), "RECREATE");
    _tree = new TTree("mytree", "Simple Out Tree");

    //_tree->Branch("GunEng", &_GunEng, "GunEng/D");
    //_tree->Branch("E1", &_energyDisFirst, "E1/D");
    //_tree->Branch("E2", &_energyDisSecond, "E2/D");
    //_tree->Branch("E3", &_energyDisThird, "E3/D");
    //_tree->Branch("TrackLength", &_TrackLength, "TrackLength/D");
    _tree->Branch("energy", &_energy, "energy/D");
}

void Run::saveTree() const {
  _file->cd();
  _tree->Write();
  _file->Close();

}

void Run::Fill() { 
  if (_energy>0){
    _tree->Fill();
  }
    //std::cout<<"caonima!"<<_energy<<std::endl;
    //_energyDisFirst = 0;
    //_energyDisSecond = 0;
    //_energyDisThird = 0;
    //_TrackLength = 0;
    //_GunEng =0;
  _energy = 0;
}
/*
void Run::AddEnergy1(double Eng1) {
  if(Eng1>0)  _energyDisFirst += Eng1 ;
}
void Run::AddEnergy2(double Eng2) {
   if(Eng2>0)   _energyDisSecond += Eng2;
}
void Run::AddEnergy3(double Eng3) {
   if(Eng3>0)   _energyDisThird += Eng3;
}
void Run::AddLength(double TrackLength){
  if(TrackLength>0)     _TrackLength+=TrackLength;
}
*/
void Run::AddEnergy(double E){
  if(E>0) _energy += E;
}

