#include <cstdlib>
#include <string>
using namespace std;
//the specification std:: before cin/cout can be ommitted
#include <iostream>
//the library for a stream on the standard input/output
#include <fstream>
//the library for classes ofstream, ifstream, fstream 
// - derived from ostream, istream
#include <sstream>
//the library for the class ostringstream
#include <math.h>
// define Console to display all results
//#define Console 
//the library containing the class of a structure number calculator
//#include "SNcA.h"
#include "SNc.h"
//the library containing the class of multi-dimensional polynomials
//#include "MDpA.h"
#include "MDp.h"

int readX(float X[60], string nameX)
// the function reads gC parameters from a file of the given name 
		{
	string sX;
	char c;

	cout << "\n Introduce the name of a parameter file..\n";
	// the string appeares on the display (standard output)
	//cin >> nameX;
	ifstream INP(nameX.c_str());
	if (!INP) {
		cout << "\n Opening mistake";
	}
	do {
		INP.get(c);
		if (!INP.eof())
			sX += c;
	} while (!INP.eof());
	cout << endl;
	istringstream mem(sX);
	int i = 1;
	while (!mem.eof())
//  do
	{
		mem >> X[i];
		i++;
	}
//  while (!mem.eof());

	return i - 2;
}

int main(int argc, char** argv)

{
//#define Console 1
	//for (int i = 0; i < argc; ++i)
	//cout << argv[i] << "\n";
	if (argc < 6) 
	{
		cout << "five arguments are necessary" << endl;
		return 0;
	}
	SNc SN;
	SN.calcSN(SN.port, SN.dimens, SN.var, SN.acls, SN.cls, SN.p, SN.Bstr, SN.cp,
			argv[1]);
	cout << "gCports = " << SN.port << endl;
	cout << "gCdimension = " << SN.dimens << endl << endl;

	int max1, max2;
	max1 = SN.varN(SN.port, SN.dimens, SN.var, SN.acls, SN.cls, SN.cp);
	cout << "max1 = " << max1 << endl;
			
// vector X of gC circuit parameters:  
	float X[60];
	max2 = readX(X, argv[2]);
	cout << "max2 = " << max2 << endl;
	if (max1 != max2)
		cout << " Warning: different numbers of variables and parameters!"
				<< endl << endl;

// class of polynomials in s domain:
	MDp S[SN.port];
	int Mp[SN.dimens];
	SN.Mpow(SN.port, SN.dimens, SN.acls, SN.p, Mp);
// cout << Mp[0] <<  Mp[1] << Mp[2] << endl;
	for (int i = 0; i < SN.port; i++) 
	{
		S[i].n = SN.dimens;
		for (int j = 0; j < SN.dimens; j++)
			S[i].k[j + 1] = Mp[j];
		SN.SNtoPoly(i, X, S[i].P, SN.dimens, SN.var, SN.acls, SN.cls, SN.p,
				SN.Bstr, SN.cp);
	}

// begin, omit to calculate samples from parameters 
/*
	for (int i = 0; i < SN.port; i++) 
	{
		std::string text = "s";
		text.push_back(i + '0');
		S[i].readPoly(text);
	}
// end, remain to obtain samples from s-domain */

	for (int i = 0; i < SN.port; i++) 
	{
		std::string text = "A";
		text.push_back(i + '0');
		S[i].writePoly(text);
	}

	for (int i = 0; i < SN.port; i++) 
	{
		S[i].T2to1();
	}

	for (int i = 0; i < SN.port; i++) 
	{
		std::string text = "M";
		text.push_back(i + '0');
		S[i].writePoly(text);
	}

// class of polynomials in z domain:
	MDp Z[SN.port];
	for (int i = 0; i < SN.port; i++) 
	{
		Z[i].n = SN.dimens;
		for (int j = 0; j < SN.dimens; j++)
			Z[i].k[j + 1] = Mp[j];
		S[i].biliT();
		Z[i].bili(S[i].n, S[i].k, S[i].P, S[i].T);
	}
	for (int i = 0; i < SN.port; i++) 
	{
		std::string text = "z";
		text.push_back(i + '0');
		Z[i].writePoly(text);
	}	
	
// class of denominator polynomials of a bank in z domain:
	MDp Zd[SN.port];
	for (int i = 0; i < SN.port; i++) 
		Zd[i].n = SN.dimens;
	for (int i = 1; i < SN.port; i++) 
	{
		std::string text = "zd";
		text.push_back(i + '0');
		Zd[i].readPoly(text);
	}

// class of numerator polynomials of a bank in z domain:
	MDp Zn[SN.port];
	for (int i = 0; i < SN.port; i++) 
		Zn[i].n = SN.dimens;
	for (int i = 1; i < SN.port; i++) 
	{
		std::string text = "zn";
		text.push_back(i + '0');
		Zn[i].readPoly(text);
	}

// class of multiplyed polynomials for denominators
	MDp ZMd[SN.port];
	for (int i = 1; i < SN.port; i++)
	{
		ZMd[i].multiply(Z[0].n, Z[0].k, Z[0].P, Zd[i].k, Zd[i].P);
		string text = "multD";
		text.push_back(i + '0');
		ZMd[i].writePoly(text);
	}

// class of multiplyed polynomials for numerators
	MDp ZMn[SN.port];
	for (int i = 1; i < SN.port; i++)
	{
		ZMn[i].multiply(Z[i].n, Z[i].k, Z[i].P, Zn[i].k, Zn[i].P);
		string text = "multN";
		text.push_back(i + '0');
		ZMn[i].writePoly(text);
	}
	
// N - numbers of samples  
		int N[3];
		    N[0] = atoi(argv[3]);
		    N[1] = atoi(argv[4]);
		    N[2] = atoi(argv[5]);

// input impulse xx:  
// dimensions of the array xx not smaller then numbers of samples!
//			float xx[128][128][64];
			float xx[32][32][32];
			string tIn = "tI";
			ifstream tInput;
			tInput.open(tIn.c_str());
			if (tInput) 
			{
		    for (int n1=0; n1<N[0]; n1++)
		    for (int n2=0; n2<N[1]; n2++)
		    for (int n3=0; n3<N[2]; n3++)
				tInput >> xx[n1][n2][n3];
		    }
            else
				cout << " Warning: input image is missing "
						<< endl;
// filter response Z[i].y calculation
// 1-st filtration
// zeroing of respose from all inputs/outputs:  
		float sumOut[N[0]][N[1]][N[2]];
		for (int i1 = 0; i1 < N[0]; i1++)
		for (int i2 = 0; i2 < N[1]; i2++)
		for (int i3 = 0; i3 < N[2]; i3++)
			sumOut[i1][i2][i3] = 0;
		for (int i = 1; i < SN.port; i++) 
		{
			string fname = "t";
			fname.push_back((i-1) + 'I');
//			Z[i].TimeResp(N, Z[i].k, Z[i].P, Z[0].P, xx, fname);
			ZMd[i].TimeResp(N, ZMd[i].k, ZMn[i].P, ZMd[i].P, xx, fname);
//			Zd[i].TimeResp(N, Zd[i].k, Zn[i].P, Zd[i].P, xx, fname);
		for (int j1 = 0; j1 < N[0]; j1++)
		for (int j2 = 0; j2 < N[1]; j2++)
		for (int j3 = 0; j3 < N[2]; j3++)
//			sumOut[j1][j2][j3] = sumOut[j1][j2][j3] + Z[i].y[j1][j2][j3];
	    	sumOut[j1][j2][j3] = sumOut[j1][j2][j3] + ZMd[i].y[j1][j2][j3];
//			sumOut[j1][j2][j3] = sumOut[j1][j2][j3] + Zd[i].y[j1][j2][j3];
		}
// 1-st inversion of the sequence		
		for (int j1 = 0; j1 < N[0]; j1++)
		for (int j2 = 0; j2 < N[1]; j2++)
		for (int j3 = 0; j3 < N[2]; j3++)
	    	xx[j1][j2][j3] = sumOut[N[0]-j1-1][N[1]-j2-1][N[2]-j3-1];
// 2-d filtration
// zeroing of respose from all inputs/outputs:  
		for (int i1 = 0; i1 < N[0]; i1++)
		for (int i2 = 0; i2 < N[1]; i2++)
		for (int i3 = 0; i3 < N[2]; i3++)
			sumOut[i1][i2][i3] = 0;
		for (int i = 1; i < SN.port; i++) 
		{
			string fname = "t";
			fname.push_back((i-1) + 'I');
//			Z[i].TimeResp(N, Z[i].k, Z[i].P, Z[0].P, xx, fname);
			ZMd[i].TimeResp(N, ZMd[i].k, ZMn[i].P, ZMd[i].P, xx, fname);
//			Zd[i].TimeResp(N, Zd[i].k, Zn[i].P, Zd[i].P, xx, fname);
		for (int j1 = 0; j1 < N[0]; j1++)
		for (int j2 = 0; j2 < N[1]; j2++)
		for (int j3 = 0; j3 < N[2]; j3++)
//			sumOut[j1][j2][j3] = sumOut[j1][j2][j3] + Z[i].y[j1][j2][j3];
	    	sumOut[j1][j2][j3] = sumOut[j1][j2][j3] + ZMd[i].y[j1][j2][j3];
//			sumOut[j1][j2][j3] = sumOut[j1][j2][j3] + Zd[i].y[j1][j2][j3];
		}
// 2-d inversion of the sequence		
		for (int j1 = 0; j1 < N[0]; j1++)
		for (int j2 = 0; j2 < N[1]; j2++)
		for (int j3 = 0; j3 < N[2]; j3++)
	    	xx[j1][j2][j3] = sumOut[N[0]-j1-1][N[1]-j2-1][N[2]-j3-1];
		for (int j1 = 0; j1 < N[0]; j1++)
		for (int j2 = 0; j2 < N[1]; j2++)
		for (int j3 = 0; j3 < N[2]; j3++)
	    	sumOut[j1][j2][j3] = xx[j1][j2][j3];
		string fname = "tOut";
		ofstream timeOut;
		timeOut.open(fname.c_str(), ios::out);
		for (int j1 = 0; j1 < N[0]; j1++)
		for (int j2 = 0; j2 < N[1]; j2++)
		for (int j3 = 0; j3 < N[2]; j3++)
		{
			timeOut.precision(6);
			timeOut.width(12);
			timeOut << fixed << sumOut[j1][j2][j3];
			timeOut << endl;
		}
	return 0;
}
