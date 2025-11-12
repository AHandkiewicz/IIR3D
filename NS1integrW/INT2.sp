.subckt INT ndd nss nip nin nop non clkp clkn
*the integrator for fp=0.01G

xCMLi ndd nss nip nind nond CM1
xCMRi ndd nss nin nipd nopd CM1
xdel ndd nss nipd nind nond nopd clkp clkn DELAY
xCMLo ndd nss nond nipd nop CM1
xCMRo ndd nss nopd nind non CM1

.subckt DELAY ndd nss nip nin nop non clo cle
*sampling in the first half of the clock period
xdel1a nip nipao clo cle ndd nss SWITCH0
xmp1 nipa nipao ndd ndd pmos1 L=64n TFIN=24n  HFIN=15n
xmn1 nipa nipao nss nss nmos1 L=50n TFIN=24n  HFIN=15n
xdel1b nipa nipao clo cle ndd nss SWITCH0
xdel1c nipa nop cle clo ndd nss SWITCH0

*sampling in the second half of the clock period
xdel1as nip nipaos cle clo ndd nss SWITCH0
xmp1s nipas nipaos ndd ndd pmos1 L=64n TFIN=24n  HFIN=15n
xmn1s nipas nipaos nss nss nmos1 L=50n TFIN=24n  HFIN=15n
xdel1bs nipas nipaos cle clo ndd nss SWITCH0
xdel1cs nipas nop clo cle ndd nss SWITCH0

*sampling in the first half of the clock period
xdel2a nin ninao clo cle ndd nss SWITCH0
xmp2 nina ninao ndd ndd pmos1 L=64n TFIN=24n  HFIN=15n
xmn2 nina ninao nss nss nmos1 L=50n TFIN=24n  HFIN=15n
xdel2b nina ninao clo cle ndd nss SWITCH0
xdel2c nina non cle clo ndd nss SWITCH0

*sampling in the second half of the clock period
xdel2as nin ninaos cle clo ndd nss SWITCH0
xmp2s ninas ninaos ndd ndd pmos1 L=64n TFIN=24n  HFIN=15n
xmn2s ninas ninaos nss nss nmos1 L=50n TFIN=24n  HFIN=15n
xdel2bs ninas ninaos cle clo ndd nss SWITCH0
xdel2cs ninas non clo cle ndd nss SWITCH0

.IC V(nipao)=0
.IC V(ninao)=0
.IC V(nipaos)=0
.IC V(ninaos)=0
.ends DELAY

.subckt SWITCH0 in out clo cle ndd nss
xmp1 in clo out ndd pmos1 L=6n TFIN=24n  HFIN=15n$14,20
xmn1 in cle out nss nmos1 L=6n TFIN=24n  HFIN=15n$10,14
.ends

.subckt CM1 VDD VSS inp out1 out2
xmp0 inp inp VDD VDD pmos1 L=52n TFIN=24n  HFIN=15n$52,50
xmn0 inp inp VSS VSS nmos1 L=40n TFIN=24n  HFIN=15n$40,38
xmp3 out1 inp VDD VDD pmos1 L=22n TFIN=24n  HFIN=15n$27,26
xmn3 out1 inp VSS VSS nmos1 L=16n TFIN=24n  HFIN=15n$20,19
xmp4 out2 inp VDD VDD pmos1 L=48n TFIN=24n  HFIN=15n
xmn4 out2 inp VSS VSS nmos1 L=36n TFIN=24n  HFIN=15n
.ends CM1

.ends INT
