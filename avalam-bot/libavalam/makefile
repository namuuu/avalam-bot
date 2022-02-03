all: install

# Pour activer le mode debugage, il faut définir __DEBUG__
debug: DEBUG=-D'__DEBUG__'
debug: install

INC=-I../include

install: libavalam.so libavalam.a
	mkdir -p ../build/lib
	cp libavalam.so libavalam.a ../build/lib

libavalam.so : libavalam.c
	gcc $(DEBUG) $(INC) -shared -fPIC libavalam.c -o libavalam.so

libavalam.a : libavalam.c
	gcc $(DEBUG) $(INC) -c  libavalam.c -o libavalam.o
	ar qvs libavalam.a  libavalam.o

clean: 
	rm -rf  libavalam.so libavalam.a libavalam.o
	rm -rf  ../build/lib/libavalam.so ../build/lib/libavalam.a

