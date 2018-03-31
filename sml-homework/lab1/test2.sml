fun sum [] = 0;
    | sum (x::L) = x + (sum L);

fun mult [] = 1;
    | mult (x::L) = x * (mult L);

