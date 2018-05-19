for i in "$@"; do sed -i 's:\(//@.*[^; ] *$\):\1;:g' $i; done
rlwrap coin -d "$@";
