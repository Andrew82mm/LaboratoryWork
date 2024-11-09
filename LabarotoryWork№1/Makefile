CXX = g++
CXXFLAGS = -Wall -std=c++17
SRCS = bmp_reader.cpp filters.cpp main.cpp rotation.cpp
HEADERS = bmp_reader.h filters.h main.h rotation.h
TARGET = main
OBJS = $(SRCS:.cpp=.o)
IMAGE_FILES = gaussian_filtered.bmp rotated_90_clockwise.bmp rotated_90_counterclockwise.bmp

all: $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run_mem: $(TARGET)
	/usr/bin/time -v ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(IMAGE_FILES)

depend: $(SRCS)
	makedepend $(SRCS)

.PHONY: all clean depend run_mem
