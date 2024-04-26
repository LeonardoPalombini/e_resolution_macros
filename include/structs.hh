// header with data struct types
#ifndef STRUCTS_HH
#define STRUCTS_HH


struct particleMC{
	int nevt;
	int npt;
	int pdg[10000];
	float vtx[10000];
	float vty[10000];
	float vtz[10000];
	float mox[10000];
	float moy[10000];
	float moz[10000];
	float e[10000];
};

struct particleRC{
	int npt;
	int pdg[100];	//called "type" in reco branch
	float mox[100];
	float moy[100];
	float moz[100];
	float e[100];
};

struct trackRC{
	int ntr;
	int idxVt[100];
	int idxCalo[100];
	int nts;
	float d0[100];
	float z0[100];
	float phi[100];
	float r1[100];
	float tlambda[100];
	float sx[100];
	float sy[100];
	float sz[100];
};

struct jetRC{
	int njets;
	float mox[100];
	float moy[100];
	float moz[100];
	float e[100];
};

struct clusterRC{
	int nclus;
	float x[1000];
	float y[1000];
	float z[1000];
	float e[1000];
};

struct caloData{
	int nevt;
	int nhits;
	float x[10000];
	float y[10000];
	float z[10000];
	float e[10000];
};

struct trackerData{
	int nevt;
	int nhits;
	float x[1000];
	float y[1000];
	float z[1000];
	float e[1000];
};


#endif