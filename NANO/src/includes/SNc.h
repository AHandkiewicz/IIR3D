using namespace std;
class SNc
// the class is a calculator of structure numbers
{
 public:
  int port, dimens, var[10][1000][10], p[10][60][10], acls[60], cls[60][2000],
      cp;
  string Bstr[10];

  //  port, dimens - number of ports and dimension of gC circuit which transfer
  //                 functions are described by structural numbers (SN)
  //  var[i][j][k] - variables in SN, i - number of gC circuit port
  //                 j - number of line and k - number of column in SN
  //                 i=0 corresponds to a denominator of transfer functions
  //                 i=1,...,port-1 correspond to transfer function numerators
  //  p    -  powers of variables (s1, s2, ... , sdimens)
  //          which divide SN into classes (p[port][acls][dimens])
  //      acls -  amount of classes in each SN
  //  cls  -  numbers of lines between which classes are located
  //  cp   -  number of columns in SN
  //  Bstr -  names of successive ports
  void calcSN(int &port, int &dimens, int var[10][1000][10], int acls[60],
              int cls[60][2000], int p[10][60][10], string Bstr[10], int &cp,
              string SNname)
  // the function writes up variables (var) of structure numbers (SN) from a
  // file
  {
    string SN;
    readSN(SN, SNname);
    istringstream mem(SN);

#ifdef DEBUG
    int d[60], l[60], b[60], e[60], r[80], s[60];

#endif /*  */
    int c[60], dp[60], lp[60], pcls[10][60];
    int p0, pN, i;
    p0 = 1;
    i = 0;
    while (findParam(mem, "DIMENSION", p0, dp[i], pN)) {
#ifdef DEBUG
      d[i] = pN;

#endif /*  */
       //                cout << "DIMENSION=" << dp[i] << " in a position " <<
       //                d[i] << endl;
      p0 = pN + 1;
      i++;
    }
    port = i;

    //      cout << "#ports = " << port << endl;
    p0 = 1;
    i = 0;
    while (findParam(mem, "LENTRIES", p0, lp[i], pN)) {
#ifdef DEBUG
      l[i] = pN;

#endif /*  */
       //                cout << "LENTRIES=" << lp[i] << " in a position " <<
       //                l[i] << endl;
      p0 = pN + 1;
      i++;
    }
    p0 = 1;
    i = 0;
    while (findParam(mem, "COLUMNS", p0, cp, pN)) {
      c[i] = pN;

      //                cout << "COLUMNS=" << cp << " in a position " << c[i] <<
      //                endl;
      p0 = pN + 1;
      i++;
    }
    p0 = 1;
    i = 0;

    //      string Bstr[60];
    while (findName(mem, "BEGIN", p0, Bstr[i], pN)) {
#ifdef DEBUG
      b[i] = pN;

#endif /*  */
       //                cout << "BEGIN  " << Bstr[i] << " in a position " <<
       //                b[i] << endl;
      p0 = pN + 1;
      i++;
    }
    p0 = 1;
    i = 0;
    string Estr[60];
    while (findName(mem, "END", p0, Estr[i], pN)) {
#ifdef DEBUG
      e[i] = pN;

#endif /*  */
       //                cout << "END  " << Estr[i] << " in a position " << e[i]
       //                << endl;
      p0 = pN + 1;
      i++;
    }
    int pd[80], ps[80];
    p0 = 1;
    i = 0;
    while (findParam(mem, "%DRP", p0, pd[i], pN)) {
#ifdef DEBUG
      r[i] = pN;

#endif /*  */
      // cout<<"I:"<<i<<endl;
      //                cout << "%DRP=" << pd[i] << " in a position " << r[i] <<
      //                endl;
      p0 = pN + 1;
      i++;
    }
    p0 = 1;
    i = 0;
    while (findParam(mem, "% S", p0, ps[i], pN)) {
#ifdef DEBUG
      s[i] = pN;

#endif /*  */
       //                cout << "% S=" << ps[i] << " in a position " << s[i] <<
       //                endl;
      p0 = pN + 1;
      i++;
    }
    string ss;
    i = 0;
    char cc;
    int cl;

    do {
      mem.seekg(c[i]);
      mem >> cc;

      //      cout << cc;
      //      getline(mem,ss,'N');
      getline(mem, ss);

      //  cout << ss << "\n";
      cl = 0;
      for (int k = 0; k < lp[i]; k++) {
        mem >> cc;
        if (cc == '%') {
          cls[i][cl] = k;
          cl++;
        }

        // cout << cl << "\n";
        while (cc == '%') {
          //      cout << cc;
          getline(mem, ss);

          //  cout << ss << "\n";
          mem >> cc;
        }
        ss = " ";
        ss += cc;
        if (cc == '-') {
          mem >> cc;
          ss += cc;
        }
        var[i][k][0] = atoi(ss.c_str());

        //      cout.width(4);
        //      cout << var[i][k][0];
        for (int j = 1; j <= cp; j++) {
          mem >> var[i][k][j];

          //              cout.width(4);
          //              cout << var[i][k][j];
        }
        //      cout << "\n";
      }
      acls[i] = cl;
      cls[i][cl] = lp[i];
      i++;
    } while (i < port);

    //      cout << "\n\n";
    /*
       for (int i=0; i < port; i++)
       {
       for (int j=0; j <= acls[i]; j++)
       {
       cout.width(4);
       cout << cls[i][j];
       }
       cout << "\n\n";
       }
     */
    dimens = 1;
    for (int i = 0; i < port; i++)
      if (dp[i] > dimens) dimens = dp[i];

    //      cout.width(4);
    //      cout << "dimension = " << dimens << endl;
    //      cout << "\n";
    int k = 0;
    for (int i = 0; i < port; i++)

    {
      //              int k = 0;
      for (int j = 0; j < acls[i]; j++) {
        if (dp[i] < 2)
          pcls[i][j] = ps[k];

        else
          pcls[i][j] = pd[k];
        k++;
      }
    }
    OUTpow(port, dimens, acls, pcls, p);
  }
  int varN(int port, int dimens, int var[10][1000][10], int acls[60],
           int cls[60][2000], int cp)
  // the function returns number of variables (var)
  {
    int N = 0;
    for (int i = 0; i < port; i++)
      for (int j = 0; j < acls[i]; j++)
        for (int k = 0; k < dimens; k++)
          for (int l = cls[i][j]; l < cls[i][j + 1]; l++)
            for (int m = 0; m <= cp; m++)
              if (N < var[i][l][m]) N = var[i][l][m];
    return N;
  }
  void Mpow(int port, int dimens, int acls[60], int p[10][60][10], int Mp[20])
  // the function calculates the max power for each dimension
  // in all classes and ports
  {
    for (int k = 0; k < dimens; k++)
      for (int i = 0; i < port; i++)
        for (int j = 0; j < acls[i]; j++)
          if (Mp[k] < p[i][j][k]) Mp[k] = p[i][j][k];
  }
  void SNtoDisp(int i, int dimens, int var[10][1000][10], int acls[60],
                int cls[60][2000], int p[10][60][10], string Bstr[10], int cp)
  // the function displays the structure number (SN) for the chosen port i
  {
#ifdef Console
    cout << Bstr[i] << endl;
    for (int j = 0; j < acls[i]; j++) {
      for (int k = 0; k < dimens; k++) {
        cout.width(3);
        cout << p[i][j][k];
      }
      cout << endl << endl;
      for (int l = cls[i][j]; l < cls[i][j + 1]; l++) {
        for (int m = 0; m <= cp; m++) {
          cout.width(4);
          cout << var[i][l][m];
        }
        cout << endl;
      }
      cout << endl;
    }
    cout << endl;

#endif /*  */
  }
  void SNtoPoly(int i, float X[60], float P[20][20][20], int dimens,
                int var[10][1000][10], int acls[60], int cls[60][2000],
                int p[10][60][10], string Bstr[10], int cp)
  // the function calculates the polynomial P for parameters X
  // and for a structure number (SN) of the given port i
  // WORNING: the polynomial P is the order not greater than 3!!!
  {
#ifdef Console
    cout << Bstr[i] << endl;

#endif /*  */
    for (int j = 0; j < acls[i]; j++) {
      /*                for (int k=0; k < dimens; k++)
         {
         cout.width(3);
         cout << p[i][j][k];
         }
         cout << endl;
       */
      P[p[i][j][0]][p[i][j][1]][p[i][j][2]] = 0;
      for (int l = cls[i][j]; l < cls[i][j + 1]; l++) {
        float prod = var[i][l][0];
        for (int m = 1; m <= cp; m++) prod = prod * X[var[i][l][m]];
        P[p[i][j][0]][p[i][j][1]][p[i][j][2]] =
            P[p[i][j][0]][p[i][j][1]][p[i][j][2]] + prod;
      }
      //                cout.precision(3);
      //                cout.width(6);
      //                cout << P[p[i][j][0]][p[i][j][1]][p[i][j][2]] << endl;
    }
    //        cout << endl;
  }

 private:
  void OUTpow(int port, int dimens, int acls[60], int pcls[10][60],
              int p[10][60][10])
  // the function calculates powers for classes
  {
    for (int i = 0; i < port; i++) {
      int k = 0;
      for (int j = 0; j < acls[i]; j++)
        if (dimens < 2) {
          p[i][j][k] = pcls[i][j];

          //                        cout.width(4);
          //                        cout << p[i][j][k];
        } else {
          k = pcls[i][j];
          for (int k1 = 0; k1 < dimens; k1++) {
            p[i][j][k1] = k % 10;

            //                        cout.width(3);
            //                        cout << p[i][j][k1];
            k = k / 10;
          }
          //                        cout << " ";
        }
      //                        cout.width(4);
      //                        cout << acls[i];
      //                        cout << endl;
    }
    //              cout << "\n\n";
  }
  void readSN(string &SN, string nameSN)
  // the function writes characters from a file of the given name
  // down (in string SN)
  {
    // string nameSN;
    char c;
    cout << "\n Introduce the structural number name..\n";

    // the string appeares on the display (standard output)
    // cin >> nameSN;
    ifstream INP(nameSN.c_str());
    if (!INP) {
      cout << "\n Opening mistake";
    }

    do {
      INP.get(c);
      if (!INP.eof()) SN += c;
    } while (!INP.eof());
    if (INP.eof())
      cout << "\n The structural number " << nameSN
           << " is written into string.\n";

    else
      cout << " Reading mistake\n";
  }
  bool findName(istringstream &s, string Name, int pos0, string &par, int &posN)
  // the function findes the name of the parameter called Name which
  // is searched from pos0; posN is the founded position
  {
    string tr = s.str();
    string::size_type nr = tr.find(Name, pos0);
    if (nr == string::npos) {
      //              cout << Name << " not found." << endl;
      return false;
    }
    posN = nr;
    int posP;
    posP = nr + Name.length();
    s.seekg(posP);
    s >> par;
    if (!s) {
      cout << " Reding error of: " << Name << endl;
      return false;
    } else
      return true;
  }
  bool findParam(istringstream &s, string Name, int pos0, int &par, int &posN)
  // the function findes the value of the parameter called Name which
  // is searched from pos0; posN is the founded position
  {
    string tr = s.str();
    string::size_type nr = tr.find(Name, pos0);
    if (nr == string::npos) {
      //              cout << Name << " not found." << endl;
      return false;
    }
    posN = nr;
    int posP;
    posP = nr + Name.length();
    s.seekg(posP);
    s >> par;
    if (!s) {
      cout << " Reding error of: " << Name << endl;
      return false;
    } else
      return true;
  }
};
