CC = g++
CFLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -O3 -D_NDEBUG -D_EJUDGE_CLIENT_SIDE
IFLAGS = -I./include/

#main
SRC_DIRS = src
OBJ_DIR = obj

SRC = $(foreach SRC_DIR, $(SRC_DIRS), $(wildcard $(SRC_DIR)/*.cc))
OBJ = $(patsubst %.cc, %.o, $(SRC))
OBJECT_FILES = $(foreach OBJECT_FILE, $(OBJ), $(OBJ_DIR)/$(OBJECT_FILE))

all : $(OBJECT_FILES) $(OBJ_DIR)/main.o
	$(CC) $^ -o log 

$(OBJECT_FILES): $(OBJ_DIR)/%.o : %.cc 
	mkdir -p $(@D)
	$(CC) $(IFLAGS) $(CFLAGS) -c $^ -o $@

$(OBJ_DIR)/main.o: main.cc
	mkdir -p $(@D)
	$(CC) $(IFLAGS) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf obj
	rm gui




