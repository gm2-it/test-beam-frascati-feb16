#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include "Caen.h"
#include "TBtrace.h"
#include "TBmakeNTP.h"
#include "TBconfig.h"

using namespace std;

void TBgenNTP(char* runfile, char* cFile)
{
	//
	TBconfig *ch= new TBconfig(runfile); // channel analyzer
	//
	// OUTPUT DATA MANAGEMENT
	//
	// Prepare output file
	TFile OutF(cFile,"recreate");
	//
	// prepare NTple tree
	char tID[10]    = "tNTP";		// tree ID
	char tTitle[50] = "Reconstructed pulses type FB";	// Tree title
	TBmakeNTP *ntple  = new TBmakeNTP(tID,tTitle);		// Create class
	TTree *tNTP = ntple->NTPsetup();
	// Setup tree structure
	//
	//	INPUT DATA MANAGEMENT
	//
	// Open input file
	cout<<"Input file "<<runfile<<endl;
	TFile infile(runfile,"r");
	//short routine to extract file number
	Int_t nrun;
	nrun = ch->GetNRun(); //exctract run number from file name
	//
	// Trace data storage
	Int_t TrLen = 1024;
	Int_t TrLen2= 500;
	Int_t TrLen3= 250000;
	Double_t Ltime=0;
	char *p;
	//
	// Traces to process
	Int_t NTr= ch->GetNTr();
	Int_t *TrCh=new Int_t[NTr];
	TrCh=ch->GetChConfig();
	//
	// Unpack root tree
	TTree *t = (TTree*) infile.Get("t");
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
	//cout<<"Got all brances"<<endl;
	Int_t nentries = t->GetEntries();
	cout << "nentries" << nentries << endl;
	//
	// Event loop
	//
	for(Int_t n=0; n<nentries; n++)
	{
		ntple->NTPreset();
		// reset NTple counters
		t->GetEntry(n);
		// Get new event
		if(nrun>=conf4min && nrun<=conf4max) Ltime= (Double_t) caen2L->system_clock;
		else Ltime = (Double_t) caen->system_clock;
		//
		if(n%100 == 0) cout<<"Event # "<<n<<", Lab time = "<<Ltime<<endl;
		//
		//Active channel loop
		for(Int_t ic=0; ic<NTr; ic++)
		{
			// Copy trace
			Int_t ich = TrCh[ic];
			p=ch->GetConfType(ich);
			//cout<<"Start channel loop. ic = "<<ich<<endl;
			// Process trace checking if given channel configuration belongs to digitizer caen 5742 or to digitizer caen 5730
			Int_t Tlen;
			Double_t *data;
			TBtrace *Tr;
			Double_t sign = 1;
			if(ich>=0 && ich <=15)
			{
				Tlen = TrLen; 
				data = new Double_t[TrLen];
				for(int j=0;j<Tlen;j++) data[j] = (Double_t) caen->trace[ich][j];
			}
			else if(ich>=20 && ich<=27)
			{
				Tlen = TrLen2; 
				//cout<<"Tlen = "<<Tlen<<endl;
				data = new Double_t[Tlen];
				for(Int_t j=0; j<Tlen; j++)
				{
					if(nrun>=conf4min && nrun<=conf4max) data[j] = (Double_t) caen2L->trace[ich-20][j];
					else 
					{
						data[j] = (Double_t) caen2->trace[ich-20][j];
						if(ich == 26) sign = -1.0;
					}
				}
			}
			//
			Tr = new TBtrace(Tlen,data,sign,p);
			Int_t Np = Tr->GetNpulse();
			//cout<<"N pulse found = "<<Np<<endl;
			for(Int_t k=0; k<Np; k++)
			{
				Double_t charge = Tr->GetCharge(k);
				Double_t time   = Tr->GetTime(k);
				Double_t ampl   = Tr->GetAmpl(k);
				Double_t timee  = (Double_t) Tr->GetXmax(k);
				//
				ntple->NTPfill(nrun,ich,k,charge,ampl,time,timee,Ltime);	// Fill NTPle arrays
			}
			Tr->~TBtrace();
			delete[] data;

		}// end of loop over the channels

		tNTP->Fill();
	}
	cout<<"End of event loop. "<<nentries<<" processed."<<endl;
	//
	// Write out TTree, close output file
	OutF.cd();
	tNTP->Write();
	OutF.Close();
	//
}
