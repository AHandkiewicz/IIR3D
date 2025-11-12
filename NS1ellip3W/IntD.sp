.subckt Int ndd nss niip niin niop nion clkp clkn 

xint1 ndd nss niip niin niop nion clkp clkn IntBranch
xint2 ndd nss niip niin niop nion clkn clkp IntBranch

.subckt IntBranch ndd nss nip nin nop non clo cle
xdel1a nip no1 clo cle ndd nss SWITCH0
xmp1 no1 nipao ndd ndd pmos1 L=52n TFIN=24n  HFIN=15n
xmn1 no1 nipao nss nss nmos1 L=40n TFIN=24n  HFIN=15n
xdel1b no1 nipao clo cle ndd nss SWITCH0
xmp1a nop nipao ndd ndd pmos1 L=52n TFIN=24n  HFIN=15n
xmn1a nop nipao nss nss nmos1 L=40n TFIN=24n  HFIN=15n

xdel2a nin no1 cle clo ndd nss SWITCH0
xmp2 no1 ninao ndd ndd pmos1 L=52n TFIN=24n  HFIN=15n
xmn2 no1 ninao nss nss nmos1 L=40n TFIN=24n  HFIN=15n
xdel2b no1 ninao cle clo ndd nss SWITCH0
xmp2a non ninao ndd ndd pmos1 L=52n TFIN=24n  HFIN=15n
xmn2a non ninao nss nss nmos1 L=40n TFIN=24n  HFIN=15n

.IC V(nipao)=0
.IC V(ninao)=0
.ends IntBranch

.subckt SWITCH0 in out clo cle ndd nss
xmp1 in clo out ndd pmos1 L=14n TFIN=24n  HFIN=15n$14
xmn1 in cle out nss nmos1 L=10n TFIN=24n  HFIN=15n$10
.ends SWITCH0
.ends IntD
