.subckt DELAY3 ndd nss nip nin nop1 non1 nop2 non2 clo cle

xdel1a nip nipao clo cle ndd nss SWITCH0
xmp1 nipa nipao ndd ndd pmos1 L=52n TFIN=24n  HFIN=15n
xmn1 nipa nipao nss nss nmos1 L=40n TFIN=24n  HFIN=15n
xdel1b nipa nipao clo cle ndd nss SWITCH0
xdel1c nipa nop1 cle clo ndd nss SWITCH0
*Cp nipao 0 1p $the delay works like an integrator
xmp1a nop2 nipao ndd ndd pmos1 L=52n TFIN=24n  HFIN=15n
xmn1a nop2 nipao nss nss nmos1 L=40n TFIN=24n  HFIN=15n

xdel2a nin ninao clo cle ndd nss SWITCH0
xmp2 nina ninao ndd ndd pmos1 L=52n TFIN=24n  HFIN=15n
xmn2 nina ninao nss nss nmos1 L=40n TFIN=24n  HFIN=15n
xdel2b nina ninao clo cle ndd nss SWITCH0
xdel2c nina non1 cle clo ndd nss SWITCH0
*Cn ninao 0 1p $the delay works like an integrator
xmp2a non2 ninao ndd ndd pmos1 L=52n TFIN=24n  HFIN=15n
xmn2a non2 ninao nss nss nmos1 L=40n TFIN=24n  HFIN=15n

.ends DELAY
