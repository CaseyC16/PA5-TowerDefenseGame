# # # DO NOT TOUCH THIS FILE YET
# # # Compile options 
# # CXXFLAGS := -g -Wall


# # # Linker Libraries
# # LDLIBS :=

# # # Target executable name
# # TARGET := a.out

# # # Default target
# # all: a.out

# # # Link the target with all object files
# # a.out: \
# # main.o \
# # battleship.o \
# # fileFunctions.o \
# # screenControl.o \
# # unit_test.o \
# # utils.o
# # 	$(CXX) $(CXXFLAGS) -o $(TARGET) $(LDLIBS) \
# # main.o \
# # battleship.o \
# # fileFunctions.o \
# # utils.o \
# # screenControl.o \
# # unit_test.o

# # main.o: \
# # main.cpp \
# # battleship.h \
# # fileFunctions.h \
# # unit_test.h \
# # screenControl.h \
# # utils.h
# # 	g++ $(CXXFLAGS)  -c -o main.o main.cpp

# # battleship.o: \
# # battleship.cpp \
# # battleship.h \
# # fileFunctions.h \
# # unit_test.h \
# # screenControl.h \
# # utils.h
# # 	g++ $(CXXFLAGS)  -c -o battleship.o battleship.cpp

# # screenControl.o: \
# # screenControl.cpp \
# # battleship.h \
# # fileFunctions.h \
# # unit_test.h \
# # screenControl.h \
# # utils.h
# # 	g++ $(CXXFLAGS)  -c -o screenControl.o screenControl.cpp


# # # Clean up target
# # .PHONY: clean
# # clean:
# # 	rm -f a.out *.o

# # Compiler
# CXX = g++

# # Compiler flags
# CXXFLAGS = -Iinclude -std=c++17 -Wall -Wextra

# # SFML Flags
# SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# # Directories
# SRC_DIR = source
# INC_DIR = include
# OBJ_DIR = obj
# BIN_DIR = bin

# # Target executable
# TARGET = $(BIN_DIR)/paFinal

# # Source files
# SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# # Object files
# OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# # Default rule
# all: $(TARGET)

# # Linking
# $(TARGET): $(OBJECTS)
# 	mkdir -p $(BIN_DIR)
# 	$(CXX) $(OBJECTS) -o $@ $(SFML_LIBS)

# # Compilation
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC_DIR)/%.h
# 	mkdir -p $(OBJ_DIR)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Clean build files
# clean:
# 	rm -rf $(OBJ_DIR) $(BIN_DIR)

# # Clean all generated files
# clean_all: clean
# 	rm -f $(TARGET)

# # Run the program
# run: $(TARGET)
# 	./$(TARGET)

# .PHONY: all clean clean_all run