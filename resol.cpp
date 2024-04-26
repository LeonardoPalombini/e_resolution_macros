//for ntuplizer.xml
#include "resinclude/declareDataObjs.cpp"
#include "include/setbranches.cpp"
#include "resinclude/getdata2.cpp"


int resol(double R = 0.1, const char* file = "../data/e_1-100gev_tot_sim.root"){

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
//set sim hit branches (setbranches.cpp)	
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

	
//declare histograms and graphs (declareDataObjs.cpp)
	declareDataObjs();

	
//produce (trk-mc)/mc momentum vs E and Theta (getdata2.cpp)
	int dt = anaTracks(0.05);

//plot (trk-mc)/mc momentum vs E and Theta
	TCanvas* d0 = new TCanvas();
	gPad->Divide(5,4);
	TCanvas* d1 = new TCanvas();
	gPad->Divide(5,3);
	for(int i = 0; i < enSteps.size(); i++){
		d0->cd(i+1);
		reco_pTkMc[i]->Draw();
	}
	for(int i = 0; i < thSteps.size(); i++){
		d1->cd(i+1);
		reco_pTkMc_th[i]->Draw();
	}
	
//fit tracking spectra for resolution and efficiency, find momentum cuts	
	fitResolEff(reco_pTkMc, resP_vsE, effP_vsE, -.015, .01, -.04, .01, 'e');
	fitResolEff(reco_pTkMc_th, resP_vsTh, effP_vsTh, -.015, .01, -.04, .015, 't');
	
	cout << "Track dP/P cuts: " << endl;
	for(int i = 0; i < enSteps.size(); i++){
		cout << enSteps[i] << " GeV : " << trackCutsE[i] << endl;
	}
	cout << endl;
	for(int i = 0; i < thSteps.size(); i++){
		cout << thSteps[i] << " eta : " << trackCutsTh[i] << endl;
	}


//produce (hits-mc)/mc energy and (hits-trk)/trk energy	vs E and Theta (getdata2.cpp)
	dt = anaCalo(0.1);

//plot (hits-mc)/mc energy and (hits-trk)/trk energy vs E and Theta
	TCanvas* d3 = new TCanvas();
	gPad->Divide(5,4);
	TCanvas* d4 = new TCanvas();
	gPad->Divide(5,4);
	TCanvas* d5 = new TCanvas();
	gPad->Divide(5,3);
	for(int i = 0; i < enSteps.size(); i++){
		d3->cd(i+1);
		reco_Ehit[i]->Draw();
		d4->cd(i+1);
		reco_pTkHt[i]->Draw();
	}
	for(int i = 0; i < thSteps.size(); i++){
		d5->cd(i+1);
		reco_pTkHt_th[i]->Draw();
	}

//fit calo energy and track-calo matching spectra for resolution and efficiency	
	fitResolEff(reco_Ehit, resE_vsE, NULL, -.015, .01, -.04, .025, 'e', 'f');
	fitResolEff(reco_pTkHt, NULL, effPHt_vsE, -.015, .01, -.025, .02, 'e');
	fitResolEff(reco_pTkHt_th, NULL, effPHt_vsTh, -.015, .01, -.04, .02, 't');


//plot final resolutions and efficiencies
	TCanvas* rs0 = new TCanvas();
	gStyle->SetOptStat(111);
	resE_vsE->Draw("a*");
	
	TCanvas* rs1 = new TCanvas();
	gStyle->SetOptStat(111);
	resP_vsE->Draw("a*");
	
	TCanvas* rs2 = new TCanvas();
	gStyle->SetOptStat(111);
	effP_vsE->Draw("a*");
	effP_vsE->GetYaxis()->SetRangeUser(0,1.2);
	
	TCanvas* rs3 = new TCanvas();
	gStyle->SetOptStat(111);
	resP_vsTh->Draw("a*");
	
	TCanvas* rs4 = new TCanvas();
	gStyle->SetOptStat(111);
	effP_vsTh->Draw("a*");
	effP_vsTh->GetYaxis()->SetRangeUser(0,1.2);
	
	TCanvas* rs5 = new TCanvas();
	gStyle->SetOptStat(111);
	effPHt_vsE->Draw("a*");
	effPHt_vsE->GetYaxis()->SetRangeUser(0,1.2);

	TCanvas* rs6 = new TCanvas();
	gStyle->SetOptStat(111);
	effPHt_vsTh->Draw("a*");
	effPHt_vsTh->GetYaxis()->SetRangeUser(0,1.2);
	
	return 0;
}