g++ -c -fPIC test.c -o hello.o -I/usr/include/python2.7/
g++ -shared -Wl,-soname,libhello.so -o libhello.so  hello.o -lpython2.7 -lboost_python


