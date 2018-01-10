# store (0x0118 << 18) >> 2 to mem[0]
addi $4, $0, 0x0118
addi $2, $0, 18
sllv $4, $4, $2
addi $2, $0, 2
srlv $4, $4, $2
sw $4, 0($0)
# get 20180000 
addi $4, $0, 0x2018 #6
addi $2, $0, 16
sllv $4, $4, $2
# get 0118 from mem[2]
lh $5, 2($0) #10
# merge to get date
add $4, $4, $5
# store ffffffff
addi $6, $0, -1 #13
sw $6, 4($0)
# get 0xfffffff=-1
lh $6, 4($0)
# check if $6 < 0
bltz $6, succ  #14
add $4, $0, $0 # ignored
succ:
# logical shift to positive
srlv $6, $6, $2 #16
bltz $6, die
# display $4 = 20180118
addi $v0, $0, 0
syscall
# halt
die:
addi $v0, $0, 10
syscall
