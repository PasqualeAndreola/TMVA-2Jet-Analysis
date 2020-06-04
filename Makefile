CFLAGS = -O
CC = h5c++
SRC = main.cpp OpenH5.cpp Groupcheck.cpp Opfunc.cpp Dataset_info.cpp
OBJ = $(SRC:.cpp = .o)

Analysis: $(OBJ)
	  $(CC) $(CFLAGS) -o Analysis $(OBJ)

.PHONY: clean

clean:
	rm -f core *.o
