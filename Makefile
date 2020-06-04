CFLAGS = -O -pthread -std=c++11 -m64 -I/usr/local/include -L/usr/local/lib -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic
CC = g++
SRC = main.cpp OpenH5.cpp Groupcheck.cpp Opfunc.cpp Dataset_info.cpp
OBJ = $(SRC:.cpp = .o)

Analysis: $(OBJ)
	  $(CC) $(CFLAGS) -o Analysis $(OBJ)

.PHONY: clean

clean:
	rm -f core *.o
