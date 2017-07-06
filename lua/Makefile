TARGET = main

CXX = g++
CXXFLAGS = -g -Wall -std=c++11
SRC = $(TARGET).cpp
LIBS = -llua -lm -ldl -lpthread
OBJ = $(SRC:.cpp=.o)
all:$(OBJ)
	$(CXX) $(CXXFALGS) -o $(TARGET)  $(OBJ) $(LIBS) 
	rm -f $(OBJ)
	./$(TARGET) test.lua
$(OBJ):%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
