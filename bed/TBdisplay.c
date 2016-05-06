#include "TFile.h"
#include "TTree.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGraph.h"
#include <TAxis.h>
#include <TLine.h>
#include <iostream>
#include "Caen.h"
#include "TBconfig.h"
#include "TBtrace.h"

void TBdisplay(char* runfile, Int_t traceN)
{
	cout<<"enter TBdisplay"<<endl;
	//
	// Trace data storage
	Int_t TrLen = 1024;
	Int_t TrLen2= 500;
	Int_t TrLen3= 250000;
	// Open input file
	cout<<"Input file "<<runfile<<endl;
	TFile infile(runfile,"r");
	if(!infile.IsOpen())
	{
		cout<<"Can't open file "<<runfile<<endl;
		return;
	}
	cout<<"File:"<<runfile<<" opened"<<endl;
	//
	// Run configuration
	TBconfig *cnf= new TBconfig(runfile);
	Int_t nrun;
	nrun = cnf->GetNRun(); //exctract run number from file name
	char *ptype;
	ptype = cnf->GetConfType(traceN); // type of signal to process
	// Unpack root tree
	TTree *t = (TTree*) infile.Get("t");
	cout<<"Tree unpacked for run "<<nrun<<endl;
	//
	caen_5742  *caen;
	caen_5730  *caen2;
	caen_5730L *caen2L;
	if(nrun<conf4min)
	{
		caen = new caen_5742;
		//t->SetBranchAddress("caen_5742",&caen.system_clock);
		t->SetBranchAddress("caen_5742",caen);
	}
	cout<<"Got first branch"<<endl;
	if(nrun>=conf4min && nrun<=conf4max)
	{
		cout<<"Inside 5730L block"<<endl;
		caen2L = new caen_5730L;
		//t->SetBranchAddress("caen_5730",&caen2L.event_index);
		t->SetBranchAddress("caen_5730",caen2L);
		TrLen2 = TrLen3;
	}
	else if(nrun>=conf2min && nrun<=conf2max)
	{
		cout<<"Inside 5730 block"<<endl;
		caen2 = new caen_5730;
		//t->SetBranchAddress("caen_5730",&caen2.event_index);
		t->SetBranchAddress("caen_5730",caen2);
	}
	//
	Int_t nentries = t->GetEntries();
	cout<<"Got entries"<<endl;
	// Event loop
	Int_t Nev = -1;
	// Handle events
	Int_t count = 0;
	TString Command;
	TCanvas *Cdsp;
	TGraph* Gr;
	TLine** Li;
	TLine** Lh;
	do
	{
		cout<<"Enter command: n =new event, q= quit"<<endl;
		cin>>Command;
		if(Command == "n")
		{
			Nev++;
			cout<<"Event nr. "<<Nev<<endl;
			if(Nev < nentries)t->GetEntry(Nev);
			else
			{
				cout<<"No more data"<<endl;
				return;
			}
			// Copy trace
			// Process trace checking if given channel configuration belongs to digitizer caen 5742 or to digitizer caen 5730
			Double_t *data;
			Double_t *x;
			TBtrace *Tr;
			Int_t Tlen = 0;
			Int_t ich  = 0;
			Double_t sign = 1.0;
			if(traceN>=0 && traceN <=15)
			{
				Tlen = TrLen; ich = traceN;
				data = new Double_t[Tlen];
				for(Int_t j=0; j<Tlen; j++) 
				{
					data[j] = (Double_t) caen->trace[ich][j];
					if(j<10)cout<<"Data["<<j<<"] = "<<data[j]<<endl;
				}
				Tr = new TBtrace(Tlen,data,sign,ptype);
			}
			else if(traceN>=20 && traceN <=27)
			{
				Tlen = TrLen2; ich = traceN-20;
				cout<<"Tlen = "<<Tlen<<endl;
				data = new Double_t[Tlen];
				for(Int_t j=0; j<Tlen; j++)
				{
					if(nrun>=conf4min && nrun<=conf4max) data[j] = (Double_t) caen2L->trace[ich][j];
					else data[j] = (Double_t) caen2->trace[ich][j];
					if(j<50)cout<<"Data["<<j<<"] = "<<data[j]<<endl;
				}
				if(traceN == 26) sign = -1.0;
				Tr = new TBtrace(Tlen,data,sign,ptype);
			}
			//
			Int_t Nis = Tr->GetNpulse();
			Double_t base   = Tr->GetBaseline();
			Double_t sbase  = Tr->GetBaseSig();
			cout<<"Baseline = "<<base<<" +/- "<<sbase<<endl;
			for(Int_t k=0; k<Nis; k++)
			{
				Double_t charge = Tr->GetCharge(k);
				Double_t time   = Tr->GetTime(k);
				Double_t ampl   = Tr->GetAmpl(k);
				Double_t amplx  = Tr->GetAmplx(k);
				cout<<"Pulse #"<<k<<": Charge = "<<charge
					<<", time = "<<time
					<<", Ampl = "<<ampl
					<<", Amplx= "<<amplx
					<<endl;
			}
			//
			// Make plot
			//
			char title[50];
			sprintf(title,"Waveform display ch.%d - Event %d.",traceN,Nev);
			Cdsp = new TCanvas("Cdsp","BTF TB event display",50,50,500,500);
			x = new Double_t[Tlen];
			for(Int_t i=0; i<Tlen; i++) x[i] = (Double_t) i;
			Gr  = new TGraph(Tlen,x,data);
			Gr->SetTitle(title);
			Double_t xmin=0; Double_t xmax= (Double_t) Tlen;
			TAxis *tx = Gr->GetXaxis();
			tx->SetLimits(xmin,xmax);
			Gr->Draw("ACP");
			//
			Li  = new TLine*[Nis]; 
			Lh  = new TLine*[Nis];
			for(Int_t i=0; i<Nis; i++)
			{
				Double_t BaseA = Tr->GetBaseline();
				Int_t imin = Tr->GetXmin(i);
				Int_t imax = Tr->GetXmax(i);
				Li[i] = new TLine((Double_t) imin, BaseA, (Double_t) imax, BaseA);
				Li[i]->SetLineColor(kMagenta);
				Li[i]->SetLineWidth(4);
				Li[i]->Draw("SAME");
				Double_t time   = Tr->GetTime(i);
				Double_t ampl   = Tr->GetAmpl(i);
				Lh[i] = new TLine(time, BaseA, time, BaseA-sign*ampl);
				Lh[i]->SetLineColor(kRed);
				Lh[i]->SetLineWidth(2);
				Lh[i]->Draw("SAME");
			}
			Cdsp->Update();
			delete[] x;
			delete[] data;
			Tr->~TBtrace();
		}
	} while (Command != "q");
	//
	cout<<"Exiting program"<<endl;
}
