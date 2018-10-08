
{
  double b1=0.1544;
  double m1=0.3890;
  double b2=0.5655;
  double m2=0.9989;
  int numberOfChannels=16384;
  int peakNo=23;
  //file name of datafile
  //file name for storing original histogram in .root file
  double bnew=m2*b1+b2;
  double mnew=m1*m2;
  double Emin=0;
  double Emax=numberOfChannels;
  double correctedEmin=Emin*mnew-bnew;
  double correctedEmax=Emax*mnew-bnew;
  //  cout<<correctedEmin<<'\t'<<correctedEmax<<endl;


  //Energy Sprectrum
  TCanvas *c1 = new TCanvas("c1","Histogram",500,700);
  //  TFile *file=new TFile("working.root","RECREATE");
  //cout<<"number of Channels= "<<numberOfChannels<<" correctedMin= "<< correctedEminMin << "correctedmax = "<<correctedEmax<<endl;
  TH1F *histo=new TH1F("histo","#font[22]{Calibrated Energy Spectrum}",numberOfChannels,correctedEmin,correctedEmax);
  // cout<<numberOfChannels<<'\t'<<correctedEmin<<'\t'<<correctedEmax<<endl;
  ifstream input("bkg_000.dat");
  Float_t x,y;
  Int_t nlines=0; //for counting the number of lines
   while(1)
    {
      input>>x>>y; //Reading the data file into two columns
      if(!input.good())break;
      histo->SetBinContent(x,y); //SetBinContent(bin,content)
      nlines++;
    }
  input.close();
  printf("found %d lines\n",nlines);
  histo->GetXaxis()->SetTitle("Energy(keV)");
  histo->GetYaxis()->SetTitle("Counts/Channel");
  gStyle->SetOptStat(1000000001);//shows only name of the histogram
  f=new TF1("f","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
  f->SetParNames("A","#mu","#sigma","a1","b1");
  double a= 147.43    ;
  double b= 509.92  ;
  double c= 2.5   ;
  double d= 501   ;
  double e= 516  ;
  f->SetParameters(a,b,c,0,0);
  histo->Fit(f,"rem+","",d,e);
  gStyle->SetOptStat(1111);
  histo->Draw();
  c1->Update();
	  
	  
}
