FILES=src/git-core.c \
      src/git-core-repository.c \
      src/tests.c
FLAGS=`pkg-config --cflags --libs \
	   glib-2.0 \
	   libgit2`
WARN = -Wall

all:
	gcc $(FILES) -o tests $(FLAGS) 
	
with-warn:
	gcc $(WARN) $(FILES) -o tests $(FLAGS) 
