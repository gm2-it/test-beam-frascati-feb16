

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include "TBntple.h"

  
void LoadBranches(TTree *t)
{
	// Clock
	t->SetBranchAddress("LabTime",&LabTime);
	//PIN 1
	t->SetBranchAddress("NpPIN1",&NpPIN1);
	t->SetBranchAddress("PIN1_q",PIN1_q);
	t->SetBranchAddress("PIN1_a",PIN1_a);
	t->SetBranchAddress("PIN1_t",PIN1_t);

	//PIN2
	t->SetBranchAddress("NpPIN2",&NpPIN2);
	t->SetBranchAddress("PIN2_q",PIN2_q);
	t->SetBranchAddress("PIN2_a",PIN2_a);
	t->SetBranchAddress("PIN2_t",PIN2_t);

	//Source Monitor

	t->SetBranchAddress("NpSM",&NpSM);
	t->SetBranchAddress("SM_q",SM_q);
	t->SetBranchAddress("SM_a",SM_a);
	t->SetBranchAddress("SM_t",SM_t);

	//HAM

	t->SetBranchAddress("NpHAM",&NpHAM);
	t->SetBranchAddress("HAM_q",HAM_q);
	t->SetBranchAddress("HAM_a",HAM_a);
	t->SetBranchAddress("HAM_t",HAM_t);

	//Local Monitor 1

	t->SetBranchAddress("NpLM1",&NpLM1);
	t->SetBranchAddress("LM1_q",LM1_q);
	t->SetBranchAddress("LM1_a",LM1_a);
	t->SetBranchAddress("LM1_t",LM1_t);

	//Local Monitor 2

	t->SetBranchAddress("NpLM2",&NpLM2);
	t->SetBranchAddress("LM2_q",LM2_q);
	t->SetBranchAddress("LM2_a",LM2_a);
	t->SetBranchAddress("LM2_t",LM2_t);

	//SiPM bottom

	t->SetBranchAddress("NpSiB",&NpSiB);
	t->SetBranchAddress("SiPMbot_q",SiPMbot_q);
	t->SetBranchAddress("SiPMbot_a",SiPMbot_a);
	t->SetBranchAddress("SiPMbot_t",SiPMbot_t);

	//SiPM left

	t->SetBranchAddress("NpSiL",&NpSiL);
	t->SetBranchAddress("SiPMlef_q",SiPMlef_q);
	t->SetBranchAddress("SiPMlef_a",SiPMlef_a);
	t->SetBranchAddress("SiPMlef_t",SiPMlef_t);

	//SiPM central

	t->SetBranchAddress("NpSiC",&NpSiC);
	t->SetBranchAddress("SiPMcen_q",SiPMcen_q);
	t->SetBranchAddress("SiPMcen_a",SiPMcen_a);
	t->SetBranchAddress("SiPMcen_t",SiPMcen_t);

	//SiPM right

	t->SetBranchAddress("NpSiR",&NpSiR);
	t->SetBranchAddress("SiPMrig_q",SiPMrig_q);
	t->SetBranchAddress("SiPMrig_a",SiPMrig_a);
	t->SetBranchAddress("SiPMrig_t",SiPMrig_t);

	//SiPM top 

	t->SetBranchAddress("NpSiT",&NpSiT);
	t->SetBranchAddress("SiPMtop_q",SiPMtop_q);
	t->SetBranchAddress("SiPMtop_a",SiPMtop_a);
	t->SetBranchAddress("SiPMtop_t",SiPMtop_t);

	//laser trigger


	t->SetBranchAddress("NpTrL",&NpTrL);
	t->SetBranchAddress("TrigL_q",TrigL_q);
	t->SetBranchAddress("TrigL_a",TrigL_a);
	t->SetBranchAddress("TrigL_t",TrigL_t);


	//Am trigger

	t->SetBranchAddress("NpTrA",&NpTrA);
	t->SetBranchAddress("TrigA_q",TrigA_q);
	t->SetBranchAddress("TrigA_a",TrigA_a);
	t->SetBranchAddress("TrigA_t",TrigA_t);


	//Global trigger

	t->SetBranchAddress("NpTrG",&NpTrG);
	t->SetBranchAddress("TrigG_q",TrigG_q);
	t->SetBranchAddress("TrigG_a",TrigG_a);
	t->SetBranchAddress("TrigG_t",TrigG_t);


	//horizontal finger

	t->SetBranchAddress("NpHF",&NpHF);
	t->SetBranchAddress("HF_q",HF_q);
	t->SetBranchAddress("HF_a",HF_a);
	t->SetBranchAddress("HF_t",HF_t);

	//vertical finger

	t->SetBranchAddress("NpVF",&NpVF);
	t->SetBranchAddress("VF_q",VF_q);
	t->SetBranchAddress("VF_a",VF_a);
	t->SetBranchAddress("VF_t",VF_t);
} 

 
void LoadBranches_Chain(TChain *t)
{
	// Clock
	t->SetBranchAddress("LabTime",&LabTime);
	//PIN 1
	t->SetBranchAddress("NpPIN1",&NpPIN1);
	t->SetBranchAddress("PIN1_q",PIN1_q);
	t->SetBranchAddress("PIN1_a",PIN1_a);
	t->SetBranchAddress("PIN1_t",PIN1_t);

	//PIN2
	t->SetBranchAddress("NpPIN2",&NpPIN2);
	t->SetBranchAddress("PIN2_q",PIN2_q);
	t->SetBranchAddress("PIN2_a",PIN2_a);
	t->SetBranchAddress("PIN2_t",PIN2_t);

	//Source Monitor

	t->SetBranchAddress("NpSM",&NpSM);
	t->SetBranchAddress("SM_q",SM_q);
	t->SetBranchAddress("SM_a",SM_a);
	t->SetBranchAddress("SM_t",SM_t);

	//HAM

	t->SetBranchAddress("NpHAM",&NpHAM);
	t->SetBranchAddress("HAM_q",HAM_q);
	t->SetBranchAddress("HAM_a",HAM_a);
	t->SetBranchAddress("HAM_t",HAM_t);

	//Local Monitor 1

	t->SetBranchAddress("NpLM1",&NpLM1);
	t->SetBranchAddress("LM1_q",LM1_q);
	t->SetBranchAddress("LM1_a",LM1_a);
	t->SetBranchAddress("LM1_t",LM1_t);

	//Local Monitor 2

	t->SetBranchAddress("NpLM2",&NpLM2);
	t->SetBranchAddress("LM2_q",LM2_q);
	t->SetBranchAddress("LM2_a",LM2_a);
	t->SetBranchAddress("LM2_t",LM2_t);

	//SiPM bottom

	t->SetBranchAddress("NpSiB",&NpSiB);
	t->SetBranchAddress("SiPMbot_q",SiPMbot_q);
	t->SetBranchAddress("SiPMbot_a",SiPMbot_a);
	t->SetBranchAddress("SiPMbot_t",SiPMbot_t);

	//SiPM left

	t->SetBranchAddress("NpSiL",&NpSiL);
	t->SetBranchAddress("SiPMlef_q",SiPMlef_q);
	t->SetBranchAddress("SiPMlef_a",SiPMlef_a);
	t->SetBranchAddress("SiPMlef_t",SiPMlef_t);

	//SiPM central

	t->SetBranchAddress("NpSiC",&NpSiC);
	t->SetBranchAddress("SiPMcen_q",SiPMcen_q);
	t->SetBranchAddress("SiPMcen_a",SiPMcen_a);
	t->SetBranchAddress("SiPMcen_t",SiPMcen_t);

	//SiPM right

	t->SetBranchAddress("NpSiR",&NpSiR);
	t->SetBranchAddress("SiPMrig_q",SiPMrig_q);
	t->SetBranchAddress("SiPMrig_a",SiPMrig_a);
	t->SetBranchAddress("SiPMrig_t",SiPMrig_t);

	//SiPM top 

	t->SetBranchAddress("NpSiT",&NpSiT);
	t->SetBranchAddress("SiPMtop_q",SiPMtop_q);
	t->SetBranchAddress("SiPMtop_a",SiPMtop_a);
	t->SetBranchAddress("SiPMtop_t",SiPMtop_t);

	//laser trigger


	t->SetBranchAddress("NpTrL",&NpTrL);
	t->SetBranchAddress("TrigL_q",TrigL_q);
	t->SetBranchAddress("TrigL_a",TrigL_a);
	t->SetBranchAddress("TrigL_t",TrigL_t);


	//Am trigger

	t->SetBranchAddress("NpTrA",&NpTrA);
	t->SetBranchAddress("TrigA_q",TrigA_q);
	t->SetBranchAddress("TrigA_a",TrigA_a);
	t->SetBranchAddress("TrigA_t",TrigA_t);


	//Global trigger

	t->SetBranchAddress("NpTrG",&NpTrG);
	t->SetBranchAddress("TrigG_q",TrigG_q);
	t->SetBranchAddress("TrigG_a",TrigG_a);
	t->SetBranchAddress("TrigG_t",TrigG_t);


	//horizontal finger

	t->SetBranchAddress("NpHF",&NpHF);
	t->SetBranchAddress("HF_q",HF_q);
	t->SetBranchAddress("HF_a",HF_a);
	t->SetBranchAddress("HF_t",HF_t);

	//vertical finger

	t->SetBranchAddress("NpVF",&NpVF);
	t->SetBranchAddress("VF_q",VF_q);
	t->SetBranchAddress("VF_a",VF_a);
	t->SetBranchAddress("VF_t",VF_t);
} 

Double_t fFit(Double_t *x, Double_t *p)
{
	Double_t q  = x[0];
	//
	Double_t A   = p[0];		// Normalization factor
	Double_t mu  = p[1];		// Signle electron peak
	Double_t k   = p[2];		// Photoelectrons conversion (mu = Npe*k)
	Double_t Sn	 = p[3];		// Electronic noise
	Double_t Pm  = p[4];		// Mean of Poisson distribution
	Double_t e50 = p[5];		// Turn on 50% point
	Double_t eSg = p[6];		// Efficiency width
	//
	Double_t Val = 0; Double_t Fact = 1;
	for(Int_t n=1; n<10; n++)	// loop on numbero of electrons
	{
		Fact *= n;
		Double_t Eff = TMath::Freq((q-e50)/eSg);
		Double_t Prob = TMath::Exp(-Pm)*pow(Pm,n)/Fact;
		Double_t m = mu*n;
		Double_t Sig = TMath::Sqrt(Sn*Sn+m*k);
		Double_t Arg = 0.5*(q-m)*(q-m)/(Sig*Sig);
		if(Arg<30)Val += A*Eff*Prob*TMath::Exp(-Arg)/Sig;
	}
	//
	return Val;
}

void PlotElFitChain(char *inList){

// calibration parameter for SiPMS
const Double_t calibbot= 5.5;
const Double_t calibtop= 5.5;
const Double_t caliblef= 6.0;
const Double_t calibcen= 5.0;
const Double_t calibrig= 5.0;
//
char FileName[50];

	FILE *inFile;
	inFile = fopen(inList,"r");	// Open runlist
	cout<<"Opening "<<inList<<endl;
	if(!inFile){cout<<"Error opening run list.  inFile = "<<inFile<<endl; return;}
	//
	TChain *chn = new TChain("tNTP");
	LoadBranches_Chain(chn);
	while(fscanf(inFile,"%s",&FileName) != EOF)
	{
		cout<<"Adding file: "<<FileName<<endl;
		chn->Add(FileName);
	}
	fclose(inFile);
	//
	TH1D *histo= new TH1D("histo","Spectrum",100,0,2000);
	TH1D *hc= new TH1D("hc","Spectrum C",100,0,10000);
	TH1D *hl= new TH1D("hl","Spectrum L",100,0,10000);
	TH1D *hr= new TH1D("hr","Spectrum R",100,0,10000);
	TH1D *ht= new TH1D("ht","Spectrum T",100,0,10000);
	TH1D *hb= new TH1D("hb","Spectrum B",100,0,10000);
	//
	Int_t nentries= chn->GetEntries();
	Int_t Ndum = 10;
	cout << "Nentries = " << nentries << endl;
	for(Int_t i=0;i<nentries;i++)
	{
		chn->GetEntry(i);
		/*
		if(i<10)
		{
			cout<<"Event nr. "<<i<<endl;
			cout<<"NpTrL: "<<NpTrL<<", NpTrA: "<<NpTrA<<", NpTrG: "<<NpTrG<<endl;
			cout<<"NpSiC: "<<NpSiC<<", NpSiL: "<<NpSiL<<", NpSiR: "<<NpSiR<<endl;
			if(NpSiC>0)cout<<"SiPMcen_q[0]: "<<SiPMcen_q[0]<<endl;
			if(NpSiL>0)cout<<"SiPMlef_q[0]: "<<SiPMlef_q[0]<<endl;
			if(NpSiR>0)cout<<"SiPMrig_q[0]: "<<SiPMrig_q[0]<<endl;
			if(NpSiT>0)cout<<"SiPMtop_q[0]: "<<SiPMtop_q[0]<<endl;
			if(NpSiB>0)cout<<"SiPMbot_q[0]: "<<SiPMbot_q[0]<<endl;
			
		}*/
		//
		if(NpTrL==0 && NpTrA==0)				// laser and americium condition
		{  
			Double_t esum = 0;

			if(NpSiC == 1) 
			{
				hc->Fill(SiPMcen_q[0]);
				esum += SiPMcen_q[0]/calibcen;
			}
			if(NpSiL == 1) 
			{
				hl->Fill(SiPMlef_q[0]);
				esum += SiPMlef_q[0]/caliblef;
			}
			if(NpSiR == 1)
			{
				hr->Fill(SiPMrig_q[0]);
				esum += SiPMrig_q[0]/calibrig;
			}
			if(NpSiB == 1) 
			{
				hb->Fill(SiPMbot_q[0]);
				esum += SiPMbot_q[0]/calibbot;
			}
			if(NpSiT == 1) 
			{
				ht->Fill(SiPMtop_q[0]);
				esum += SiPMtop_q[0]/calibtop;
			}
			histo->Fill(esum);
		}									// end of laser and americium condition

	}
	//
	// Fit histograms
	//
	TF1* fc = new TF1("fc",fFit,0.,10000,7);
	fc->SetParName(0,"Norm");
	fc->SetParName(1,"Electron peak");
	fc->SetParName(2,"Npe conversion");
	fc->SetParName(3,"Noise");
	fc->SetParName(4,"Poisson mean");
	fc->SetParName(5,"Efficiency mean");
	fc->SetParName(6,"Efficiency sigma");
	Double_t pc[7] = {1e6,1100.,10.,250.,2.5,35.,100.};
	fc->SetParameters(pc);
	hc->Fit("fc");

	TF1* fr = new TF1("fr",fFit,0.,10000,7);
	fr->SetParName(0,"Norm");
	fr->SetParName(1,"Electron peak");
	fr->SetParName(2,"Npe conversion");
	fr->SetParName(3,"Noise");
	fr->SetParName(4,"Poisson mean");
	fr->SetParName(5,"Efficiency mean");
	fr->SetParName(6,"Efficiency sigma");
	Double_t pr[7] = {1e5,800.,10.,250.,2.0,350.,100.};
	fr->SetParameters(pr);
	hr->Fit("fr");

	TF1* fl = new TF1("fl",fFit,0.,10000,7);
	fl->SetParName(0,"Norm");
	fl->SetParName(1,"Electron peak");
	fl->SetParName(2,"Npe conversion");
	fl->SetParName(3,"Noise");
	fl->SetParName(4,"Poisson mean");
	fl->SetParName(5,"Efficiency mean");
	fl->SetParName(6,"Efficiency sigma");
	Double_t pl[7] = {1e5,500.,10.,250.,0.2,350.,100.};
	fl->SetParameters(pl);
	hl->Fit("fl");

	TF1* fb = new TF1("fb",fFit,0.,10000,7);
	fb->SetParName(0,"Norm");
	fb->SetParName(1,"Electron peak");
	fb->SetParName(2,"Npe conversion");
	fb->SetParName(3,"Noise");
	fb->SetParName(4,"Poisson mean");
	fb->SetParName(5,"Efficiency mean");
	fb->SetParName(6,"Efficiency sigma");
	Double_t pb[7] = {1e5,500.,10.,250.,0.1,350.,100.};
	fb->SetParameters(pb);
	hb->Fit("fb");
	
	TF1* fall = new TF1("fall",fFit,0.,2000,7);
	fall->SetParName(0,"Norm");
	fall->SetParName(1,"Electron peak");
	fall->SetParName(2,"Npe conversion");
	fall->SetParName(3,"Noise");
	fall->SetParName(4,"Poisson mean");
	fall->SetParName(5,"Efficiency mean");
	fall->SetParName(6,"Efficiency sigma");
	Double_t pall[7] = {4e5,230.,6.,40.,2.5,100.,100.};
	fall->SetParameters(pall);
	histo->Fit("fall");
	//
	//
	//
	TCanvas *Cnv = new TCanvas("Cnv","Electron signal",100,100,800,500);
	Cnv->Divide(2,2);
	Cnv->cd(1); hc->Draw();
	Cnv->cd(2); hl->Draw();
	Cnv->cd(3); hr->Draw();
	Cnv->cd(4); hb->Draw();
	//
	TCanvas *Cnv1 = new TCanvas("Cnv1","Electron signal 1",200,200,800,500);
	Cnv1->Divide(1,1);
	Cnv1->cd(1);  histo->Draw();
}
