clean:
	-rm ./try1
	-rm ./try2
try:
	-g++ -g -o ./try1 try1.cpp -std=c++2a -I/usr/local/include/flint -lflint -lmpfr
	-g++ -g -o ./try2 try2.cpp -std=c++2a -I/usr/local/include/flint -lflint -lmpfr
debug:
	-g++ -g -o ./factorize intfact.cpp -D_DEBUG -std=c++2a -I/usr/local/include/flint -I/usr/include/flint -lgmp -lpthread -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -lflint -lmpfr -L/opt/homebrew/lib/ `mysql_config --cflags --libs` -I/usr/local/mysql-connector-c-6.1.11-macos10.12-x86_64/include
prod:
	-g++ -O3 -o ./factorize intfact.cpp -D_PROD -std=c++2a -I/usr/local/include/flint -I/usr/include/flint -lgmp -lpthread -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -lflint -lmpfr -L/opt/homebrew/lib/ `mysql_config --cflags --libs` -I/usr/local/mysql-connector-c-6.1.11-macos10.12-x86_64/include
all:
	-g++ -g -o ./factorize intfact.cpp -std=c++2a -I/usr/local/include/flint -I/usr/include/flint -lgmp -lpthread -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -lflint -lmpfr -L/opt/homebrew/lib/
#	-g++ -O3 -o ./factorize intfact.cpp -std=c++2a -I/usr/local/include/flint -I/usr/include/flint -lgmp -lpthread -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -lflint -lmpfr -L/opt/homebrew/lib/
