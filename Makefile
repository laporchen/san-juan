all:
	gcc -c sanJuan.c
	gcc -o SanJuanTheGame main.c sanJuan.o  -fsanitize=address -g
clean:
	rm sanJuan.o
	rm SanJuanTheGame