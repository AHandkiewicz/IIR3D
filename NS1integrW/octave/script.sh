file="$1"
fileo="$2"
x="$(grep -n '             vip        vin        voutp      voutn  ' $file | cut -f1 -d:)"
y="$(grep -n '***** job concluded' $file | cut -f1 -d:)"
#tail -n +$line $file 
sed -n $((x+1)),$((y-3))'p' $file > output
sed -i 's/n//g' output
sed -i 's/u/*1000/g' output
sed -i 's/p/*0.001/g' output
echo -n '%' > $fileo
sed -n $x'p' $file >> $fileo
echo -n '%' >> $fileo
sed -n $((x-1))'p' $file >> $fileo
echo 'R=['>> $fileo
cat output >> $fileo
echo '];'>> $fileo


