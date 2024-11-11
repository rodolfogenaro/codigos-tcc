COMPILE EVERY FILE LIKE SO, AND THEN CREATE THE EXECUTABLE:

g++ -c naive_implementation.cpp && \
g++ -c kmp.cpp && \
g++ -c rabin_karp.cpp && \
g++ -c test.cpp && \
g++ naive_implementation.o kmp.o rabin_karp.o test.o -o test

EXECUTE:

./test
