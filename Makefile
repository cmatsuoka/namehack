
all:
	gcc -Wall -shared -fPIC -o libnamehack.so namehack.c -ldl

clean:
	rm -f namehack.o libnamehack.so



