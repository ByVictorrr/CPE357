#usage: gdb -x debugger.gdb ./pro
#set follow-fork-mode child
b main
tui enable
r
