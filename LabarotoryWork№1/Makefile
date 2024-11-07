CXX = g++
CXXFLAGS = -Wall -std=c++17
SRCS = write.cpp read.cpp filter.cpp main.cpp rotation.cpp
HEADERS = write.h read.h filters.h main.h rotation.h
TARGET = main
OBJS = $(SRCS:.cpp=.o)
all: $(TARGET)
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
clean:
	rm -f $(OBJS) $(TARGET)
depend: $(SRCS)
	makedepend $(SRCS)
.PHONY: all clean depend
