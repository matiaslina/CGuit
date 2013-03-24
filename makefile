FLAGS=`pkg-config --cflags --libs glib-2.0 libgit2`

all:
	gcc $(FLAGS) git-core.c -o test 
