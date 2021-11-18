# make => Compila e Executa
# make compile => Apenas compila
# make clean => Limpa o executável e *.o

# Compila e executa
all: hashtable.o main.o
	gcc hashtable.o main.o -o main
	rm -f *.o
	clear
	./main

# Apenas compila
compile: hashtable.o main.o
	gcc hashtable.o main.o -o main

hashtable.o: hashtable.h hashtable.c
	gcc -c hashtable.c

main.o: main.c
	gcc -c main.c

# Limpa o executável
.PHONY: clean

clean:
	rm -f *.o main