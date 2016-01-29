SRCDIR = src
BINDIR = bin
OBJDIR = obj
INCDIR = inc

CXX = g++
WARNINGS = -Werror -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option
LD_FLAGS = -o $@ $^ -std=c++11 $(WARNINGS) -g
CC_FLAGS = -I $(INCDIR) -c -o $@ $< -std=c++11 $(WARNINGS) -g

CPP_FILES := $(wildcard $(SRCDIR)/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))

bin/maze: $(OBJ_FILES)
	$(CXX) $(LD_FLAGS)

obj/%.o: src/%.cpp
	$(CXX) $(CC_FLAGS)

clean:
	rm obj/* bin/*

run:
	bin/maze