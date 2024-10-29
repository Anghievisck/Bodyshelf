main.o: main.c
	gcc -c main.c

user.o: pseudo-classes/user.c pseudo-classes/user.h
	gcc -c pseudo-classes/user.c

base.o: pseudo-classes/base.c pseudo-classes/base.h
	gcc -c pseudo-classes/base.c

all: main.o base.o user.o
	gcc -o rede_social main.o base.o user.o

clean:
	rm base.o
	rm user.o
	rm main.o
	rm ./rede_social.exe

run:
	./rede_social.exe