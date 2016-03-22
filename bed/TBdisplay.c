
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGraph.h"
#include <TAxis.h>
#include <TLine.h>
#include <iostream>
#include "Caen.h"
#include "TBtrace.h"

using namespace std;

void TBdisplay(char* runfile, Int_t traceN)
{
	//
	// Trace data storage
	const Int_t TrLen = 1024;
	const Int_t TrLen2= 500;
	// Open input file
	cout<<"Input file "<<runfile<<endl;
	TFile infile(runfile,"r");
	// Unpack root tree
	TTree *t = (TTree*) infile.Get("t");
	caen_5742 caen;
	caen_5730 caen2;
	t->SetBranchAddress("caen_5742",&caen.system_clock);
	t->SetBranchAddress("caen_5730",&caen2.event_index);
	Int_t nentries = t->GetEntries();
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
			Double_t sign = 1;
			if(traceN>=0 && traceN <=15)
			{
				Tlen = TrLen; ich = traceN;
				data = new Double_t[Tlen];
				for(Int_t j=0; j<Tlen; j++) 
				{
					data[j] = (Double_t) caen.trace[ich][j];
					if(j<100)cout<<"Data["<<j<<"] = "<<data[j]<<endl;
				}
				Tr = new TBtrace(Tlen,data,sign);
			}
			else if(traceN>=20 && traceN <=27)
			{
				Tlen = TrLen2; ich = traceN-20;
				data = new Double_t[Tlen];
				for(Int_t j=0; j<Tlen; j++)
				{
					data[j] = (Double_t) caen2.trace[ich][j];
					if(j<100)cout<<"Data["<<j<<"] = "<<data[j]<<endl;
				}
				if(traceN == 26) sign = -1;
				Tr = new TBtrace(Tlen,data,sign);
			}
			//
			Int_t Nis = Tr->GetNpulse();
			for(Int_t k=0; k<Nis; k++)
			{
				Double_t base   = Tr->GetBaseline();
				Double_t charge = Tr->GetCharge(k);
				Double_t time   = Tr->GetTime(k);
				Double_t ampl   = Tr->GetAmpl(k);
				cout<<"Pulse #"<<k<<": Charge = "<<charge
					<<", time = "<<time
					<<", Ampl = "<<ampl
					<<", base = "<<base
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
	cout<<"Exiting program"<<endl;
}
