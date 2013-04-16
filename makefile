CC=clang
ARCH=i386

FILES=src/git-core/common.c \
      src/git-core/test.c \
      src/guit-commit-list-store.c \
      src/guit-logview.c \
      src/guit-clone-dialog.c \
      src/guit-new-commit-dialog.c \
      src/tests.c
FLAGS=`pkg-config --cflags --libs \
      glib-2.0 \
      gtk+-3.0` \
      -L./lib/$(ARCH) -Iinclude -lgit2 
WARN = -Wall -Wextra

all:
	$(CC) $(FILES) -o tests $(FLAGS)

with-warn:
	$(CC) $(WARN) $(FILES) -o tests $(FLAGS) 
