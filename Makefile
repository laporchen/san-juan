all:
	gcc -c sanJuan.c
	gcc -o SanJuanTheGame main.c sanJuan.o
clean:
	rm sanJuan.o
	rm SanJuanTheGame