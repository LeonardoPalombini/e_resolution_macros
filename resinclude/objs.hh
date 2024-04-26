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
//	vector<double> thSteps{15.,25.,45.,55.,65.,75.,85.};
	vector<double> enSteps{2.5,7.5,12.5,17.5,22.5,27.5,32.5,37.5,42.5,47.5,52.5,57.5,62.5,67.5,72.5,77.5,82.5,87.5,92.5,97.5};
	vector<double> thSteps{12.5,17.5,22.5,27.5,42.5,47.5,52.5,57.5,62.5,67.5,72.5,77.5,82.5,87.5};
	
	vector<TH1F*> reco_Ehit(enSteps.size());		//E dep
//	vector<TH1F*> reco_Epnd(enSteps.size());
	vector<TH1F*> reco_pTkMc(enSteps.size());
	vector<TH1F*> reco_pTkHt(enSteps.size());

	vector<TH1F*> reco_Ehit_th(enSteps.size());	//th dep
//	vector<TH1F*> reco_Epnd_th(enSteps.size());
//	vector<TH1F*> layerHit(enSteps.size());
	vector<TH1F*> reco_pTkMc_th(thSteps.size());
	vector<TH1F*> reco_pTkHt_th(thSteps.size());
		
	vector<int> evtBinsE(enSteps.size(),0);	//evts for effic
	vector<int> evtBinsTh(thSteps.size(),0);
	
	TGraphErrors* resE_vsE;	//resol Ehits vs E
//	TGraphErrors* resolE_vsTh;

//	TGraphErrors* resE_vsE_pnd;
	
	TGraphErrors* resP_vsE;	//resol P vs E
	TGraphErrors* effP_vsE;		//eff P cut vs E

	TGraphErrors* resP_vsTh;	//resol P vs th
	TGraphErrors* effP_vsTh;	//eff P cut vs th
	
	TGraphErrors* effPHt_vsE;	//eff matching E P vs E
	TGraphErrors* effPHt_vsTh;	//eff matching E P vs th
//	TGraphErrors* effRPnd_vsE;
//	TGraphErrors* effRPnd_vsTh;

//calibration values per angle range	
/*	vector<double> p0{1.43755e-02,1.90202e-02,1.71674e-02,1.22481e-02,1.63224e-02,1.91224e-02,1.46840e-02};
	vector<double> p1{2.77955e-02,2.95257e-02,2.96925e-02,2.99156e-02,2.97177e-02,2.95225e-02,2.77951e-02};
*/	
//correction values for Sim Hits per angle range
	vector<double> p0{9.00095e-02,1.13749e-01,1.05779e-01,6.84440e-02,9.35360e-02,1.17239e-01,9.30997e-02};
	vector<double> p1{1.06254e+00,1.05792e+00,1.06358e+00,1.07284e+00,1.06536e+00,1.05745e+00,1.06209e+00};
	
	vector<int> trStates;
	vector<double> enTrack;
	vector<double> trackCutsE(enSteps.size());
	vector<double> trackCutsTh(thSteps.size());
	
#endif