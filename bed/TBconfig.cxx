#include <iostream>
#include "TBconfig.h"

using namespace std;

TBconfig::TBconfig(char* runfile){
	//
	Int_t TrCh1[13] = {0, 1, 2, 3, 6, 7, 9,10,11,12,13,14,15}; //from run 214 through run 420
	Int_t TrCh2[15] = {0, 1, 2, 6, 7,13,14,15,20,21,22,23,24,25,27}; // from run 839 through run 846
	Int_t TrCh3[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15}; // from run 1081 through run 1107
	Int_t TrCh4[ 8] = {20,21,22,23,24,25,26,27}; // flight simulator from 1137 through 1191


	nrun=GetRunNumber(runfile);
	//
	for(Int_t i= 0; i<16; i++) strncpy(s[i],"EC",100);
	for(Int_t i=20; i<28; i++) strncpy(s[i],"EC",100);     

	if(nrun>=conf1min && nrun <= conf1max)
	{
		NTr = 13;
		TrCh = new Int_t[NTr];
		for(int i=0;i<NTr;i++)TrCh[i]=TrCh1[i];
		strncpy(s[0],"PIN",100);
		strncpy(s[1],"PIN",100);
		strncpy(s[2],"SM",100);
		strncpy(s[3],"PMT",100);
		strncpy(s[6],"PMT",100);
		strncpy(s[7],"PMT",100);
		strncpy(s[9],"PMT",100);
		strncpy(s[10],"PMT",100);
		strncpy(s[11],"PMT",100);
		strncpy(s[12],"PMT",100);
		strncpy(s[13],"trigger",100);
		strncpy(s[14],"trigger",100);
		strncpy(s[15],"trigger",100);
	}
	else if(nrun>=conf2min && nrun<=conf2max)
	{
		NTr = 15;
		TrCh = new Int_t[NTr];
		for(int i=0;i<NTr;i++)TrCh[i]=TrCh2[i];
		strncpy(s[0],"PIN",100);
		strncpy(s[1],"PIN",100);
		strncpy(s[2],"SM",100);
		strncpy(s[6],"PMT",100);
		strncpy(s[7],"PMT",100);
		strncpy(s[13],"trigger",100);
		strncpy(s[14],"trigger",100);
		strncpy(s[15],"trigger",100);
		strncpy(s[20],"PMT",100);
		strncpy(s[21],"PMT",100);
		strncpy(s[22],"PMT",100);
		strncpy(s[23],"PMT",100);
		strncpy(s[24],"PMT",100);
		strncpy(s[25],"PMT",100);
		strncpy(s[26],"trigger",100);
		strncpy(s[27],"PMT",100);
	}
	else if(nrun>=conf3min && nrun<=conf3max)
	{
		NTr = 16;
		TrCh = new Int_t[NTr];
		for(int i=0;i<NTr;i++)TrCh[i]=TrCh3[i];
		strncpy(s[0],"PIN",100);
		strncpy(s[1],"PIN",100);
		strncpy(s[2],"SM",100);
		strncpy(s[3],"PMT",100);
		strncpy(s[4],"PMT",100);
		strncpy(s[5],"trigger",100);
		strncpy(s[6],"trigger",100);
		strncpy(s[7],"trigger",100);
		strncpy(s[8],"PMT",100);
		strncpy(s[9],"PMT",100);
		strncpy(s[10],"PMT",100);
		strncpy(s[11],"PMT",100);
		strncpy(s[12],"PMT",100);
		strncpy(s[13],"PMT",100);
		strncpy(s[14],"PMT",100);
		strncpy(s[15],"PMT",100);
	}
	else if(nrun>=conf4min && nrun<=conf4max){
		NTr = 8;
		TrCh = new Int_t[NTr];
		for(int i=0;i<NTr;i++)TrCh[i]=TrCh4[i];
		strncpy(s[20],"PMT",100);
		strncpy(s[21],"PMT",100);
		strncpy(s[22],"PMT",100);
		strncpy(s[23],"PMT",100);
		strncpy(s[24],"PMT",100);
		strncpy(s[25],"PMT",100);
		strncpy(s[26],"trigger",100);
		strncpy(s[27],"SM",100);
	}
	else
	{       
		NTr=0;
		cout<<"Run out of supported ranges"<<endl;
	}
}
//
TBconfig::~TBconfig(){
	nrun=0;
	NTr=0;
	delete[] TrCh;
	delete[] s;
}
//
Int_t TBconfig::GetNRun(){
	return nrun;
}
//
Int_t *TBconfig::GetChConfig(){
	return TrCh;
}
//
Int_t TBconfig::GetNTr(){
	Int_t nchannel;
	if(nrun>=conf1min && nrun <= conf1max)
	{
		nchannel = 13;
	}
	else if(nrun>=conf2min && nrun<=conf2max)
	{
		nchannel = 15;
	}
	else if(nrun>=conf3min && nrun<=conf3max)
	{
		nchannel = 16;
	}
	else if(nrun>=conf4min && nrun<=conf4max){
		nchannel=8;
	}
	else
	{       
		nchannel=0;
		cout<<"Run out of supported ranges"<<endl;
	}
	return nchannel;
}
//
char *TBconfig::GetConfType(Int_t chn){
	return s[chn];
}
//
Int_t GetRunNumber(char* runfile){  //this function extracts the run number from the string frascatirun_xxxx.root and returns xxxx

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


