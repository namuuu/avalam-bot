all: dep install 

# Pour activer le mode debugage, il faut définir __DEBUG__
debug:DEBUG=-D'__DEBUG__'
debug: dep install

dep: 
	cd ../libavalam; make

install: standalone.static standalone.exe
	cp standalone.exe ../build/
	cp standalone.static ../build/

LIB=-L../build/lib
INC=-I../include

standalone.exe:standalone.c 
	gcc $(DEBUG) $(LIB) $(INC) standalone.c -o standalone.exe -lavalam

standalone.static:standalone.c 
	gcc -static $(DEBUG) $(INC) $(LIB)  standalone.c -o standalone.static  -lavalam

clean: 
	rm -rf standalone.exe standalone.static
	rm -rf ../build/standalone.*

cleanall: clean
	cd ../libavalam; make clean
