

#ifndef TBNTPLE_H
#define TBNTPLE_H


// these are all the variables contained in the compressed root file

const Int_t MaxPulse=100;
Double_t LabTime;

Int_t NpPIN1;
Double_t PIN1_q[MaxPulse];
Double_t PIN1_a[MaxPulse];
Double_t PIN1_t[MaxPulse];

Int_t NpPIN2;
Double_t PIN2_q[MaxPulse];
Double_t PIN2_a[MaxPulse];
Double_t PIN2_t[MaxPulse];

Int_t NpSM;
Double_t SM_q[MaxPulse];
Double_t SM_a[MaxPulse];
Double_t SM_t[MaxPulse];

Int_t NpHAM;
Double_t HAM_q[MaxPulse];
Double_t HAM_a[MaxPulse];
Double_t HAM_t[MaxPulse];

Int_t NpLM1;
Double_t LM1_q[MaxPulse];
Double_t LM1_a[MaxPulse];
Double_t LM1_t[MaxPulse];

Int_t NpLM2;
Double_t LM2_q[MaxPulse];
Double_t LM2_a[MaxPulse];
Double_t LM2_t[MaxPulse];

Int_t NpSiB;
Double_t SiPMbot_q[MaxPulse];
Double_t SiPMbot_a[MaxPulse];
Double_t SiPMbot_t[MaxPulse];

Int_t NpSiL;
Double_t SiPMlef_q[MaxPulse];
Double_t SiPMlef_a[MaxPulse];
Double_t SiPMlef_t[MaxPulse];

Int_t NpSiC;
Double_t SiPMcen_q[MaxPulse];
Double_t SiPMcen_a[MaxPulse];
Double_t SiPMcen_t[MaxPulse];

Int_t NpSiR;
Double_t SiPMrig_q[MaxPulse];
Double_t SiPMrig_a[MaxPulse];
Double_t SiPMrig_t[MaxPulse];

Int_t NpSiT;
Double_t SiPMtop_q[MaxPulse];
Double_t SiPMtop_a[MaxPulse];
Double_t SiPMtop_t[MaxPulse];

Int_t NpTrL;
Double_t TrigL_q[MaxPulse];
Double_t TrigL_a[MaxPulse];
Double_t TrigL_t[MaxPulse];

Int_t NpTrA;
Double_t TrigA_q[MaxPulse];
Double_t TrigA_a[MaxPulse];
Double_t TrigA_t[MaxPulse];

Int_t NpTrG;
Double_t TrigG_q[MaxPulse];
Double_t TrigG_a[MaxPulse];
Double_t TrigG_t[MaxPulse];

Int_t NpHF;
Double_t HF_q[MaxPulse];
Double_t HF_a[MaxPulse];
Double_t HF_t[MaxPulse];

Int_t NpVF;
Double_t VF_q[MaxPulse];
Double_t VF_a[MaxPulse];
Double_t VF_t[MaxPulse];

#endif

