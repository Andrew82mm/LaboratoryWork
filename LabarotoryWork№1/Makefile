CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Wpedantic

TARGET = main
ALLNEWBMP = BMP_clockwise.bmp BMP_counterclockwise.bmp BMP_filtered.bmp

SRC_FILES = $(wildcard *.cpp)

OBJ_FILES = $(SRC_FILES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) $(ALLNEWBMP)

