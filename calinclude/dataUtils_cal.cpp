#include "../include/structs.hh"
#include "objs_cal.hh"

double getTheta(double x, double y, double z){
	double th = atan( sqrt( x*x + y*y ) / z );
	th = th > 0. ? th : 3.1416+th;
	return th;
}

double getEta(double x, double y, double z){
	double th = atan( sqrt( x*x + y*y ) / z );
	th = th > 0. ? th : 3.1416+th;
	return - log( tan(th/2.) );
}

double getPhi(double x, double y){
	double phi;
	if(x > 0) phi = atan( y / x );
	else{
		if(y > 0) phi = atan( y / x ) + 3.14159;
		else phi = atan( y / x ) - 3.14159;
	}
	return phi;
}

double getEneEndcap(double e, double th){
	
	th = th*180/3.14159;
	int i = 0;
	if(th < 40.) i = 0;
	else if(th > 140) i = 6;
	
	return e * ( p0[i] / sqrt(e) + p1[i] );
}

double getEneBarrel(double e, double th){
	
	th = th*180/3.14159;
	int i = 0;
	if(th < 60) i = 1;
	else if(th > 120) i = 5;
	else i = ((int)(th-60.)/20.) + 2;
	return e * (p0[i]/sqrt(e) + p1[i]);
}


//=======================================================================

//find track associated to mc
int bestTrack(double mcEta, double mcPhi, double cutRtrk = 0.05){
	
//exclude trackless events
	if(trkRC.ntr == 0) return -100;

//find track associated to primary e	
	int firstTS, lastTS;
	int bestTS = -10;
	double trkTheta, trkEta, trkPhi, dR;
	
	double mom, bestMom = 0.;
	int bestI;
	
	for(int iTr = 0; iTr < trkRC.ntr; iTr++){
		
		firstTS = trkRC.idxVt[iTr];
		lastTS = trkRC.idxCalo[iTr];
		trkEta = log( tan( (atan(trkRC.tlambda[firstTS]) +0.5*3.14159) / 2. ) );	// no (-) to adapt coordinates
		trkPhi = trkRC.phi[firstTS];
		
		dR = sqrt(pow(mcEta-trkEta,2)+pow(mcPhi-trkPhi,2));
		if(dR < cutRtrk){
			bestTS = lastTS;	//to improve adding closest track condition
			bestI = iTr;
		}
	}
	
	if(bestTS < -1) return -200;
	else return bestTS;
}
/*
// compute energy inside the track cone
double coneHitEnergy(int bestTS = 3, double cutR = 0.2){

	double trkTheta, trkEta, trkPhi, dR;
	
//sum hits inside cone of best track
	trkTheta = getTheta(trkRC.sx[bestTS], trkRC.sy[bestTS], trkRC.sz[bestTS]);
	trkEta = getEta(trkRC.sx[bestTS], trkRC.sy[bestTS], trkRC.sz[bestTS]);
	trkPhi = getPhi(trkRC.sx[bestTS], trkRC.sy[bestTS]);	
	
	double hitTheta, hitEta, hitPhi;
	
	double sumE = 0.;
	for(int iEB = 0; iEB < ecBarHits.nhits; iEB++){
		
		hitEta = getEta(ecBarHits.x[iEB], ecBarHits.y[iEB], ecBarHits.z[iEB]);
		hitPhi = getPhi(ecBarHits.x[iEB], ecBarHits.y[iEB]);
		
		dR = sqrt(pow(hitEta-trkEta,2)+pow(hitPhi-trkPhi,2));
		if(dR < cutR) sumE += ecBarHits.e[iEB];
	}
	for(int iEE = 0; iEE < ecEndHits.nhits; iEE++){
		
		hitEta = getEta(ecEndHits.x[iEE], ecEndHits.y[iEE], ecEndHits.z[iEE]);
		hitPhi = getPhi(ecEndHits.x[iEE], ecEndHits.y[iEE]);
		
		dR = sqrt(pow(hitEta-trkEta,2)+pow(hitPhi-trkPhi,2));	//getEneEndcap( ecEndHits.e[iEE], getTheta(ecEndHits.x[iEE], ecEndHits.y[iEE], ecEndHits.z[iEE]) )
		if(dR < cutR) sumE += ecEndHits.e[iEE];
	}
	for(int iHB = 0; iHB < hcBarHits.nhits; iHB++){
		
		hitEta = getEta(hcBarHits.x[iHB], hcBarHits.y[iHB], hcBarHits.z[iHB]);
		hitPhi = getPhi(hcBarHits.x[iHB], hcBarHits.y[iHB]);
		
		dR = sqrt(pow(hitEta-trkEta,2)+pow(hitPhi-trkPhi,2));
		if(dR < cutR) sumE += hcBarHits.e[iHB]; //assume same as ecal
	}
	for(int iHE = 0; iHE < hcEndHits.nhits; iHE++){
		
		hitEta = getEta(hcEndHits.x[iHE], hcEndHits.y[iHE], hcEndHits.z[iHE]);
		hitPhi = getPhi(hcEndHits.x[iHE], hcEndHits.y[iHE]);
		
		dR = sqrt(pow(hitEta-trkEta,2)+pow(hitPhi-trkPhi,2));
		if(dR < cutR) sumE += hcEndHits.e[iHE];
	}
	
	return sumE;
}
*/


// compute energy inside the track cone
double coneSimHitEnergy(int bestTS = 3, double cutR = 0.2, double thr = 0.002){

	double trkTheta, trkEta, trkPhi, dR;
	
//sum hits inside cone of best track
	trkTheta = getTheta(trkRC.sx[bestTS], trkRC.sy[bestTS], trkRC.sz[bestTS]);
	trkEta = getEta(trkRC.sx[bestTS], trkRC.sy[bestTS], trkRC.sz[bestTS]);
	trkPhi = getPhi(trkRC.sx[bestTS], trkRC.sy[bestTS]);	
	
	double hitTheta, hitEta, hitPhi;
	
	double sumE = 0.;
	for(int iEB = 0; iEB < ecBarSimHits.nhits; iEB++){
		
		hitEta = getEta(ecBarSimHits.x[iEB], ecBarSimHits.y[iEB], ecBarSimHits.z[iEB]);
		hitPhi = getPhi(ecBarSimHits.x[iEB], ecBarSimHits.y[iEB]);
		
		dR = sqrt(pow(hitEta-trkEta,2)+pow(hitPhi-trkPhi,2));
		if(ecBarSimHits.e[iEB]>thr) hitrad_temp->Fill(dR);
		if(dR < cutR && ecBarSimHits.e[iEB]>thr) sumE += ecBarSimHits.e[iEB];
	}
	
	for(int iEE = 0; iEE < ecEndSimHits.nhits; iEE++){
		
		hitEta = getEta(ecEndSimHits.x[iEE], ecEndSimHits.y[iEE], ecEndSimHits.z[iEE]);
		hitPhi = getPhi(ecEndSimHits.x[iEE], ecEndSimHits.y[iEE]);
		
		dR = sqrt(pow(hitEta-trkEta,2)+pow(hitPhi-trkPhi,2));
		if(ecBarSimHits.e[iEE]>thr) hitrad_temp->Fill(dR);
		if(dR < cutR && ecEndSimHits.e[iEE]>thr) sumE += ecEndSimHits.e[iEE];
	}
	
	for(int iHB = 0; iHB < hcBarSimHits.nhits; iHB++){
		
		hitEta = getEta(hcBarSimHits.x[iHB], hcBarSimHits.y[iHB], hcBarSimHits.z[iHB]);
		hitPhi = getPhi(hcBarSimHits.x[iHB], hcBarSimHits.y[iHB]);
		
		dR = sqrt(pow(hitEta-trkEta,2)+pow(hitPhi-trkPhi,2));
		if(ecBarSimHits.e[iHB]>thr) hitrad_temp->Fill(dR);
		if(dR < cutR && hcBarSimHits.e[iHB]>thr) sumE += hcBarSimHits.e[iHB]; //assume same as ecal
	}
	
	for(int iHE = 0; iHE < hcEndSimHits.nhits; iHE++){
		
		hitEta = getEta(hcEndSimHits.x[iHE], hcEndSimHits.y[iHE], hcEndSimHits.z[iHE]);
		hitPhi = getPhi(hcEndSimHits.x[iHE], hcEndSimHits.y[iHE]);
		
		dR = sqrt(pow(hitEta-trkEta,2)+pow(hitPhi-trkPhi,2));
		if(ecBarSimHits.e[iHE]>thr) hitrad_temp->Fill(dR);
		if(dR < cutR && hcEndSimHits.e[iHE]>thr) sumE += hcEndSimHits.e[iHE];
	}
	
	return sumE;
}



double PNDrecoEnergy(double mcEta, double mcPhi, double cutReco = 0.05){
	
	double en;
	double recoEta, recoPhi, dR;
	
	for(int iPt = 0; iPt < partMC.npt; iPt++){
		
		recoEta = getEta(partMC.mox[iPt], partMC.moy[iPt], partMC.moz[iPt]);
		recoPhi = getPhi(partMC.mox[iPt], partMC.moy[iPt]);
		
		dR = sqrt(pow(recoEta-mcEta,2)+pow(recoPhi-mcPhi,2));
		if(dR < cutReco) en = partRC.e[iPt];
	}
	
	return en;
}


void fitCalibrations(){
	
	double min = 1.06, max = 1.14;
//	cout << "Select min fit range:  ";
//	cin >> min;
//	cout << "Select max fit range:  ";
//	cin >> max;
	
	TF1* gauss = new TF1("gauss", "gaus", min, max);
	
	double oldM, oldE;
	for(int i = 0; i < hitcal_vsE.size(); i++){
		
		hitcal_vsE[i]->Fit(gauss, "N0R+");
		oldM = gauss->GetParameter(1);
		oldE = gauss->GetParError(1);
		
		hitcal_vsE[i]->Fit(gauss, "M+","", gauss->GetParameter(1)-2.*gauss->GetParameter(2), gauss->GetParameter(1)+2.*gauss->GetParameter(2));
			
		if(gauss->GetParameter(0) < 0. || gauss->GetParError(1)>0.5*gauss->GetParameter(1)){
			cout << "Failed fit, falling back to default." << endl;
			hitcal_vsE[i]->Fit(gauss, "MR+");
		}
		
		hitcal_gr->SetPoint(i, (0.5+(double)i)*10., gauss->GetParameter(1));
		hitcal_gr->SetPointError(i, 5., gauss->GetParError(1));
	}
	
	TF1* fitgr = new TF1("fitgr", "[0]/x^0.5+[1]",1,100);
	fitgr->SetParameters(0.1, 1.06);
	hitcal_gr->Fit(fitgr,"SR+");
	
}
