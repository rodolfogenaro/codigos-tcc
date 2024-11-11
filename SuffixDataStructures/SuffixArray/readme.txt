COMPILE EVERY FILE LIKE SO, AND THEN CREATE THE EXECUTABLE:

g++ -c suffix_array.cpp && \
g++ -c string_matching.cpp && \
g++ -c test.cpp && \
g++ suffix_array.o string_matching.o test.o -o test

EXECUTE:

./test
