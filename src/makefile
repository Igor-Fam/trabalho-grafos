OBJS	= main.o grafo.o no.o aresta.o
SOURCE	= main.cpp grafo.cpp no.cpp aresta.cpp
HEADER	= grafo.h no.h aresta.h
OUT	= grafos.exe
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 

grafo.o: grafo.cpp
	$(CC) $(FLAGS) grafo.cpp 

no.o: no.cpp
	$(CC) $(FLAGS) no.cpp 

aresta.o: aresta.cpp
	$(CC) $(FLAGS) aresta.cpp 


clean:
	rm -f $(OBJS) $(OUT)
