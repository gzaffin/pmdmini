#
# Makefile
#

include mak/general.mak

SRC_DIR = src
SRC_PMDDIR = $(SRC_DIR)/pmdwin
SRC_FMGEN = $(SRC_DIR)/fmgen

CFLAGS += -std=c11
CXXFLAGS += -std=c++11
CFLAGS += -I$(SRC_DIR)
CFLAGS += -I$(SRC_PMDDIR)
CFLAGS += -I$(SRC_FMGEN)
CXXFLAGS += -I$(SRC_DIR)
CXXFLAGS += -I$(SRC_PMDDIR)
CXXFLAGS += -I$(SRC_FMGEN)

SDL_LIBS = `sdl2-config --libs`
SDL_CFLAGS = `sdl2-config --cflags`

#
# definations for packing
#

TITLE = pmdmini
TARGET = pmdplay

FILES = Makefile Makefile.lib $(TITLE).txt
FILES += sdlplay.c

FILES_ORG = inherits
LIB = lib$(TITLE).a

MAK_DIR = mak


ZIPSRC = $(TITLE)`date +"%y%m%d"`.zip
TOUCH = touch -t `date +"%m%d0000"`


OBJS = sdlplay.o $(LIB)


all : $(TARGET)

$(TARGET) : $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) $(SDL_LIBS) -o $@

$(LIB):
	make -f Makefile.lib

%.o : %.c
	$(CC) -o $@ $< -c $(CFLAGS) $(SDL_CFLAGS)

clean :
	make -f Makefile.lib clean
	rm -f $(TARGET) $(OBJS)

dist :
	find . -name ".DS_Store" -exec rm -f {} \;
	find $(FILES) $(SRC_DIR) -exec $(TOUCH) {} \;
	find $(MAK_DIR) -exec $(TOUCH) {} \;

	rm -f $(ZIPSRC)
	zip -r $(ZIPSRC) $(MAK_DIR) $(SRC_DIR) $(FILES) $(FILES_ORG)

