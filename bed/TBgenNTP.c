#include <string>
#include <algorithm>
#include "TROOT.h"
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include "Caen.h"
#include "TBtrace.h"
#include "TBmakeNTP.h"

using namespace std;

Int_t GetNRun(char* runfile){
	Int_t nrun;
	int comma;
	string s1;
	string s2;
	string s3;
	string ss(runfile);
	comma=ss.find("_");
	s1=ss.substr(0,comma);
	s2=ss.substr(comma+1);
	comma=s2.find(".");
	s3=s2.substr(0,comma);
	nrun=atoi(s3.c_str());
	return nrun;

}


void TBgenNTP(char* runfile, char* cFile)
{
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
	TTree *tNTP = ntple->NTPsetup();					// Setup tree structure
	//
	//	INPUT DATA MANAGEMENT
	//
	// Open input file
	cout<<"Input file "<<runfile<<endl;
	TFile infile(runfile,"r");
	//short routine to extract file number
	Int_t nrun;
	nrun = GetNRun(runfile); //exctract run number from file name
	cout << "nrun = " << nrun << endl;

	//
	// Trace data storage
	const Int_t TrLen = 1024;
	const Int_t TrLen2= 500;
	//
	// Traces to process
	Int_t NTr;
	Int_t *TrCh;
	Int_t TrCh1[13] = {0, 1, 2, 3, 6, 7, 9,10,11,12,13,14,15};
	Int_t TrCh2[15] = {0, 1, 2, 7, 8,13,14,15,20,21,22,23,24,25,27};
	Int_t TrCh3[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15};
	if(nrun>=214 && nrun <= 420)
	{
		NTr = 13;
		TrCh = new Int_t[NTr];
		TrCh = TrCh1;
	}
	else if(nrun>=839 && nrun<=846)
	{
		NTr = 15;
		TrCh = new Int_t[NTr];
		TrCh = TrCh2;
	}
	else if(nrun>=1081 && nrun<=1107)
	{
		NTr = 16;
		TrCh = new Int_t[NTr];
		TrCh = TrCh3;
	}
	else
	{
		cout<<"Run out of supported ranges"<<endl;
		return;
	}
	//
	// Unpack root tree
	TTree *t = (TTree*) infile.Get("t");
	caen_5742 caen;
	caen_5730 caen2;
	t->SetBranchAddress("caen_5742",&caen.system_clock);
	t->SetBranchAddress("caen_5730",&caen2.event_index);
	//cout<<"Got all brances"<<endl;
	Int_t nentries = t->GetEntries();
	//
	// Event loop
	//
	for(Int_t n=0; n<nentries; n++)
	{
		ntple->NTPreset();		// reset NTple counters
		t->GetEntry(n);
		//t1->GetEntry(n);			// Get new event
		Double_t Ltime = (Double_t) caen.system_clock;
		if(n%10000 == 0) cout<<"Event # "<<n<<", Lab time = "<<Ltime<<endl;
		//
		//Active channel loop
		for(Int_t ic=0; ic<NTr; ic++)
		{
			// Copy trace
			Int_t ich = TrCh[ic];
			//cout<<"Start channel loop. ic = "<<ich<<endl;
			// Process trace checking if given channel configuration belongs to digitizer caen 5742 or to digitizer caen 5730
			Double_t *data;
			TBtrace *Tr;
			if(ich>=0 && ich <=15)
			{
				Double_t sign = 1;
				data = new Double_t[TrLen];
				for(int j=0;j<TrLen;j++) data[j] = (Double_t) caen.trace[ich][j];
				Tr = new TBtrace(TrLen,data,sign);
			}
			else if(ich>=20 && ich <=27)
			{
				Double_t sign = 1; if(ich == 26) sign = -1;
				data = new Double_t[TrLen2];
				for(int j=0;j<TrLen2;j++) data[j] = (Double_t) caen2.trace[ich-20][j];
				Tr = new TBtrace(TrLen2,data,sign);
			}
			//
			Int_t Np = Tr->GetNpulse();
			//cout<<"N pulse found = "<<Np<<endl;
			for(Int_t k=0; k<Np; k++)
			{
				Double_t charge = Tr->GetCharge(k);
				Double_t time   = Tr->GetTime(k);
				Double_t ampl   = Tr->GetAmpl(k);
				ntple->NTPfill(nrun,ich,k,charge,ampl,time,Ltime);	// Fill NTPle arrays
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
