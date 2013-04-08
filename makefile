FILES=src/git-core/git-core.c \
      src/git-core/repository.c \
      src/gui/guit-commit-list-store.c \
      src/gui/guit-new-commit-dialog.c \
      src/tests.c
FLAGS=`pkg-config --cflags --libs \
	   glib-2.0 \
	   libgit2 \
	   gtk+-3.0`
WARN = -Wall -Wextra

CC=clang

all:
	$(CC) $(FILES) -o tests $(FLAGS) 
	
with-warn:
	$(CC) $(WARN) $(FILES) -o tests $(FLAGS) 
