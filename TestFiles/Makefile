CFLAGS = -O
CC = h5c++
SRC = test.cpp test_OpenH5.cpp
OBJ = $(SRC:.cpp = .o)

Test: $(OBJ)
	$(CC) $(CFLAGS) -o Test $(OBJ)

clean:
	rm -f core *.o
