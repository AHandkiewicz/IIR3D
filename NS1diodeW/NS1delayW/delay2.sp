.subckt DELAY2 ndd nss nip nin nop non clo cle

xdel1a nip nipao clo cle ndd nss SWITCH0
xmp1 nipa nipao ndd ndd pmos1 L=64n TFIN=24n  HFIN=15n
xmn1 nipa nipao nss nss nmos1 L=50n TFIN=24n  HFIN=15n
xdel1b nipa nipao clo cle ndd nss SWITCH0
xdel1c nipa nop cle clo ndd nss SWITCH0
*Cp nipao 0 1p $the delay works like an integrator

xdel2a nin ninao clo cle ndd nss SWITCH0
xmp2 nina ninao ndd ndd pmos1 L=64n TFIN=24n  HFIN=15n
xmn2 nina ninao nss nss nmos1 L=50n TFIN=24n  HFIN=15n
xdel2b nina ninao clo cle ndd nss SWITCH0
xdel2c nina non cle clo ndd nss SWITCH0
*Cn ninao 0 1p $the delay works like an integrator

*xdel2a nin ninao cle clo ndd nss SWITCH0
*xmp2 nina ninao ndd ndd pmos1 L=64n TFIN=24n  HFIN=15n
*xmn2 nina ninao nss nss nmos1 L=50n TFIN=24n  HFIN=15n
*xdel2b nina ninao cle clo ndd nss SWITCH0
*xdel2c nina non clo cle ndd nss SWITCH0
*Cn ninao 0 1p $the delay works like an integrator

.IC V(nipao)=0
.IC V(ninao)=0
.ends DELAY
