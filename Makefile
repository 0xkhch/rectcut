cc = gcc
src = main.c
include = raylib-5.5_linux_amd64/include
link = raylib-5.5_linux_amd64/lib/
name = build/main
flags = -Wall -Wextra -Werror -ggdb

all: build main

main:
	$(cc) $(src) -o $(name) $(flags) -I$(include) -L$(link) -l:libraylib.a -lm

build:
	mkdir build

clean:
	rm -rf build
