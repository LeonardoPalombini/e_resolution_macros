//for ntuplizer.xml
#include "calinclude/objs_cal.hh"
#include "include/setbranches.cpp"
#include "calinclude/getdata_cal.cpp"


int calib(double th0 = 10., double th1 = 30., double R = 0.1, const char* file = "../data/e_1-100gev_tot_sim.root"){

	TFile* input_file = new TFile(file, "read");
	cout << "Reading file:  ";
	input_file->Print();

//reco tree from acts+pandora
	recoTuple = (TTree*) input_file->Get("MyLCTuple");

//digi hits
/*	vdxBarrelTuple = (TTree*) input_file->Get("VDXTrackerTuple");
	vdxEndcapTuple = (TTree*) input_file->Get("VDXTrackerEndCapTuple");
	itBarrelTuple = (TTree*) input_file->Get("ITrackerTuple");
	itEndcapTuple = (TTree*) input_file->Get("ITrackerEndCapTuple");
	otBarrelTuple = (TTree*) input_file->Get("OTrackerTuple");
	otEndcapTuple = (TTree*) input_file->Get("OTrackerEndCapTuple");
	ecBarrelTuple = (TTree*) input_file->Get("ECalBarrelTuple");
	ecEndcapTuple = (TTree*) input_file->Get("ECalEndcapTuple");
	hcBarrelTuple = (TTree*) input_file->Get("HCalBarrelTuple");
	hcEndcapTuple = (TTree*) input_file->Get("HCalEndcapTuple");
*/
//sim hits
	vdxBarrelSimTuple = (TTree*) input_file->Get("VertexBarrelCollection");
	vdxEndcapSimTuple = (TTree*) input_file->Get("VertexEndcapCollection");
	itBarrelSimTuple = (TTree*) input_file->Get("InnerTrackerBarrelCollection");
	itEndcapSimTuple = (TTree*) input_file->Get("InnerTrackerEndcapCollection");
	otBarrelSimTuple = (TTree*) input_file->Get("OuterTrackerBarrelCollection");
	otEndcapSimTuple = (TTree*) input_file->Get("OuterTrackerEndcapCollection");
	ecBarrelSimTuple = (TTree*) input_file->Get("ECalBarrelCollectionTuple");
	ecEndcapSimTuple = (TTree*) input_file->Get("ECalEndcapCollectionTuple");
	hcBarrelSimTuple = (TTree*) input_file->Get("HCalBarrelCollectionTuple");
	hcEndcapSimTuple = (TTree*) input_file->Get("HCalEndcapCollectionTuple");
	
	
//set reco branches
	branch_particleMC(recoTuple, partMC);
	branch_particleRC(recoTuple, partRC);
	branch_trackRC(recoTuple, trkRC);
	branch_jetRC(recoTuple, jtRC);
	branch_clusterRC(recoTuple, cluRC);
	
//set hit branches	
/*	branch_caloData(ecBarrelTuple, ecBarHits);	
	branch_caloData(ecEndcapTuple, ecEndHits);	
	branch_caloData(hcBarrelTuple, hcBarHits);	
	branch_caloData(hcEndcapTuple, hcEndHits);	
	branch_trackerData(vdxBarrelTuple, vxBarHits);
	branch_trackerData(vdxEndcapTuple, vxEndHits);
	branch_trackerData(itBarrelTuple, itBarHits);
	branch_trackerData(itEndcapTuple, itEndHits);
	branch_trackerData(otBarrelTuple, otBarHits);
	branch_trackerData(otEndcapTuple, otEndHits);
*/
//set sim hit branches		
	branch_caloSimData(ecBarrelSimTuple, ecBarSimHits);	
	branch_caloSimData(ecEndcapSimTuple, ecEndSimHits);	
	branch_caloSimData(hcBarrelSimTuple, hcBarSimHits);	
	branch_caloSimData(hcEndcapSimTuple, hcEndSimHits);	
	branch_trackerSimData(vdxBarrelSimTuple, vxBarSimHits);
	branch_trackerSimData(vdxEndcapSimTuple, vxEndSimHits);
	branch_trackerSimData(itBarrelSimTuple, itBarSimHits);
	branch_trackerSimData(itEndcapSimTuple, itEndSimHits);
	branch_trackerSimData(otBarrelSimTuple, otBarSimHits);
	branch_trackerSimData(otEndcapSimTuple, otEndSimHits);
	
	
//declare hists
	
	for(int i = 0; i< hitcal_vsE.size(); i++){
		hitcal_vsE[i] = new TH1F(Form("hitcal_vsE_%i",i), Form("Hit E / MC E (%i#circ - %i#circ) - %.2f GeV", (int)th0, (int)th1, enSteps[i]), 80, 1., 1.2);
		hitrad_vsE[i] = new TH1F(Form("hitrad_vsE_%i",i), Form("Hit radius (%i#circ - %i#circ) - %.2f GeV", (int)th0, (int)th1, enSteps[i]), 1000, 0., 0.3);
	}
	hitrad_temp = new TH1F("htemp","htemp", 1000, 0., 0.3);
	hitcal_gr=new TGraphErrors();
	hitcal_gr->SetTitle(Form("Hit E / MC E (%i#circ - %i#circ) vs Hit E", (int)th0, (int)th1));
	hitrad_gr=new TGraphErrors();
	hitrad_gr->SetTitle(Form("Hit radii (%i#circ - %i#circ) vs True E", (int)th0, (int)th1));
	
	int dt = getCalibration(th0, th1);


	TCanvas* c = new TCanvas();
	gPad->Divide(5,4);
	for(int i = 0; i < 20; i++){
		c->cd(i+1);
		hitcal_vsE[i]->Draw();
	}
	
	fitCalibrations();
	
	TCanvas* g = new TCanvas();
	gStyle->SetOptStat(111);
	hitcal_gr->Draw("a*");
	
	TCanvas* d = new TCanvas();
	gPad->Divide(5,4);
	for(int i = 0; i < 20; i++){
		d->cd(i+1);
		hitrad_vsE[i]->Scale(1./hitrad_vsE[i]->GetEntries());
		hitrad_vsE[i]->Draw();
	}
	
	return 0;
}