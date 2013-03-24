FLAGS=`pkg-config --cflags --libs glib-2.0 libgit2`
WARN = -Wall

all:
	gcc $(FLAGS) git-core.c -o test 
	
with-warn:
	gcc $(WARN) $(FLAGS) git-core.c -o test
