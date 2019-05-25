#usage: gdb -x debugger.gdb ./mytar
b mytar.c:96
b mytarfuncs.c:246
b mytarfuncs.c:176
r ./mytar cf outputs/TreePrefix inputs/TreePrefix
tui enable

