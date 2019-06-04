#usage: gdb -x debugger.gdb ./pro
b 188
set follow-fork-mode child
tui enable
r
