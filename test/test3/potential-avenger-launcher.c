//potential-avenger-launcher.c
//Andrew Stershic
//DCML, Duke University
//(c) 2013, 2014

#include <potential-avenger.h>

using namespace std;

void writeDisplacements (const vector<double>& uIn, const double& L) {
    //write displacements to file for testing
    string dispFil = "./raw_disp.out";
    FILE * pFileP;
    pFileP = fopen(dispFil.c_str(), "w");
    fprintf( pFileP, "#raw displacements normalized by length\n");
    for (unsigned j = 0; j < uIn.size(); ++j) fprintf(pFileP, "%0.8g\n",uIn.at(j)/L);
	fclose(pFileP);
	return;
}

int main(int argc, const char* argv[]) {
    assert(argc == 19);
 
	//read input from potential-avenger-launcher.py
    double strain_rate = atof(argv[1]);
    double ts_refine = atof(argv[2]);
    double end_t = atof(argv[3]);
    unsigned Nelt = atoi(argv[4]);
    double lc = atof(argv[5]);
    double alpha = atof(argv[6]);
    double CV = atof(argv[7]);
    unsigned startWithLoad = atoi(argv[8]);
    unsigned printVTK = atoi(argv[9]);
    string sm = string(argv[10]);
    int oneAtATime = atoi(argv[11]);
    double minOpenDist = atof(argv[12]);
    unsigned TLSoption = atoi(argv[13]);
    unsigned visualizeCracks = atoi(argv[14]);
    unsigned fullCompression = atoi(argv[15]);
	unsigned elemDeath = atoi(argv[16]);
	unsigned frontExtension = atoi(argv[17]);
	unsigned maxIteration = atoi(argv[18]);
    string path = ".";
 
    PotentialAvenger pa = PotentialAvenger(strain_rate, ts_refine, end_t, Nelt, lc, printVTK, oneAtATime, minOpenDist, alpha, TLSoption, visualizeCracks, fullCompression, sm, elemDeath, frontExtension, maxIteration, path);

	//"serious" hard-coded input
	unsigned Nnod = Nelt + 1;
	double E = 610.0;
	double rho = 3.9e-6;
	double A = 0.2;
	double L = 1.0;
	double Yc = 8.1969e-4;
	vector<double> pg;
	pg.push_back((1-sqrt(3)/3)/2); pg.push_back((1+sqrt(3)/3)/2); 
	vector<double> wg;
	wg.push_back(0.5); wg.push_back(0.5); 
	vector<double> phiIn = vector<double>(Nnod, -1.0);
	bool vbc = true;

	double h = 1.0/static_cast<double>(Nelt) * L;
	double alfa = 1.0 - pow(1.0 - L * strain_rate * sqrt(rho / (2*Yc)),2);
	double qty = sqrt(2.0 * Yc * (1.0 - alfa)/E) * static_cast<double>(startWithLoad);
	double e0 = qty;
	vector<double> eIn = vector<double>(Nelt,e0);
	vector<double> xIn = vector<double>(Nnod,0);
	vector<double> uIn = vector<double>(Nnod,0);
	vector<double> vIn = vector<double>(Nnod,0);
	vector<double> YcvIn = vector<double>(Nnod, Yc);
	unsigned i1 = 0.6 * (double)Nelt -1;
	unsigned i2 = 0.6 * (double)Nelt;
	YcvIn.at(i1) *= (1.0 - alfa);
	YcvIn.at(i2) *= (1.0 - alfa);
	DamageModel dm = DamageModel("Parabolic", lc);


	for (unsigned j = 0; j < Nnod; ++j) {
		xIn[j] = static_cast<double>(j) * h;
		uIn[j] = xIn[j] * e0;
		vIn[j] = static_cast<double>(vbc) * strain_rate * xIn[j];
		if (xIn[j] >= 0.6) phiIn[j] = 2.0 * h - xIn[j] + 0.6;
		else phiIn[j] = 2.0 * h + xIn[j] - 0.6;
	}	
	vIn[Nnod-1] = strain_rate;

	vector<Segment*> segIn;
	Segment* seg1 = new Segment(0.6, 2.0*h, 1);
	Segment* seg2 = new Segment(0.6, 2.0*h, -1);
	segIn.push_back(seg1);
	segIn.push_back(seg2);
	unsigned nucleated = 1;

    pa.run(E, rho, A, L, Yc, pg, wg, phiIn, segIn, nucleated, vbc, eIn, xIn, uIn, vIn, YcvIn, dm);
	
	//write displacements to file for testing
	writeDisplacements(uIn,L);
}

