FLAGS=`pkg-config --cflags --libs \
	   glib-2.0 \
	   libgit2`
WARN = -Wall

all:
	gcc git-core.c -o test $(FLAGS) 
	
with-warn:
	gcc $(WARN) git-core.c -o test $(FLAGS) 
