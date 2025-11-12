*Custom Compiler Version S-2021.09
*current mode continuous-time integrator
*L=5-100(n), W=5nm, SHEETS=3 
*Lpmos    14  27  40  52  64  77  89 101 114 126
*Lnmos    10  20  30  40  50  60  70  80  90 100
*IB(uA)   15  10 7.8 6.4 5.4 4.6 4.1 3.7 3.3   3
*IB for Iin=0, min/max Iin=+-6uA for Rin=50k and k=1
.hdl "./source/bsimcmg.va"
.include "./modelcard_HP_3nm.nmos"
.include "./modelcard_HP_3nm.pmos"
.include "./InvDiod.sp"
.include "./Mirrors.sp"
.include "./clock.sp"
.include "./INT.sp"
*.include "./IntD.sp"

*signal parameters
.param fp=0.01G vp=0.3 vm=-0.3 k=40
vdd ndd 0 dc=0.35
vss nss 0 dc=-0.35
*vinp ninp 0  PWL( 0 0 '0.02/fp' 0 '0.04/fp' 'vp/k' '0.51/fp' 'vp/k' '0.53/fp' 0 '1/fp' 0 '1.02/fp' 'vm/k' '1.04/fp' 'vm/k' '1.49/fp' 'vm/k' '1.51/fp' 0)
*vinn 0 ninn  PWL( 0 0 '0.02/fp' 0 '0.04/fp' 'vp/k' '0.51/fp' 'vp/k' '0.53/fp' 0 '1/fp' 0 '1.02/fp' 'vm/k' '1.04/fp' 'vm/k' '1.49/fp' 'vm/k' '1.51/fp' 0)
*vinp ninp 0  PWL( 0 0 '0.02/fp' 0 '0.04/fp' 'vp/k'  '1/fp' 'vp/k' '1.02/fp' 'vm/k' )
*vinn 0 ninn  PWL( 0 0 '0.02/fp' 0 '0.04/fp' 'vp/k'  '1/fp' 'vp/k' '1.02/fp' 'vm/k' )
*vinp ninp 0  PWL( 0 0 '0.02/fp' 0 '0.04/fp' 'vp/k'  '1.8/fp' 'vp/k' '1.82/fp' 0 )
*vinn 0 ninn  PWL( 0 0 '0.02/fp' 0 '0.04/fp' 'vp/k'  '1.8/fp' 'vp/k' '1.82/fp' 0 )
*vinp ninp 0  PWL( 0 0 '0.02/fp' 0 '0.04/fp' 'vp/k'  '0.12/fp' 'vp/k' '0.14/fp' 0 )
*vinn 0 ninn  PWL( 0 0 '0.02/fp' 0 '0.04/fp' 'vp/k'  '0.12/fp' 'vp/k' '0.14/fp' 0 )
vinp ninp 0  PWL( 0 0 '0.02/fp' 0 '0.04/fp' 'vp/k'  '0.07/fp' 'vp/k' '0.09/fp' 0 )
vinn 0 ninn  PWL( 0 0 '0.02/fp' 0 '0.04/fp' 'vp/k'  '0.07/fp' 'vp/k' '0.09/fp' 0 )

.param td='0.022/fp' tr='0.002/fp' tf='0.002/fp' tp='0.047/fp' tpe='0.098/fp'
xclk1 clkp clkn td tr tf tp tpe CLOCK

xinp ndd nss ninp nip INV_X4
vip nip  s1p  0

xinn ndd nss ninn nin INV_X4
vin nin  s1n  0

*discrete-time integrators:
xint0 ndd nss s1p s1n s2p s2n clkp clkn INT
xint1 ndd nss s3p s3n s4p s4n clkp clkn INT
xint2 ndd nss s5p s5n s6p s6n clkp clkn INT
*current mirrors:
xCM00p ndd nss s01p s1n CM00
xCM00m ndd nss s01n s1p CM00
xCM01p ndd nss s2p s1p s3p s6no CM01
xCM01o3p ndd nss s6po s6n CM01o3
xCM01o3m ndd nss s6no s6p CM01o3
xCM01m ndd nss s2n s1n s3n s6po CM01
xCM02p ndd nss s4p s1n s5p CM02
xCM02m ndd nss s4n s1p s5n CM02
xCM03p ndd nss s6p s2no s3n s5po s7n CM03
xCM03po1 ndd nss s2po s2n CM03o1
xCM03mo1 ndd nss s2no s2p CM03o1
xCM03po1a ndd nss s5po s5noo CM03o3x2
xCM03mo1a ndd nss s5no s5poo CM03o3x2
xCM03po1b ndd nss s5poo s5n CM03o3x2
xCM03mo1b ndd nss s5noo s5p CM03o3x2
xCM03m ndd nss s6n s2po s3p s5no s7p CM03

voutp s7p  nilp  0
xdop ndd nss nilp D_X4

voutn s7n  niln  0
xdon ndd nss niln D_X4

.TEMP 25
.TRAN 0.01/fp 2/fp

.print i(vip) i(vin) i(voutp) i(voutn)
.options list node post

