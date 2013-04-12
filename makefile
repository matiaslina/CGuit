FILES=src/git-core/common.c \
	  src/git-core/clone.c \
      src/git-core/test.c \
      src/gui/guit-commit-list-store.c \
      src/gui/guit-log-textview.c \
      src/gui/guit-clone-dialog.c \
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
