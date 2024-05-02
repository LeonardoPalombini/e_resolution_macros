//declare hists and graphs

#include "objs.hh"
#include "dataUtils.cpp"

void declareDataObjs(){

	for(int i = 0; i< reco_Ehit.size(); i++){
		reco_Ehit[i] = new TH1F( Form("reco_Ehit_%i",i), Form("(E_{reco}-E_{mc})/E_{mc} (hits) %.0f GeV; #DeltaE/E",enSteps[i]), 60,-0.09,0.09);
//		reco_Epnd[i] = new TH1F( Form("reco_Epnd_%i",i), Form("(E_{reco}-E_{mc})/E_{mc} (Pandora) %.0f GeV; #DeltaE/E",enSteps[i]), 50,-0.06,0.06);
		reco_pTkMc[i] = new TH1F( Form("reco_pTkMc_%i",i), Form("(p_{reco}-p_{mc})/p_{mc} (ACTS) %.0f GeV; #Deltap/p",enSteps[i]), 50,-0.09,0.09);
		reco_pTkHt[i] = new TH1F( Form("reco_pTkHt_%i",i), Form("(E_{hits}-E_{trk})/E_{trk} (ACTS+hits) %.0f GeV; #DeltaE/E",enSteps[i]), 50,-0.09,0.09);
//		layerHit[i] = new TH1F( Form("layerHit_%i",i), Form("Hit layers %.0f GeV; E [GeV]",enSteps[i]), 10,0,10);
	}
	
	double eta;
	for(int i = 0; i< reco_Ehit_th.size(); i++){
//		eta = .5 * ( getEtafromTheta(thSteps[i]+5.) + getEtafromTheta(thSteps[i]-5.) );
//		reco_Ehit_th[i] = new TH1F( Form("reco_Ehit_th_%i",i), Form("(E_{reco}-E_{mc})/E_{mc} (hits) #eta=%.1f; #DeltaE/E",eta), 50,-0.06,0.06);
		reco_pTkMc_th[i] = new TH1F( Form("reco_pTkMc_th_%i",i), Form("(p_{reco}-p_{mc})/p_{mc} (ACTS) #theta=%.1f; #Deltap/p",thSteps[i]), 50,-0.09,0.09);
		reco_pTkHt_th[i] = new TH1F( Form("reco_pTkHt_th_%i",i), Form("(E_{hits}-E_{trk})/E_{trk} (ACTS+hits) #theta=%.1f; #DeltaE/E",thSteps[i]), 40,-0.09,0.09);
	}
	
	resE_vsE = new TGraphErrors();
	resE_vsE->SetTitle("Energy resolution (hits) vs True E (sim); true E [GeV]");
	
//	resE_vsE_pnd = new TGraphErrors();
//	resE_vsE_pnd->SetTitle("Energy resolution (Pandora) vs True E (sim); true E [GeV]");
	
	resP_vsE = new TGraphErrors();
	resP_vsE->SetTitle("Momentum resolution vs True E; true E [GeV]");
	effP_vsE = new TGraphErrors();
	effP_vsE->SetTitle("Tracking efficiency vs True E; true E [GeV]");
	
	resP_vsTh = new TGraphErrors();
	resP_vsTh->SetTitle("Momentum resolution vs True #theta; true #theta");
	effP_vsTh = new TGraphErrors();
	effP_vsTh->SetTitle("Tracking efficiency vs True #theta; true #theta");
	
	effPHt_vsE = new TGraphErrors();
	effPHt_vsE->SetTitle("Match efficiency vs True E; true E [GeV]");
	effPHt_vsTh = new TGraphErrors();
	effPHt_vsTh->SetTitle("Match efficiency vs True #theta; true #theta");
	
}