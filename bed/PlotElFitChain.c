

#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TF1.h>
#include <TF2.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
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
	t->SetBranchAddress("SiPMbot_te",SiPMbot_te);

	//SiPM left

	t->SetBranchAddress("NpSiL",&NpSiL);
	t->SetBranchAddress("SiPMlef_q",SiPMlef_q);
	t->SetBranchAddress("SiPMlef_a",SiPMlef_a);
	t->SetBranchAddress("SiPMlef_t",SiPMlef_t);
	t->SetBranchAddress("SiPMlef_te",SiPMlef_te);

	//SiPM central

	t->SetBranchAddress("NpSiC",&NpSiC);
	t->SetBranchAddress("SiPMcen_q",SiPMcen_q);
	t->SetBranchAddress("SiPMcen_a",SiPMcen_a);
	t->SetBranchAddress("SiPMcen_t",SiPMcen_t);
	t->SetBranchAddress("SiPMcen_te",SiPMcen_te);

	//SiPM right

	t->SetBranchAddress("NpSiR",&NpSiR);
	t->SetBranchAddress("SiPMrig_q",SiPMrig_q);
	t->SetBranchAddress("SiPMrig_a",SiPMrig_a);
	t->SetBranchAddress("SiPMrig_t",SiPMrig_t);
	t->SetBranchAddress("SiPMrig_te",SiPMrig_te);

	//SiPM top 

	t->SetBranchAddress("NpSiT",&NpSiT);
	t->SetBranchAddress("SiPMtop_q",SiPMtop_q);
	t->SetBranchAddress("SiPMtop_a",SiPMtop_a);
	t->SetBranchAddress("SiPMtop_t",SiPMtop_t);
	t->SetBranchAddress("SiPMtop_te",SiPMtop_te);

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
/*
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
//
Double_t fFit(Double_t *x, Double_t *p)
{
	Double_t q  = x[0];
	//
	Double_t A   = p[0];		// Normalization factor
	Double_t mu  = p[1];		// Signle electron peak
	Double_t k   = p[2];		// Photoelectrons conversion (mu = Npe*k)
	Double_t Sn	 = p[3];		// Electronic noise
	Double_t Pm1 = p[4];		// Mean of Poisson distribution electrons
	Double_t Pm2 = p[5];		// Mean of Poisson distribution positrons
	Double_t frp = p[6];		// positron fraction
	//
	Double_t Val = 0; Double_t Fact = 1;
	for(Int_t n=1; n<10; n++)	// loop on numbero of electrons
	{
		Fact *= n;
		Double_t Prob1 = TMath::Exp(-Pm1)*pow(Pm1,n)/Fact;
		Double_t Prob2 = TMath::Exp(-Pm2)*pow(Pm2,n)/Fact;
		Double_t Prob = (1-frp)*Prob1+frp*Prob2;
		Double_t m = mu*n;
		Double_t Sig = TMath::Sqrt(Sn*Sn+m*k);
		Double_t Arg = 0.5*(q-m)*(q-m)/(Sig*Sig);
		if(Arg<30)Val += A*Prob*TMath::Exp(-Arg)/Sig;
	}
	//
	return Val;
}
*/
//
Double_t fFit(Double_t *x, Double_t *p)
{
	//
	Double_t A1   = p[0];		// Normalization factor 1
	Double_t A2   = p[1];		// Normalization factor 2
	Double_t A3   = p[2];		// Normalization factor 3
	Double_t A4	  = p[3];		// Normalization factor 4
	Double_t A5   = p[4];		// Normalization factor 5
	Double_t A6   = p[5];		// Normalization factor 6
	Double_t mu	  = p[6];		// Single electron peak
	Double_t k	  = p[7];		// Width calibration (S^2 = Snoise^2+k*mu)
	Double_t Shf  = p[8];		// Shift
	//
	Double_t q  = x[0] - Shf;
	//
	Double_t A[6] = {A1,A2,A3,A4,A5,A6};
	//
	Double_t Val = 0; 
	for(Int_t n=0; n<6; n++)	// loop on numbero of electrons
	{
		Double_t m = mu*(n+1);
		Double_t Sig = TMath::Sqrt(m*k);
		Double_t Arg = 0.5*(q-m)*(q-m)/(Sig*Sig);
		if(Arg<30)Val += A[n]*TMath::Exp(-Arg)/Sig;
	}
	//
	return Val;
}
//
//
Double_t fFit2(Double_t *x, Double_t *p)
{
	//
	Double_t A1   = p[0];		// Normalization factor 1
	Double_t A2   = p[1];		// Normalization factor 2
	Double_t A3   = p[2];		// Normalization factor 3
	Double_t A4	  = p[3];		// Normalization factor 4
	Double_t A5   = p[4];		// Normalization factor 5
	Double_t A6   = p[5];		// Normalization factor 6
	Double_t mu	  = p[6];		// Single electron peak
	Double_t k	  = p[7];		// Width calibration (S^2 = Snoise^2+k*mu)
	Double_t t1   = p[8];		// Reference pulse width 1 el
	Double_t tn   = p[9];		// Reference pulse width n el
	Double_t Sigt = p[10];		// Time difference distribution sigma
	Double_t s[6];
	s[0]		  = p[11];		// width dependence 1 electron
	s[1]		  = p[12];		// width dependence 2 electron
	s[2]		  = p[13];		// width dependence 3 electron
	s[3]		  = p[14];		// width dependence 4 electron
	s[4]		  = p[15];		// width dependence 5 electron
	s[5]		  = p[16];		// width dependence 6 electron
	//
	Double_t q  = x[1];
	Double_t t  = x[0];
	//
	Double_t A[6] = {A1,A2,A3,A4,A5,A6};
	//
	Double_t Val = 0; 
	for(Int_t n=0; n<6; n++)	// loop on numbero of electrons
	{
		Double_t m = mu*(n+1);
		if(n==0) m += s[n]*(t-t1);
		else m += s[n]*(t-tn);
		Double_t Sig = TMath::Sqrt(m*k);
		Double_t Arg1 = 0.5*(q-m)*(q-m)/(Sig*Sig);
		Double_t Arg2;
		if(n==0)Arg2 = 0.5*(t-t1)*(t-t1)/(Sigt*Sigt);
		else Arg2 = 0.5*(t-tn)*(t-tn)/(Sigt*Sigt);
		if(Arg1<30&&Arg2<30)Val += A[n]*TMath::Exp(-Arg1)*TMath::Exp(-Arg2)/(Sig*Sigt);
	}
	//
	return Val;
}
void PlotElFitChain(char *inList){

// calibration parameter for SiPMS
const Double_t calibbot= 4.7; 
const Double_t calibtop= 5.5;
const Double_t caliblef= 4.6;
const Double_t calibcen= 4.1;
const Double_t calibrig= 5.1;
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
	TH1D *histo= new TH1D("histo","Spectrum",400,0,10000);
	TH1D *hc= new TH1D("hc","Spectrum C",400,0,10000);
	TH1D *hl= new TH1D("hl","Spectrum L",400,0,10000);
	TH1D *hr= new TH1D("hr","Spectrum R",400,0,10000);
	TH1D *ht= new TH1D("ht","Spectrum T",400,0,10000);
	TH1D *hb= new TH1D("hb","Spectrum B",400,0,10000);
	//
	TH2D *hqt  = new TH2D("hqt","Correlations",50,0.5,50.5,100,0.,10000.);
	TH2D *hqt1 = new TH2D("hqt1","Correlations peak1",50,0.5,50.5,100,0.,2500.);
	TH2D *hqt2 = new TH2D("hqt2","Correlations peak2",50,0.5,50.5,100,2500.,4000.);
	TH2D *hqt3 = new TH2D("hqt3","Correlations peak3",50,0.5,50.5,100,4000.,5800.);
	TH2D *hqt4 = new TH2D("hqt4","Correlations peak4",50,0.5,50.5,100,5800.,7600.);
	TH2D *hqt5 = new TH2D("hqt5","Correlations peak5",50,0.5,50.5,100,7600.,9500.);
	//
	Int_t nentries= chn->GetEntries();
	Int_t Ndum = 10;
	cout << "Nentries = " << nentries << endl;
	for(Int_t i=0;i<nentries;i++)
	{
		chn->GetEntry(i);
		//
		if(NpTrL==0 && NpTrA==0)				// laser and americium condition
		{  
			Double_t esum = 0;

			if(NpSiC == 1) 
			{
				hc->Fill(SiPMcen_q[0]);
				esum += SiPMcen_q[0];
			}
			if(NpSiL == 1) 
			{
				hl->Fill(SiPMlef_q[0]);
				esum += SiPMlef_q[0]*calibcen/caliblef;
			}
			if(NpSiR == 1)
			{
				hr->Fill(SiPMrig_q[0]);
				esum += SiPMrig_q[0]*calibcen/calibrig;
			}
			if(NpSiB == 1) 
			{
				hb->Fill(SiPMbot_q[0]);
				esum += SiPMbot_q[0]*calibcen/calibbot;
			}
			if(NpSiT == 1) 
			{
				ht->Fill(SiPMtop_q[0]);
				esum += SiPMtop_q[0]*calibcen/calibtop;
			}
			histo->Fill(esum);
			hqt->Fill(SiPMcen_te[0]-SiPMcen_t[0],esum);
			if(esum<2500) hqt1->Fill(SiPMcen_te[0]-SiPMcen_t[0],esum);
			if(esum>2500 && esum<4000) hqt2->Fill(SiPMcen_te[0]-SiPMcen_t[0],esum);
			if(esum>4000 && esum<5800) hqt3->Fill(SiPMcen_te[0]-SiPMcen_t[0],esum);
			if(esum>5800 && esum<7600) hqt4->Fill(SiPMcen_te[0]-SiPMcen_t[0],esum);
			if(esum>7600 && esum<9500) hqt5->Fill(SiPMcen_te[0]-SiPMcen_t[0],esum);
		}									// end of laser and americium condition

	}
	//
	// Fit histograms
	//
	TF1* fc = new TF1("fc",fFit,0.0,10000.0,9);
	fc->SetParName(0,"Norm1");
	fc->SetParName(1,"Norm2");
	fc->SetParName(2,"Norm3");
	fc->SetParName(3,"Norm4");
	fc->SetParName(4,"Norm5");
	fc->SetParName(5,"Norm6");
	fc->SetParName(6,"Electron peak");
	fc->SetParName(7,"Npe conversion");
	fc->SetParName(8,"Shift");
	Double_t pc[9] = {2e4,1e5,1e5,6e4,2e4,1e4,1500,18,0};
	fc->SetParameters(pc);
	fc->SetNpx(400);
	hc->Fit("fc");
	//
	TF1* fall = new TF1("fall",fFit,0.0,10000.,9);
	fall->SetParName(0,"Norm1");
	fall->SetParName(1,"Norm2");
	fall->SetParName(2,"Norm3");
	fall->SetParName(3,"Norm4");
	fall->SetParName(4,"Norm5");
	fall->SetParName(5,"Norm6");
	fall->SetParName(6,"Electron peak");
	fall->SetParName(7,"Npe conversion");
	fall->SetParName(8,"Shift");
	Double_t pall[9] = {2e4,1e5,1e5,6e4,2e4,1e4,1500,18,0};
	fall->SetParameters(pall);
	fall->SetNpx(400);
	histo->Fit("fall");
	//
	Double_t peak1 = fall->GetParameter(6);
	Double_t peak2 = 2*fall->GetParameter(6);
	Double_t peak3 = 3*fall->GetParameter(6);
	Double_t peak4 = 4*fall->GetParameter(6);
	Double_t peak5 = 5*fall->GetParameter(6);
	//
	//
	//
	TCanvas *Cnv = new TCanvas("Cnv","Electron signal",100,100,800,500);
	Cnv->Divide(2,2);
	Cnv->cd(1); hc->Draw("E");
	Cnv->cd(2); hl->Draw();
	Cnv->cd(3); hr->Draw();
	Cnv->cd(4); hb->Draw();
	//
	TCanvas *Cnv1 = new TCanvas("Cnv1","Electron signal 1",200,200,800,500);
	Cnv1->Divide(1,1);
	Cnv1->cd(1);  histo->Draw("E");
	//
	TCanvas *Cnv2 = new TCanvas("Cnv2","Electron signal vs Dt",300,250,800,500);
	Cnv2->Divide(1,1);
	Cnv2->cd(1);
	hqt->Draw();
	//
	TCanvas *Cnv3 = new TCanvas("Cnv3","Electron signal vs Dt profiles",350,300,800,500);
	Cnv3->Divide(2,2);
	Cnv3->cd(1);
	TProfile *hqt1_pfx = hqt1->ProfileX(); hqt1_pfx->Fit("pol1","","",11,19);
	Cnv3->cd(2);
	TProfile *hqt2_pfx = hqt2->ProfileX(); hqt2_pfx->Fit("pol1","","",11,19);
	Cnv3->cd(3);
	TProfile *hqt3_pfx = hqt3->ProfileX(); hqt3_pfx->Fit("pol1","","",11,19);
	Cnv3->cd(4);
	TProfile *hqt4_pfx = hqt4->ProfileX(); hqt4_pfx->Fit("pol1","","",11,19);
	//
	TCanvas *Cnv4 = new TCanvas("Cnv4","Electron signal vs Dt profiles",400,350,800,500);
	//
	// 2 dimensional fit
	//
	TF2* f2all = new TF2("f2all",fFit2,10.,25.,0.,10000.,17);
	f2all->SetParName(0,"Norm1");
	f2all->SetParName(1,"Norm2");
	f2all->SetParName(2,"Norm3");
	f2all->SetParName(3,"Norm4");
	f2all->SetParName(4,"Norm5");
	f2all->SetParName(5,"Norm6");
	f2all->SetParName(6,"Electron peak");
	f2all->SetParName(7,"Npe conversion");
	f2all->SetParName(8,"t1");
	f2all->SetParName(9,"tn");
	f2all->SetParName(10,"Sigma t");
	f2all->SetParName(11,"s1");
	f2all->SetParName(12,"s2");
	f2all->SetParName(13,"s3");
	f2all->SetParName(14,"s4");
	f2all->SetParName(15,"s5");
	f2all->SetParName(16,"s6");
	Double_t p2all[17];
	for(Int_t i=0; i<8; i++) p2all[i]= fall->GetParameter(i);
	p2all [8] = 13;
	p2all [9] = 15;
	p2all[10] =  2;
	p2all[11] =  14;
	p2all[12] = -17;
	p2all[13] = -13;
	p2all[14] = -13;
	p2all[15] = -13;
	p2all[16] = -13;
	f2all->SetParameters(p2all);
	f2all->SetNpx(400);
	hqt->Fit("f2all");
	Cnv4->Divide(1,1);
	Cnv4->cd(1);
	hqt->Draw("CONT");
}
