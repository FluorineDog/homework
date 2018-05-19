#for i in "$@"; do sed -i 's:\(\w\)++:\1=\1+1:g' $i; done
for i in "$@"; do sed -i 's:++\(\w\+\):\1+=1:g' $i; done
for i in "$@"; do sed -i 's:\(//@.*[^; ] *$\):\1;:g' $i; done
cc0 -o a.out "$@" &&
./a.out

