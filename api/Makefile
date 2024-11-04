EXEC = backendapi
CXX = g++
CXXFLAGS = -std=c++17 -Iinc
LDFLAGS = -L/usr/local/lib -lsqlcipher
SRCS = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.o: src/%.cpp | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	mkdir -p $@

clean:
	rm -f $(OBJS) $(EXEC)
	rm -rf obj

.PHONY: all clean