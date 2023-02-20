    for ((i=0; i<=9; i++)); 
	do
	./optimizer -c 1 -x -n -t 0.00001 -a s -i 100000 7ellip1D.sn init > "f$i"
	grep Goal "f$i"
	done
	