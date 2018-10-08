//Name of data file: bkg_000.dat
//Energy calibration function....:      0.15448454 keV +     0.38903224 keV/chn
//FWHM   calibration function....:      3.38180470 keV +     0.00080216 keV/chn
//void compactbkg000()
{
  ifstream input;
  input.open("bkg_000.dat");//opening the data file
  Float_t x,y;
  Int_t nlines=0; //for counting the number of lines
  string line;
  const int peakNo=23;

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
  c->Divide(6,4);// c->Divide(column,row);
  TFile *file=new TFile("finalfittedhistograms.root","RECREATE");
  TH1F *histo=new TH1F("histo","#font[22]{Calibrated Energy Spectrum}",16384,-0.1544,6373);
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
  // h->Draw();
  /*  double firstParameter[peakNo]={1077,481,292.5,556.20,1018.16,
		         1535.70,147,1103.58,137,83,
		         78,96,290,124,95,
		         633,49,25,52.8,240,
		         43,19,24,65,22,
		         120};
  double secondParameter[peakNo]={25,75,86,241.60,294.85,
			351.71,510.92,609.57,768.2,785.77,
			911.4,935,1121,1238.75,1378.7,
			1461,1510,1662,1730.5,1766,
			1842,2104.5,2119.5,2205.5,2449.5,
			2616.5};
  double thirdParameter[peakNo]={0.4,3,3.5,2,1.15,
		         1.25,2.5,1.5,2,1.5,
		         2,1.25,1.5,2,2,
		         2,2.25,2.34,2.5,2.25,
		         2.25,3,3,3,2.25,
		         3};
  double fourthParameter[peakNo]={0};
  double fifthParameter[peakNo]={0};
  double firstLimit[peakNo]={23.5,68.5,82,236,291,
		     345.85,501,603,765,783.5,
		     909,930,1115,1234,1373,
		     1456,1504.5,1655,1725,1760,
		     1844.25,2099.6,2113.5,2199,2444,
		     2612};
  double secondLimit[peakNo]={26.5,84,90,245,298,
		      356.93,517,615,772,789,
		      915,940,1127,1243,1383,
		      1466,1516,1668,1735,1771,
		      1854.25,2111.6,2126.5,2213,2456,
		      2622};*/
  double firstParameter[peakNo]={0};
  double secondParameter[peakNo]={0};
  double thirdParameter[peakNo]={0};
  double firstLimit[peakNo]={0};
  double secondLimit[peakNo]={0};
  ifstream gussedParameter("gussedParameterfinal.dat"); //File containing the estimated fit parameters
  if(gussedParameter.is_open())
	{
	  cout<<"File reading is OK"<<endl;
	}
	else
	  {
		cout<<"Error in reading the file for estimated paramters"<<endl;
		return 0;
	  }
  int peakCount=0;
  cout<<"Before while loop"<<endl;
  //  if(gussedParameter.is_open()){
    while(gussedParameter>>firstParameter[peakCount]>>secondParameter[peakCount]>>thirdParameter[peakCount] >>firstLimit[peakCount]>>secondLimit[peakCount])
    {
      // gussedParameter>>firstParameter[peakCount]>>secondParameter[peakCount]>>thirdParameter[peakCount] >>firstLimit[peakCount]>>secondLimit[peakCount];
      cout<<firstParameter[peakCount]<<'\t'<<secondParameter[peakCount]<<'\t'<<thirdParameter[peakCount] <<'\t'<<firstLimit[peakCount]<<'\t'<<secondLimit[peakCount]<<endl;
      if(!gussedParameter.good())break;
      cout<<"Inside the while loop"<<endl;
      peakCount++;
    }
  //the array for the function and histogram
  cout<<"After excution of while loop"<<endl;
  for(int i=0;i<peakNo;i++){
    cout<<firstParameter[i]<<'\t'<<secondParameter[i]<<'\t'<<thirdParameter[i] <<'\t'<<firstLimit[i]<<'\t'<<secondLimit[i]<<endl;}
  TF1 * f[peakNo];
  TH1F * h[peakNo]; //Array of histograms
  for(int i=0;i<peakNo;i++)
    {
      f[i]=new TF1("f[i]","[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
      f[i]->SetParNames("A","#mu","#sigma","a1","b1");
      f[i]->SetParameters(firstParameter[i],secondParameter[i],thirdParameter[i],firstLimit[i],secondLimit[i]);
      c->cd(i+1);
      h[i]=(TH1F)histo->Clone(Form("h%d",i+1));
      h[i]->GetXaxis()->SetTitle("Energy(keV)");
      h[i]->GetXaxis()->CenterTitle();
      h[i]->GetYaxis()->SetTitle("Counts/Channel");
      h[i]->GetYaxis()->CenterTitle();
      h[i]->Fit("f[i]","rem+","",firstLimit[i],secondLimit[i]);
      cout<<"########################  Peak "<<(i+1)<<"  #########################     "<<endl;
      h[i]->Sumw2();
      gStyle->SetOptFit(1111);
      h[i]->Draw();
      file->cd();
      h[i]->Write();
    }

  ///////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%555/////////////////////////////////////
 //Storing the Gaussian mean and Number of Counts in Peak based on fit parametes%%%%%%%%%%%%%%%555555///
  
 ofstream myfile("finalerrordata.dat");
 const double binWidth=histo->GetBinWidth(1);
 if(myfile.is_open())
 {
  myfile<<fixed<<setprecision(2);
     for(int i=0;i<peakNo;i++)
       {
         myfile<< f[i]->GetParameter(1)<<"\t"<<f[i]->GetParError(1)<<"\t"<<f[i]->GetParameter(0)/binWidth<<endl;
       }
     cout<<"successfully stored gaussian mean and Number of events in \"mean_counts.dat\""<<endl;
 }
 else cout<<"unable to open the file \"mean_counts.dat\" " <<endl;
 file->Close(); 
}
