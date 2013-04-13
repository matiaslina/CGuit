
SRC_SOURCES=$(wildcard src/*.c)
SRC_HEADERS=$(wildcard src/*.h)
SRC_OBJECTS=$(SRC_SOURCES:.c=.o)
GC_SOURCES=$(wildcard src/git-core/*.c)
GC_HEADERS=$(wildcard src/git-core/*.h)
GC_OBJECTS=$(GC_SOURCES:.c=.o)

SOURCES = $(SRC_SOURCES) $(GC_SOURCES)
OBJECTS = $(SRC_OBJECTS) $(GC_OBJECTS)
      
TARGET=cguit

LIBS=`pkg-config --cflags --libs \
	   glib-2.0 \
	   gthread-2.0 \
	   libgit2 \
	   gtk+-3.0`
FLAGS = -Wall -Wextra -g

#CC=clang
CC=gcc
all: $(TARGET)
	
$(TARGET): $(SOURCES)
	$(CC) $(FLAGS) $(OBJECTS) -o $@ $(LIBS)


$(SOURCES): print
	$(CC) $(FLAGS) -c $@ $(LIBS)
	
objects: $(SOURCES)	

clean:
	rm -f $(TARGET) $(OBJECTS)
	
# Don't know why we need this on $(SOURCES)
# objective =/
print:
	@
