# TMVA-2Jet-Analysis

Readme with information about MVA-2Jet-Analysis project

# Documentation

Documentation of the project can be found here: https://pasqualeandreola.github.io/TMVA-2Jet-Analysis/

# Prerequisites

- HDF5-1.12.0 (Needed if the user wants to convert "".h5 files to "".root)
- Root, built with support to C++17 and TMVA
- Fastjet

# Install instruction
1) Open the makefile
2) Modify "includes" with your own libraries' include path
3) Modify "libs" with your own librares' lib path
4) Place input files in the "InputFiles" folder
5) Change the input file list and input variables in "main.cpp"
6) Start "make" in a shell opened in the TMVA-2Jet-Analysis folder
7) Execute "./BinFiles/Analysis" in the shell
8) Enjoy your results :)
9) Optional: if you want to document the program, install doxygen
