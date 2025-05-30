CXX = g++
CXXFLAGS = -std=c++20 -w -Wextra -I./include -I/opt/homebrew/opt/sfml/include -fsanitize=address -fsanitize=undefined
LFLAGS = -L/opt/homebrew/opt/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCDIR = Src
OBJDIR = obj
BINDIR = .
EXECUTABLE = $(BINDIR)/SheepFight

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(EXECUTABLE)
