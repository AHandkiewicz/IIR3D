    for ((i=0; i<=9; i++)); do
#H/L:
	./optimizer -c 1 -x -n -t 1 -a t -i 500 -d 16 16 16 2+2+2C3D3.sn initialsImag3 > "f$i"
	cat "f$i" | grep Goal
	done
	