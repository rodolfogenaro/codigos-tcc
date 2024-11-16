COMPILE EVERY FILE LIKE SO, AND THEN CREATE THE EXECUTABLE:

g++ -c suffix_tree.cpp && \
g++ -c test.cpp && \
g++ suffix_tree.o test.o -o test

EXECUTE:

./test
