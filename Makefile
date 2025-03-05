clean:
	-rm ./factorize
all:
	-g++ -g -o ./factorize intfact.cpp -std=c++2a -I/usr/local/include/flint -I/usr/include/flint -lgmp -lpthread -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -lflint -lmpfr -L/opt/homebrew/lib/
#	-g++ -O3 -o ./factorize intfact.cpp -std=c++2a -I/usr/local/include/flint -I/usr/include/flint -lgmp -lpthread -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -lflint -lmpfr -L/opt/homebrew/lib/
