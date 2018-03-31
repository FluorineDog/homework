fun oddP 0 = false
    | oddP 1 = true
    | oddP n = oddP(n-2);