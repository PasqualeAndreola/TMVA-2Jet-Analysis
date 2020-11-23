#Compiler
CXX 	 := g++

#Executable program
TARGET 	 :=	Test

#Source, build and executable directories
SRCDIR    := SourceFiles
BUILDDIR  := BuildFiles
TARGETDIR := BinFiles
INPUTDIR  := InputFiles
OUTPUTDIR := OutputFiles

#Source and build file extension
SRCEXT := cpp
OBJEXT := o
DEPEXT := d

#Flags
CXXFLAGS 	 := -O3 -g --std=c++17 -lstdc++fs

#Includes
INCROOT 	 := -I/home/pasquale/root/include
INCJET  	 := -I/home/pasquale/fastjet/include -I/home/pasquale/fastjet/include/fastjet
INCHDF5 	 := -I/home/pasquale/hdf5/include
INCLUDES     :=  $(INCROOT) $(INCJET) $(INCHDF5)

#Libraries that has to be linked
LIBSROOT 	 := -L/home/pasquale/root/lib -lTMVA -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps
LIBSROOT 	 += -L/home/pasquale/root/lib -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore
LIBSJET	     := -Wl,-rpath,/home/pasquale/fastjet/lib -L/home/pasquale/fastjet/lib -lfastjettools -lfastjet -lm
LIBSHDF5     := -Wl,-rpath,/home/pasquale/hdf5/lib -L/home/pasquale/hdf5/lib /home/pasquale/hdf5/lib/libhdf5_hl_cpp.a /home/pasquale/hdf5/lib/libhdf5_cpp.a 
LIBSHDF5     += /home/pasquale/hdf5/lib/libhdf5_hl.a /home/pasquale/hdf5/lib/libhdf5.a -lz -ldl -lm -Wl,-rpath -Wl,/home/pasquale/hdf5/lib
LIBS 	 	 := $(LIBSROOT)  $(LIBSJET)  $(LIBSHDF5)

#Sources and objects research
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))	

#Default make execution
all: directories rootdictionaries $(TARGET)
	@./BinFiles/Test
	@find ./SourceFiles -type f ! -name "test*.cpp" -exec rm -r {} \;

#Remake
remake: cleaner all

#Making of directories
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(INPUTDIR)
	@mkdir -p $(OUTPUTDIR)
	@cp -f -r ../$(SRCDIR) ./
	@rm -f ./$(SRCDIR)/main.cpp

#Making of the root dictionaries
rootdictionaries:
	@rm --force $(TARGETDIR)/JetDictionary.cpp
	@rootcling  $(INCLUDES) $(TARGETDIR)/JetDictionary.cpp $(SRCDIR)/headers/jetdict.h

#Clean Build
clean:
	@$(RM) -rf $(BUILDDIR)

#Clean everything
cleaner: clean
	@$(RM) -rf $(TARGETDIR)

#Getting the dipendencies
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

#Setting up the linker
$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGETDIR)/$(TARGET) $^ $(LIBS)

#Compiling
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

.PHONY: all remake clean cleaner doxy