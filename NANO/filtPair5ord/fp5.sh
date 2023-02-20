    for ((i=0; i<=9; i++)); do
	./optimizer -c 1 -x -n -t 0.000001 -a s -i 10000 5pair1Dmin.sn init > "f$i"
	cat "f$i" | grep Goal
	done
	
