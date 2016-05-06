//

#ifndef G__TBMAKENTP_H
#define G__TBMAKENTP_H
//
class TBmakeNTP{
	//
	// NTPle building class for Frascati test beam.
	//
	// Example usage:
	//
	// TFile *f = new TFile("run345.root","recreate");
	// char tID[10] = "tNTP";
	// char tTitle[50] = "Compressed NTPle";
	// TBmakeNTP *A = new TBmakeNTP(tID,tTitle);
	// TTree *t = A->NTPsetup();
	// EventLoop:
	//	A->NTPreset();
	//	Ltime = LocalTime;
	//	ChannelLoop: (ch)
	//		PulseNrLoop: (Np)
	//			charge = ...
	//			ampl = ...
	//			time = ...
	//			A->NTPfill(nrun, ch, Np, charge, ampl, time, Ltime);
	//		PulseNrLoop end
	//	ChannelLoop end
	//	t->Fill();
	// EventLoop end
	// f->cd();
	// t->Write();
	// f->Close();
	//
private:
	char* ftID;					// Tree identifier
	char* ftTitle;				// Tree description

	Double_t LabTime;			// System time in milliseconds
	//
	// Source monitor
	Int_t NpPIN1;				// Number of pulses in PIN1
	Double_t* PIN1_q;	// Source monitor PIN1 charge
	Double_t* PIN1_a;	// Source monitor PIN1 amplitude
	Double_t* PIN1_t;	// Source monitor PIN1 time
	//
	Int_t NpPIN2;				// Number of pulses in PIN2
	Double_t* PIN2_q;	// Source monitor PIN2 charge
	Double_t* PIN2_a;	// Source monitor PIN2 amplitude
	Double_t* PIN2_t;	// Source monitor PIN2 time
	//
	Int_t NpSM;						// Number of pulses in SM PMT
	Double_t* SM_q;		// Sources monitor PMT with AM and Laser charge
	Double_t* SM_a;		// Sources monitor PMT with AM and Laser amplitude
	Double_t* SM_t;		// Sources monitor PMT with AM and Laser time
	//
	Int_t NpHAM;					// Number of pulses in HAM
	Double_t* HAM_q;		// ?? charge
	Double_t* HAM_a;		// ?? 
	Double_t* HAM_t;		// ?? charge
	//
	// Local monitor
	Int_t NpLM1;					// Number of pulses in PMT1
	Double_t* LM1_q;		// Local monitor PMT1 charge
	Double_t* LM1_a;		// Local monitor PMT1 amplitude
	Double_t* LM1_t;		// Local monitor PMT1 time
	//
	Int_t NpLM2;					// Number of pulses in PMT2
	Double_t* LM2_q;		// Local monitor PMT2 charge
	Double_t* LM2_a;		// Local monitor PMT2 amplitude
	Double_t* LM2_t;		// Local monitor PMT2 time
	//
	// Crystal SiPM
	Int_t NpSiB;					// Number of pulses in bottom SiPM
	Double_t* SiPMbot_q;	// Bottom SiPM charge
	Double_t* SiPMbot_a;	// Bottom SiPM ammplitude
	Double_t* SiPMbot_t;	// Bottom SiPM time
	Double_t* SiPMbot_te;	// Bottom SiPM end time
	// 
	Int_t NpSiL;					// Number of pulses in left SiPM
	Double_t* SiPMlef_q;	// Left SiPM charge
	Double_t* SiPMlef_a;	// Left SiPM amplitude
	Double_t* SiPMlef_t;	// Left SiPM time
	Double_t* SiPMlef_te;	// Left SiPM end time
	//
	Int_t NpSiC;					// Number of pulses in central SiPM
	Double_t* SiPMcen_q;	// Center SiPM charge
	Double_t* SiPMcen_a;	// Center SiPM amplitude
	Double_t* SiPMcen_t;	// Center SiPM time
	Double_t* SiPMcen_te;	// Center SiPM end time
	//
	Int_t NpSiR;					// Number of pulses in right SiPM
	Double_t* SiPMrig_q;	// Right SiPM charge
	Double_t* SiPMrig_a;	// Right SiPM amplitude
	Double_t* SiPMrig_t;	// Right SiPM time
	Double_t* SiPMrig_te;	// Right SiPM end time
	//
	Int_t NpSiT;					// Number of pulses in top SiPM
	Double_t* SiPMtop_q;	// Top SiPM charge
	Double_t* SiPMtop_a;	// Top SiPM amplitude
	Double_t* SiPMtop_t;	// Top SiPM time
	Double_t* SiPMtop_te;	// Top SiPM end time
	//
	// Trigger flags
	Int_t NpTrL;				// Number of pulses in laser trigger
	Double_t* TrigL_q;	// Laser trigger flag charge
	Double_t* TrigL_a;	// Laser trigger flag amplitude
	Double_t* TrigL_t;	// Laser trigger flag time
	//
	Int_t NpTrA;				// Number of pulses in americium trigger
	Double_t* TrigA_q;	// Americium trigger flag charge
	Double_t* TrigA_a;	// Americium trigger flag amplitude
	Double_t* TrigA_t;	// Americium trigger flag time
	//
	Int_t NpTrG;				// Number of pulses in americium trigger
	Double_t* TrigG_q;	// Americium trigger flag charge
	Double_t* TrigG_a;	// Americium trigger flag amplitude
	Double_t* TrigG_t;	// Americium trigger flag time

	//Horizontal finger

	Int_t NpHF;             
	Double_t* HF_q;         // horizontal finger charge
	Double_t* HF_a;          // horizontal finger amplitude
	Double_t* HF_t;         //horizontal finger time

	//Vertical finger

	Int_t NpVF;             
	Double_t* VF_q;        //vertical finger charge
	Double_t* VF_a;        //vertical finger amplitude
	Double_t* VF_t;        //vertical finger time

	//
public:
	//
	//constructor
	TBmakeNTP(char* tID, char* tTitle);
	//
	// destructor
	~TBmakeNTP();
	//
	// Configure NTPle tree structure
	TTree *NTPsetup();
	//
	// Pulse counter reset.
	void NTPreset();
	//
	// Generic NTP filling routine
	void NTPfill(Int_t nrun, Int_t ch, Int_t Np, Double_t charge, Double_t ampl, Double_t time, Double_t timee, Double_t Ltime);
	//
	// Specific NTP filling routine for run range 214 - 420
	void NTPfill1(Int_t ch, Int_t Np, Double_t charge, Double_t ampl, Double_t time, Double_t timee, Double_t Ltime);
	// Specific NTP filling routine for run range 839 - 846
	void NTPfill2(Int_t ch, Int_t Np, Double_t charge, Double_t ampl, Double_t time, Double_t timee, Double_t Ltime);
	// Specific NTP filling routine for run range 1081 - 1107
	void NTPfill3(Int_t ch, Int_t Np, Double_t charge, Double_t ampl, Double_t time, Double_t timee, Double_t Ltime);
	// Specific NTP filling routine for run range 1137 - 1191
	void NTPfill4(Int_t ch, Int_t Np, Double_t charge, Double_t ampl, Double_t time, Double_t timee, Double_t Ltime);

};





#endif
