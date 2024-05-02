// get data from trees
#include "dataUtils.cpp"


/*bool getCaloAndRecoEntries(int);
bool getTrackerEntries(int);*/
bool getCaloSimAndRecoEntries(int);
bool getTrackerSimEntries(int);


// find best tracks and momentum
int anaTracks(double cutR = 0.05){
	
	bool check1, check2;
	
	double mcE, mcTheta, mcEta, mcPhi, mcP;
	int ascTrk;
	double trackPi, trackPf;
	double dE, midE, dEta, minEta, maxEta, theta;
	
	int entries = recoTuple->GetEntries();
	cout << "Analyzing tracks, events: " << entries << endl;
//	entries = 3000;
	for(int i = 0; i < entries; i++){
		
		if(10*i % entries == 0) cout << 100.*(int)i / (int)entries << "%" << endl;
		
		check1 = getCaloSimAndRecoEntries(i);
		check2 = getTrackerSimEntries(i);
		if(!check1 || !check2){
			cout << "Error:: Event number inconsistency!"<<endl;
			return 9;
		}
		
		mcE = partMC.e[0];
		mcTheta = getTheta( partMC.mox[0], partMC.moy[0], partMC.moz[0] );
		mcEta = getEta( partMC.mox[0], partMC.moy[0], partMC.moz[0] );
		mcPhi = getPhi( partMC.mox[0], partMC.moy[0] );
		mcP = getTotP( partMC.mox[0], partMC.moy[0], partMC.moz[0] );
		
		ascTrk = bestTrack( mcE, mcEta, mcPhi, trackPi, trackPf, cutR );
		
		trStates.push_back(ascTrk);
		enTrack.push_back(trackPf);
		
		for(int est = 0; est < enSteps.size(); est++){
			midE = enSteps[est];
//			dE = 20.; //for			
			dE = 5.; //for 1-100 gev
			
			if(mcE <= (midE-0.5*dE) || mcE > (midE+0.5*dE)) continue;

			reco_pTkMc[est]->Fill( (trackPi - mcP)/mcP );
			evtBinsE[est]++;
		}
				
		for(int tst = 0; tst < thSteps.size(); tst++){
//			minEta = getEtafromTheta(thSteps[tst]+2.5);
//			maxEta = getEtafromTheta(thSteps[tst]-2.5);
			theta = mcTheta * 180 / 3.14159;
			theta = (theta<90.) ? theta : 180.-theta;
			if(theta <= (thSteps[tst]-1.) || theta > (thSteps[tst]+1.)) continue;
//			if(abs(mcEta) <= minEta || abs(mcEta) > maxEta) continue;
			
			reco_pTkMc_th[tst]->Fill( (trackPi - mcP)/mcP );
			evtBinsTh[tst]++;
		}
	}	
	return 0;	
}


//get calo hits and match with tracks
int anaCalo(double R = 0.1){
	
	bool check1, check2;
	
	double mcE, mcTheta, mcEta, mcPhi, mcP;
	int ascTrk;
	double manEnergy;
	double dE, midE, dEta, minEta, maxEta, theta;
	
	int entries = recoTuple->GetEntries();
	cout << "Analyzing calo hits, events: " << entries << endl;
//	entries = 3000;
	for(int i = 0; i < entries; i++){
		
		if(10*i % entries == 0) cout << 100.*(int)i / (int)entries << "%" << endl;
		
		check1 = getCaloSimAndRecoEntries(i);
		check2 = getTrackerSimEntries(i);
		if(!check1 || !check2){
			cout << "Error:: Event number inconsistency!"<<endl;
			return 9;
		}
		
		mcE = partMC.e[0];
		mcTheta = getTheta( partMC.mox[0], partMC.moy[0], partMC.moz[0] );
		mcEta = getEta( partMC.mox[0], partMC.moy[0], partMC.moz[0] );
		mcPhi = getPhi( partMC.mox[0], partMC.moy[0] );
		mcP = getTotP( partMC.mox[0], partMC.moy[0], partMC.moz[0] );
				
		manEnergy = coneSimHitEnergy( trStates[i], R );	
		
		for(int est = 0; est < enSteps.size(); est++){
			midE = enSteps[est];
//			dE = 10. * sqrt( midE / 10. ); for 1-1000 gev
			dE = 5.; //for 1-100 gev
			
			if(mcE <= (midE-0.5*dE) || mcE > (midE+0.5*dE)) continue;
			if( abs(enTrack[i]-mcE)/mcE > trackCutsE[est]) continue; 	//track match selection
			
			reco_Ehit[est]->Fill( (manEnergy-mcE)/mcE );
//			reco_Epnd[est]->Fill( (recoEnergy-mcE)/mcE );
			reco_pTkHt[est]->Fill( (manEnergy - enTrack[i]) / enTrack[i] );
		}
				
		for(int tst = 0; tst < thSteps.size(); tst++){
//			minEta = getEtafromTheta(thSteps[tst]+2.5);
//			maxEta = getEtafromTheta(thSteps[tst]-2.5);
			theta = mcTheta * 180 / 3.14159;
			theta = (theta<90.) ? theta : 180.-theta;
			if(theta <= (thSteps[tst]-2.5) || theta > (thSteps[tst]+2.5)) continue;
//			if(abs(mcEta) <= minEta || abs(mcEta) > maxEta) continue;
			if( abs(enTrack[i]-mcE)/mcE > trackCutsTh[tst]) continue; 	//track match selection
			
//			reco_Ehit_th[tst]->Fill( (manEnergy-mcE)/mcE );
			reco_pTkHt_th[tst]->Fill( (manEnergy - enTrack[i]) / enTrack[i] );
		}
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