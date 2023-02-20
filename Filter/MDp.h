using namespace std;
class MDp

// the class transforms bilinearly multi-dimensional polynomials
// between s and z domains
{
 public:
  int n, k[20];
  float P[20][20][20];
  float y[32][32][32];
  //	float y[64][64][16];
  // see dimensions of xx in TimeResp
  // n - the polynomial order
  // !!! the class is build for n <= 3 !!!
  // k - the polynomial ranks (array k[n])
  // P - the array of polynomial coefficients (array P[k[1]]...[k[n]])
  //     indices of the array P are powers of the variables s or 1/z
  // y - samples of responses for transfer functions built of polynomials
  // (1-dim)
  float T[20][20][20];
  // T - the array of the bilinear transformation
  //    (array T[m][i][j], m=1...n, i,j,=0...k[m])

  void readPoly(string plikIn)
  // the function reads the polynomial from a file
  {
#ifdef DEBUG
    int w1, w2;  // width (w1) and precision (w2) of the output data
    w1 = w2 = 6;
#endif
    int l[20];
    // string plikIn;
    ifstream matrIn;
    // input file stream (declaration of the stream from a file)
#ifdef DEBUG
    cout << " Introduce the name of a given polynomial..\n";
#endif
    // the string appears on the display (standard output)
    // cin >> plikIn;
    matrIn.open(plikIn.c_str());
    if (matrIn) {
      matrIn >> n;
#ifdef DEBUG
      cout.width(w1);
      cout << n << '\n';
#endif
      int i;
      for (i = 1; i <= n; ++i) {
        matrIn >> k[i];
#ifdef DEBUG
        cout.width(w1);
        cout << k[i];
#endif
      }
#ifdef DEBUG
      cout << '\n';
#endif
      for (i = 0; i <= 2; ++i) l[i] = 0;
      do {
        for (i = 0; i < n; ++i) {
          matrIn >> l[i];
#ifdef DEBUG
          cout.width(w1);
          cout << l[i];
#endif
        }
        matrIn >> P[l[0]][l[1]][l[2]];
#ifdef DEBUG
        cout.width(w1 + w2);
        cout.precision(w2);
        cout << P[l[0]][l[1]][l[2]] << '\n';
#endif
      } while (!matrIn.eof());
    }
  }

	void writePoly(string plikOut)
// the function writes the polynomial into a file
			{
		int w1, w2;   // width (w1) and precision (w2) of the output data
		w1 = w2 = 8;
//		float eps = 0.01;
		// coefficients with absolute value less than eps are not written
		//string plikOut;
		ofstream matrOut;
		//output file stream (declaration of the stream into a file)

#ifdef Console				
		cout << " Introduce the name of a result polynomial..\n";
#endif				
		// the string appears on the display (standard output)
		//cin >> plikOut;
		matrOut.open(plikOut.c_str(), ios::out);
		if (matrOut) {
			matrOut<<fixed;
#ifdef Console				
			cout<<fixed;
#endif				
			matrOut.width(w1);
			matrOut << n << '\n';
#ifdef Console				
			cout.width(w1);
			cout << n << '\n';
#endif				
			int i;
			for (i = 1; i <= n; ++i) {
				matrOut.width(w1);
				matrOut << k[i];
#ifdef Console				
				cout.width(w1);
				cout << k[i];
#endif				
			}
			matrOut << '\n';
#ifdef Console				
			cout << '\n';
#endif				
			int i1, i2, i3;
			switch (n) {
			case 1: {
				for (i1 = 0; i1 <= k[1]; ++i1)
					//if ((eps < P[i1][0][0]) || (P[i1][0][0] < -eps)) 
if ((P[i1][0][0] != 0)) 
{
						matrOut.width(w1);
						matrOut << i1 << ' ';
#ifdef Console				
						cout.width(w1);
						cout << i1 << ' ';
#endif				
						matrOut.precision(w2);
						matrOut.width(w1 + w2);
						matrOut << P[i1][0][0] << '\n';
#ifdef Console				
						cout.precision(w2);
						cout.width(w1 + w2);
						cout << P[i1][0][0] << '\n';
#endif				
					}
				break;
			}
			case 2: {
				for (i1 = 0; i1 <= k[1]; ++i1)
					for (i2 = 0; i2 <= k[2]; ++i2)
						//if ((eps < P[i1][i2][0]) || (P[i1][i2][0] < -eps)) 
if ((P[i1][i2][0] != 0)) 
{ 
							matrOut.width(w1);
							matrOut << i1 << ' ';
							matrOut.width(w1);
							matrOut << i2 << ' ';
#ifdef Console				
							cout.width(w1);
							cout << i1 << ' ';
							cout.width(w1);
							cout << i2 << ' ';
#endif				
							matrOut.precision(w2);
							matrOut.width(w1 + w2);
							matrOut << P[i1][i2][0] << '\n';
#ifdef Console				
							cout.precision(w2);
							cout.width(w1 + w2);
							cout << P[i1][i2][0] << '\n';
#endif				
						}
				break;
			}
			case 3: {
				for (i1 = 0; i1 <= k[1]; ++i1)
					for (i2 = 0; i2 <= k[2]; ++i2)
						for (i3 = 0; i3 <= k[3]; ++i3)
							//if ((eps < P[i1][i2][i3]) || (P[i1][i2][i3] < -eps)) 
if ((P[i1][i2][i3] != 0)) 
{
								matrOut.width(w1);
								matrOut << i1 << ' ';
								matrOut.width(w1);
								matrOut << i2 << ' ';
								matrOut.width(w1);
								matrOut << i3 << ' ';
#ifdef Console				
								cout.width(w1);
								cout << i1 << ' ';
								cout.width(w1);
								cout << i2 << ' ';
								cout.width(w1);
								cout << i3 << ' ';
#endif				
								matrOut.precision(w2);
								matrOut.width(w1 + w2);
								matrOut << P[i1][i2][i3] << '\n';
#ifdef Console				
								cout.precision(w2);
								cout.width(w1 + w2);
								cout << P[i1][i2][i3] << '\n';
#endif				
							}
				break;
			}
			}
		}
		matrOut.close();
	}

  void move(int nn, int kk[20], float PP[20][20][20])
  // the function moves the polynomial given as the argument into an object
  {
    int i1, i2, i3;
    switch (nn) {
      case 1: {
        n = nn;
        k[1] = kk[1];
        for (i1 = 0; i1 <= k[1]; ++i1) P[i1][0][0] = PP[i1][0][0];
        break;
      }
      case 2: {
        n = nn;
        k[1] = kk[1];
        k[2] = kk[2];
        for (i1 = 0; i1 <= k[1]; ++i1)
          for (i2 = 0; i2 <= k[2]; ++i2) P[i1][i2][0] = PP[i1][i2][0];
        break;
      }
      case 3: {
        n = nn;
        k[1] = kk[1];
        k[2] = kk[2];
        k[3] = kk[3];
        for (i1 = 0; i1 <= k[1]; ++i1)
          for (i2 = 0; i2 <= k[2]; ++i2)
            for (i3 = 0; i3 <= k[3]; ++i3) P[i1][i2][i3] = PP[i1][i2][i3];
        break;
      }
    }
  }

  void T2to1()
  // the function compensates T=2 chosen in the bilinear transformation
  {
    switch (n) {
      case 1: {
        for (int i1 = 0; i1 <= k[1]; ++i1)
          P[i1][0][0] = power2(i1) * P[i1][0][0];
        break;
      }
      case 2: {
        for (int i1 = 0; i1 <= k[1]; ++i1)
          for (int i2 = 0; i2 <= k[2]; ++i2)
            P[i1][i2][0] = power2(i1 + i2) * P[i1][i2][0];
        break;
      }
      case 3: {
        for (int i1 = 0; i1 <= k[1]; ++i1)
          for (int i2 = 0; i2 <= k[2]; ++i2)
            for (int i3 = 0; i3 <= k[3]; ++i3)
              P[i1][i2][i3] = power2(i1 + i2 + i3) * P[i1][i2][i3];
        break;
      }
    }
  }

  void reverse(int nn, int kk[20], float PP[20][20][20])
  // the function reverses the polynomial coefficients (PP) with respect
  // to powers of variables s (or z) and saves as a new object (P)
  {
    int i1, i2, i3;
    switch (nn) {
      case 1: {
        n = nn;
        k[1] = kk[1];
        for (i1 = 0; i1 <= k[1]; ++i1) P[k[1] - i1][0][0] = PP[i1][0][0];
        break;
      }
      case 2: {
        n = nn;
        k[1] = kk[1];
        k[2] = kk[2];
        for (i1 = 0; i1 <= k[1]; ++i1)
          for (i2 = 0; i2 <= k[2]; ++i2)
            P[k[1] - i1][k[2] - i2][0] = PP[i1][i2][0];
        break;
      }
      case 3: {
        n = nn;
        k[1] = kk[1];
        k[2] = kk[2];
        k[3] = kk[3];
        for (i1 = 0; i1 <= k[1]; ++i1)
          for (i2 = 0; i2 <= k[2]; ++i2)
            for (i3 = 0; i3 <= k[3]; ++i3)
              P[k[1] - i1][k[2] - i2][k[3] - i3] = PP[i1][i2][i3];
        break;
      }
    }
  }

  void bili(int nn, int kk[20], float PP[20][20][20], float TT[20][20][20])
  // the function calculates a bilinearly transformed object P
  // for the polynomial and the transformation array given as the arguments
  {
    int i1, i2, i3, j1, j2, j3;
    switch (nn) {
      case 1: {
        n = nn;
        k[1] = kk[1];
        for (i1 = 0; i1 <= k[1]; ++i1) {
          P[i1][0][0] = 0;
          for (j1 = 0; j1 <= k[1]; ++j1)
            P[i1][0][0] = P[i1][0][0] + PP[j1][0][0] * TT[1][j1][i1];
        }
        break;
      }
      case 2: {
        n = nn;
        k[1] = kk[1];
        k[2] = kk[2];
        for (i1 = 0; i1 <= k[1]; ++i1)
          for (i2 = 0; i2 <= k[2]; ++i2) {
            P[i1][i2][0] = 0;
            for (j1 = 0; j1 <= k[1]; ++j1)
              for (j2 = 0; j2 <= k[2]; ++j2)
                P[i1][i2][0] = P[i1][i2][0] +
                               PP[j1][j2][0] * TT[1][j1][i1] * TT[2][j2][i2];
          }
        break;
      }
      case 3: {
        n = nn;
        k[1] = kk[1];
        k[2] = kk[2];
        k[3] = kk[3];
        for (i1 = 0; i1 <= k[1]; ++i1)
          for (i2 = 0; i2 <= k[2]; ++i2)
            for (i3 = 0; i3 <= k[3]; ++i3) {
              P[i1][i2][i3] = 0;
              for (j1 = 0; j1 <= k[1]; ++j1)
                for (j2 = 0; j2 <= k[2]; ++j2)
                  for (j3 = 0; j3 <= k[3]; ++j3)
                    P[i1][i2][i3] =
                        P[i1][i2][i3] + PP[j1][j2][j3] * TT[1][j1][i1] *
                                            TT[2][j2][i2] * TT[3][j3][i3];
            }
        break;
      }
    }
  }

  void biliT()
  // the function calculates the array T for bilinear transformation
  //    (array T[m][i][j], m=1...n, i,j,=0...k[m])
  {
    int i1, i2, i3;
#ifdef DEBUG
    int w1, w2;
    w1 = w2 = 3;
#endif
    for (i1 = 1; i1 <= n; ++i1)
      for (i2 = 0; i2 <= k[i1]; ++i2)
        for (i3 = 0; i3 <= k[i1]; ++i3) T[i1][i2][i3] = 1;
    for (i1 = 1; i1 <= n; ++i1)
      for (i3 = 0; i3 <= k[i1]; ++i3)
        T[i1][0][i3] = factorial(k[i1]) / factorial(i3) / factorial(k[i1] - i3);
    for (i1 = 1; i1 <= n; ++i1)
      for (i2 = 1; i2 <= k[i1]; ++i2)
        for (i3 = 1; i3 <= k[i1]; ++i3)
          T[i1][i2][i3] =
              T[i1][i2 - 1][i3] - (T[i1][i2 - 1][i3 - 1] + T[i1][i2][i3 - 1]);
#ifdef DEBUG
    for (i1 = 1; i1 <= n; ++i1)
      for (i2 = 0; i2 <= k[i1]; ++i2) {
        for (i3 = 0; i3 <= k[i1]; ++i3) {
          cout.precision(w2);
          cout.width(w1 + w2);
          cout << T[i1][i2][i3];
        }
        cout << '\n';
      }
#endif
  }

  void multiply(int nn, int k1[20], float P1[20][20][20], int k2[20],
                float P2[20][20][20])
  // the function multiplyes the polynomial P1 by the polynomial P2
  {
    n = nn;
    switch (n) {
      case 1: {
        k[1] = k1[1] + k2[1];
        for (int i = 0; i <= k[1]; ++i) P[i][0][0] = 0;
        for (int i11 = 0; i11 <= k1[1]; ++i11)
          for (int i12 = 0; i12 <= k2[1]; ++i12)
            P[i11 + i12][0][0] =
                P[i11 + i12][0][0] + P1[i11][0][0] * P2[i12][0][0];
        break;
      }
      case 2: {
        k[1] = k1[1] + k2[1];
        k[2] = k1[2] + k2[2];
        for (int i1 = 0; i1 <= k[1]; ++i1)
          for (int i2 = 0; i2 <= k[2]; ++i2) P[i1][i2][0] = 0;
        for (int i11 = 0; i11 <= k1[1]; ++i11)
          for (int i12 = 0; i12 <= k2[1]; ++i12)
            for (int i21 = 0; i21 <= k1[2]; ++i21)
              for (int i22 = 0; i22 <= k2[2]; ++i22)
                P[i11 + i12][i21 + i22][0] = P[i11 + i12][i21 + i22][0] +
                                             P1[i11][i21][0] * P2[i12][i22][0];
        break;
      }
      case 3: {
        k[1] = k1[1] + k2[1];
        k[2] = k1[2] + k2[2];
        k[3] = k1[3] + k2[3];
        for (int i1 = 0; i1 <= k[1]; ++i1)
          for (int i2 = 0; i2 <= k[2]; ++i2)
            for (int i3 = 0; i3 <= k[3]; ++i3) P[i1][i2][i3] = 0;
        for (int i11 = 0; i11 <= k1[1]; ++i11)
          for (int i12 = 0; i12 <= k2[1]; ++i12)
            for (int i21 = 0; i21 <= k1[2]; ++i21)
              for (int i22 = 0; i22 <= k2[2]; ++i22)
                for (int i31 = 0; i31 <= k1[3]; ++i31)
                  for (int i32 = 0; i32 <= k2[3]; ++i32)
                    P[i11 + i12][i21 + i22][i31 + i32] =
                        P[i11 + i12][i21 + i22][i31 + i32] +
                        P1[i11][i21][i31] * P2[i12][i22][i32];
        break;
      }
    }
  }

  void TimeResp(int N[3], int kk[20], float A[20][20][20], float B[20][20][20],
                float xx[32][32][32], string fname)
  // the function calculates N samples of a response y for an input signal xx
  // A and B are numerator and denominator polynomials of a transfer function
  // k contains ranks of polynomials
  {
    // ofstream matrOut;

    // matrOut.open(fname.c_str(), ios::out);
    // if (matrOut)
    {
      if (B[0][0][0] != 0) {
        // reseting of output samples y[n1][n2][n3]
        for (int n1 = 0; n1 < N[0]; n1++)
          for (int n2 = 0; n2 < N[1]; n2++)
            for (int n3 = 0; n3 < N[2]; n3++) y[n1][n2][n3] = 0;
        // calculation of output samples y[n1][n2][n3]
        for (int n1 = 0; n1 < N[0]; n1++)
          for (int n2 = 0; n2 < N[1]; n2++)
            for (int n3 = 0; n3 < N[2]; n3++) {
              float sa;
              for (int i1 = 0; i1 <= kk[1]; i1++)
                for (int i2 = 0; i2 <= kk[2]; i2++)
                  for (int i3 = 0; i3 <= kk[3]; i3++) {
                    if (((n1 - i1) < 0) || ((n2 - i2) < 0) || ((n3 - i3) < 0))
                      sa = 0;
                    else
                      sa = y[n1 - i1][n2 - i2][n3 - i3];
                    // components with output samples y[n1][n2][n3]
                    // y[0][0][0]=0 at the beginning of calculations
                    y[n1][n2][n3] = y[n1][n2][n3] - B[i1][i2][i3] * sa;
                    // initial conditions from the image margin
                    int ni1 = n1 - i1;
                    int ni2 = n2 - i2;
                    int ni3 = n3 - i3;
                    if (ni1 < 0) ni1 = -ni1;
                    if (ni2 < 0) ni2 = -ni2;
                    if (ni3 < 0) ni3 = -ni3;
                    sa = xx[ni1][ni2][ni3];
                    // zero initial conditions
                    if (((n1 - i1) < 0) || ((n2 - i2) < 0) || ((n3 - i3) < 0))
                      sa = 0;
                    // components with input samples x[n1][n2][n3]
                    y[n1][n2][n3] = y[n1][n2][n3] + A[i1][i2][i3] * sa;
                  }
              y[n1][n2][n3] = y[n1][n2][n3] / B[0][0][0];
              //					cout.precision(6);
              //					cout.width(12);
              //		matrOut.precision(6);
              //		matrOut.width(12);
              //		matrOut << fixed << y[n1][n2][n3];
              //		matrOut << endl;
              //					cout << y[n1][n2][n3];
            }
        //				cout << endl;

      } else
        cout << " WARNING: the coefficient in the denominator is 0" << endl;
    }
  }

 private:
  float factorial(float nn) {
    if (nn > 1) return nn = nn * factorial(nn - 1);
    return 1;
  }

  int power2(int nn) {
    if (nn > 0) {
      int y = 2;
      while (nn > 1) {
        y = 2 * y;
        --nn;
      }
      return y;
    }
    return 1;
  }
};
