//
#include "TBtrace.h"
#include <iostream>
#include <TMath.h>
#include <TSpline.h>
#include <TF1.h>
#include <TVectorD.h>
#include <TMatrixDSym.h>

//
// Constructors
//
TBtrace::TBtrace(Int_t N, Double_t *A, Double_t sign,char *type)
{
	//
	// Create arrays
	//
	//cout<<"In TBtrace1"<<endl;
	fTrLen = TMath::Min(250000,N);
	fThr   = 100;
	fSign  = sign;
	fType  = new char[100];
	strncpy(fType,type,100);
	fA = new Double_t[fTrLen]; 			// Input array
	//
	NpMax = 500;		// Max number of pulses
	fPtime   = new Double_t[NpMax]; 	// Vector of pulse times
	fPcharge = new Double_t[NpMax];		// Vector of pulse charges
	fPampl   = new Double_t[NpMax];		// Vector of pulse amplitudes
	fimin    = new Int_t[NpMax];		// Vector of start of island
	fimax    = new Int_t[NpMax];		// Vector of end of island
	fPamplx  = new Int_t[NpMax];		// ?????
	//
	// Store input array
	for(Int_t i=0; i<fTrLen; i++) fA[i] = A[i];
	//
	// Find Pulses and their ranges (islands)
	//
	FindIslands();
	//
	// Calculate and store pulse properties
	//
	SetValues();
	//
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
	delete[] fType;
	delete[] fPcharge;
	delete[] fPtime;
	delete[] fPampl;
	delete[] fPamplx;
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
// Returns baseline sigma
Double_t TBtrace::GetBaseSig()
{
	return fsBase;
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
// Max location of pulse Np
Int_t TBtrace::GetAmplx(Int_t Np)	// Location of maximum amplitude
{
	if(Np<fNpulse) return fPamplx[Np];
	else
	{
		cout<<"TBtrace::GetAmplx pulse number out of bounds. Np = "<<Np<<endl;
		Double_t AXerr = -999.0;
		return AXerr;
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
// Set pulse properties
//
void TBtrace::SetValues()
{
	//
	// Set charge, amplitude and timing
	//
	if(fNpulse>0)
	{
		for(Int_t i=0; i<fNpulse; i++)
		{
			//
			// Amplitude
			//
			//
			//cout<<"sign = "<<fSign<<endl;
			Int_t kmax=0; 
			Double_t pmin = 50000; if(fSign <0) pmin = 0;
			for(Int_t k=fimin[i]; k<fimax[i]+1; k++)
			{
				if(fSign*(fA[k]-pmin) < 0) 
				{
					pmin = fA[k];
					kmax=k;
				}
			}
			//
			fPamplx[i] = kmax;
			//cout<<"minimum at "<<kmax<<"  with value "<<pmin<<endl;
			if(strcmp(fType,"PIN")==0) fPampl[i]= fSign*(fBaseA-FindPinMaximum(kmax));
			else fPampl [i] = fSign*(fBaseA-pmin);
			//
			// Charge
			//
			if(strcmp(fType,"PMT")==0 || (strcmp(fType,"SM")==0 && fimax[i]!=fTrLen-1))
			{
				Int_t minx;
				Int_t k=kmax;
				while(fBaseA-fA[k]>0 && k<=fimax[i]){minx=k; k++;}
				//cout<<"Max of range: "<<fimax[i]<<", Max for integration: "<<minx<<endl;;
				//
				fimax[i] = minx;
				fPcharge[i] = IntegralWithSpline(fimin[i],fimax[i]);
			}
			else
			{
				Double_t Charge = 0;
				for(Int_t k=fimin[i]; k<fimax[i]+1; k++) Charge += fSign*(fBaseA-fA[k]);
				fPcharge[i] = Charge;
			}
			//
			// Timing of leading edge
			Double_t Time = -999.0;
			Double_t Thresh = fPampl[i]/2.0;
			Int_t k = fimin[i];
			while (fSign*(fBaseA-fA[k]) < Thresh && k<fimax[i]) 
			{
				Time = (Double_t) k;
				k++;
			}
			fPtime[i] = Time;
		}
	}
}
//
Double_t TBtrace::FindPinMaximum(Int_t maxpos)
{
	//
	// Interpolate maximum/minimum with nth order polynomial
	//
	Int_t range = 40;			// 1/2 range used for fit
	const int Deg = 2;			// Degree of fitting polynomial
	TVectorD t(Deg+1);			t.Zero();
	TVectorD tx(Deg+1);			tx.Zero();
	TVectorD tsum(Deg+1);		tsum.Zero();
	TVectorD a(Deg+1);			a.Zero();
	TMatrixDSym T(Deg+1);		T.Zero();
	TMatrixDSym Tsum(Deg+1);	Tsum.Zero();
	//
	Double_t min;
	//
	// loop over defined range 
	for(Int_t i=TMath::Max(maxpos-range,0); i<=TMath::Min(maxpos+range,fTrLen-1); i++)
	{
		t(0) = 1.0;
		t(1) = (Double_t) i;    
		t(2) = (Double_t) i*i;
		Tsum.Rank1Update(t,1.0);
		tx = fA[i]*t;
		tsum += tx; // add t to tsum
	}
	//
	Tsum.Invert();
	a = Tsum*tsum;		// Get polymomial coefficients  
	//
	min= (4*a(0)*a(2) -a(1)*a(1))/(4*a(2));   // Calculate polynomial value at min/max
	return min;
}
//
Double_t TBtrace::Sfun(Double_t *x, Double_t *p)
{
	return fSpl->Eval(x[0]);
}
//
Double_t TBtrace::IntegralWithSpline(Int_t xmin, Int_t xmax)
{
	//
	// Define spline 10 channels beyond given range to avoid edge effects
	Int_t Xmin = TMath::Max(xmin-10,0);
	Int_t Xmax = TMath::Min(xmax+10,fTrLen-1);
	Int_t len = Xmax-Xmin+1;
	Double_t *Sy = new Double_t[len];
	Double_t *Sx = new Double_t[len];
	for(Int_t i=0; i<len; i++)
	{
		Sx[i] = Xmin+i;
		Sy[i] = fBaseA-fA[Xmin+i];
	}
	//
	fSpl = new TSpline3("TstSpline",Sx,Sy,len);		// Interpolate points with 3-spline
	//
	// Associate spline with function
	TF1 *Fun = new TF1("Fun",this,&TBtrace::Sfun,(Double_t) xmin, (Double_t) xmax,1,"TBtrace","Sfun");
	Int_t np = 100;
	double *x=new double[np];
	double *w=new double[np];
	Fun->CalcGaussLegendreSamplingPoints(np,x,w,1e-15);
	Double_t charge = Fun->IntegralFast(np,x,w,(Double_t) xmin, (Double_t) xmax);
	//Double_t charge = Fun->Integral((Double_t) xmin, (Double_t) xmax);
	Fun->~TF1();
	fSpl->~TSpline3();
	delete [] Sx;
	delete [] Sy;
	delete [] x;
	delete [] w;
	//
	return charge;
}
//
void TBtrace::FindIslands()
{
	// 
	// Find baseline and its spread
	Int_t Nbase = 50;				// Numer of points for rough baseline determination
	fBaseA = fA[0];					// Iniitialize average
	Double_t Base2 = fA[0]*fA[0];	// Initialize mean of x^2
	for(Int_t i=1; i<Nbase; i++)
	{
		fBaseA = ((Double_t) (i-1)/(Double_t) i)*fBaseA + fA[i]      /(Double_t) i;
		Base2 = ((Double_t) (i-1)/(Double_t) i)* Base2 + fA[i]*fA[i]/(Double_t) i;
	}
	Double_t sBase = TMath::Sqrt(Base2-fBaseA*fBaseA);
	fThr   = 10*sBase;			// Set threshold based on baseline spread
	//cout<<"TBtrace:: Approx baseline = "<<fBaseA<<", Spread = " <<sBase<<endl;
	//
	// Now get islands
	//
	fNpulse = 0;						// Reset nr. of islands
	Int_t* imn = new Int_t[NpMax]; 
	Int_t* imx = new Int_t[NpMax];
	Bool_t Up = kFALSE;
	for(Int_t i=0; i<fTrLen; i++)
	{
		imn[fNpulse] = 0; imx[fNpulse] = fTrLen-1; 
		if(!Up && (fSign*(fBaseA-fA[i])) > fThr)
		{
			Up = kTRUE;
			imn[fNpulse] = i;
			if(fNpulse+1 > NpMax) 
			{
				cout<<"TBtrace:: Too many islands"<<endl;
				cout<<"TBtrace: fBase = "<<fBaseA<<" width = "<<sBase<<endl;
				cout<<"Dumping pulses"<<endl;
				for(Int_t kp=0; kp<100;  kp++)
					cout<<"NP: "<<kp<<" ,min: "<<imn[kp]<<" - "<<fA[imn[kp]]
									<<" ,max: "<<imx[kp]<<" - "<<fA[imx[kp]]<<endl;
				return;
			}
			fNpulse++;
		}
		if(Up && (fSign*(fBaseA-fA[i])) < fThr)
		{
			Up = kFALSE;
			imx[fNpulse-1] = i;
		}
	}
	// Add margin around foundsignals
	Int_t OffL = 20;
	Int_t OffR = 40; 
	for(Int_t i=0; i<fNpulse; i++)
	{
		fimin[i] = TMath::Max(0,imn[i]-OffL);
		fimax[i] = TMath::Min(imx[i]+OffR,fTrLen-1);
		if((fimax[i]- fimin[i]) > 100)	// Americium/PIN/Triggers
		{
			fimax[i] = fTrLen-1; 
			fimin[i] = TMath::Max(0,imn[i]-OffL-20);
		}
	}
	//
	// Process found pulses
	//
	if(fNpulse>0)
		//
		// Merge overlapping islands
		//
	{
		Int_t Np = 0;					// Final number of pulses
		delete [] imn; delete [] imx;	// Reset min/max arrays
		Int_t *imn = new Int_t[fNpulse];
		Int_t *imx = new Int_t[fNpulse];
		// Loop on first round of pulses to suppress duplicates
		for(Int_t i=0; i<fNpulse; i++)
		{
			if(fimax[i-1]>fimin[i] && i>0)	// Pulses overlap so extend end of pulse
			{
				imx[Np-1] = fimax[i];
			}
			else							// Pulses do no overlap so keep existing pulse
			{
				imn[Np] = fimin[i]; 
				imx[Np] = fimax[i];
				Np++;
			}
		}
		//
		// Store final pulses
		//
		delete [] fimin; delete [] fimax;
		fNpulse = Np;
		fimin = new Int_t[fNpulse];
		fimax = new Int_t[fNpulse];
		for(Int_t i=0; i<fNpulse; i++)
		{
			fimin[i] = imn[i];
			fimax[i] = imx[i];
			if((fimax[i]- fimin[i]) > 400) fimax[i] = fTrLen-1; // Americium/PIN/Trigger
		}
		delete [] imn;
		delete [] imx;
		//
		// Update baseline
		//
		fBaseA = fA[0];			// Initialize average
		Base2  = fA[0]*fA[0];	// Initialize mean of x^2
		Int_t Nu = 0;
		Int_t minB = TMath::Max(fimin[0]-100,0);
		Int_t maxB = TMath::Min(fimax[fNpulse-1]+100,fTrLen);
		for(Int_t i=minB; i<maxB; i++)
		{
			Bool_t active = kTRUE;
			for(Int_t k=0; k<fNpulse; k++)if(i>=fimin[k] && i<=fimax[k]) active = kFALSE;
			if(active)
			{
				Nu++;
				fBaseA = ((Double_t) (Nu-1)/(Double_t) Nu)*fBaseA + fA[i]      /(Double_t) Nu;
				Base2  = ((Double_t) (Nu-1)/(Double_t) Nu)* Base2 + fA[i]*fA[i]/(Double_t) Nu;
			}
		}
		fsBase = TMath::Sqrt(Base2-fBaseA*fBaseA);
	}
}






