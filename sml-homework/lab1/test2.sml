fun sum [] = 0;
    | sum (x::L) = x + (sum L);

fun mult [] = 1;
    | mult (x::L) = x * (mult L);

fun Mult [] = 1l
    | mult (x_list::L)  = (mult x_list) * (Mult L)
