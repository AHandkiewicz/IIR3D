for i in $(seq 1 1 22)
do
	for j in $(seq 1 1 57)
	do
	#echo "tOut$i $j"
	cp "tI$i $j" tI
#	rm "tI$i $j"
#high-pass filter, struc: 3+3+3C3D4.sn, param: fOut9C4*
#d=1 in videoS, goal=35.5/35.8 for *h1a/*h1b
#d=2 in videoS, goal=44.9/45.0 for *h2a/*h2b
#d=4 in videoS, goal=58.7/59.4 for *h4a/*h4b
#d=6 in videoS, goal=68.8/71.1 for *h6a/*h6b
#d=8 in videoS, goal=73.2/74.6 for *h8a/*h8b
#d=10 in videoS, goal=72.6/77.3 for *h10a/*h10b
#L: d=8 in videoS, goal=34.56/34.63 for *L8a/*L8b
#L: d=6 in videoS, goal=33.95/35.46 for *L6a/*L6b
#L: d=4 in videoS, goal=32.15     for *L4
#L: d=2 in videoS, goal=27.9/28.5 for *L2a/L2b
#L: d=1 in videoS, goal=21.9/23.4 for *L1a/L1b
#./Fi 3+3+3C3D4.sn fOut9C4h10a 16 16 16 
#H: d=1 in videoS, goal=35.5/35.5 for *1Ha/*1Hb
#H: d=4 in videoS, goal=59.5/59.7 for *4Ha/*4Hb, i=500
#H: d=4 in videoS, goal=59.5/59.5 for *14p4Ha1/*14p4Hb1, i=1000 
#H: d=6 in videoS, goal=68.8/68.8 for *6Ha/*6Hb
#H: d=8 in videoS, goal=73.3/73.3 for *8Ha/*8Hb
#H: d=10 in videoS, goal=73.3/73.3 for *10Ha/*10Hb
#L: d=1 in videoS, goal=24.87/24.87 for *1La/1Lb
#L: d=2 in videoS, goal=29.7/29.7 for *2La/2Lb
#L: d=4 in videoS, goal=36.6/36.6 for *4La/4Lb
#HH: d=1 in videoS, goal=35.6841688 for *1HH
#HH: d=6 in videoS, goal=68.83856 for *6HH
#LL: d=1 in videoS, goal=25.5647652 for *1LL
#LL: d=6 in videoS, goal=40.57819 for *6LL
./Fi2 2+2+2C3D3.sn fOut14p6Ha 16 16 16 
#H: d=1 in videoS, goal=36.42/36.42 for *6p1Ha/*6p1Hb
#H: d=2 in videoS, goal=46.21/46.22 for *6p2Ha/*6p2Hb
#H: d=4 in videoS, goal=61.79/61.79 for *6p4Ha/*6p4Hb
#H: d=6 in videoS, goal=72/72 for *6p6Ha/*6p6Hb
#H: d=8 in videoS, goal=77.2/77.3 for *6p8Ha/*6p8Hb
#L: d=1 in videoS, goal=27.26/27.26 for *6p1La/*6p1Lb
#L: d=2 in videoS, goal=33.38/33.38 for *6p2La/*6p2Lb
#L: d=4 in videoS, goal=43.28/43.28 for *6p4La/*6p4Lb
#L: d=6 in videoS, goal=49.8/49.8 for *6p6La/*6p6Lb
#L: d=8 in videoS, goal=52.9/52.9 for *6p8La/*6p8Lb
#./Fi 1+1+1C3D2.sn fOut6p8La 16 16 16 
#L: d=6 in videoS, goal=294.4/736.1 for *L6a/*L6b
#./Fi 3+3+3C3D.sn fOut9C3L6a 32 32 30 
	cp tOut "tOut$i $j"
#	cp tOut "tI$i $j"
    rm tI	
	rm tOut
	done
done
	