cc = gcc
cc_win = x86_64-w64-mingw32-gcc
src = main.c
include = raylib-5.5_linux_amd64/include
link = raylib-5.5_linux_amd64/lib/
name = build/main
name_win = build/main.exe
flags = -Wall -Wextra -ggdb

all: build main windows

windows:
	${cc_win} $(src)  -Iraylib-5.5_win64_mingw-w64/include -Lraylib-5.5_win64_mingw-w64/lib -l:libraylib.a -lgdi32 -lwinmm -lm -Wl,--subsystem,windows -o ${name}

main:
	$(cc) $(src) -o $(name) $(flags) -I$(include) -L$(link) -l:libraylib.a -lm

build:
	mkdir build

clean:
	rm -rf build
