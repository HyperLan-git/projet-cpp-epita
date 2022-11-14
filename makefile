IDIRS = -I include

CFLAGS = -std=c++17 -O3
SDLFLAGS = `sdl2-config --cflags --libs`

OBJDIR = bin/obj
SRCFOLDER = src

SRC = $(shell find $(SRCFOLDER) -type f -name '*.cpp' | sed -z 's/\n/ /g')

OBJ = $(SRC:$(SRCFOLDER)/%.cpp=$(OBJDIR)/%.o)


all: bin Game

bin:
	mkdir bin

Game:
	make $(OBJ)
	g++ -o bin/main $(OBJ) $(CFLAGS) $(SDLFLAGS)


$(OBJDIR)/%.o: $(SRCFOLDER)/%.cpp
	@mkdir -p '$(@D)'
	g++ $(CFLAGS) -c $< $(DEBUG) $(IDIRS) -o $@

clean:
	rm -rf bin/*