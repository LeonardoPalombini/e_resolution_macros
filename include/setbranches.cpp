// set branch addresses

#include "structs.hh"

void branch_particleMC(TTree* nt, particleMC &s){
	
	nt->SetBranchAddress("evevt", &(s.nevt));
	nt->SetBranchAddress( "nmcp" , &(s.npt) );
	nt->SetBranchAddress( "mcpdg" , &(s.pdg) );
	nt->SetBranchAddress( "mcvtx" , &(s.vtx) );
	nt->SetBranchAddress( "mcvty" , &(s.vty) );
	nt->SetBranchAddress( "mcvtz" , &(s.vtz) );
	nt->SetBranchAddress( "mcmox" , &(s.mox) );
	nt->SetBranchAddress( "mcmoy" , &(s.moy) );
	nt->SetBranchAddress( "mcmoz" , &(s.moz) );
	nt->SetBranchAddress( "mcene" , &(s.e) );
	return;
}

void branch_particleRC(TTree* nt, particleRC &s){
	
	nt->SetBranchAddress( "nrec" , &(s.npt) );
	nt->SetBranchAddress( "rctyp" , &(s.pdg) );
	nt->SetBranchAddress( "rcmox" , &(s.mox) );
	nt->SetBranchAddress( "rcmoy" , &(s.moy) );
	nt->SetBranchAddress( "rcmoz" , &(s.moz) );
	nt->SetBranchAddress( "rcene" , &(s.e) );
	return;
}

void branch_trackRC(TTree* nt, trackRC &s){
	
	nt->SetBranchAddress( "ntrk" , &(s.ntr) );
	nt->SetBranchAddress( "trsca" , &(s.idxCalo) );
	nt->SetBranchAddress( "trsip" , &(s.idxVt) );
	nt->SetBranchAddress( "ntrst" , &(s.nts) );
	nt->SetBranchAddress( "tsdze" , &(s.d0) );
	nt->SetBranchAddress( "tszze" , &(s.z0) );
	nt->SetBranchAddress( "tsphi" , &(s.phi) );
	nt->SetBranchAddress( "tsome" , &(s.r1) );
	nt->SetBranchAddress( "tstnl" , &(s.tlambda) );
	nt->SetBranchAddress( "tsrpx" , &(s.sx) );
	nt->SetBranchAddress( "tsrpy" , &(s.sy) );
	nt->SetBranchAddress( "tsrpz" , &(s.sz) );
	return;
}

void branch_jetRC(TTree* nt, jetRC &s){
	
	nt->SetBranchAddress( "njet" , &(s.njets) );
	nt->SetBranchAddress( "jmox" , &(s.mox) );
	nt->SetBranchAddress( "jmoy" , &(s.moy) );
	nt->SetBranchAddress( "jmoz" , &(s.moz) );
	nt->SetBranchAddress( "jene" , &(s.e) );
	return;
}

void branch_clusterRC(TTree* nt, clusterRC &s){
	
	nt->SetBranchAddress( "nclu" , &(s.nclus) );
	nt->SetBranchAddress( "clpox" , &(s.x) );
	nt->SetBranchAddress( "clpoy" , &(s.y) );
	nt->SetBranchAddress( "clpoz" , &(s.z) );
	nt->SetBranchAddress( "clene" , &(s.e) );
	return;
}

void branch_caloData(TTree* nt, caloData &s){
	
	nt->SetBranchAddress("evevt", &(s.nevt));
	nt->SetBranchAddress( "ncah" , &(s.nhits) );
	nt->SetBranchAddress( "capox" , &(s.x) );
	nt->SetBranchAddress( "capoy" , &(s.y) );
	nt->SetBranchAddress( "capoz" , &(s.z) );
	nt->SetBranchAddress( "caene" , &(s.e) );
	return;
}

void branch_trackerData(TTree* nt, trackerData &s){
	
	nt->SetBranchAddress("evevt", &(s.nevt));
	nt->SetBranchAddress( "ntrh" , &(s.nhits) );
	nt->SetBranchAddress( "thpox" , &(s.x) );
	nt->SetBranchAddress( "thpoy" , &(s.y) );
	nt->SetBranchAddress( "thpoz" , &(s.z) );
	nt->SetBranchAddress( "thedp" , &(s.e) );
	return;
}

void branch_caloSimData(TTree* nt, caloData &s){
	
	nt->SetBranchAddress("evevt", &(s.nevt));
	nt->SetBranchAddress( "nsch" , &(s.nhits) );
	nt->SetBranchAddress( "scpox" , &(s.x) );
	nt->SetBranchAddress( "scpoy" , &(s.y) );
	nt->SetBranchAddress( "scpoz" , &(s.z) );
	nt->SetBranchAddress( "scene" , &(s.e) );
	return;
}

void branch_trackerSimData(TTree* nt, trackerData &s){
	
	nt->SetBranchAddress("evevt", &(s.nevt));
	nt->SetBranchAddress( "nsth" , &(s.nhits) );
	nt->SetBranchAddress( "stpox" , &(s.x) );
	nt->SetBranchAddress( "stpoy" , &(s.y) );
	nt->SetBranchAddress( "stpoz" , &(s.z) );
	nt->SetBranchAddress( "stedp" , &(s.e) );
	return;
}