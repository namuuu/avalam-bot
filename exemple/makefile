all: dep install 

# Pour activer le mode debugage, il faut définir __DEBUG__
debug: DEBUG=-D'__DEBUG__'
debug: dep install

dep: 
	cd ../libavalam; make

install: exemple.static exemple.exe
	cp exemple.exe ../build/
	cp exemple.static ../build/

LIB=-L../build/lib
INC=-I../include

exemple.exe:exemple.c 
	gcc $(DEBUG) $(LIB) $(INC) exemple.c -o exemple.exe -lavalam

exemple.static:exemple.c 
	gcc -static $(DEBUG) $(INC) $(LIB)  exemple.c -o exemple.static  -lavalam

clean: 
	rm -rf exemple.exe exemple.static
	rm -rf ../build/exemple.*

cleanall: clean
	cd ../libavalam; make clean
