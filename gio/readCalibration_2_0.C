#include <iostream>
#include "Riostream.h"

struct tree {
	Double_t integralP2_mean;
	Double_t integralP2_sigma;
	Double_t integralP2_mean_error;
	Double_t integralP2_sigma_error;
};

void readCalibration_2_0(
		int lm = 1,			//LM num
		int nstart = 1081,	//start file
		int nfiles = 9		//num of files
		)
{
	tree intree;
	Float_t run[9],mean[9],mean_error[9],sigma[9],sigma_error[9],sigma2[9],sigma2_error[9];
    TFile* infile;
    char fname[100]=0;

	TFile *outf = new TFile("calibration.root","RECREATE");

	for (int i=0;i<nfiles;i++){
		sprintf(fname,"./calibration/LM%i_out_0%i.root",lm,nstart+i);
	    TFile *infile = new TFile(fname);
		cout<<fname<<endl;
	    TTree *t = (TTree*) infile->Get("LM_cal");
		t->SetBranchAddress("LM_P2_Integral_mean", &intree.integralP2_mean);
		t->SetBranchAddress("LM_P2_Integral_sigma", &intree.integralP2_sigma);
		t->SetBranchAddress("LM_P2_Integral_mean_error", &intree.integralP2_mean_error);
		t->SetBranchAddress("LM_P2_Integral_sigma_error", &intree.integralP2_sigma_error);

		t->Print();
		t->GetEntry(0);
		mean[i] = intree.integralP2_mean;
		sigma[i] = intree.integralP2_sigma;
		mean_error[i] = intree.integralP2_mean_error;
		sigma_error[i] = intree.integralP2_sigma_error;

	}

	for (int i=0;i<nfiles;i++) sigma2[i]=sigma[i]*sigma[i];
	for (int i=0;i<nfiles;i++) sigma2_error[i]=2*sigma[i]*sigma_error[i];

	TGraphErrors* g = new TGraphErrors(nfiles,mean,sigma2,mean_error,sigma2_error);
	g->SetMarkerColor(4);
	g->SetMarkerSize(1);
	g->SetMarkerStyle(7);
	char title[100];
	sprintf(title,"Calibration LM%i runs %i-%i",lm,nstart,nstart+nfiles-1);
	g->SetTitle(title);
	g->GetXaxis()->SetTitle("peaks integral mean");
	g->GetYaxis()->SetTitle("Variance");

	g->Draw("AP");

	outf->Write();
}
