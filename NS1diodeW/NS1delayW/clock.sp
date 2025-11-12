.subckt CLOCK clo cle td tr tf tp tpe
VGO   clo   0    PULSE( vm  vp  td tr tf tp tpe)
VGE   cle   0    PULSE( vp  vm  td tr tf tp tpe)
.ends

*L = 100/126, 10/14
.subckt SWITCH0 in out clo cle ndd nss
xmp1 in clo out ndd pmos1 L=14n TFIN=24n  HFIN=15n
xmn1 in cle out nss nmos1 L=10n TFIN=24n  HFIN=15n
.ends
