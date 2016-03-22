***************************************
** Running trace display program     **
***************************************
TBdisplay("inputWaveformfile.root",channel)
when second digitizer present use 20+channel to select second digitizer	
		
root [0] .L TBtrace.cxx+				(class to process each trace)
root [1] .L TBdisplay.c+				(program to display trace)
root [2] TBdisplay("data/frascatirun_01091.root",5)
Input file data/frascatirun_01091.root
Error in <TTree::SetBranchAddress>: unknown branch -> caen_5730
Enter command: n =new event, q= quit
n
Event nr. 0
Data[0] = 3579
Data[1] = 3579
Data[2] = 3581
Data[3] = 3572
Data[4] = 3578
Data[5] = 3582
Data[6] = 3579
Data[7] = 3575
Data[8] = 3578
Data[9] = 3576
Data[10] = 3579
Data[11] = 3580
Data[12] = 3580
Data[13] = 3575
Data[14] = 3582
Data[15] = 3583
Data[16] = 3582
Data[17] = 3580
Data[18] = 3580
Data[19] = 3581
Data[20] = 3581
Data[21] = 3577
Data[22] = 3582
Data[23] = 3574
Data[24] = 3578
Data[25] = 3580
Data[26] = 3584
Data[27] = 3578
Data[28] = 3577
Data[29] = 3577
Data[30] = 3578
Data[31] = 3572
Data[32] = 3576
Data[33] = 3579
Data[34] = 3575
Data[35] = 3578
Data[36] = 3580
Data[37] = 3574
Data[38] = 3577
Data[39] = 3575
Data[40] = 3579
Data[41] = 3580
Data[42] = 3579
Data[43] = 3579
Data[44] = 3579
Data[45] = 3576
Data[46] = 3575
Data[47] = 3579
Data[48] = 3579
Data[49] = 3579
Data[50] = 3579
Data[51] = 3578
Data[52] = 3581
Data[53] = 3578
Data[54] = 3579
Data[55] = 3578
Data[56] = 3582
Data[57] = 3581
Data[58] = 3579
Data[59] = 3577
Data[60] = 3578
Data[61] = 3575
Data[62] = 3581
Data[63] = 3579
Data[64] = 3579
Data[65] = 3578
Data[66] = 3581
Data[67] = 3578
Data[68] = 3580
Data[69] = 3578
Data[70] = 3581
Data[71] = 3576
Data[72] = 3576
Data[73] = 3578
Data[74] = 3576
Data[75] = 3574
Data[76] = 3580
Data[77] = 3580
Data[78] = 3579
Data[79] = 3578
Data[80] = 3575
Data[81] = 3580
Data[82] = 3578
Data[83] = 3579
Data[84] = 3579
Data[85] = 3578
Data[86] = 3583
Data[87] = 3577
Data[88] = 3575
Data[89] = 3577
Data[90] = 3578
Data[91] = 3583
Data[92] = 3581
Data[93] = 3580
Data[94] = 3584
Data[95] = 3581
Data[96] = 3577
Data[97] = 3577
Data[98] = 3578
Data[99] = 3580
Pulse #0: Charge = 1.08509e+006, time = 687, Ampl = 3266.38, base = 3578.38
Enter command: n =new event, q= quit

***************************************
** Running NTple compression program **
***************************************
TBgenNTP("inputWaveformFile.root","outputCompressedFile.root")

root [0] .L TBtrace.cxx+        (class to process each trace)
root [1] .L TBmakeNTP.cxx+	(class with compressed NTple structure)
root [2] .L TBgenNTP.c+		(program creating the compressed NTple)
root [3] gROOT->Reset():
root [4] TBgenNTP("data/frascatirun_00352.root","data/352.root")
Input file data/frascatirun_00352.root
nrun = 352
Error in <TTree::SetBranchAddress>: unknown branch -> caen_5730
Event # 0, Lab time = 3
Event # 10000, Lab time = 102731
Event # 20000, Lab time = 200538
Event # 30000, Lab time = 294196
Event # 40000, Lab time = 406102
Event # 50000, Lab time = 511934
Event # 60000, Lab time = 605145
Event # 70000, Lab time = 708244
Event # 80000, Lab time = 806699
Event # 90000, Lab time = 909834
Event # 100000, Lab time = 1.0183e+006
End of event loop. 100673 processed.
root [5]



***************************************
** Using compressed NTple            **
***************************************
- Example 1: Plots beam events in four crystals and normalized sum

root [0] .L PlotEl.c+	(user program - Needs TBntple.h)
root [1] PlotEl("data/1091.root")
Nentries = 100167
root [2] 


- Example 2: as before with fit of results and merging several files

root [0] .L PlotElFitChain.c+	(user program - Needs TBntple.h)
root [1] PlotElFitChain("TB1100.txt")
Opening TB1100.txt
Adding file: data/1101.root
Adding file: data/1102.root
Adding file: data/1104.root
Adding file: data/1105.root
Adding file: data/1106.root
Nentries = 500634
Info in <TCanvas::MakeDefCanvas>:  created default TCanvas with name c1
 FCN=2445.51 FROM MIGRAD    STATUS=CONVERGED     358 CALLS         359 TOTAL
                     EDM=1.30292e-007    STRATEGY= 1  ERROR MATRIX UNCERTAINTY   0.7 per cent
  EXT PARAMETER                                   STEP         FIRST
  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
   1  Norm        9.21845e+006  3.33023e+004  6.84007e+000 -5.29735e-009
   2  Electron peak  1.14193e+003  4.51147e-001 -6.53040e-004  1.30355e-004
   3  Npe conversion  1.86675e+001  3.62516e-001 -5.71399e-004 -1.12124e-003
   4  Noise       1.84104e+002  2.71272e+000  2.11492e-003 -8.12665e-005
   5  Poisson mean  2.66119e+000  6.65801e-003 -5.39765e-006 -1.61499e-002
   6  Efficiency mean  1.44640e+003  6.81450e+000  3.02533e-003 -7.26840e-005
   7  Efficiency sigma  5.55549e+002  7.08253e+000 -9.14443e-003  1.11360e-004

................
...............
root [2]