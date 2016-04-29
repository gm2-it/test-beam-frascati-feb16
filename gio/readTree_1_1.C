/*
 * TBF 2016 readTree.C Version 1.1
 *
*/

#include <iostream>

struct caen_5742 {
	ULong64_t system_clock;
	ULong64_t device_clock[18];
	UShort_t trace[18][1024];
};

const Int_t nbins = 1024;
Int_t i,bin;
Int_t nfound;

TGraph* g;
TSpectrum *s;
Double_t * source;
Double_t * dest;
TFile* outfile;
TTree* outTree;

Double_t fPositionX1;
Double_t fPositionY1;
Double_t fPositionX2;
Double_t fPositionY2;
Double_t integralP2;
Double_t timeline;
Double_t baseline[nbins];

//Spectrum Fit
void graphFit ()
{
	Double_t a;
	TH1F* gh2 = g->GetHistogram();
	gh2->FillN(nbins,g->GetX(),g->GetY());
    Bool_t *FixPos =new Bool_t[nfound];
    Bool_t *FixAmp = new Bool_t[nfound];
    for(i = 0; i< nfound ; i++){
       FixPos[i] = kFALSE;
       FixAmp[i] = kFALSE;
    }

    Double_t *PosX = new Double_t[nfound];
    Double_t *PosY = new Double_t[nfound];
    PosX = s->GetPositionX();

    for (i = 0; i < nfound; i++) {
       a=PosX[i];
       bin = 1 + Int_t(a + 0.5);
       PosY[i] = gh2->GetBinContent(bin);
    }

    TSpectrumFit *sf = new TSpectrumFit(nfound);
    sf->SetFitParameters(0, nbins-1, 100, 0.1, sf->kFitOptimChiCounts,
    sf->kFitAlphaOptimal, sf->kFitPower12,
	sf->kFitTaylorOrderSecond);
    sf->SetPeakParameters(2, kFALSE, PosX, (Bool_t *) FixPos, PosY, (Bool_t *) FixAmp);
    sf->FitAwmi(dest);
    Double_t *CalcPositions = new Double_t[nfound];
    Double_t *CalcAmplitudes = new Double_t[nfound];
    Double_t *CalcAreas = new Double_t[nfound];
    CalcPositions = sf->GetPositions();
    CalcAmplitudes = sf->GetAmplitudes();
    CalcAreas = sf->GetAreas();
    //for (int i=0;i<nfound;i++) printf("pos = %f ampl = %f area = %f\n",CalcPositions[i], CalcAmplitudes[i],CalcAreas[i]);
    integralP2 = CalcAreas[1];
}

//Main function
void readTree_1_1(
		char* filename = "frascatirun",			//input file
		int filenum = 1100, 					//file number
		int channel = 7, 						//trace channel
		int flagChannel = 7, 					//laser flag channel
		Double_t entriesN = 10,					//number of entries for prcessing
		int sleep = 10,							//sleep time between 2 processed entries, helpful for viewing traces
		bool gui = true							//enable or disable trace visualization
		)
{
	caen_5742 caen;
	Double_t entries = entriesN;

	TCanvas *c1 = new TCanvas("c1","frascatirun",900,700);
	c1->Divide(1,2);
	c1->cd(1);

	g = new TGraph();
	TH1F* lmPeaks = new TH1F("lm","Peaks Ratio", 500, 0, 5);
    TH1F* d = new TH1F("d","",nbins,0,nbins);
    TH1F* back = new TH1F("Back","",nbins,0,nbins);

    // input file
    char fname[100];
    sprintf(fname,"%s_0%i.root",filename,filenum);

	TChain *t = new TChain("t");
	t->Add(fname);
	//t->Add("data/frascatirun_01101.root");
	//t->Add("data/frascatirun_01102.root");
	//t->Add("data/frascatirun_01103.root");
	//t->Add("data/frascatirun_01104.root");
	//t->Add("data/frascatirun_01105.root");
	//t->Add("data/frascatirun_01106.root");
	//t->Add("data/frascatirun_01107.root");

	//gSystem->Setenv("LOCAL_FILES",(char*)gSystem->GetListOfFileHandlers ());
	if(gSystem->Getenv("LOCAL_FILES")!=NULL) {
		TString ftemp(gSystem->Getenv("LOCAL_FILES"));
		cout<<"ftemp=" <<ftemp<<endl;;
		TObjArray* foa = ftemp.Tokenize(" ");
		for(int i=0; i<foa->GetEntries(); i++) {
		  t->AddFile(((TObjString*) foa->At(i))->String().Data(),
					  TChain::kBigNumber);
		}
	}

	t->SetBranchAddress("caen_5742", &caen.system_clock);

	t->Print();

	if(entriesN<=0)
		entries = t->GetEntries();

	//out file
	outfile = new TFile("out_LM1.root","RECREATE");
	outTree = new TTree("tree","frascatirun output");
	outTree->Branch("LM_PX1",&fPositionX1,"PX1/D");
	outTree->Branch("LM_PX2",&fPositionX2,"PX2/D");
	outTree->Branch("LM_PY1",&fPositionY1,"PY1/D");
	outTree->Branch("LM_PY2",&fPositionY2,"PY2/D");
	outTree->Branch("LM_P2_Integral",&integralP2,"IP2/D");
	//outTree->Branch("baseline",baseline,"baseline[1024]/F");
	outTree->Branch("timeline",&timeline,"timeline/D");

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
			for (i = 0; i < nbins; ++i){
				g->SetPoint(i, i, caen.trace[channel][i]);
			}

			Double_t y_max = TMath::MaxElement(g->GetN(),g->GetY());
			source = new Double_t[nbins];
			dest = new Double_t[nbins];

			for (i = 0; i < nbins; ++i){
				source[i]=y_max-caen.trace[channel][i];
				g->SetPoint(i, i, source[i]);
			}

			//Use TSpectrum to find the peak candidates
			s = new TSpectrum();
		   	nfound = s->SearchHighRes(source, dest, nbins, 2, 20, kTRUE, 2, kFALSE, 5);

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
			for (int i = 0; i < nbins; i++) baseline[i] = source[i];
		    s->Background(baseline, ssize, numberIterations,	direction, filterOrder,	smoothing, smoothWindow, compton);

		    /**************************************
		     * Peaks and integral estimation
		     **************************************
		    */
		    Double_t px[2], py[2];
		    for (int i = 0; i < nbins; i++) dest[i] = source[i]-baseline[i];
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

			   //graphFit();
			   integralP2 = g->Integral (fPositionX2-10,fPositionX2+25);
		    }

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
				lmPeaks->Fill(fPositionY1/fPositionY2);
				outTree->Fill();
			}
	       //printf("time= %d, posx1= %d, posy1= %d\n",time, fPositionX1, fPositionY1);
	       //printf("time= %d, posx2= %d, posy2= %d\n",timeline, fPositionX2, fPositionY2);
		}
	}

	/**************************************
     * switch to the bottom pan and Draw Histogram
     **************************************
    */
	c1->cd(2);
	//lmPeaks->SetAxisRange(TMath::MinElement(entries,binmin),TMath::MaxElement(entries,binmax)+100);
	lmPeaks->SetAxisRange(0,4);
	lmPeaks->Draw();
	c1->Update();

	outfile->cd();
	gROOT->GetList()->Write();
	outTree->Write();
	outfile->Close();
}
