

#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
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

void PlotEl(char *inData){

// calibration parameter for SiPMS
const Double_t calibbot= 5.5;
const Double_t calibtop= 5.5;
const Double_t caliblef= 6.0;
const Double_t calibcen= 5.0;
const Double_t calibrig= 5.0;
//
	TFile *fin = new TFile(inData,"read");
	TTree *t = (TTree *) fin->Get("tNTP");
	LoadBranches(t);
	//
	TH1D *histo= new TH1D("histo","Spectrum",100,0,3000);
	TH1D *hc= new TH1D("hc","Spectrum C",100,0,15000);
	TH1D *hl= new TH1D("hl","Spectrum L",100,0,15000);
	TH1D *hr= new TH1D("hr","Spectrum R",100,0,15000);
	TH1D *ht= new TH1D("ht","Spectrum T",100,0,15000);
	TH1D *hb= new TH1D("hb","Spectrum B",100,0,15000);
	//
	Int_t nentries= t->GetEntries();
	Int_t Ndum = 10;
	cout << " nentries" << nentries << endl;
	for(Int_t i=0;i<nentries;i++)
	{
		t->GetEntry(i);
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
				hc->Fill(SiPMtop_q[0]);
				esum += SiPMtop_q[0]/calibtop;
			}
			histo->Fill(esum);
			
		}									// end of laser and americium condition

	}
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
