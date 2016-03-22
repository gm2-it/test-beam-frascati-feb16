//
#include <TAxis.h>
#include <TLine.h>
#include <TGraph.h>
#include <TCanvas.h>
#include "TBtrace.h"
#include <iostream>
//
// Constructors
//
TBtrace::TBtrace(Int_t N, Double_t *A, Double_t Sign)
{
	//
	// Create arrays
	//
	fTrLen = TMath::Min(1024,N);
	fThr   = 100;
	fA = new Double_t[fTrLen]; 			// Input array
	//
	NpMax = 100;		// Max number of pulses
	fPtime   = new Double_t[NpMax]; 	// Vector of pulse times
	fPcharge = new Double_t[NpMax];		// Vector of pulse charges
	fPampl   = new Double_t[NpMax];		// Vector of pulse amplitudes
	fimin    = new Int_t[NpMax];		// Vector of start of island
	fimax    = new Int_t[NpMax];		// Vector of end of island
  //
  // Copy input array
  for(Int_t i=0; i<fTrLen; i++) fA[i] = A[i];
  //
  // 
	Int_t Nbase = 90;
	fBaseA = fA[0];
	for(Int_t i=1; i<Nbase; i++) fBaseA = ((Double_t) (i-1)/(Double_t) i)*fBaseA + fA[i]/(Double_t) i;
	//cout<<"TBtrace:: Approx baseline = "<<fBaseA<<endl;
  //
  // Now get islands, time and charge
	fNpulse = 0;						// Reset nr. of islands
	Int_t* imn = new Int_t[NpMax]; 
	Int_t* imx = new Int_t[NpMax];
	Bool_t Up = kFALSE;
	for(Int_t i=0; i<fTrLen; i++)
	{
		imn[fNpulse] = 0; imx[fNpulse] = fTrLen-1; 
		if(!Up && (Sign*(fBaseA-fA[i])) > fThr)
		{
			Up = kTRUE;
			imn[fNpulse] = i;
			if(fNpulse+1 > NpMax) 
			{
				cout<<"TBtrace:: Too many islands"<<endl;
				return;
			}
			fNpulse++;
		}
		if(Up && (Sign*(fBaseA-fA[i])) < fThr)
		{
			Up = kFALSE;
			imx[fNpulse-1] = i;
		}
	}
	Int_t OffL = 30;
	Int_t OffR = 50; 
	for(Int_t i=0; i<fNpulse; i++)
	{
		fimin[i] = TMath::Max(0,imn[i]-OffL);
		fimax[i] = TMath::Min(imx[i]+OffR,fTrLen-1);
	}
	//
	// if pulses found fill charge and time arrays
	//
	if(fNpulse > 0)
	{
		for(Int_t i=0; i<fNpulse; i++)
		{
			//
			// Charge
			if((fimax[i]- fimin[i]) > 150) fimax[i] = TMath::Min(fimax[i]+300,fTrLen-1); // Americium
			Double_t Charge = 0;
			for(Int_t k=fimin[i]; k<fimax[i]+1; k++) Charge += Sign*(fBaseA-fA[k]);
			fPcharge[i] = Charge;
			//
			// Max amplitude
			Double_t Time = -999.0; Double_t pmin = 10000; if(Sign <0) pmin = 0;
			for(Int_t k=fimin[i]; k<fimax[i]+1; k++) if(Sign*(fA[k]-pmin) < 0) pmin = fA[k];
			fPampl[i] = Sign*(fBaseA-pmin);
		//
		// Timing of leading edge
			Double_t Thresh = fPampl[i]/2.0;
			Int_t k = fimin[i];
			while (Sign*(fBaseA-fA[k]) < Thresh && k<fimax[i]) 
			{
				Time = (Double_t) k;
				k++;
			}
			fPtime[i] = Time;
		}
		//
		// Suppress duplicate pulses
		Bool_t *Kill = new Bool_t[NpMax];
		Int_t ind = 0;
		if(fNpulse > 1)
		{
			Kill[0] = kFALSE;
			//cout<<"TBtrace: k=0 "<<Kill[0]<<"  - Charge = "<<fPcharge[0]
			//						      <<", Time = "<<fPtime[0]<<endl;
			for(Int_t k=1; k<fNpulse; k++)
			{
				Double_t tim2 = fPtime[k];
				Double_t tim1 = fPtime[k-1];
				Kill[k]= kFALSE; 
				if(tim1 == tim2 || tim2<0) Kill[k] = kTRUE;
				//cout<<"TBtrace: k="<<k<<" "<<Kill[k]<<"  - Charge = "<<fPcharge[k]
				//								    <<", Time = "<<fPtime[k]<<endl;
			}
			for(Int_t k=0; k<fNpulse; k++)
			{
				if(!Kill[k])
				{
					fPtime[ind] = fPtime[k];
					fPampl[ind] = fPampl[k];
					fimin [ind] = fimin [k];
					fimax [ind] = fimax [k];
					ind++;
				}
			}
			fNpulse = ind;
			for(Int_t j=0; j<fNpulse; j++)
			{	
				//
				// Charge recalculation
				Double_t Charge = 0;
				for(Int_t k=fimin[j]; k<fimax[j]+1; k++) Charge += fBaseA-fA[k];
				fPcharge[j] = Charge;
			}
		}
	}
	//cout<<"TBtrace: "<<fNpulse<<" islands found"<<endl;
}
//
// Destructor
//
TBtrace::~TBtrace()
{
	//cout<<"TBtrace: entering destructor"<<endl;
  fN = 0;
  fNpulse = 0;
  delete[] fA;
  delete[] fPcharge;
  delete[] fPtime;
  delete[] fPampl;
  delete[] fimin;
  delete[] fimax;
	//cout<<"TBtrace: exiting destructor"<<endl;

}
//
// Returns baseline
Double_t TBtrace::GetBaseline()
{
	return fBaseA;
}
//
// Number of pulses
Int_t TBtrace::GetNpulse()
{
	return fNpulse;
}
//
// Charge of pulse Np
Double_t TBtrace::GetCharge(Int_t Np)
{
	if(Np<fNpulse) return fPcharge[Np];
	else
	{
		cout<<"TBtrace::GetCharge pulse number out of bounds. Np = "<<Np<<endl;
		Double_t Qerr = -999.0;
		return Qerr;
	}
}
//
// Amplitude of pulse Np
Double_t TBtrace::GetAmpl(Int_t Np)
{
	if(Np<fNpulse) return fPampl[Np];
	else
	{
		cout<<"TBtrace::GetAmpl pulse number out of bounds. Np = "<<Np<<endl;
		Double_t Aerr = -999.0;
		return Aerr;
	}
}
//
// Time of pulse Np
Double_t TBtrace::GetTime(Int_t Np)
{
	if(Np<fNpulse) return fPtime[Np];
	else
	{
		cout<<"TBtrace::GetTime pulse number out of bounds. Np = "<<Np<<endl;
		Double_t Terr = -999.0;
		return Terr;
	}
}
//
// Min island channel
Int_t TBtrace::GetXmin(Int_t Np)
{
	if(Np<NpMax) return fimin[Np];
	else
	{
		cout<<"TBtrace::GetXmin pulse number out of buonds. Np = "<<Np<<endl;
		Double_t XmnErr = -999.0;
		return XmnErr;
	}
}
//
// Max island channel
Int_t TBtrace::GetXmax(Int_t Np)
{
	if(Np<NpMax) return fimax[Np];
	else
	{
		cout<<"TBtrace::GetXmin pulse number out of buonds. Np = "<<Np<<endl;
		Double_t XmxErr = -999.0;
		return XmxErr;
	}
}
//
// Display trace and islands
/*
TCanvas* TBtrace::Show(char* title)
{
	TCanvas *Cdsp = new TCanvas("Cdsp","BTF TB event display",50,50,500,500);
	cout<<"TBtrace::Show: TCanvas created"<<endl;
	Double_t* x = new Double_t[fTrLen];
	for(Int_t i=0; i<fTrLen; i++) x[i] = (Double_t) i;
	cout<<" x create with length = "<<fTrLen<<endl;
	TGraph* Gr  = new TGraph(fTrLen,x,fA);
	cout<<"Graph made"<<endl;
	Gr->SetTitle(title);
	cout<<"Title set. title = "<<title<<endl;
	Double_t xmin=0; Double_t xmax= (Double_t) fTrLen;
	cout<<"Limits are:  "<<xmin<<"  "<<xmax<<endl;
	//TAxis *tx = Gr->GetXaxis();
	cout<<"After GetXaxis"<<endl;
	//tx->SetLimits(xmin,xmax);
	cout<<"After SetLimits"<<endl;
	cout<<"Graph limits set"<<endl;
	Gr->Draw("ACP");
	cout<<"Graph drawn"<<endl;
	//
	TLine** Li  = new TLine*[fNpulse]; 
	TLine** Lh  = new TLine*[fNpulse];
	for(Int_t i=0; i<fNpulse; i++)
	{
		Li[i] = new TLine((Double_t) fimin[i], fBaseA, (Double_t) fimax[i], fBaseA);
		Li[i]->SetLineColor(kMagenta);
		Li[i]->SetLineWidth(4);
		Li[i]->Draw("SAME");
		Lh[i] = new TLine(fPtime[i], fBaseA, fPtime[i], fBaseA-fPampl[i]);
		Lh[i]->SetLineColor(kRed);
		Lh[i]->SetLineWidth(2);
		Lh[i]->Draw("SAME");
	}
	//
	return Cdsp;
}
	*/