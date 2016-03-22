//

#ifndef G__TBTRACE_H
#define G__TBTRACE_H
//
#include <TCanvas.h>
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
  Int_t fNpulse;		// Number of pulses
  Double_t fBaseA;		// Approximate baseline
  Double_t fThr;	// Island threshold
  // Arrays
  Int_t fTrLen;
  Double_t* fA; 			// Input array
  Int_t NpMax;
  Double_t* fPtime; 		// Vector of pulse times
  Double_t* fPcharge;	// Vector of pulse charges
  Double_t* fPampl;		// Vector of pulse amplitudes
  Int_t* fimin;			// Vector of start of island
  Int_t* fimax;			// Vector of end of island
  //
 public:
  //
  // Constructors
  TBtrace(Int_t N, Double_t *A, Double_t Sign);
  // Destructor
  ~TBtrace();
  // Accessors
  Double_t GetBaseline();		// Returns baseline
  Int_t GetNpulse();			// Number of pulses
  Double_t GetCharge(Int_t Np);	// Charge of pulse Np
  Double_t GetAmpl(Int_t Np);	// Amplitude of pulse Np
  Double_t GetTime(Int_t Np);	// Time of pulse Np
  Int_t GetXmin(Int_t Np);		// Min island channel
  Int_t GetXmax(Int_t Np);		// Max island channel
  //
  //
  // Display
  //
  //TCanvas* Show(char* title);					// Display trace and islands
};

#endif
