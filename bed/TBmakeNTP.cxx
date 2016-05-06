
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TGraph.h"
#include <TLine.h>
#include <TStyle.h>
#include <iostream>
#include "TBtrace.h"
#include "TBconfig.h"
#include "TBmakeNTP.h"


//
// Constructor
//
TBmakeNTP::TBmakeNTP(char* tID, char* tTitle)
{
	//
	// tID     = tree name/ID
	// tTitle  - tree description
	//
	ftID = tID;
	ftTitle = tTitle;
	//
	const Int_t MaxPulse = 1000;
	//
	LabTime = 0;			// System time in milliseconds
	//
	// Source monitor
	NpPIN1 = 0;				// Number of pulses in PIN1
	PIN1_q = new Double_t[MaxPulse];	// Source monitor PIN1 charge
	PIN1_a = new Double_t[MaxPulse];	// Source monitor PIN1 amplitude
	PIN1_t = new Double_t[MaxPulse];	// Source monitor PIN1 time
	//
	NpPIN2 = 0;				// Number of pulses in PIN2
	PIN2_q = new Double_t[MaxPulse];	// Source monitor PIN2 charge
	PIN2_a = new Double_t[MaxPulse];	// Source monitor PIN2 amplitude
	PIN2_t = new Double_t[MaxPulse];	// Source monitor PIN2 time
	//
	NpSM = 0;						// Number of pulses in SM PMT
	SM_q = new Double_t[MaxPulse];		// Sources monitor PMT with AM and Laser charge
	SM_a = new Double_t[MaxPulse];		// Sources monitor PMT with AM and Laser amplitude
	SM_t = new Double_t[MaxPulse];		// Sources monitor PMT with AM and Laser time
	//
	NpHAM = 0;					// Number of pulses in HAM
	HAM_q = new Double_t[MaxPulse];		// ?? charge
	HAM_a = new Double_t[MaxPulse];		// ?? 
	HAM_t = new Double_t[MaxPulse];		// ?? charge
	//
	// Local monitor
	NpLM1 = 0;					// Number of pulses in PMT1
	LM1_q = new Double_t[MaxPulse];		// Local monitor PMT1 charge
	LM1_a = new Double_t[MaxPulse];		// Local monitor PMT1 amplitude
	LM1_t = new Double_t[MaxPulse];		// Local monitor PMT1 time
	//
	NpLM2 = 0;					// Number of pulses in PMT2
	LM2_q = new Double_t[MaxPulse];		// Local monitor PMT2 charge
	LM2_a = new Double_t[MaxPulse];		// Local monitor PMT2 amplitude
	LM2_t = new Double_t[MaxPulse];		// Local monitor PMT2 time
	//
	// Crystal SiPM
	NpSiB = 0;					// Number of pulses in bottom SiPM
	SiPMbot_q = new Double_t[MaxPulse];	// Bottom SiPM charge
	SiPMbot_a = new Double_t[MaxPulse];	// Bottom SiPM ammplitude
	SiPMbot_t = new Double_t[MaxPulse];	// Bottom SiPM time
	SiPMbot_te= new Double_t[MaxPulse];	// Bottom SiPM time end
	// 
	NpSiL = 0;					// Number of pulses in left SiPM
	SiPMlef_q = new Double_t[MaxPulse];	// Left SiPM charge
	SiPMlef_a = new Double_t[MaxPulse];	// Left SiPM amplitude
	SiPMlef_t = new Double_t[MaxPulse];	// Left SiPM time
	SiPMlef_te= new Double_t[MaxPulse];	// Left SiPM time end
	//
	NpSiC = 0;					// Number of pulses in central SiPM
	SiPMcen_q = new Double_t[MaxPulse];	// Center SiPM charge
	SiPMcen_a = new Double_t[MaxPulse];	// Center SiPM amplitude
	SiPMcen_t = new Double_t[MaxPulse];	// Center SiPM time
	SiPMcen_te= new Double_t[MaxPulse];	// Center SiPM time end
	//
	NpSiR = 0;					// Number of pulses in right SiPM
	SiPMrig_q = new Double_t[MaxPulse];	// Right SiPM charge
	SiPMrig_a = new Double_t[MaxPulse];	// Right SiPM amplitude
	SiPMrig_t = new Double_t[MaxPulse];	// Right SiPM time
	SiPMrig_te= new Double_t[MaxPulse];	// Right SiPM time end
	//
	NpSiT = 0;					// Number of pulses in top SiPM
	SiPMtop_q = new Double_t[MaxPulse];	// Top SiPM charge
	SiPMtop_a = new Double_t[MaxPulse];	// Top SiPM amplitude
	SiPMtop_t = new Double_t[MaxPulse];	// Top SiPM time
	SiPMtop_te= new Double_t[MaxPulse];	// Top SiPM time end
	//
	// Trigger flags
	NpTrL = 0;				// Number of pulses in laser trigger
	TrigL_q = new Double_t[MaxPulse];	// Laser trigger flag charge
	TrigL_a = new Double_t[MaxPulse];	// Laser trigger flag amplitude
	TrigL_t = new Double_t[MaxPulse];	// Laser trigger flag time
	//
	NpTrA = 0;				// Number of pulses in americium trigger
	TrigA_q = new Double_t[MaxPulse];	// Americium trigger flag charge
	TrigA_a = new Double_t[MaxPulse];	// Americium trigger flag amplitude
	TrigA_t = new Double_t[MaxPulse];	// Americium trigger flag time
	//
	NpTrG = 0;				// Number of pulses in americium trigger
	TrigG_q = new Double_t[MaxPulse];	// Americium trigger flag charge
	TrigG_a = new Double_t[MaxPulse];	// Americium trigger flag amplitude
	TrigG_t = new Double_t[MaxPulse];	// Americium trigger flag time
	//

	NpHF = 0;
	HF_q=new Double_t[MaxPulse];      //Horizontal finger charge
	HF_a=new Double_t[MaxPulse];       //horizontal finger amplitude
	HF_t=new Double_t[MaxPulse];       //horizontal finger time

	// vertical finger

	NpVF=0;
	VF_q=new Double_t[MaxPulse];      //vertical finger charge
	VF_a=new Double_t[MaxPulse];       //vertical finger amplitude
	VF_t=new Double_t[MaxPulse];       //vertical finger time

}
//
// Destructor
//
TBmakeNTP::~TBmakeNTP()
{
	//cout<<"TBmakeNTP: entering destructor"<<endl;
	//
	// Delete all arrays
	//
	//
	// Source monitor
	NpPIN1 = 0;;				// Number of pulses in PIN1
	delete[] PIN1_q;	// Source monitor PIN1 charge
	delete[] PIN1_a;	// Source monitor PIN1 amplitude
	delete[] PIN1_t;	// Source monitor PIN1 time
	//
	NpPIN2 = 0;				// Number of pulses in PIN2
	delete[] PIN2_q;	// Source monitor PIN2 charge
	delete[] PIN2_a;	// Source monitor PIN2 amplitude
	delete[] PIN2_t;	// Source monitor PIN2 time
	//
	NpSM = 0;						// Number of pulses in SM PMT
	delete[] SM_q;		// Sources monitor PMT with AM and Laser charge
	delete[] SM_a;		// Sources monitor PMT with AM and Laser amplitude
	delete[] SM_t;		// Sources monitor PMT with AM and Laser time
	//
	NpHAM = 0;					// Number of pulses in HAM
	delete[] HAM_q;		// ?? charge
	delete[] HAM_a;		// ?? 
	delete[] HAM_t;		// ?? charge
	//
	// Local monitor
	NpLM1 = 0;					// Number of pulses in PMT1
	delete[] LM1_q;		// Local monitor PMT1 charge
	delete[] LM1_a;		// Local monitor PMT1 amplitude
	delete[] LM1_t;		// Local monitor PMT1 time
	//
	NpLM2 = 0;					// Number of pulses in PMT2
	delete[] LM2_q;		// Local monitor PMT2 charge
	delete[] LM2_a;		// Local monitor PMT2 amplitude
	delete[] LM2_t;		// Local monitor PMT2 time
	//
	// Crystal SiPM
	NpSiB = 0;					// Number of pulses in bottom SiPM
	delete[] SiPMbot_q;	// Bottom SiPM charge
	delete[] SiPMbot_a;	// Bottom SiPM ammplitude
	delete[] SiPMbot_t;	// Bottom SiPM time
	delete[] SiPMbot_te;	// Bottom SiPM time end
	// 
	NpSiL = 0;					// Number of pulses in left SiPM
	delete[] SiPMlef_q;	// Left SiPM charge
	delete[] SiPMlef_a;	// Left SiPM amplitude
	delete[] SiPMlef_t;	// Left SiPM time
	delete[] SiPMlef_te;	// Left SiPM time end
	//
	NpSiC = 0;					// Number of pulses in central SiPM
	delete[] SiPMcen_q;	// Center SiPM charge
	delete[] SiPMcen_a;	// Center SiPM amplitude
	delete[] SiPMcen_t;	// Center SiPM time
	delete[] SiPMcen_te;	// Center SiPM time end
	//
	NpSiR = 0;					// Number of pulses in right SiPM
	delete[] SiPMrig_q;	// Right SiPM charge
	delete[] SiPMrig_a;	// Right SiPM amplitude
	delete[] SiPMrig_t;	// Right SiPM time
	delete[] SiPMrig_te;	// Right SiPM time end
	//
	NpSiT = 0;					// Number of pulses in top SiPM
	delete[] SiPMtop_q;	// Top SiPM charge
	delete[] SiPMtop_a;	// Top SiPM amplitude
	delete[] SiPMtop_t;	// Top SiPM time
	delete[] SiPMtop_te;	// Top SiPM time end
	//
	// Trigger flags
	NpTrL = 0;				// Number of pulses in laser trigger
	delete[] TrigL_q;	// Laser trigger flag charge
	delete[] TrigL_a;	// Laser trigger flag amplitude
	delete[] TrigL_t;	// Laser trigger flag time
	//
	NpTrA = 0;				// Number of pulses in americium trigger
	delete[] TrigA_q;	// Americium trigger flag charge
	delete[] TrigA_a;	// Americium trigger flag amplitude
	delete[] TrigA_t;	// Americium trigger flag time
	//
	NpTrG = 0;				// Number of pulses in americium trigger
	delete[] TrigG_q;	// Americium trigger flag charge
	delete[] TrigG_a;	// Americium trigger flag amplitude
	delete[] TrigG_t;	// Americium trigger flag time
	//cout<<"TBmakeNTP: exiting destructor"<<endl;
	//horizontal finger
	NpHF = 0;
	delete[] HF_q;
	delete[] HF_a;
	delete[] HF_t;

	//vertical finger
	NpVF = 0;
	delete[] VF_q;
	delete[] VF_a;
	delete[] VF_t;
}
//
//
void TBmakeNTP::NTPreset()
{
	//
	// Zero all pulse number counters
	//
	NpPIN1 = 0;
	NpPIN2 = 0;
	NpSM   = 0;
	NpHAM  = 0;
	NpLM1  = 0;
	NpLM2  = 0;
	NpSiB  = 0;
	NpSiL  = 0;
	NpSiC  = 0;
	NpSiR  = 0;
	NpSiT  = 0;
	NpTrL  = 0;
	NpTrA  = 0;
	NpTrG  = 0;
	NpHF = 0;
	NpVF = 0;
}
//
void TBmakeNTP::NTPfill(Int_t nrun, Int_t ch,Int_t Np, Double_t charge, Double_t ampl, Double_t time, Double_t timee, Double_t Ltime)
{
	if(nrun>= conf1min && nrun<= conf1max)	NTPfill1(ch, Np, charge, ampl, time, timee, Ltime);
	if(nrun>= conf2min && nrun<= conf2max)	NTPfill2(ch, Np, charge, ampl, time, timee, Ltime);
	if(nrun>= conf3min && nrun<= conf3max) 	NTPfill3(ch, Np, charge, ampl, time, timee, Ltime);
    if(nrun>= conf4min && nrun<= conf4max)  NTPfill4(ch, Np, charge, ampl, time, timee, Ltime);

}
// Start NTPfillN
void TBmakeNTP::NTPfill1(Int_t ch, Int_t Np, Double_t charge, Double_t ampl, Double_t time, Double_t timee, Double_t Ltime)
{
	//
	// Fill NTPle arrays for run period 1
	// 
	LabTime= Ltime;
	switch (ch)
	{
	case 0:
		{
			NpPIN1 = Np+1;			// Number pf pulses
			PIN1_q[Np] = charge;
			PIN1_a[Np] = ampl;
			PIN1_t[Np] = time;
			break;
		}
	case 1:
		{
			NpPIN2 = Np+1;			// Number pf pulses
			PIN2_q[Np] = charge;
			PIN2_a[Np] = ampl;
			PIN2_t[Np] = time;
			break;
		}
	case 2:
		{
			NpSM = Np+1;			// Number pf pulses
			SM_q[Np] = charge;
			SM_a[Np] = ampl;
			SM_t[Np] = time;
			break;
		}
	case 3:
		{
			NpHAM = Np+1;			// Number pf pulses
			HAM_q[Np] = charge;
			HAM_a[Np] = ampl;
			HAM_t[Np] = time;
			break;
		}
	case 6:
		{
			NpLM1 = Np+1;			// Number pf pulses
			LM1_q[Np] = charge;
			LM1_a[Np] = ampl;
			LM1_t[Np] = time;
			break;
		}
	case 7:
		{
			NpLM2 = Np+1;			// Number pf pulses
			LM2_q[Np] = charge;
			LM2_a[Np] = ampl;
			LM2_t[Np] = time;
			break;
		}
	case 8:
		{
			NpSiB = Np+1;			// Number pf pulses
			SiPMbot_q[Np] = charge;
			SiPMbot_a[Np] = ampl;
			SiPMbot_t[Np] = time;
			SiPMbot_te[Np] = timee;
			break;
		}
	case 9:
		{
			NpSiL = Np+1;			// Number pf pulses
			SiPMlef_q[Np] = charge;
			SiPMlef_a[Np] = ampl;
			SiPMlef_t[Np] = time;
			SiPMlef_te[Np] = timee;
			break;
		}
	case 10:
		{
			NpSiC = Np+1;			// Number pf pulses
			SiPMcen_q[Np] = charge;
			SiPMcen_a[Np] = ampl;
			SiPMcen_t[Np] = time;
			SiPMcen_te[Np] = timee;
			break;
		}
	case 11:
		{
			NpSiR = Np+1;			// Number pf pulses
			SiPMrig_q[Np] = charge;
			SiPMrig_a[Np] = ampl;
			SiPMrig_t[Np] = time;
			SiPMrig_te[Np] = timee;
			break;
		}
	case 12:
		{
			NpSiT = Np+1;			// Number pf pulses
			SiPMtop_q[Np] = charge;
			SiPMtop_a[Np] = ampl;
			SiPMtop_t[Np] = time;
			SiPMtop_te[Np] = timee;
			break;
		}
	case 13:
		{
			NpTrL = Np+1;			// Number pf pulses
			TrigL_q[Np] = charge;
			TrigL_a[Np] = ampl;
			TrigL_t[Np] = time;
			break;
		}
	case 14:
		{
			NpTrA = Np+1;			// Number pf pulses
			TrigA_q[Np] = charge;
			TrigA_a[Np] = ampl;
			TrigA_t[Np] = time;
			break;
		}
	case 15:
		{
			NpTrG = Np+1;			// Number pf pulses
			TrigG_q[Np] = charge;
			TrigG_a[Np] = ampl;
			TrigG_t[Np] = time;
			break;
		}
	default: 
		break;
	}
}// End NTPfill1

//
void TBmakeNTP::NTPfill2(Int_t ch, Int_t Np, Double_t charge, Double_t ampl, Double_t time, Double_t timee, Double_t Ltime)
{
	//
	// Fill NTPle arrays for run period 2
	// 
	LabTime = Ltime;
	switch (ch)
	{
	case 0:
		{
			NpPIN1 = Np+1;			// Number pf pulses
			PIN1_q[Np] = charge;
			PIN1_a[Np] = ampl;
			PIN1_t[Np] = time;
			break;
		}
	case 1:
		{
			NpPIN2 = Np+1;			// Number pf pulses
			PIN2_q[Np] = charge;
			PIN2_a[Np] = ampl;
			PIN2_t[Np] = time;
			break;
		}
	case 2:
		{
			NpSM = Np+1;			// Number pf pulses
			SM_q[Np] = charge;
			SM_a[Np] = ampl;
			SM_t[Np] = time;
			break;
		}

	case 6:
		{
			NpLM1 = Np+1;			// Number pf pulses
			LM1_q[Np] = charge;
			LM1_a[Np] = ampl;
			LM1_t[Np] = time;
			break;
		}
	case 7:
		{
			NpLM2 = Np+1;			// Number pf pulses
			LM2_q[Np] = charge;
			LM2_a[Np] = ampl;
			LM2_t[Np] = time;
			break;
		}


	case 13:
		{
			NpTrL = Np+1;			// Number pf pulses
			TrigL_q[Np] = charge;
			TrigL_a[Np] = ampl;
			TrigL_t[Np] = time;
			break;
		}


	case 14:
		{
			NpTrA = Np+1;			// Number pf pulses
			TrigA_q[Np] = charge;
			TrigA_a[Np] = ampl;
			TrigA_t[Np] = time;
			break;
		}
	case 15:
		{
			NpTrG = Np+1;			// Number pf pulses
			TrigG_q[Np] = charge;
			TrigG_a[Np] = ampl;
			TrigG_t[Np] = time;
			break;
		}
	case 20:
		{
			NpSiL = Np+1;			// Number pf pulses
			SiPMlef_q[Np] = charge;
			SiPMlef_a[Np] = ampl;
			SiPMlef_t[Np] = time;
			SiPMlef_te[Np] = timee;
			break;
		}
	case 21:
		{
			NpSiC = Np+1;			// Number pf pulses
			SiPMcen_q[Np] = charge;
			SiPMcen_a[Np] = ampl;
			SiPMcen_t[Np] = time;
			SiPMcen_te[Np] = timee;
			break;
		}
	case 22:
		{
			NpSiR = Np+1;			// Number pf pulses
			SiPMrig_q[Np] = charge;
			SiPMrig_a[Np] = ampl;
			SiPMrig_t[Np] = time;
			SiPMrig_te[Np] = timee;
			break;
		}
	case 23:
		{
			NpSiT = Np+1;			// Number pf pulses
			SiPMtop_q[Np] = charge;
			SiPMtop_a[Np] = ampl;
			SiPMtop_t[Np] = time;
			SiPMtop_te[Np] = timee;
			break;
		}
	case 24:
		{
			NpSiB = Np+1;			// Number pf pulses
			SiPMbot_q[Np] = charge;
			SiPMbot_a[Np] = ampl;
			SiPMbot_t[Np] = time;
			SiPMbot_te[Np] = timee;
			break;
		}
	case 25:
		{
			NpHF = Np+1;			// Number pf pulses
			HF_q[Np] = charge;
			HF_a[Np] = ampl;
			HF_t[Np] = time;
			break;
		}

	case 27:
		{
			NpVF = Np+1;			// Number pf pulses
			VF_q[Np] = charge;
			VF_a[Np] = ampl;
			VF_t[Np] = time;
			break;
		}


	default: 
		break;
	}
} // end NTPfill2


void TBmakeNTP::NTPfill3(Int_t ch, Int_t Np, Double_t charge, Double_t ampl, Double_t time, Double_t timee, Double_t Ltime)
{
	//
	// Fill NTPle arrays for run period 3
	// 
	LabTime= Ltime;
	switch (ch)
	{
	case 0:
		{
			NpPIN1 = Np+1;			// Number pf pulses
			PIN1_q[Np] = charge;
			PIN1_a[Np] = ampl;
			PIN1_t[Np] = time;
			break;
		}
	case 1:
		{
			NpPIN2 = Np+1;			// Number pf pulses
			PIN2_q[Np] = charge;
			PIN2_a[Np] = ampl;
			PIN2_t[Np] = time;
			break;
		}
	case 2:
		{
			NpSM = Np+1;			// Number pf pulses
			SM_q[Np] = charge;
			SM_a[Np] = ampl;
			SM_t[Np] = time;
			break;
		}

	case 3:
		{
			NpLM1 = Np+1;			// Number pf pulses
			LM1_q[Np] = charge;
			LM1_a[Np] = ampl;
			LM1_t[Np] = time;
			break;
		}
	case 4:
		{
			NpLM2 = Np+1;			// Number pf pulses
			LM2_q[Np] = charge;
			LM2_a[Np] = ampl;
			LM2_t[Np] = time;
			break;
		}


	case 5:
		{
			NpTrL = Np+1;			// Number pf pulses
			TrigL_q[Np] = charge;
			TrigL_a[Np] = ampl;
			TrigL_t[Np] = time;
			break;
		}


	case 6:
		{
			NpTrA = Np+1;			// Number pf pulses
			TrigA_q[Np] = charge;
			TrigA_a[Np] = ampl;
			TrigA_t[Np] = time;
			break;
		}
	case 7:
		{
			NpTrG = Np+1;			// Number pf pulses
			TrigG_q[Np] = charge;
			TrigG_a[Np] = ampl;
			TrigG_t[Np] = time;
			break;
		}
	case 9:
		{
			NpSiL = Np+1;			// Number pf pulses
			SiPMlef_q[Np] = charge;
			SiPMlef_a[Np] = ampl;
			SiPMlef_t[Np] = time;
			SiPMlef_te[Np] = timee;
			break;
		}
	case 10:
		{
			NpSiC = Np+1;			// Number pf pulses
			SiPMcen_q[Np] = charge;
			SiPMcen_a[Np] = ampl;
			SiPMcen_t[Np] = time;
			SiPMcen_te[Np] = timee;
			break;
		}
	case 11:
		{
			NpSiR = Np+1;			// Number pf pulses
			SiPMrig_q[Np] = charge;
			SiPMrig_a[Np] = ampl;
			SiPMrig_t[Np] = time;
			SiPMrig_te[Np] = timee;
			break;
		}
	case 12:
		{
			NpSiT = Np+1;			// Number pf pulses
			SiPMtop_q[Np] = charge;
			SiPMtop_a[Np] = ampl;
			SiPMtop_t[Np] = time;
			SiPMtop_te[Np] = timee;
			break;
		}
	case 8:
		{
			NpSiB = Np+1;			// Number pf pulses
			SiPMbot_q[Np] = charge;
			SiPMbot_a[Np] = ampl;
			SiPMbot_t[Np] = time;
			SiPMbot_te[Np] = timee;
			break;
		}
	case 14:
		{
			NpHF = Np+1;			// Number pf pulses
			HF_q[Np] = charge;
			HF_a[Np] = ampl;
			HF_t[Np] = time;
			break;
		}

	case 15:
		{
			NpVF = Np+1;			// Number pf pulses
			VF_q[Np] = charge;
			VF_a[Np] = ampl;
			VF_t[Np] = time;
			break;
		}


	case 13:
		{
			NpHAM = Np+1;			// Number pf pulses
			HAM_q[Np] = charge;
			HAM_a[Np] = ampl;
			HAM_t[Np] = time;
			break;
		}


	default: 
		break;
	}
} // end NTPfill3

void TBmakeNTP::NTPfill4(Int_t ch, Int_t Np, Double_t charge, Double_t ampl, Double_t time, Double_t timee, Double_t Ltime)
{
	//
	// Fill NTPle arrays for run period 3
	// 
	LabTime= Ltime;
	switch (ch)
	{
	case 27:
		{
			NpSM = Np+1;			// Number pf pulses
			SM_q[Np] = charge;
			SM_a[Np] = ampl;
			SM_t[Np] = time;
			break;
		}
	case 25:
		{
			NpLM1 = Np+1;			// Number pf pulses
			LM1_q[Np] = charge;
			LM1_a[Np] = ampl;
			LM1_t[Np] = time;
			break;
		}
	case 26:
		{
			NpTrL = Np+1;			// Number pf pulses
			TrigL_q[Np] = charge;
			TrigL_a[Np] = ampl;
			TrigL_t[Np] = time;
			break;
		}
	case 21:
		{
			NpSiL = Np+1;			// Number pf pulses
			SiPMlef_q[Np] = charge;
			SiPMlef_a[Np] = ampl;
			SiPMlef_t[Np] = time;
			SiPMlef_te[Np] = timee;
			break;
		}
	case 22:
		{
			NpSiC = Np+1;			// Number pf pulses
			SiPMcen_q[Np] = charge;
			SiPMcen_a[Np] = ampl;
			SiPMcen_t[Np] = time;
			SiPMcen_te[Np] = timee;
			break;
		}
	case 23:
		{
			NpSiR = Np+1;			// Number pf pulses
			SiPMrig_q[Np] = charge;
			SiPMrig_a[Np] = ampl;
			SiPMrig_t[Np] = time;
			SiPMrig_te[Np] = timee;
			break;
		}
	case 24:
		{
			NpSiT = Np+1;			// Number pf pulses
			SiPMtop_q[Np] = charge;
			SiPMtop_a[Np] = ampl;
			SiPMtop_t[Np] = time;
			SiPMtop_te[Np] = timee;
			break;
		}
	case 20:
		{
			NpSiB = Np+1;			// Number pf pulses
			SiPMbot_q[Np] = charge;
			SiPMbot_a[Np] = ampl;
			SiPMbot_t[Np] = time;
			SiPMbot_te[Np] = timee;
			break;
		}
	default: 
		break;
	}
} 
// end NTPfill4







TTree *TBmakeNTP::NTPsetup()
{
	TTree *tNTP = new TTree(ftID,ftTitle);
	//
	tNTP->Branch("LabTime",&LabTime,"LabTime/D");
	//
	// Source monitor
	tNTP->Branch("NpPIN1",&NpPIN1,"NpPIN1/I");
	tNTP->Branch("PIN1_q",PIN1_q,"PIN1_q[NpPIN1]/D");
	tNTP->Branch("PIN1_a",PIN1_a,"PIN1_a[NpPIN1]/D");
	tNTP->Branch("PIN1_t",PIN1_t,"PIN1_t[NpPIN1]/D");
	//
	tNTP->Branch("NpPIN2",&NpPIN2,"NpPIN2/I");
	tNTP->Branch("PIN2_q",PIN2_q,"PIN2_q[NpPIN2]/D");
	tNTP->Branch("PIN2_a",PIN2_a,"PIN2_a[NpPIN2]/D");
	tNTP->Branch("PIN2_t",PIN2_t,"PIN2_t[NpPIN2]/D");
	//
	tNTP->Branch("NpSM",&NpSM,"NpSM/I");
	tNTP->Branch("SM_q",SM_q,"SM_q[NpSM]/D");
	tNTP->Branch("SM_a",SM_a,"SM_a[NpSM]/D");
	tNTP->Branch("SM_t",SM_t,"SM_t[NpSM]/D");
	//
	tNTP->Branch("NpHAM",&NpHAM,"NpHAM/I");
	tNTP->Branch("HAM_q",HAM_q,"HAM_q[NpHAM]/D");
	tNTP->Branch("HAM_a",HAM_a,"HAM_a[NpHAM]/D");
	tNTP->Branch("HAM_t",HAM_t,"HAM_t[NpHAM]/D");
	//
	// Local monitor
	tNTP->Branch("NpLM1",&NpLM1,"NpLM1/I");
	tNTP->Branch("LM1_q",LM1_q,"LM1_q[NpLM1]/D");
	tNTP->Branch("LM1_a",LM1_a,"LM1_a[NpLM1]/D");
	tNTP->Branch("LM1_t",LM1_t,"LM1_t[NpLM1]/D");
	//
	tNTP->Branch("NpLM2",&NpLM2,"NpLM2/I");
	tNTP->Branch("LM2_q",LM2_q,"LM2_q[NpLM2]/D");
	tNTP->Branch("LM2_a",LM2_a,"LM2_a[NpLM2]/D");
	tNTP->Branch("LM2_t",LM2_t,"LM2_t[NpLM2]/D");
	//
	// Crystal SiPM
	//
	tNTP->Branch("NpSiB",&NpSiB,"NpSiB/I");
	tNTP->Branch("SiPMbot_q",SiPMbot_q,"SiPMbot_q[NpSiB]/D");
	tNTP->Branch("SiPMbot_a",SiPMbot_a,"SiPMbot_a[NpSiB]/D");
	tNTP->Branch("SiPMbot_t",SiPMbot_t,"SiPMbot_t[NpSiB]/D");
	tNTP->Branch("SiPMbot_te",SiPMbot_te,"SiPMbot_te[NpSiB]/D");
	//
	tNTP->Branch("NpSiL",&NpSiL,"NpSiL/I");
	tNTP->Branch("SiPMlef_q",SiPMlef_q,"SiPMlef_q[NpSiL]/D");
	tNTP->Branch("SiPMlef_a",SiPMlef_a,"SiPMlef_a[NpSiL]/D");
	tNTP->Branch("SiPMlef_t",SiPMlef_t,"SiPMlef_t[NpSiL]/D");
	tNTP->Branch("SiPMlef_te",SiPMlef_te,"SiPMlef_te[NpSiL]/D");
	//
	tNTP->Branch("NpSiC",&NpSiC,"NpSiC/I");
	tNTP->Branch("SiPMcen_q",SiPMcen_q,"SiPMcen_q[NpSiC]/D");
	tNTP->Branch("SiPMcen_a",SiPMcen_a,"SiPMcen_a[NpSiC]/D");
	tNTP->Branch("SiPMcen_t",SiPMcen_t,"SiPMcen_t[NpSiC]/D");
	tNTP->Branch("SiPMcen_te",SiPMcen_te,"SiPMcen_te[NpSiC]/D");
	//
	tNTP->Branch("NpSiR",&NpSiR,"NpSiR/I");
	tNTP->Branch("SiPMrig_q",SiPMrig_q,"SiPMrig_q[NpSiR]/D");
	tNTP->Branch("SiPMrig_a",SiPMrig_a,"SiPMrig_a[NpSiR]/D");
	tNTP->Branch("SiPMrig_t",SiPMrig_t,"SiPMrig_t[NpSiR]/D");
	tNTP->Branch("SiPMrig_te",SiPMrig_te,"SiPMrig_te[NpSiR]/D");
	//
	tNTP->Branch("NpSiT",&NpSiT,"NpSiT/I");
	tNTP->Branch("SiPMtop_q",SiPMtop_q,"SiPMtop_q[NpSiT]/D");
	tNTP->Branch("SiPMtop_a",SiPMtop_a,"SiPMtop_a[NpSiT]/D");
	tNTP->Branch("SiPMtop_t",SiPMtop_t,"SiPMtop_t[NpSiT]/D");
	tNTP->Branch("SiPMtop_te",SiPMtop_te,"SiPMtop_te[NpSiT]/D");
	//
	// Trigger flags
	// Laser
	tNTP->Branch("NpTrL",&NpTrL,"NpTrL/I");
	tNTP->Branch("TrigL_q",TrigL_q,"TrigL_q[NpTrL]/D");
	tNTP->Branch("TrigL_a",TrigL_a,"TrigL_a[NpTrL]/D");
	tNTP->Branch("TrigL_t",TrigL_t,"TrigL_t[NpTrL]/D");
	// Americium
	tNTP->Branch("NpTrA",&NpTrA,"NpTrA/I");
	tNTP->Branch("TrigA_q",TrigA_q,"TrigA_q[NpTrA]/D");
	tNTP->Branch("TrigA_a",TrigA_a,"TrigA_a[NpTrA]/D");
	tNTP->Branch("TrigA_t",TrigA_t,"TrigA_t[NpTrA]/D");
	// Global
	tNTP->Branch("NpTrG",&NpTrG,"NpTrG/I");
	tNTP->Branch("TrigG_q",TrigG_q,"TrigG_q[NpTrL]/D");
	tNTP->Branch("TrigG_a",TrigG_a,"TrigG_a[NpTrL]/D");
	tNTP->Branch("TrigG_t",TrigG_t,"TrigG_t[NpTrL]/D");
	// Horizontal finger
	tNTP->Branch("NpHF",&NpHF,"NpHF/I");
	tNTP->Branch("HF_q",HF_q,"HF_q[NpTrL]/D");
	tNTP->Branch("HF_a",HF_a,"HF_a[NpTrL]/D");
	tNTP->Branch("HF_t",HF_t,"HF_t[NpTrL]/D");
	// Vertical finger
	tNTP->Branch("NpVF",&NpVF,"NpVF/I");
	tNTP->Branch("VF_q",VF_q,"VF_q[NpTrL]/D");
	tNTP->Branch("VF_a",VF_a,"VF_a[NpTrL]/D");
	tNTP->Branch("VF_t",VF_t,"VF_t[NpTrL]/D");
	//
	//
	return tNTP;
}
