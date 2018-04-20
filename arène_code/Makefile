build-fake-ias:
	g++ -ggdb -Wall main.cpp `sdl-config --cflags --libs` -lSDL_mixer -lSDL_image -lSDL_ttf -o arene.exe

build-light:
	g++ *.cpp *.c ias/*.c `sdl-config --cflags --libs` -lSDL_mixer -lSDL_image -lSDL_ttf -o arene.exe
build:
	g++ *.cpp *.c ias/*.c -ggdb -Wall `sdl-config --cflags --libs` -lSDL_mixer -lSDL_image -lSDL_ttf -o arene.exe

copy:
	cp ../Images/* .

all: copy build

find_ias:
	grep -E -m1 '^int [^=]*\(.*\)[^;]*$' *.c


find_more_than_one:
	mkdir too_much
	grep -E -c '^int [^=]*\(.*\)[^;]*$' *.c | grep -E -v ":1$" | sed 's/:[0-9]\+$//'  | xargs -I{} mv {} too_much

find_not_matching:
	mkdir excluded
	grep -L -E -m1 '^int [^=]*\(.*\)[^;]*$' *.c | xargs -I{} mv {} excluded

replace_fn_name:
	sed -i.bak 's/\(^int\) [^=(]*\((.*)[^;]*\)$/\1 ia_1 \2/' *.c
	mkdir oldfiles && mv *.bak oldfiles
	mkdir output
	i=0; for file in *.c; do; i=$((i+1)); sed -n '/int ia_1/,$p' "$file" | sed "s/int ia_1/int ia_$i/" | sed '1s/^/#include <stdlib.h>\n#include <stdio.h>\n#include <time.h>\n#include <SDL\/SDL.h>\n#include <SDL\/SDL_image.h>\n#include <SDL\/SDL_ttf.h>\n#include <SDL\/SDL_mixer.h>\n#include <math.h>\n#include "..\/constantes.h"\n/'> "output/$file";done
