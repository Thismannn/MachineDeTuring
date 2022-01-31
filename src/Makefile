run: main
	./main


main: machine.o main.o
	gcc -o main machine.o main.o

main.o: main.c machine.h
	gcc -c -Wall main.c

machine.o: machine.c machine.h
	gcc -c -Wall machine.c

clean:
	rm -f machine.o
	rm -f main.o
	rm -f main
	ls -l
