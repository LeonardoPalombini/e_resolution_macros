// get data
#include "dataUtils_cal.cpp"


/*bool getCaloAndRecoEntries(int);
bool getTrackerEntries(int);*/
bool getCaloSimAndRecoEntries(int);
bool getTrackerSimEntries(int);




int getCalibration(double th0, double th1, double R = 0.2){
	
	bool check1, check2;
	
	double mcE, mcTheta, mcEta, mcPhi;
	int ascTrk;
	double manEnergy, recoEnergy;
	double dE, midE;
	
	int entries = recoTuple->GetEntries();
	cout << "Total entries = " << entries << endl;
//	entries = 10;
	int ngr;
	for(int i = 0; i < entries; i++){
		
		if(10*i % entries == 0) cout << 100.*(int)i / (int)entries << "%" << endl;
		
		check1 = getCaloSimAndRecoEntries(i);
		check2 = getTrackerSimEntries(i);
		if(!check1 || !check2){
			cout << "Error:: Event number inconsistency!"<<endl;
			return 9;
		}
		mcTheta = getTheta( partMC.mox[0], partMC.moy[0], partMC.moz[0] ) * 180. / 3.14159;
		if(!(mcTheta > th0 && mcTheta < th1)) continue;
		
		mcE = partMC.e[0];
		mcEta = getEta( partMC.mox[0], partMC.moy[0], partMC.moz[0] );
		mcPhi = getPhi( partMC.mox[0], partMC.moy[0] );
		
		ascTrk = bestTrack( mcEta, mcPhi, 0.05 );
		manEnergy = coneSimHitEnergy( ascTrk, R );
		recoEnergy = PNDrecoEnergy( mcEta, mcPhi, 0.01 );
		
		//mcTheta = getTheta(partMC.mox[0], partMC.moy[0], partMC.moz[0]) * 180. / 3.14159;	//mc cheat
		
		ngr = -1;
		for(int j = 0; j < enSteps.size(); j++){
			if(abs(enSteps[j]-mcE)<2.5) ngr = j;
		}
		if(ngr < 0) continue;
		
		hitcal_vsE[ngr]->Fill(mcE/manEnergy);
		hitrad_vsE[ngr]->Add(hitrad_temp);
		hitrad_temp->Reset();
	}

	
	return 0;
}




/*
bool getCaloAndRecoEntries(int i){
	
	recoTuple->GetEntry(i);
	ecBarrelTuple->GetEntry(i);
	ecEndcapTuple->GetEntry(i);
	hcBarrelTuple->GetEntry(i);
	hcEndcapTuple->GetEntry(i);
	
	return (partMC.nevt == ecBarHits.nevt 
			&& ecBarHits.nevt == ecEndHits.nevt
			&& ecEndHits.nevt == hcBarHits.nevt
			&& hcBarHits.nevt == hcEndHits.nevt);
}

bool getTrackerEntries(int i){
	
	vdxBarrelTuple->GetEntry(i);
	vdxEndcapTuple->GetEntry(i);
	itBarrelTuple->GetEntry(i);
	itEndcapTuple->GetEntry(i);
	otBarrelTuple->GetEntry(i);
	otEndcapTuple->GetEntry(i);
	
	return (vxBarHits.nevt == vxEndHits.nevt 
			&& vxEndHits.nevt == itBarHits.nevt
			&& itBarHits.nevt == itEndHits.nevt
			&& itEndHits.nevt == otBarHits.nevt
			&& otBarHits.nevt == otEndHits.nevt);
}
*/

bool getCaloSimAndRecoEntries(int i){
	
	recoTuple->GetEntry(i);
	ecBarrelSimTuple->GetEntry(i);
	ecEndcapSimTuple->GetEntry(i);
	hcBarrelSimTuple->GetEntry(i);
	hcEndcapSimTuple->GetEntry(i);
	
	return (partMC.nevt == ecBarSimHits.nevt
			&& ecBarSimHits.nevt == ecEndSimHits.nevt
			&& ecEndSimHits.nevt == hcBarSimHits.nevt
			&& hcBarSimHits.nevt == hcEndSimHits.nevt);
}

bool getTrackerSimEntries(int i){
	
	vdxBarrelSimTuple->GetEntry(i);
	vdxEndcapSimTuple->GetEntry(i);
	itBarrelSimTuple->GetEntry(i);
	itEndcapSimTuple->GetEntry(i);
	otBarrelSimTuple->GetEntry(i);
	otEndcapSimTuple->GetEntry(i);
	
	return (vxBarSimHits.nevt == vxEndSimHits.nevt 
			&& vxEndSimHits.nevt == itBarSimHits.nevt
			&& itBarSimHits.nevt == itEndSimHits.nevt
			&& itEndSimHits.nevt == otBarSimHits.nevt
			&& otBarSimHits.nevt == otEndSimHits.nevt);
}
