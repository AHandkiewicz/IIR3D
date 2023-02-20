    for ((i=0; i<=9; i++)); do
#	./optimizer -c 1 -x -n -t 0.01 -a t -i 1000 -d 16 1 1 3in1o5o.sn init5 > "f$i"
	./optimizer -c 1 -x -n -t 0.01 -a t -i 1000 -d 16 1 1 3in1o1D.sn init1D > "f$i"
	grep Goal "f$i"
	done
	