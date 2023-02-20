/*
 * sn.cpp
 *
 *  Created on: Aug 19, 2019
 *      Author: konrad
 */

using namespace std;
// the specification std:: before cin/cout can be ommitted
#include <iostream>
// the library for a stream on the standard input/output
#include <fstream>
// the library for classes ofstream, ifstream, fstream
// - derived from ostream, istream
#include <sstream>
// the library for the class ostringstream
#include <cmath>

#include "includes/MDp.h"
#include "includes/SNc.h"
#include "includes/hooke-jeeves.h"
char type;
extern int XX;
extern int samp;
SNc SN;
extern int d1, d2, d3;
double P1[200 * 200 * 200];
unsigned char read = 0;
MDp *Z1;
MDp *S1;
int initSN(char *prjName) {
  SN.calcSN(SN.port, SN.dimens, SN.var, SN.acls, SN.cls, SN.p, SN.Bstr, SN.cp,
            prjName);
  cout << "gCports = " << SN.port << endl;
  cout << "gCdimension = " << SN.dimens << endl << endl;

  int max1 = 0;
  max1 = SN.varN(SN.port, SN.dimens, SN.var, SN.acls, SN.cls, SN.cp);
  cout << "max1 = " << max1 << endl;
  return SN.port;
}
char anal;
int nr;
extern float ideal[8192];
double calculation(struct variable *vekX, int nVar) {
  double res = 0;
  // char analize = 's';
  // vector X of gC circuit parameters:
  float X[60];
  /*	max2 = readX(X, argv[2]);
   cout << "max2 = " << max2 << endl;
   if (max1 != max2)
   cout << " Warning: different numbers of variables and parameters!"
   << endl << endl;
   */
  for (int i = 0; i < nVar; i++) X[i] = 0;
  for (int i = 1; i <= nVar; i++) {
    X[i] = vekX[i].value;
    // printf("ideal:%f\n", ideal[i]);
#ifdef DEBUG
    printf("Xi:%f\n", X[i]);
#endif
  }
  // class of polynomials in s domain:
  MDp S[SN.port];
  int Mp[SN.dimens];
  SN.Mpow(SN.port, SN.dimens, SN.acls, SN.p, Mp);
  for (int i = 0; i < SN.port; i++) {
    S[i].n = SN.dimens;
    for (int j = 0; j < SN.dimens; j++) S[i].k[j + 1] = Mp[j];
    SN.SNtoPoly(i, X, S[i].P, SN.dimens, SN.var, SN.acls, SN.cls, SN.p, SN.Bstr,
                SN.cp);
  }

  if (anal != 's') {
    for (int i = 0; i < SN.port; i++) {
      S[i].T2to1();
    }
  }

  // class of polynomials in z domain:
  MDp Z[SN.port];
  for (int i = 0; i < SN.port; i++) {
    Z[i].n = SN.dimens;
    for (int j = 0; j < SN.dimens; j++) Z[i].k[j + 1] = Mp[j];
    S[i].biliT();
    Z[i].bili(S[i].n, S[i].k, S[i].P, S[i].T);
  }

  // class of denominator polynomials of a bank in z domain:
  MDp Zd[SN.port];
  for (int i = 0; i < SN.port; i++) Zd[i].n = SN.dimens;
  for (int i = 1; i < SN.port; i++) {
    std::string text = "zd";
    text.push_back(i + '0');
    Zd[i].readPoly(text);
  }

  // class of numerator polynomials of a bank in z domain:
  MDp Zn[SN.port];
  for (int i = 0; i < SN.port; i++) Zn[i].n = SN.dimens;
  for (int i = 1; i < SN.port; i++) {
    std::string text = "zn";
    text.push_back(i + '0');
    Zn[i].readPoly(text);
  }

  // class of multiplyed polynomials for denominators
  MDp ZMd[SN.port];
  for (int i = 1; i < SN.port; i++) {
    ZMd[i].multiply(Z[0].n, Z[0].k, Z[0].P, Zd[i].k, Zd[i].P);
  }

  // class of multiplyed polynomials for numerators
  MDp ZMn[SN.port];
  for (int i = 1; i < SN.port; i++) {
    ZMn[i].multiply(Z[i].n, Z[i].k, Z[i].P, Zn[i].k, Zn[i].P);
  }

  if (anal == 's') {
    if (read == 0) {
	// class of given polynomials (s domain):
      S1 = new MDp[SN.port];
      for (int i = 0; i < SN.port; i++) {
        std::string text = "s";
        text.push_back(i + '0');
        S1[i].readPoly(text);
      }
      read = 1;
    }
#ifdef DEBUG
    printf("sn.port:%d\n", SN.port);
    printf("s1:%d\n", S[0].k[1]);
    printf("s2:%d\n", S[0].k[2]);
    printf("s3:%d\n", S[0].k[3]);
    printf("s1:%d\n", S[1].k[1]);
    printf("s2:%d\n", S[1].k[2]);
    printf("s3:%d\n", S[1].k[3]);
#endif
    int wsk = 0;
    for (int i = 0; i < SN.port; i++)
      for (int j1 = 0; j1 <= S[i].k[1]; j1++)
        for (int j2 = 0; j2 <= S[i].k[2]; j2++)
          for (int j3 = 0; j3 <= S[i].k[3]; j3++) {
#ifdef DEBUG
            printf("sss\n");
            printf("S1:%f S:%f\n", S1[i].P[j1][j2][j3], S[i].P[j1][j2][j3]);
            printf("returnnn res:%f\n", res);
#endif
            P1[wsk] = S[i].P[j1][j2][j3];
            if (S1[i].P[j1][j2][j3] != 0.0) wsk++;
            res = res + (S1[i].P[j1][j2][j3] - S[i].P[j1][j2][j3]) *
                            (S1[i].P[j1][j2][j3] - S[i].P[j1][j2][j3]);
          }
  }

  if (anal == 'z') {
    if (read == 0) {
	// class of given polynomials (z domain):
      Z1 = new MDp[SN.port];
      for (int i = 0; i < SN.port; i++) {
        std::string text = "z";
        text.push_back(i + '0');
        Z1[i].readPoly(text);
      }
      read = 1;
    }
    int wsk = 0;
    for (int i = 0; i < SN.port; i++)
      for (int j1 = 0; j1 <= Z[i].k[1]; j1++)
        for (int j2 = 0; j2 <= Z[i].k[2]; j2++)
          for (int j3 = 0; j3 <= Z[i].k[3]; j3++) {
            P1[wsk] = Z[i].P[j1][j2][j3];
            if (Z1[i].P[j1][j2][j3] != 0.0) wsk++;
            res = res + (Z1[i].P[j1][j2][j3] - Z[i].P[j1][j2][j3]) *
                            (Z1[i].P[j1][j2][j3] - Z[i].P[j1][j2][j3]);
          }
  }

  if (anal == 't' || anal == 'm') {
    //anal == 't' - multiInput->oneOtput (only t1 is needed for ideal)
    //anal == 'm' - oneInput->multiOtput (t1,t2,... are needed for ideal)
    //np - number of ports
    int np = SN.port;
//	if (anal == 't') np = 2;
    // N - numbers of samples
    int N[3];
    N[0] = d1;
    N[1] = d2;
    N[2] = d3;
    // printf("d1=%d d2=%d d3=%d\n",d1,d2,d3);
    // input samples xx are reading from the file t0
    // dimensions of the array xx not smaller then numbers of samples!
    //			float xx[64][64][16];
    float xx[32][32][32];
    string tIn = "t0";
    ifstream tInput;
    tInput.open(tIn.c_str());
    if (tInput) {
      for (int n1 = 0; n1 < N[0]; n1++)
        for (int n2 = 0; n2 < N[1]; n2++)
          for (int n3 = 0; n3 < N[2]; n3++) tInput >> xx[n1][n2][n3];
    } else
      cout << " Warning: input image is missing " << endl;
    // reset sum of resposes from all inputs:
    float sumOut[N[0]][N[1]][N[2]];
    for (int i1 = 0; i1 < N[0]; i1++)
      for (int i2 = 0; i2 < N[1]; i2++)
        for (int i3 = 0; i3 < N[2]; i3++) sumOut[i1][i2][i3] = 0;
    // impulse response Z[i].y calculated for xx on successive inputs:
    for (int i = 1; i < np; i++) {
      string fname = "t";
      fname.push_back((i - 1) + '0');
      //			Z[i].TimeResp(N, Z[i].k, Z[i].P, Z[0].P, xx,
      // fname);
      ZMd[i].TimeResp(N, ZMd[i].k, ZMn[i].P, ZMd[i].P, xx, fname);
      //			Zd[i].TimeResp(N, Zd[i].k, Zn[i].P, Zd[i].P, xx,
      // fname);
	  if (anal == 't') 
      for (int j1 = 0; j1 < N[0]; j1++)
        for (int j2 = 0; j2 < N[1]; j2++)
          for (int j3 = 0; j3 < N[2]; j3++)
            // impulse response sumOut calculated from all inputs:
            //			sumOut[j1][j2][j3] = sumOut[j1][j2][j3] +
            // Z[i].y[j1][j2][j3];
            sumOut[j1][j2][j3] = sumOut[j1][j2][j3] + ZMd[i].y[j1][j2][j3];
      //			sumOut[j1][j2][j3] = sumOut[j1][j2][j3] +
      // Zd[i].y[j1][j2][j3];
    }
	// goal function res calculated
    string fname = "tOut";
    ofstream timeOut;
    int i = 0;
    timeOut.open(fname.c_str(), ios::out);
	if (anal == 't') 
    for (int j1 = 0; j1 < N[0]; j1++)
      for (int j2 = 0; j2 < N[1]; j2++)
        for (int j3 = 0; j3 < N[2]; j3++) {
          timeOut.precision(6);
          timeOut.width(12);
          timeOut << fixed << sumOut[j1][j2][j3];
          timeOut << endl;
          res = res + (sumOut[j1][j2][j3] - ideal[i]) *
                          (sumOut[j1][j2][j3] - ideal[i]);
          P1[i] = sumOut[j1][j2][j3];
          i++;
        }
    if (anal == 'm')
	for (int n = 1; n < np; n++)
    for (int j1 = 0; j1 < N[0]; j1++)
      for (int j2 = 0; j2 < N[1]; j2++)
        for (int j3 = 0; j3 < N[2]; j3++) {
          timeOut.precision(6);
          timeOut.width(12);
          timeOut << fixed << ZMd[n].y[j1][j2][j3];
          timeOut << endl;
          res = res + (ZMd[n].y[j1][j2][j3] - ideal[i]) *
                          (ZMd[n].y[j1][j2][j3] - ideal[i]);
          P1[i] = ZMd[n].y[j1][j2][j3];
          i++;
        }
  }
  return res;
}