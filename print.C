{
  gROOT->Reset();
   
  TFile f1("test1.root") ;
  TTree* t1 = (TTree*)f1.Get("mytree");
  double edep ; 
  TBranch* b1=t1->GetBranch("energy");
  b1->SetAddress(&edep);

  const int binums = 250;
 
  TH1D* h1 = new TH1D("1","1", binums , 0, 2.5);
  int nentries = (int)t1->GetEntries();
  for (int i=0; i<nentries; i++)
  {
    b1->GetEntry(i);
    h1->Fill(edep);
  }
 

  FILE* myfile=fopen ("data.txt", "w");

  fprintf(myfile, "%-10s%-10s \n" , "Channel", "Counts");     
  
  double count ;  
  for (int i=0; i<binums; i++)
  {
   count= h1->GetBinContent(i);
   fprintf(myfile, "%-10d%-10.0f \n" ,i,count);     
  }

  fclose(myfile);
}  
