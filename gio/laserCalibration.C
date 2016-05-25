/*
 * TBF 2016 laserCalibration.C Version 1.0
 *
*/

#include <iostream>

struct caen_5742 {
	ULong64_t system_clock;
	ULong64_t device_clock[18];
	UShort_t trace[18][1024];
};

Double_t fPositionX1;
Double_t fPositionY1;
Double_t fPositionX2;
Double_t fPositionY2;
Double_t integralP2;
Double_t integralP2_mean;
Double_t integralP2_sigma;
Double_t integralP2_mean_error;
Double_t integralP2_sigma_error;

Double_t timeline;
Float_t baseline[1024];

TFile* outfile;
TTree* outTree;

void laserCalibration(
		char* filename = "frascatirun", //input file
		int filenum = 1081, 					//file number
		int channel = 3, 						//trace channel
		int flagChannel = 5, 					//laser flag channel
		Double_t entriesN = 10,					//number of entries for prcessing
		int sleep = 10,							//sleep time between 2 processed entries, helpful for viewing traces
		bool gui = true							//enable or disable trace visualization
		)
{
	caen_5742 caen;
	Int_t nbins = 1024;
	Double_t entries = entriesN;
	Int_t bin;

	TCanvas *c1 = new TCanvas("c1","frascatirun",900,700);
	c1->Divide(1,2);
	c1->cd(1);

	TGraph* g = new TGraph();
	TH1F* lmPeaks = new TH1F("lm","Peaks Ratio", 1000, 0, 5000);
    TH1F* d = new TH1F("d","",nbins,0,nbins);
    TH1F* back = new TH1F("Back","",nbins,0,nbins);

    // input file
    char fname[100]=0;
    sprintf(fname,"%s_0%i.root",filename,filenum);

    TFile* infile = new TFile(fname);
	TTree *t = (TTree*) infile->Get("t");
	t->SetBranchAddress("caen_5742", &caen.system_clock);
	t->Print();

	if(entriesN<=0)
		entries = t->GetEntries();

	//out file
    char foutname[100]=0;
    int lm=0;
    if (channel ==3)lm=1;
    if (channel ==4)lm=2;
    sprintf(foutname,"./calibration/LM%i_out_0%i.root",lm,filenum);
	outfile = new TFile(foutname,"RECREATE");
	outTree = new TTree("LM","frascatirun output");
	calibTree = new TTree("LM_cal","frascatirun output");
	outTree->Branch("LM_PX1",&fPositionX1,"PX1/D");
	outTree->Branch("LM_PX2",&fPositionX2,"PX2/D");
	outTree->Branch("LM_PY1",&fPositionY1,"PY1/D");
	outTree->Branch("LM_PY2",&fPositionY2,"PY2/D");
	//outTree->Branch("baseline",baseline,"baseline[1024]/F");
	outTree->Branch("time",&timeline,"time/D");
	outTree->Branch("LM_P2_Integral",&integralP2,"IP2/D");
	calibTree->Branch("LM_P2_Integral_mean",&integralP2_mean,"IP2_mean/D");
	calibTree->Branch("LM_P2_Integral_mean_error",&integralP2_mean_error,"IP2_mean_error/D");
	calibTree->Branch("LM_P2_Integral_sigma",&integralP2_sigma,"IP2_sigma/D");
	calibTree->Branch("LM_P2_Integral_sigma_error",&integralP2_sigma_error,"IP2_sigma_error/D");

    /**************************************
     * read entries
     **************************************
    */
	for (int j = 0; j < entries; ++j){
		gSystem->Sleep (sleep);

		t->GetEntry(j);

		//TRIGGER SELECTION
		if(caen.trace[flagChannel][400]>1000 && caen.trace[flagChannel][800]<3000){
			timeline = caen.system_clock;

			/**************************************
		     * Peaks estimation
		     **************************************
		    */
			for (int i = 0; i < nbins; ++i){
				g->SetPoint(i, i, caen.trace[channel][i]);
			}

			Double_t y_max = TMath::MaxElement(g->GetN(),g->GetY());
			Float_t * source = new Float_t[nbins];
			Float_t * dest = new Float_t[nbins];

			for (int i = 0; i < nbins; ++i){
				source[i]=y_max-caen.trace[channel][i];
				g->SetPoint(i, i, source[i]);
			}

			//Use TSpectrum to find the peak candidates
			TSpectrum *s = new TSpectrum();
		   	Int_t nfound = s->SearchHighRes(source, dest, nbins, 3, 2, kTRUE, 2, kFALSE, 5);

		    /**************************************
		     * Background estimation
		     **************************************
		    */
		    Int_t  	ssize = nbins;
		    Int_t  	numberIterations = 20;
		    Int_t  	direction = s->kBackIncreasingWindow;
		    Int_t  	filterOrder = s->kBackOrder2;
		    bool  	smoothing = kFALSE;
		    Int_t  	smoothWindow = s->kBackSmoothing3;
		    bool  	compton = kFALSE;
		    for (int i = 0; i < nbins; ++i) baseline[i] = source[i];
		    s->Background(baseline, ssize, numberIterations, direction, filterOrder, smoothing, smoothWindow, compton);

		    /**************************************
		     * Peaks and integral estimation
		     **************************************
		    */
		    Double_t px[2], py[2];
		    for (int i = 0; i < nbins; ++i) dest[i] = source[i]-baseline[i];
		    if(nfound==2){
			   bin = s->GetPositionX()[0];
			   fPositionX1 = bin;
			   fPositionY1 = dest[bin];
			   px[0] = bin;
			   py[0] = dest[bin];
			   bin = s->GetPositionX()[1];
			   fPositionX2 = bin;
			   fPositionY2 = dest[bin];
			   px[1] = bin;
			   py[1] = dest[bin];
		    }
			int posxa=6;
		    int posxb=9;
		    switch (filenum){
		    	case 1081:
		    		posxa=6;
		    		posxb=9;
		    		break;

		    	case 1082:
		    		posxa=5;
		    		posxb=7;
		    		break;

		    	case 1083:
		    		posxa=5;
		    		posxb=8;
		    		break;

		    	case 1084:
		    		posxa=5;
		    		posxb=7;
		    		break;

		    	case 1085:
		    		posxa=5;
		    		posxb=7;
		    		break;

		    	case 1086:
		    		posxa=5;
		    		posxb=5;
		    		break;

		    	case 1087:
		    		posxa=4;
		    		posxb=4;
		    		break;

		    	case 1088:
		    		posxa=3;
		    		posxb=4;
		    		break;

		    	case 1089:
		    		posxa=3;
		    		posxb=3;
		    		break;

		    	default:
		    		posxa=6;
		    		posxb=9;
}

		    integralP2 = g->Integral (fPositionX2-posxa,fPositionX2+posxb);

		    /**************************************
		     * print and update the canvas
		     **************************************
		    */
		    if(gui==true){
				TH1F* gh = g->GetHistogram();
				gh->FillN(nbins,g->GetX(),g->GetY());
				g->Draw();

				TPolyMarker* pm = (TPolyMarker*)gh->GetListOfFunctions()->FindObject("TPolyMarker");
				if (pm) {
				   gh->GetListOfFunctions()->Remove(pm);
				   delete pm;
				}
				pm = new TPolyMarker(nfound, px, py);

				gh->GetListOfFunctions()->Add(pm);
				pm->SetMarkerStyle(23);
				pm->SetMarkerColor(kBlue);
				pm->SetMarkerSize(1.3);
				for (i = 0; i < nbins; i++) d->SetBinContent(i,dest[i]);
				d->SetLineColor(kRed);
				d->Draw("SAME");

				for (i = 0; i < nbins; i++) back->SetBinContent(i,baseline[i]);
			    back->SetLineColor(kGreen);
			    back->Draw("SAME");
				c1->Update();
		    }

		    /**************************************
		     * Fill tree and peaks data Histogram
		     **************************************
		    */
			if(nfound==2)
			{
				lmPeaks->Fill(integralP2);
				outTree->Fill();
			}
	        //printf("time= %d, posx1= %d, posy1= %d\n",time, fPositionX1, fPositionY1);
			//printf("time= %d, posx2= %d, posy2= %d\n",time, fPositionX2, fPositionY2);
			//for (int i=0;i<nbins;i++) printf("time = %d\n",baseline[i]);
		}
	}

	/**************************************
     * switch to the bottom pan and Draw Histogram
     **************************************
    */
	c1->cd(2);
	//lmPeaks->SetAxisRange(TMath::MinElement(entries,binmin),TMath::MaxElement(entries,binmax)+100);
	//lmPeaks->SetAxisRange(0,3000);
	lmPeaks->Fit("gaus");
	integralP2_mean = lmPeaks->GetFunction("gaus")->GetParameter(1);
	integralP2_sigma = lmPeaks->GetFunction("gaus")->GetParameter(2);
	integralP2_mean_error = lmPeaks->GetFunction("gaus")->GetParError(1);
	integralP2_sigma_error = lmPeaks->GetFunction("gaus")->GetParError(2);
	//printf("mean = %f\n",integralP2_mean);
	//printf("sigma = %f\n",integralP2_sigma);
	calibTree->Fill();
	lmPeaks->Draw();
	c1->Update();

	outfile->cd();
	gROOT->GetList()->Write();
	outTree->Write();
	calibTree->Write();
	outfile->Close();
}
