gcc -c ./src/main.c ./src/gui.c ./src/input_control.c ./src/robot.c ./src/room.c ./src/helpers.c -std=gnu99 -Wall -Werror -g -I../ZDK -L../ZDK -I../sim/h -L../sim/h
gcc main.o gui.o input_control.o robot.o room.o helpers.o -o a1_n10009671 -std=gnu99 -Wall -Werror -g -lzdk -lncurses -lm -I../ZDK -L../ZDK -I../sim/h -L../sim/h
rm main.o gui.o input_control.o robot.o room.o drawing.o helpers.o