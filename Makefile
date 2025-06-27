CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -O2 -pthread
LDFLAGS := -pthread
TARGET := game

SRCS := main.cpp \
        game_state.cpp \
        input.cpp \
        grid.cpp \
        game_logic.cpp \
        render.cpp \
        ui.cpp \
        utils.cpp

OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

all: $(TARGET)

-include $(DEPS)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

.PHONY: all clean
