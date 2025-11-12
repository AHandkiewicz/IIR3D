    for ((i=0; i<=1; i++)); do
	./optimizer -c 1 -x -n -t 0.00001 -a z -i 100000 3ellip1D.sn init > "f$i"
	cat "f$i" | grep Goal
	done
	
