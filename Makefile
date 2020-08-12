CFLAGS = -O -L/usr/local/lib -I/home/pasquale/root/include/root -L/home/pasquale/root/lib/root -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -lm -ldl -rdynamic -I/home/pasquale/fastjet/include -I/home/pasquale/fastjet/include/fastjet -Wl,-rpath,/home/pasquale/fastjet/lib -L/home/pasquale/fastjet/lib -lfastjettools -lfastjet -lm
CC = h5c++
SRC = main.cpp OpenH5.cpp Groupcheck.cpp Opfunc.cpp Dataset_info.cpp TreeCreator.cpp TreeJetCreator.cpp JetDictionary.cpp
OBJ = $(SRC:.cpp = .o) 

Analysis: $(OBJ)
	  $(CC) $(CFLAGS) -o Analysis $(OBJ)

.PHONY: clean

clean:
	rm -f core *.o
