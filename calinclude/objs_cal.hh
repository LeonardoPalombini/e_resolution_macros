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
	vector<double> enSteps{2.5,7.5,12.5,17.5,22.5,27.5,32.5,37.5,42.5,47.5,52.5,57.5,62.5,67.5,72.5,77.5,82.5,87.5,92.5,97.5};
//	vector<double> enSteps{5.,15.,25,35.,45.,55.,65.,75.,85.,95.};
//	vector<TH1F*> reco_Ehit(enSteps.size());
//	vector<TH1F*> reco_Epnd(enSteps.size());
//	vector<TH1F*> layerHit(enSteps.size());
//	TGraphErrors* resolE_vsE;
//	TGraphErrors* resolE_vsE_pnd;
	
	vector<TH1F*> hitcal_vsE(enSteps.size());
	TGraphErrors* hitcal_gr;
	
	vector<TH1F*> hitrad_vsE(enSteps.size());
	TH1F* hitrad_temp;
	TGraphErrors* hitrad_gr;
	

//calibration values per angle range
	//dummies for calib procedure
	vector<double> p0(7,1.);	
	vector<double> p1(7,1.);
	
#endif