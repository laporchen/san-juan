all:
	gcc -c sanJuan.c
	gcc -c saving.c
	gcc -o SanJuanTheGame main.c sanJuan.o saving.o -fsanitize=address -g
clean:
	rm sanJuan.o
	rm SanJuanTheGame