fun divisibleByThree 0 = true
    | divisibleByThree 1 = false
    | divisibleByThree 2 = false
    | divisibleByThree n = if(n < 0) then divisibleByThree (~n) else divisibleByThree (n-3)
