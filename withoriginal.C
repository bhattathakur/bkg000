//Name of data file: bkg_000.dat
//Energy calibration function....:      0.15448454 keV +     0.38903224 keV/chn
//FWHM   calibration function....:      3.38180470 keV +     0.00080216 keV/chn
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
{
 Int_t x,y; //for histogram
  Int_t nlines=0; //for counting the number of lines
  string line;
  ifstream input("bkg_000orignal.dat");//opening the file
  TCanvas *c = new TCanvas("c","Histogram",500,700);
  TFile *f=new TFile("bkg000.root","RECREATE");
  TH1F *h=new TH1F("h","Calibrated Energy Spectrum",16384,-0.1544,6373);
  if(input.is_open())
    {
      int flag=0;
      while(getline(input,line))
        {
	flag++;
	//if (flag<=6) continue;
	//	if (flag>=16391) break;
	//	getline(input,line);
	if(flag>6 && flag<16391)
	  {
	    stringstream sstr(line);
	    sstr>>x>>y; //Reading the data file into two columns
	    h->SetBinContent(x,y); //SetBinContent(bin,content)
	    //	    cout<<line<<endl;
	    nlines++;
	  }
        }
      input.close();
    }
  else cout<<"unable to open file"<<endl;
  input.close(); //closing the data file
  printf("found %d lines\n",nlines);
  h->GetXaxis()->SetTitle("Energy(keV)");
  h->GetYaxis()->SetTitle("Counts/Channel");
  gStyle->SetOptStat(0);//To remove the information about mean, rms etc
  h->Draw();
  f->Write();
}
