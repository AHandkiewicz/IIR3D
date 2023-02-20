    for ((i=0; i<=2; i++)); 
	do
	./optimizer -c 1 -x -n -t 0.001 -a s -i 1000 3ellip1D.sn init > "f$i"
#	cat "f$i" | grep Goal
	grep Goal "f$i"
	done
	
