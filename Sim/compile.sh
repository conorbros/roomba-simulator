gcc -c main.c gui.c input_control.c robot.c drawing.c room.c -std=gnu99 -Wall -Werror -g -I../ZDK -L../ZDK -I./
gcc main.o gui.o input_control.o robot.o drawing.o room.o -o a1_n10009671 -std=gnu99 -Wall -Werror -g -lzdk -lncurses -lm -I../ZDK -L../ZDK -I./
