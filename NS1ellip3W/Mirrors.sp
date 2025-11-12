.subckt CM00 VDD VSS inp out
xmp0 inp inp VDD VDD pmos1 L=126n TFIN=24n  HFIN=15n
xmn0 inp inp VSS VSS nmos1 L=100n TFIN=24n  HFIN=15n
xmp1 out inp VDD VDD pmos1 L=110n TFIN=24n  HFIN=15n
xmn1 out inp VSS VSS nmos1 L=87n TFIN=24n  HFIN=15n
.ends CM00

.subckt CM01 VDD VSS inp out1 out2 out3
xmp0 inp inp VDD VDD pmos1 L=39n TFIN=24n  HFIN=15n
xmn0 inp inp VSS VSS nmos1 L=29n TFIN=24n  HFIN=15n
xmp1 out1 inp VDD VDD pmos1 L=31n TFIN=24n  HFIN=15n
xmn1 out1 inp VSS VSS nmos1 L=23n TFIN=24n  HFIN=15n
xmp2 out2 inp VDD VDD pmos1 L=39n TFIN=24n  HFIN=15n
xmn2 out2 inp VSS VSS nmos1 L=29n TFIN=24n  HFIN=15n
xmp3 out3 inp VDD VDD pmos1 L=126n TFIN=24n  HFIN=15n
xmn3 out3 inp VSS VSS nmos1 L=100n TFIN=24n  HFIN=15n
.ends CM01

.subckt CM01o3 VDD VSS inp out
xmp0 inp inp VDD VDD pmos1 L=39n TFIN=24n  HFIN=15n
xmn0 inp inp VSS VSS nmos1 L=29n TFIN=24n  HFIN=15n
xmp1 out inp VDD VDD pmos1 L=126n TFIN=24n  HFIN=15n
xmn1 out inp VSS VSS nmos1 L=100n TFIN=24n  HFIN=15n
.ends CM01o3

.subckt CM02 VDD VSS inp out1 out2
xmp0 inp inp VDD VDD pmos1 L=93n TFIN=24n  HFIN=15n
xmn0 inp inp VSS VSS nmos1 L=73n TFIN=24n  HFIN=15n
xmp1 out1 inp VDD VDD pmos1 L=84n TFIN=24n  HFIN=15n
xmn1 out1 inp VSS VSS nmos1 L=66n TFIN=24n  HFIN=15n
xmp2 out2 inp VDD VDD pmos1 L=126n TFIN=24n  HFIN=15n
xmn2 out2 inp VSS VSS nmos1 L=100n TFIN=24n  HFIN=15n
.ends CM02

.subckt CM03 VDD VSS inp out1 out2 out3 out4
xmp0 inp inp VDD VDD pmos1 L=45n TFIN=24n  HFIN=15n
xmn0 inp inp VSS VSS nmos1 L=34n TFIN=24n  HFIN=15n
xmp1 out1 inp VDD VDD pmos1 L=126n TFIN=24n  HFIN=15n
xmn1 out1 inp VSS VSS nmos1 L=100n TFIN=24n  HFIN=15n
xmp2 out2 inp VDD VDD pmos1 L=56n TFIN=24n  HFIN=15n
xmn2 out2 inp VSS VSS nmos1 L=43n TFIN=24n  HFIN=15n
xmp3 out3 inp VDD VDD pmos1 L=116n TFIN=24n  HFIN=15n
xmn3 out3 inp VSS VSS nmos1 L=92n TFIN=24n  HFIN=15n
xmp4 out4 inp VDD VDD pmos1 L=42n TFIN=24n  HFIN=15n
xmn4 out4 inp VSS VSS nmos1 L=32n TFIN=24n  HFIN=15n
.ends CM03

.subckt CM03o1 VDD VSS inp out
xmp0 inp inp VDD VDD pmos1 L=45n TFIN=24n  HFIN=15n
xmn0 inp inp VSS VSS nmos1 L=34n TFIN=24n  HFIN=15n
xmp1 out inp VDD VDD pmos1 L=126n TFIN=24n  HFIN=15n
xmn1 out inp VSS VSS nmos1 L=100n TFIN=24n  HFIN=15n
.ends CM03o1

.subckt CM03o3x2 VDD VSS inp out
xmp0 inp inp VDD VDD pmos1 L=50n TFIN=24n  HFIN=15n
xmn0 inp inp VSS VSS nmos1 L=38n TFIN=24n  HFIN=15n
xmp1 out inp VDD VDD pmos1 L=126n TFIN=24n  HFIN=15n
xmn1 out inp VSS VSS nmos1 L=100n TFIN=24n  HFIN=15n
.ends CM03o3x2
