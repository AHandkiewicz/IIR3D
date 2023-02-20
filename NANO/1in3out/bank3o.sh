    for ((i=0; i<=9; i++)); do
#	./optimizer -c 1 -x -n -t 0.01 -a m -i 5000 -d 16 1 1 1in3o5o.sn init5 > "f$i"
#	./optimizer -c 1 -x -n -t 0.1 -a m -i 500 -d 16 1 1 1in3o4o.sn init4 > "f$i"
	./optimizer -c 1 -x -n -t 0.01 -a m -i 1000 -d 16 1 1 1in3o1D.sn init1D > "f$i"
	grep Goal "f$i"
	done
	