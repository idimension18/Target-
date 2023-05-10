EXEC = target++

CC=g++
CFLAGS=-W -Wall
LDFLAGS=-I/usr/include/SDL2 -L/usr/lib/ -Wl,-rpath=/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lrt
SOURCE_DIR = src
BUILD_DIR = build

SRCS = $(shell find $(SOURCE_DIR) -name '*.cpp')
FILE = $(SRCS:$(SOURCE_DIR)/%=%)
HEADERS = $(shell find $(SOURCE_DIR) -name '*.h')
OBJS = $(FILE:.cpp=.o)

all : dir $(EXEC)

dir :
	mkdir $(BUILD_DIR)

$(EXEC) : $(OBJS)
	$(CC) -o $(BUILD_DIR)/$@ $(addprefix $(BUILD_DIR)/,$(OBJS)) $(LDFLAGS)

main.o : $(HEADERS)

$(OBJS): %.o: $(SOURCE_DIR)/%.cpp
	$(CC) -o $(BUILD_DIR)/$@ -c $< $(CFLAGS) $(LDFLAGS)

clean:
	rm -r $(BUILD_DIR)
