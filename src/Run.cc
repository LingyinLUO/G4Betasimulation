
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
{
  rootFileName = "test.root";
  fRunMessenger = new RunMessenger(this);
  _energy =0;
}

Run::~Run() {
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
  
  _energy = 0;
}

void Run::AddEnergy(double E){
  if(E>0) _energy += E;
}

