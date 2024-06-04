CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2


SRCS = team.cpp csvParser.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)


TARGET = assignment4

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

