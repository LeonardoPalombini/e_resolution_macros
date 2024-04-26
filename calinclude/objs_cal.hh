// header with global objects

#ifndef OBJS_HH
#define OBJS_HH

#include "../include/structs.hh"

//reco tree from acts+pandora
	TTree* recoTuple;

//trees digi hits
	TTree* vdxBarrelTuple;
	TTree* vdxEndcapTuple;
	TTree* itBarrelTuple;
	TTree* itEndcapTuple;
	TTree* otBarrelTuple;
	TTree* otEndcapTuple;
	TTree* ecBarrelTuple;
	TTree* ecEndcapTuple;
	TTree* hcBarrelTuple;
	TTree* hcEndcapTuple;
	
//trees sim hits
	TTree* vdxBarrelSimTuple;
	TTree* vdxEndcapSimTuple;
	TTree* itBarrelSimTuple;
	TTree* itEndcapSimTuple;
	TTree* otBarrelSimTuple;
	TTree* otEndcapSimTuple;
	TTree* ecBarrelSimTuple;
	TTree* ecEndcapSimTuple;
	TTree* hcBarrelSimTuple;
	TTree* hcEndcapSimTuple;

//branches' addresses MC RC
	particleMC partMC;
	particleRC partRC;
	trackRC trkRC;
	jetRC jtRC;
	clusterRC cluRC;
//branches' addresses Hits	
	trackerData vxBarHits;
	trackerData vxEndHits;
	trackerData itBarHits;
	trackerData itEndHits;
	trackerData otBarHits;
	trackerData otEndHits;
	caloData ecBarHits;
	caloData ecEndHits;
	caloData hcBarHits;
	caloData hcEndHits;
//branches' addresses SimHits		
	trackerData vxBarSimHits;
	trackerData vxEndSimHits;
	trackerData itBarSimHits;
	trackerData itEndSimHits;
	trackerData otBarSimHits;
	trackerData otEndSimHits;
	caloData ecBarSimHits;
	caloData ecEndSimHits;
	caloData hcBarSimHits;
	caloData hcEndSimHits;	
	

//data containers
//	vector<double> enSteps{10.,50.,100.,150.,200.,250.,300.,350.,400.,450.,500.,550.,600.,650.,700.,750.,800.,850.,900.,950.};
//	vector<double> enSteps{5.,15.,25,35.,45.,55.,65.,75.,85.,95.};
//	vector<TH1F*> reco_Ehit(enSteps.size());
//	vector<TH1F*> reco_Epnd(enSteps.size());
//	vector<TH1F*> layerHit(enSteps.size());
//	TGraphErrors* resolE_vsE;
//	TGraphErrors* resolE_vsE_pnd;
	
	vector<TH1F*> hitcal_vsE(10);
	TGraphErrors* hitcal_gr;
	

//calibration values per angle range
	//dummies for calib procedure
	vector<double> p0(7,1.);	
	vector<double> p1(7,1.);
	
#endif