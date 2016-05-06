//

#ifndef G__TBTRACE_H
#define G__TBTRACE_H
//
#include <TSpline.h>
#include <TF1.h>

//

class TBtrace{
	// 
	// Input:  Digitized trace for a single event
	//
	// Output: Trace classification: pulse or trigger
	// Pulses: Nr., time (leading), charge of each, island start and stop indices
	// Trigger: time (leading)
	// Other: Baseline, avg. noise
	//
private:
	Int_t fN;				// Number of trace channels
	Double_t fSign;			// Channnel inversion signal
	Int_t fNpulse;			// Number of pulses
	Double_t fBaseA;		// Approximate baseline
	Double_t fsBase;		// Baseline sigma
	Double_t fThr;			// Island threshold
	char *fType;			// Trace type
	//
	TSpline3 *fSpl;
	// Arrays
	Int_t fTrLen;
	Double_t* fA; 			// Input array
	Int_t NpMax;
	Double_t* fPtime; 		// Vector of pulse times
	Double_t* fPcharge;		// Vector of pulse charges
	Double_t* fPampl;		// Vector of pulse amplitudes
	Int_t* fPamplx;			// Vector of ocation of maximum
	Int_t* fimin;			// Vector of start of island
	Int_t* fimax;			// Vector of end of island
	//
public:
	//
	// Constructors
	TBtrace(Int_t N, Double_t *A, Double_t sign,char *type);
	// Destructor
	~TBtrace();
	// Accessors
	Double_t GetBaseline();		// Returns baseline
	Double_t GetBaseSig();		// Returns baseline sigma
	Int_t GetNpulse();			// Number of pulses
	Double_t GetCharge(Int_t Np);	// Charge of pulse Np
	Double_t GetAmpl(Int_t Np);	// Amplitude of pulse Np
	Int_t GetAmplx(Int_t Np);	// Location of maximum amplitude
	Double_t GetTime(Int_t Np);	// Time of pulse Np
	Int_t GetXmin(Int_t Np);		// Min island channel
	Int_t GetXmax(Int_t Np);		// Max island channel
	// Service
	void  SetValues();
	Double_t FindPinMaximum(Int_t maxpos);
	Double_t IntegralWithSpline(Int_t xmin,Int_t max);
	void FindIslands();
	Double_t Sfun(Double_t *x, Double_t *p);
};

#endif
