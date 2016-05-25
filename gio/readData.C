#include <iostream>

struct tree {
	Double_t LM_PX1;
	Double_t LM_PX2;
	Double_t LM_PY1;
	Double_t LM_PY2;
	Double_t LM_P2_Integral;
	Double_t timeline;
	//Float_t baseline[1024];
};

TChain *t;
TChain *t1;
tree intree;
Int_t nbins;
Int_t entries;
Int_t sleep;

void clearTree()
{
	intree.LM_PX1 = -999;
	intree.LM_PX2 = -999;
	intree.LM_PY1 = -999;
	intree.LM_PY2 = -999;
	intree.LM_P2_Integral = -999;
	intree.timeline = -999;
}

void makePlot(char* canv)
{
	t->SetBranchAddress("LM_PX1", &intree.LM_PX1);
	t->SetBranchAddress("LM_PX2", &intree.LM_PX2);
	t->SetBranchAddress("LM_PY1", &intree.LM_PY1);
	t->SetBranchAddress("LM_PY2", &intree.LM_PY2);
	t->SetBranchAddress("LM_P2_Integral", &intree.LM_P2_Integral);
	t->SetBranchAddress("time", &intree.timeline);
	t->Print();

	if(entries<=0)
		entries = t->GetEntries();

	char title[100]=0;
	sprintf(title,"%s runs 1100-1107",canv);
	TProfile *prof = new TProfile(title,title,24,0,entries);
	TProfile *prof1 = new TProfile(title,title,24,0,entries);
	TProfile *prof2 = new TProfile(title,title,24,0,entries);

	/**************************************
     * read entries
     **************************************
    */
	Double_t *ratio = new Double_t[entries];
	Double_t *parmean = new Double_t[entries];
	Double_t *p1 = new Double_t[entries];
	Double_t *p2 = new Double_t[entries];

	for (int j = 0; j < entries; ++j){
		gSystem->Sleep (sleep);
		t->GetEntry(j);
		ratio[j] = intree.LM_PY1/intree.LM_PY2;
		p1[j] = intree.LM_PY1;
		p2[j] = intree.LM_PY2;
		//cout<<"entry "<<j<<" peak2 "<<intree.LM_PY2<<endl;
	}

	Double_t mean = TMath::Mean(entries,ratio);
	Double_t mean1 = TMath::Mean(entries,p1);
	Double_t mean2 = TMath::Mean(entries,p2);
	for (int j = 0; j < entries; ++j){
		prof->Fill(j,(ratio[j]/mean-1)*100);
		prof1->Fill(j,(p1[j]/mean1-1)*100);
		prof2->Fill(j,(p2[j]/mean2-1)*100);
	}

	TCanvas *c1 = new TCanvas(canv,"frascatirun",900,700);
	c1->cd();

    char axisXname[100];
	sprintf(axisXname,"Time (Entries) (total: %i)",entries);
	prof->SetXTitle(axisXname);
	prof->SetYTitle("Variation (%)");
	prof->SetMaximum(1);
	prof->SetMinimum(-1);
	prof->SetMarkerColor(4);
	prof->SetMarkerSize(1);
	prof->SetMarkerStyle(8);
	prof->SetStats(kFALSE);
	prof->Draw();

	prof1->SetMarkerColor(5);
	prof1->SetMarkerSize(1);
	prof1->SetMarkerStyle(6);
	prof1->Draw("same");

	prof2->SetMarkerColor(1);
	prof2->SetMarkerSize(1);
	prof2->SetMarkerStyle(7);
	prof2->Draw("same");

/*	TLegend leg = new TLegend(0.1,0.7,0.48,0.9);
	leg->SetHeader("The Legend Title");
	leg->AddEntry(h1,"Histogram filled with random numbers","f");
	leg->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
	leg->AddEntry("gr","Graph with error bars","lep");
	leg->Draw("same");
*/
}

//Main function
void readData(
		char* filename = "./output/LM2_out", //input file name
		int filenum = 1100, 					//file number
		Double_t entriesN = 0,					//number of entries for prcessing
		int nsleep = 0							//sleep time between 2 processed entries, helpful for viewing traces
		)
{
	nbins = 1024;
	entries = entriesN;
	sleep = nsleep;

	// input file
    char fname[100]=0;
    sprintf(fname,"%s_0%i.root",filename,filenum);

    // TChain fill
	t = new TChain("tree");
	t->Add(fname);
	//t->Add("./output/LM2_out_01092.root");
	//t->Add("./output/LM2_out_01093.root");
	//t->Add("./output/LM2_out_01094.root");
	//t->Add("./output/LM2_out_01096.root");
	//t->Add("./output/LM2_out_01097.root");
	//t->Add("./output/LM2_out_01098.root");
	//t->Add("./output/LM2_out_01100.root");
	t->Add("./output/LM2_out_01101.root");
	t->Add("./output/LM2_out_01102.root");
	t->Add("./output/LM2_out_01103.root");
	t->Add("./output/LM2_out_01104.root");
	t->Add("./output/LM2_out_01105.root");
	t->Add("./output/LM2_out_01106.root");
	t->Add("./output/LM2_out_01107.root");
/*
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
*/
	//function that make plots
	makePlot("LM2");

	entries = entriesN;

	delete t;
	t = new TChain("tree");
	t1 = new TChain("ntuple");
	//t->Add("./output/LM1_out_01091.root");
	//t->Add("./output/LM1_out_01092.root");
	//t->Add("./output/LM1_out_01093.root");
	//t->Add("./output/LM1_out_01094.root");
	//t->Add("./output/LM1_out_01096.root");
	//t->Add("./output/LM1_out_01097.root");
	//t->Add("./output/LM1_out_01098.root");
	t->Add("./output/LM1_out_01100.root");
	t->Add("./output/LM1_out_01101.root");
	t->Add("./output/LM1_out_01102.root");
	t->Add("./output/LM1_out_01103.root");
	t->Add("./output/LM1_out_01104.root");
	t->Add("./output/LM1_out_01105.root");
	t->Add("./output/LM1_out_01106.root");
	t->Add("./output/LM1_out_01107.root");
	t1->Add("160229_160307_PTU.root");

	clearTree();

	//function that make plots
	makePlot("LM1");
}
