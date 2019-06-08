#usage: gdb -x debugger.gdb ./pro
#set follow-fork-mode child
b 332 if i == 28
tui enable
r inputs/final_test
