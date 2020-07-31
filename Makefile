CFLAGS = -O -L/usr/local/lib -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic -I/home/pasquale/fastjet/include/fastjet -L/home/pasquale/fastjet/lib -lfastjettools -lfastjet -lm -I/home/pasquale/fastjet/include -Wl,-rpath,/home/pasquale/fastjet/lib -L/home/pasquale/fastjet/lib -lfastjettools -lfastjet -lm -lfastjetplugins -lsiscone_spherical -lsiscone -L/usr/lib/gcc/x86_64-linux-gnu/9 -L/usr/lib/gcc/x86_64-linux-gnu/9/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/9/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/9/../../.. -lgfortran -lm -lquadmath
CC = h5c++
SRC = main.cpp OpenH5.cpp Groupcheck.cpp Opfunc.cpp Dataset_info.cpp TreeCreator.cpp
OBJ = $(SRC:.cpp = .o)

Analysis: $(OBJ)
	  $(CC) $(CFLAGS) -o Analysis $(OBJ)

.PHONY: clean

clean:
	rm -f core *.o
