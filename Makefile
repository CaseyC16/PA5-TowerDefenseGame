# DO NOT TOUCH THIS FILE YET
# Compile options 
CXXFLAGS := -g -Wall


# Linker Libraries
LDLIBS :=

# Target executable name
TARGET := a.out

# Default target
all: a.out

# Link the target with all object files
a.out: \
main.o \
battleship.o \
fileFunctions.o \
screenControl.o \
unit_test.o \
utils.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(LDLIBS) \
main.o \
battleship.o \
fileFunctions.o \
utils.o \
screenControl.o \
unit_test.o

main.o: \
main.cpp \
battleship.h \
fileFunctions.h \
unit_test.h \
screenControl.h \
utils.h
	g++ $(CXXFLAGS)  -c -o main.o main.cpp

battleship.o: \
battleship.cpp \
battleship.h \
fileFunctions.h \
unit_test.h \
screenControl.h \
utils.h
	g++ $(CXXFLAGS)  -c -o battleship.o battleship.cpp

screenControl.o: \
screenControl.cpp \
battleship.h \
fileFunctions.h \
unit_test.h \
screenControl.h \
utils.h
	g++ $(CXXFLAGS)  -c -o screenControl.o screenControl.cpp


# Clean up target
.PHONY: clean
clean:
	rm -f a.out *.o