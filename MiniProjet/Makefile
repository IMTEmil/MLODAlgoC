snake: snake.c projet.c
	gcc -o snake projet.c snake.c -I${HOME}/Raylib.git/src/ -Wall -std=c11 ${HOME}//Raylib.git/src/libraylib.a -lm -ldl -lrt -lpthread -lGL -lX11

game: snake
	./snake
clean: 
	rm snake
