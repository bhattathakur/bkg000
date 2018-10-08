//Name of data file: bkg_000.dat
//Energy calibration function....:      0.15448454 keV +     0.38903224 keV/chn
//FWHM   calibration function....:      3.38180470 keV +     0.00080216 keV/chn
void bkg000()
{
  ifstream input;
  input.open("bkg_000.dat");//opening the file
  Float_t x,y;
  Int_t nlines=0; //for counting the number of lines
  string line;

  /*
Application of Calibration function:
Given:
E-min=0
E-max=16384
const=0.1544
energy/chn=0.3890
Corrected:
E-min=0*0.3890-0.1544=-0.1544 (Emin*energy/chn-Emin)
E-max=16384*0.3890-0.1544=6373
   */

  TCanvas *c = new TCanvas("c","Histogram",500,700);
  c->Divide(7,4);// c->Divide(column,row);
  TFile *f=new TFile("bkg000.root","RECREATE");
  TH1F *h=new TH1F("h","#font[22]{Calibrated Energy Spectrum}",16384,-0.1544,6373);
   while(1)
    {
      input>>x>>y; //Reading the data file into two columns
      if(!input.good())break;
      h->SetBinContent(x,y); //SetBinContent(bin,content)
      nlines++;
    }
  input.close();
  printf("found %d lines\n",nlines);
  h->GetXaxis()->SetTitle("Energy(keV)");
  h->GetYaxis()->SetTitle("Counts/Channel");
  gStyle->SetOptStat(1000000001);//shows only name of the histogram
  // h->Draw();

  //Defining the array for the function
  /* TF1 * f[27];
  for(int i=0;i<27;i++)
    {
      f[i]=new TF1("f[i]","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
      f[i]->SetParNames("A","#mu","#sigma","a1","b1");
    }
  TH1F * h[27]; //Array of histograms
  for(int i=0;i<27;i++)
    {
      h[i]=(TH1F)h->Clone("h[i]");
      h[i]->GetXaxis()->SetTitle("Energy(keV)");
      h[i]->GetXaxis()->CenterTitle();
      h[i]->GetYaxis()->SetTitle("Counts/Channel");
      h[i]->GetYaxis()->CenterTitle();
      }*/
 //First peak
 c->cd(1);
 TH1F *h1=(TH1F*)h->Clone("h1");
 h1->GetXaxis()->SetTitle("Energy(keV)");
 h1->GetXaxis()->CenterTitle();
 h1->GetYaxis()->SetTitle("Counts/Channel");
 h1->GetYaxis()->CenterTitle();
 TF1 *f1=new TF1("f1","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");  //Gaus->(x,mean,sigma,normalization) 1->normalization -true
 f1->SetParNames("A","#mu","#sigma","a1","b1");
 f1->SetParameters(556.20,241.60,2,0,0);
 h1->Fit("f1","rem+","",236,245);//r-in given range,e->with better error estimation, m->improve fitting result,last two options are range of fit,
 //+->Add fitted fn to the list of functions
 //Printing the fitting parameters in the text file
 h1->Sumw2();
 gStyle->SetOptFit(1111);//SetOptFit(pcev), p->prob ,c->chi square/#df, e->error,v->value of parameters when e=1,v=1,
 //SetOptFit(1)=SetOptFit(111),v=1->only non fixed parameters, v=2->all paramters
 h1->Draw();
 
 //Second Range
 c->cd(2);
 TH1F *h2=(TH1F*)h->Clone("h2");
 h2->GetXaxis()->SetTitle("Energy(keV)");
 h2->GetXaxis()->CenterTitle();
 h2->GetYaxis()->SetTitle("Counts/Channel");
 h2->GetYaxis()->CenterTitle();
 TF1 *f2=new TF1("f2","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f2->SetParNames("A","#mu","#sigma","a1","b1");
 f2->SetParameters(1018.16,294.85,1.15,0,0);
 h2->Fit("f2","rem+","",291,298);
 h2->Sumw2();
 gStyle->SetOptFit(1111);
 h2->Draw();
 
 //Third Range
 c->cd(3);
 TH1F *h3=(TH1F*)h->Clone("h3");
 h3->GetXaxis()->SetTitle("Energy(keV)");
 h3->GetXaxis()->CenterTitle();
 h3->GetYaxis()->SetTitle("Counts/Channel");
 h3->GetYaxis()->CenterTitle();
 TF1 *f3=new TF1("f3","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f3->SetParNames("A","#mu","#sigma","a1","b1");
 f3->SetParameters(1535.70,351.71,1.25,0,0);
 h3->Fit("f3","rem+","",345.85,356.93);
 h3->Sumw2();
 gStyle->SetOptFit(1111);
 h3->Draw();
 //Forth Range
 c->cd(4);
 TH1F *h4=(TH1F*)h->Clone("h4");
 h4->GetXaxis()->SetTitle("Energy(keV)");
 h4->GetXaxis()->CenterTitle();
 h4->GetYaxis()->SetTitle("Counts/Channel");
 h4->GetYaxis()->CenterTitle();
 TF1 *f4=new TF1("f4","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f4->SetParNames("A","#mu","#sigma","a1","b1");
 f4->SetParameters(147,510.92,2.5,0,0);
 h4->Fit("f4","rem+","",501,517);
 h4->Sumw2();
 gStyle->SetOptFit(1111);
 h4->Draw();
 
 //Fifth Peak
 c->cd(5);
 TH1F *h5=(TH1F*)h->Clone("h5");
 h5->GetXaxis()->SetTitle("Energy(keV)");
 h5->GetXaxis()->CenterTitle();
 h5->GetYaxis()->SetTitle("Counts/Channel");
 h5->GetYaxis()->CenterTitle();
 TF1 *f5=new TF1("f5","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f5->SetParNames("A","#mu","#sigma","a1","b1");
 f5->SetParameters(1103.58,609.57,1.5,0,0);
 h5->Fit("f5","rem+","",603,615);
 h5->Sumw2();
 gStyle->SetOptFit(1111);
 h5->Draw();
 
 //Sixth Peak
 c->cd(6);
 TH1F *h6=(TH1F*)h->Clone("h6");
 h6->GetXaxis()->SetTitle("Energy(keV)");
 h6->GetXaxis()->CenterTitle();
 h6->GetYaxis()->SetTitle("Counts/Channel");
 h6->GetYaxis()->CenterTitle();
 TF1 *f6=new TF1("f6","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f6->SetParNames("A","#mu","#sigma","a1","b1");
 f6->SetParameters(137,768,2,0,0);
 h6->Fit("f6","rem+","",765,772);
 h6->Sumw2();
 gStyle->SetOptFit(1111);
 h6->Draw();
 
 //Eighth Peak
 c->cd(8);
 TH1F *h8=(TH1F*)h->Clone("h8");
 h8->GetXaxis()->SetTitle("Energy(keV)");
 h8->GetXaxis()->CenterTitle();
 h8->GetYaxis()->SetTitle("Counts/Channel");
 h8->GetYaxis()->CenterTitle();
 TF1 *f8=new TF1("f8","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f8->SetParNames("A","#mu","#sigma","a1","b1");
 f8->SetParameters(83,785.77,1.5,0,0);
 h8->Fit("f8","rem+","",783.5,789);
 h8->Sumw2();
 gStyle->SetOptFit(1111);
 h8->Draw();
 
 //Ninth Peak
 c->cd(9);
 TH1F *h9=(TH1F*)h->Clone("h9");
 h9->GetXaxis()->SetTitle("Energy(keV)");
 h9->GetXaxis()->CenterTitle();
 h9->GetYaxis()->SetTitle("Counts/Channel");
 h9->GetYaxis()->CenterTitle();
 TF1 *f9=new TF1("f9","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f9->SetParNames("A","#mu","#sigma","a1","b1");
 f9->SetParameters(78,911.4,2,0,0);
 h9->Fit("f9","rem+","",909,915);
 h9->Sumw2();
 gStyle->SetOptFit(1111);
 h8->Draw();
 
 //Tenth Peak
 c->cd(10);
 TH1F *h10=(TH1F*)h->Clone("h10");
 h10->GetXaxis()->SetTitle("Energy(keV)");
 h10->GetXaxis()->CenterTitle();
 h10->GetYaxis()->SetTitle("Counts/Channel");
 h10->GetYaxis()->CenterTitle();
 TF1 *f10=new TF1("f10","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f10->SetParNames("A","#mu","#sigma","a1","b1");
 f10->SetParameters(96,935,1.25,0,0);
 h10->Fit("f10","rem+","",930,940);
 h10->Sumw2();
 gStyle->SetOptFit(1111);
 h10->Draw();

 //Eleventh Peak
  c->cd(11);
 TH1F *h11=(TH1F*)h->Clone("h11");
 h11->GetXaxis()->SetTitle("Energy(keV)");
 h11->GetXaxis()->CenterTitle();
 h11->GetYaxis()->SetTitle("Counts/Channel");
 h11->GetYaxis()->CenterTitle();
 TF1 *f11=new TF1("f11","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f11->SetParNames("A","#mu","#sigma","a1","b1");
 f11->SetParameters(290,1121,1.5,0,0);
 h11->Fit("f11","rem+","",1115,1127);
 h11->Sumw2();
 gStyle->SetOptFit(1111);
 h11->Draw();
 
 //Twevelth Peak
 c->cd(12);
 TH1F *h12=(TH1F*)h->Clone("h12");
 h12->GetXaxis()->SetTitle("Energy(keV)");
 h12->GetXaxis()->CenterTitle();
 h12->GetYaxis()->SetTitle("Counts/Channel");
 h12->GetYaxis()->CenterTitle();
 TF1 *f12=new TF1("f12","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f12->SetParNames("A","#mu","#sigma","a1","b1");
 f12->SetParameters(95,1378.7,2,0,0);
 h12->Fit("f12","rem+","",1373,1383);
 h12->Sumw2();
 gStyle->SetOptFit(1111);
 h12->Draw();
  
 //Thirteenth Peak
 c->cd(13);
 TH1F *h13=(TH1F*)h->Clone("h13");
 h13->GetXaxis()->SetTitle("Energy(keV)");
 h13->GetXaxis()->CenterTitle();
 h13->GetYaxis()->SetTitle("Counts/Channel");
 h13->GetYaxis()->CenterTitle();
 TF1 *f13=new TF1("f13","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f13->SetParNames("A","#mu","#sigma","a1","b1");
 f13->SetParameters(633,1461,2,0,0);
 h13->Fit("f13","rem+","",1456,1466);
 h13->Sumw2();
 gStyle->SetOptFit(1111);
 h13->Draw();
 
 //14th peak
 c->cd(14);
 TH1F *h14=(TH1F*)h->Clone("h14");
 h14->GetXaxis()->SetTitle("Energy(keV)");
 h14->GetXaxis()->CenterTitle();
 h14->GetYaxis()->SetTitle("Counts/Channel");
 h14->GetYaxis()->CenterTitle();
 TF1 *f14=new TF1("f14","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f14->SetParNames("A","#mu","#sigma","a1","b1");
 f14->SetParameters(240,1766,2.25,0,0);
 h14->Fit("f14","rem+","",1760,1771);
 h14->Sumw2();
 gStyle->SetOptFit(1111);
 h14->Draw();

 //15th peak
 c->cd(15);
 TH1F *h15=(TH1F*)h->Clone("h15");
 h15->GetXaxis()->SetTitle("Energy(keV)");
 h15->GetXaxis()->CenterTitle();
 h15->GetYaxis()->SetTitle("Counts/Channel");
 h15->GetYaxis()->CenterTitle();
 TF1 *f15=new TF1("f15","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f15->SetParNames("A","#mu","#sigma","a1","b1");
 f15->SetParameters(43,1849,2.25,0,0);
 h15->Fit("f15","rem+","",1844.25,1854.25);
 h15->Sumw2();
 gStyle->SetOptFit(1111);
 h15->Draw();

 //begining peak(p17)
 c->cd(16);
 TH1F *h16=(TH1F*)h->Clone("h16");
 h16->GetXaxis()->SetTitle("Energy(keV)");
 h16->GetXaxis()->CenterTitle();
 h16->GetYaxis()->SetTitle("Counts/Channel");
 h16->GetYaxis()->CenterTitle();
 TF1 *f16=new TF1("f16","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f16->SetParNames("A","#mu","#sigma","a1","b1");
 f16->SetParameters(1077,25,0.4,0,0);
 h16->Fit("f16","rem+","",23.5,26.5);
 h16->Sumw2();
 gStyle->SetOptFit(1111);
 h16->Draw();

 //Left p-17
 c->cd(17);
 TH1F *h17=(TH1F*)h->Clone("h17");
 h17->GetXaxis()->SetTitle("Energy(keV)");
 h17->GetXaxis()->CenterTitle();
 h17->GetYaxis()->SetTitle("Counts/Channel");
 h17->GetYaxis()->CenterTitle();
 TF1 *f17=new TF1("f17","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f17->SetParNames("A","#mu","#sigma","a1","b1");
 f17->SetParameters(481,75,3,0,0);
 h17->Fit("f17","rem+","",68.5,84);
 h17->Sumw2();
 gStyle->SetOptFit(1111);
 h17->Draw();

 //Left p-18
 cout<<"Left Third Peak"<<endl;
 c->cd(18);
 TH1F *h18=(TH1F*)h->Clone("h18");
 h18->GetXaxis()->SetTitle("Energy(keV)");
 h18->GetXaxis()->CenterTitle();
 h18->GetYaxis()->SetTitle("Counts/Channel");
 h18->GetYaxis()->CenterTitle();
 TF1 *f18=new TF1("f18","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f18->SetParNames("A","#mu","#sigma","a1","b1");
 f18->SetParameters(292.5,86,3.5,0,0);
 h18->Fit("f18","rem+","",82,90);
 h18->Sumw2();
 gStyle->SetOptFit(1111);
 h18->Draw();
 
  //Left p-19
 cout<<"Between 1200 -1300"<<endl;
 c->cd(19);
 TH1F *h19=(TH1F*)h->Clone("h19");
 h19->GetXaxis()->SetTitle("Energy(keV)");
 h19->GetXaxis()->CenterTitle();
 h19->GetYaxis()->SetTitle("Counts/Channel");
 h19->GetYaxis()->CenterTitle();
 TF1 *f19=new TF1("f19","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f19->SetParNames("A","#mu","#sigma","a1","b1");
 f19->SetParameters(124,1238.75,2,0,0);
 h19->Fit("f19","rem+","",1234,1243);
 h19->Sumw2();
 gStyle->SetOptFit(1111);
 h19->Draw();

 //p20
 cout<<"Near 1500"<<endl;
 c->cd(20);
 TH1F *h20=(TH1F*)h->Clone("h20");
 h20->GetXaxis()->SetTitle("Energy(keV)");
 h20->GetXaxis()->CenterTitle();
 h20->GetYaxis()->SetTitle("Counts/Channel");
 h20->GetYaxis()->CenterTitle();
 TF1 *f20=new TF1("f20","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f20->SetParNames("A","#mu","#sigma","a1","b1");
 f20->SetParameters(49,1510,2.25,0,0);
 h20->Fit("f20","rem+","",1504.5,1516);
 h20->Sumw2();
 gStyle->SetOptFit(1111);
 h20->Draw();
 
 //p21
 cout<<"Peak Near 1650"<<endl;
 c->cd(21);
 TH1F *h21=(TH1F*)h->Clone("h21");
 h21->GetXaxis()->SetTitle("Energy(keV)");
 h21->GetXaxis()->CenterTitle();
 h21->GetYaxis()->SetTitle("Counts/Channel");
 h21->GetYaxis()->CenterTitle();
 TF1 *f21=new TF1("f21","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f21->SetParNames("A","#mu","#sigma","a1","b1");
 f21->SetParameters(25,1662,2.34,0,0);
 h21->Fit("f21","rem+","",1655,1668);
 h21->Sumw2();
 gStyle->SetOptFit(1111);
 h21->Draw();

 //p22
 cout<<"Near 1750 "<<endl;
 c->cd(22);
 TH1F *h22=(TH1F*)h->Clone("h22");
 h22->GetXaxis()->SetTitle("Energy(keV)");
 h22->GetXaxis()->CenterTitle();
 h22->GetYaxis()->SetTitle("Counts/Channel");
 h22->GetYaxis()->CenterTitle();
 TF1 *f22=new TF1("f22","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f22->SetParNames("A","#mu","#sigma","a1","b1");
 f22->SetParameters(52.8,1730.5,2.5,0,0);
 h22->Fit("f22","rem+","",1725,1735);
 h22->Sumw2();
 gStyle->SetOptFit(1111);
 h22->Draw();

 //p23
 cout<<"Between 2000 - 2200"<<endl;
 c->cd(23);
 TH1F *h23=(TH1F*)h->Clone("h23");
 h23->GetXaxis()->SetTitle("Energy(keV)");
 h23->GetXaxis()->CenterTitle();
 h23->GetYaxis()->SetTitle("Counts/Channel");
 h23->GetYaxis()->CenterTitle();
 TF1 *f23=new TF1("f23","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f23->SetParNames("A","#mu","#sigma","a1","b1");
 f23->SetParameters(19,2104.5,3,0,0);
 h23->Fit("f23","rem+","",2099.6,2111.6);
 h23->Sumw2();
 gStyle->SetOptFit(1111);
 h23->Draw();

 //p24
 cout<<"Second Between 2000 - 2200"<<endl;
 c->cd(24);
 TH1F *h24=(TH1F*)h->Clone("h24");
 h24->GetXaxis()->SetTitle("Energy(keV)");
 h24->GetXaxis()->CenterTitle();
 h24->GetYaxis()->SetTitle("Counts/Channel");
 h24->GetYaxis()->CenterTitle();
 TF1 *f24=new TF1("f24","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f24->SetParNames("A","#mu","#sigma","a1","b1");
 f24->SetParameters(24,2119.5,3,0,0);
 h24->Fit("f24","rem+","",2113.5,2126.5);
 h24->Sumw2();
 gStyle->SetOptFit(1111);
 h24->Draw();

 //p25
 cout<<"Peak at 2200"<<endl;
 c->cd(25);
 TH1F *h25=(TH1F*)h->Clone("h25");
 h25->GetXaxis()->SetTitle("Energy(keV)");
 h25->GetXaxis()->CenterTitle();
 h25->GetYaxis()->SetTitle("Counts/Channel");
 h25->GetYaxis()->CenterTitle();
 TF1 *f25=new TF1("f25","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f25->SetParNames("A","#mu","#sigma","a1","b1");
 f25->SetParameters(65,2205.5,3,0,0);
 h25->Fit("f25","rem+","",2199,2213);
 h25->Sumw2();
 gStyle->SetOptFit(1111);
 h25->Draw();

 //p26
 cout<<"Peak near 2400"<<endl;
 c->cd(26);
 TH1F *h26=(TH1F*)h->Clone("h26");
 h26->GetXaxis()->SetTitle("Energy(keV)");
 h26->GetXaxis()->CenterTitle();
 h26->GetYaxis()->SetTitle("Counts/Channel");
 h26->GetYaxis()->CenterTitle();
 TF1 *f26=new TF1("f26","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f26->SetParNames("A","#mu","#sigma","a1","b1");
 f26->SetParameters(22,2449.5,2.25,0,0);
 h26->Fit("f26","rem+","",2444,2456);
 h26->Sumw2();
 gStyle->SetOptFit(1111);
 h26->Draw();

 //p27
 cout<<"Peak near 2600"<<endl;
 c->cd(27);
 TH1F *h27=(TH1F*)h->Clone("h27");
 h27->GetXaxis()->SetTitle("Energy(keV)");
 h27->GetXaxis()->CenterTitle();
 h27->GetYaxis()->SetTitle("Counts/Channel");
 h27->GetYaxis()->CenterTitle();
 TF1 *f27=new TF1("f27","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
 f27->SetParNames("A","#mu","#sigma","a1","b1");
 f27->SetParameters(120,2616.5,3,0,0);
 h27->Fit("f27","rem+","",2612,2622);
 h27->Sumw2();
 gStyle->SetOptFit(1111);
 h27->Draw();
 f->Write();

 ///////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%555/////////////////////////////////////
 //Storing the Gaussian mean and Number of Counts in Peak based on fit parametes%%%%%%%%%%%%%%%555555///
 ofstream myfile("mean_counts.dat");
 const double binWidth=h->GetBinWidth(1);
 if(myfile.is_open())
   {
     /* myfile<<fixed<<setprecision(2);
     myfile
       <<f1->GetParameter(1)<<"\t"<<f1->GetParError(1)<<'\t'<<f1->GetParameter(0)/binWidth<<"\n"
        <<f2->GetParameter(1)<<"\t"<<f2->GetParError(1)<<'\t'<<f2->GetParameter(0)/binWidth<<"\n"
       <<f3->GetParameter(1)<<"\t"<<f3->GetParError(1)<<'\t'<<f3->GetParameter(0)/binWidth<<"\n"
       <<f4->GetParameter(1)<<"\t"<<f4->GetParError(1)<<'\t'<<f4->GetParameter(0)/binWidth<<"\n"
       <<f5->GetParameter(1)<<"\t"<<f5->GetParError(1)<<'\t'<<f5->GetParameter(0)/binWidth<<"\n"
       <<f6->GetParameter(1)<<"\t"<<f6->GetParError(1)<<'\t'<<f6->GetParameter(0)/binWidth<<"\n"
       <<f8->GetParameter(1)<<"\t"<<f8->GetParError(1)<<'\t'<<f8->GetParameter(0)/binWidth<<"\n"
       <<f9->GetParameter(1)<<"\t"<<f9->GetParError(1)<<'\t'<<f9->GetParameter(0)/binWidth<<"\n"
       <<f10->GetParameter(1)<<"\t"<<f10->GetParError(1)<<'\t'<<f10->GetParameter(0)/binWidth<<"\n"
       <<f11->GetParameter(1)<<"\t"<<f11->GetParError(1)<<'\t'<<f11->GetParameter(0)/binWidth<<"\n"
       <<f12->GetParameter(1)<<"\t"<<f12->GetParError(1)<<'\t'<<f12->GetParameter(0)/binWidth<<"\n"
       <<f13->GetParameter(1)<<"\t"<<f13->GetParError(1)<<'\t'<<f13->GetParameter(0)/binWidth<<"\n"
       <<f14->GetParameter(1)<<"\t"<<f14->GetParError(1)<<'\t'<<f14->GetParameter(0)/binWidth<<"\n"
        <<f15->GetParameter(1)<<"\t"<<f15->GetParError(1)<<'\t'<<f15->GetParameter(0)/binWidth<<"\n"
       <<f16->GetParameter(1)<<"\t"<<f16->GetParError(1)<<'\t'<<f16->GetParameter(0)/binWidth<<"\n"
       <<f17->GetParameter(1)<<"\t"<<f17->GetParError(1)<<'\t'<<f17->GetParameter(0)/binWidth<<"\n"
       <<f18->GetParameter(1)<<"\t"<<f18->GetParError(1)<<'\t'<<f18->GetParameter(0)/binWidth<<"\n"
       <<f19->GetParameter(1)<<"\t"<<f19->GetParError(1)<<'\t'<<f19->GetParameter(0)/binWidth<<"\n"
       <<f20->GetParameter(1)<<"\t"<<f20->GetParError(1)<<'\t'<<f20->GetParameter(0)/binWidth<<"\n"
       <<f21->GetParameter(1)<<"\t"<<f21->GetParError(1)<<'\t'<<f21->GetParameter(0)/binWidth<<"\n"
       <<f22->GetParameter(1)<<"\t"<<f22->GetParError(1)<<'\t'<<f22->GetParameter(0)/binWidth<<"\n";
       myfile<<f23->GetParameter(1)<<"\t"<<f23->GetParError(1)<<'\t'<<f23->GetParameter(0)/binWidth<<"\n"
       <<f24->GetParameter(1)<<"\t"<<f24->GetParError(1)<<'\t'<<f24->GetParameter(0)/binWidth<<"\n"
       <<f25->GetParameter(1)<<"\t"<<f25->GetParError(1)<<'\t'<<f25->GetParameter(0)/binWidth<<"\n"
       <<f26->GetParameter(1)<<"\t"<<f26->GetParError(1)<<'\t'<<f26->GetParameter(0)/binWidth<<"\n"
       <<f27->GetParameter(1)<<"\t"<<f27->GetParError(1)<<'\t'<<f27->GetParameter(0)/binWidth<<"\n";*/
       for(int i=1;i<=6;i++)
         {
	 myfile<<fi->GetParameter(1)<<endl;
         }
     cout<<"successfully stored gaussian mean and Number of events in \"mean_counts.dat\""<<endl;
   }
 else cout<<"unable to open the file \"mean_counts.dat\" " <<endl;
 
}
