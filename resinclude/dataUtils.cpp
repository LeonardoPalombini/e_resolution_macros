//data analysis routines

#ifndef DATAUTILS_CPP
#define DATAUTILS_CPP


#include "../include/structs.hh"
#include "objs.hh"

// conversions

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

double getEtafromTheta(double th){ 	//conv from degrees
	th = th * 3.14159 / 180.;
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

double getTotP(double x, double y, double z){
	return sqrt(x*x+y*y+z*z);
}


//energy corrections (from calibration)
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
int bestTrack(double mcE, double mcEta, double mcPhi, double &mom0, double &mom1, double cutRtrk = 0.05){
	
//exclude trackless events
	if(trkRC.ntr == 0) return -100;

//find track associated to primary e	
	int firstTS, lastTS;
	int bestTS = -10;
	double trkTheta, trkEta, trkPhi, dR;
	double pre_dR = 1.;

	int bestI;
	
	double testMom;
	mom0 = -1000.;
	mom1 = -1000.;
	for(int iTr = 0; iTr < trkRC.ntr; iTr++){
		
		firstTS = trkRC.idxVt[iTr];
		lastTS = trkRC.idxCalo[iTr];
		trkEta = log( tan( (atan(trkRC.tlambda[firstTS]) +0.5*3.14159) / 2. ) );	// no (-) to adapt coordinates
		trkPhi = trkRC.phi[firstTS];
		
		dR = sqrt(pow(mcEta-trkEta,2)+pow(mcPhi-trkPhi,2));
		testMom = 0.3 * 4. / ( abs(trkRC.r1[firstTS]) * 1000. * cos( atan( trkRC.tlambda[firstTS] ) ) );
		
		if(dR < cutRtrk && dR < pre_dR && abs(testMom-mcE)/mcE < 0.1){
			bestTS = lastTS;	//to improve adding closest track condition
			bestI = iTr;
			pre_dR = dR;
			if(trkRC.r1[firstTS] < 0){
				mom0 = testMom;
				mom1 = 0.3 * 4. / ( abs(trkRC.r1[lastTS]) * 1000. * cos( atan( trkRC.tlambda[lastTS] ) ) );
			} 
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
	
	trkTheta = trkTheta *180./3.14159;
	if(trkTheta > 36.5 && trkTheta < 143.5) sumE = getEneBarrel(sumE, trkTheta);
	else if(trkTheta < 36.5 || trkTheta > 143.5) sumE = getEneEndcap(sumE, trkTheta);
	else sumE = 0.;
	
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
		if(dR < cutR && ecBarSimHits.e[iEB]>thr) sumE += ecBarSimHits.e[iEB] * 1.0672142727;
	}
	
	for(int iEE = 0; iEE < ecEndSimHits.nhits; iEE++){
		
		hitEta = getEta(ecEndSimHits.x[iEE], ecEndSimHits.y[iEE], ecEndSimHits.z[iEE]);
		hitPhi = getPhi(ecEndSimHits.x[iEE], ecEndSimHits.y[iEE]);
		
		dR = sqrt(pow(hitEta-trkEta,2)+pow(hitPhi-trkPhi,2));
		if(dR < cutR && ecEndSimHits.e[iEE]>thr) sumE += ecEndSimHits.e[iEE] * 1.0672142727;
	}
	
	for(int iHB = 0; iHB < hcBarSimHits.nhits; iHB++){
		
		hitEta = getEta(hcBarSimHits.x[iHB], hcBarSimHits.y[iHB], hcBarSimHits.z[iHB]);
		hitPhi = getPhi(hcBarSimHits.x[iHB], hcBarSimHits.y[iHB]);
		
		dR = sqrt(pow(hitEta-trkEta,2)+pow(hitPhi-trkPhi,2));
		if(dR < cutR && hcBarSimHits.e[iHB]>thr) sumE += hcBarSimHits.e[iHB] * 49.2031079063;
	}
	
	for(int iHE = 0; iHE < hcEndSimHits.nhits; iHE++){
		
		hitEta = getEta(hcEndSimHits.x[iHE], hcEndSimHits.y[iHE], hcEndSimHits.z[iHE]);
		hitPhi = getPhi(hcEndSimHits.x[iHE], hcEndSimHits.y[iHE]);
		
		dR = sqrt(pow(hitEta-trkEta,2)+pow(hitPhi-trkPhi,2));
		if(dR < cutR && hcEndSimHits.e[iHE]>thr) sumE += hcEndSimHits.e[iHE] * 53.6263377733;
	}
	
	for(int iHR = 0; iHR < hcRinSimHits.nhits; iHR++){
		
		hitEta = getEta(hcRinSimHits.x[iHR], hcRinSimHits.y[iHR], hcRinSimHits.z[iHR]);
		hitPhi = getPhi(hcRinSimHits.x[iHR], hcRinSimHits.y[iHR]);
		
		dR = sqrt(pow(hitEta-trkEta,2)+pow(hitPhi-trkPhi,2));
		if(dR < cutR && hcRinSimHits.e[iHR]>thr) sumE += hcRinSimHits.e[iHR] * 62.2125698179;
	}
	
	/*trkTheta = trkTheta *180./3.14159;
	if(trkTheta > 36.5 && trkTheta < 143.5) sumE = getEneBarrel(sumE, trkTheta);
	else if(trkTheta < 36.5 || trkTheta > 143.5) sumE = getEneEndcap(sumE, trkTheta);
	else sumE = 0.; correction from calib*/	
	
	return sumE;
}



// pandora reco energy (not used now)
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



// generic fit procedure for reco and match spectra
// minG=-0.015, maxG=0.01, minC=-0.04, maxC=0.02, optT=e(energy),t(angle), optF=f(fit resolution), n(no fit resolution)
void fitResolEff(vector<TH1F*> v, TGraphErrors* gr, TGraphErrors* ge, double minG, double maxG, double minC, double maxC, char optT='e', char optF='n'){
	
	vector<TF1*> fsk(v.size());
	TF1* gauss = new TF1("gauss", "gaus", -0.1, 0.1);

	double minEta, maxEta;
	int minx, manx;
	
	if(gr!=NULL) gr->Print();
	if(ge!=NULL) ge->Print();
	
	for(int i = 0; i < fsk.size(); i++){
		
		fsk[i] = new TF1("fsk", "crystalball", -0.1, 0.1);
		fsk[i]->SetParNames("k","#mu","#sigma","#alpha","n");
		
		v[i]->Fit(gauss, "NQ0", "", minG, maxG);
		fsk[i]->SetParameters(gauss->GetParameter(0),gauss->GetParameter(1),gauss->GetParameter(2),1.,10.);
		
		v[i]->Fit(fsk[i], "SMQ+", "", minC, maxC);

		minx = v[i]->FindBin(fsk[i]->GetParameter(1)-5*fsk[i]->GetParameter(2));
		manx = v[i]->FindBin(fsk[i]->GetParameter(1)+5*fsk[i]->GetParameter(2));
		
		if(optT == 'e'){
			if(gr != NULL){
				gr->SetPoint(i, enSteps[i], fsk[i]->GetParameter(2)*100);
				gr->SetPointError(i, 2.5, fsk[i]->GetParError(2)*100);
				trackCutsE[i] = 5*fsk[i]->GetParameter(2);
			}
			if(ge != NULL){
				ge->SetPoint(i, enSteps[i], v[i]->Integral(minx,manx) / evtBinsE[i]);
				ge->SetPointError(i, 2.5, sqrt(v[i]->Integral(minx,manx)) / evtBinsE[i]);
			}
		}
		else{
//			minEta = getEtafromTheta(thSteps[i]+2.5);
//			maxEta = getEtafromTheta(thSteps[i]-2.5);
			if(gr != NULL){
				gr->SetPoint(i, thSteps[i], fsk[i]->GetParameter(2)*100);
				gr->SetPointError(i, 2.5, fsk[i]->GetParError(2)*100);
				trackCutsTh[i] = 5*fsk[i]->GetParameter(2);
			}
			if(ge != NULL){
				ge->SetPoint(i, thSteps[i], v[i]->Integral(minx,manx) / evtBinsTh[i]);
				ge->SetPointError(i, 2.5, sqrt(v[i]->Integral(minx,manx)) / evtBinsTh[i]);
			}
		}
	}
	
	if(optF != 'f') return;
	
	TF1* fitgr = new TF1("fitgr", "sqrt(([0]/x^0.5)^2+([1])^2)",1,99);
	fitgr->SetParNames("a [%%]","b [%%]");
	fitgr->SetParameters(1.5, 0.18);
	gr->Fit(fitgr,"SMR+");
	gStyle->SetOptFit(111);
}

/*
void fitEfficiencies(vector<double> x, vector<TH1F*> v, TGraphErrors* g, double minG=-0.015, double maxG=0.01, double minC=-0.04, double maxC=0.02, const char opt = 'e'){
	
	vector<TF1*> fsk(v.size());
	TF1* gauss = new TF1("gauss", "gaus", -0.1, 0.1);
	
	double minEta, maxEta;
	int minx, manx;
	
	for(int i = 0; i < fsk.size(); i++){
		
		fsk[i] = new TF1("fsk", "crystalball", -0.1, 0.1);
		fsk[i]->SetParNames("k","#mu","#sigma","#alpha","n");
		
		v[i]->Fit(gauss, "NQ0", "", minG, maxG);
		fsk[i]->SetParameters(gauss->GetParameter(0),gauss->GetParameter(1),gauss->GetParameter(2),1.,10.);
		
		v[i]->Fit(fsk[i], "SM+", "", minC, maxC);
		minx = v[i]->FindBin(fsk[i]->GetParameter(1)-5*fsk[i]->GetParameter(2));
		manx = v[i]->FindBin(fsk[i]->GetParameter(1)+5*fsk[i]->GetParameter(2));
		
		if(opt == 'e'){
			cout << "EvBinsE " << i << ": " << evtBinsE[i] << endl;
			cout << "FoundEvts " << i << ": " << v[i]->Integral(minx,manx) << endl;
			g->SetPoint(i, x[i], v[i]->Integral(minx,manx) / evtBinsE[i]);
			g->SetPointError(i, 5., sqrt(v[i]->Integral(minx,manx)) / evtBinsE[i]);
		}
		else{
			minEta = getEtafromTheta(x[i]+5.);
			maxEta = getEtafromTheta(x[i]-5.);
			g->SetPoint(i, .5*(minEta+maxEta), v[i]->Integral(minx,manx) / evtBinsTh[i]);
			g->SetPointError(i, .5*(maxEta-minEta), sqrt(v[i]->Integral(minx,manx)) / evtBinsTh[i]);
		}
	}
	
}*/



#endif