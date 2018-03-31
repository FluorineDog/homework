(* ENSURES: mult_helper(L, a) returns a * mult L  *)
fun mult_helper ([], a) = a | mult_helper (x::L, a) = mult_helper(L, a*x);

fun Mult_helper ([], a) = a | Mult_helper (x_list::L, a) = Mult_helper(L, (mult_helper(x_list, 1) * a));


