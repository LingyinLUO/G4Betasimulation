//
// 2016/1/20 ----Created by herbertqiao
// 2018/4/15-----modified by  SONG Yunxuan
//2018/4/25----- Add set ROOT File Name by Siguang WANG ( siguang@pku.edu.cn)
//

#ifndef GEANT4_INTRODUCTION_RUN_HH
#define GEANT4_INTRODUCTION_RUN_HH 1



#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include "globals.hh"


class RunMessenger;

class Run {
public:
    Run();
    static Run* GetInstance();
    virtual ~Run();
    void initTree();
    void saveTree() const;
    void Fill();
    //void AddEnergy1(double Eng1);
    //void AddEnergy2(double Eng2);
    //void AddEnergy3(double Eng3);
    //void AddLength(double fTrackLength);
    //void RecPrimPartEng(double fGunEnergy){_GunEng =fGunEnergy; };
    void AddEnergy(double E);
   void SetROOTFullName(G4String NewRootFileFullName){ rootFileName = NewRootFileFullName;};
    
private:
    G4String rootFileName;
    TTree *_tree;
    TFile *_file;
  /*Double_t _energyDisFirst;
    Double_t _energyDisSecond;
    Double_t _energyDisThird;
    Double_t  _TrackLength;
    Double_t _GunEng;*/
    Double_t _energy;
    RunMessenger* fRunMessenger;
};

#endif //GEANT4_INTRODUCTION_RUN_H
