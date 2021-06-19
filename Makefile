all:
	gcc -c sanJuan.c
	gcc -c saving.c
	gcc -o SanJuanTheGame main.c sanJuan.o saving.o
	gcc -o Editor editor.c
clean:
	rm sanJuan.o
	rm SanJuanTheGame
	rm Editor
	rm saving.o