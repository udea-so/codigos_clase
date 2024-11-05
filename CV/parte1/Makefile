
FLAGS = -Wall -pthread
INCLUDES = .

all: main1 main2

clean:
	rm -f main1 main2

t0: t0.c
	gcc -I $(INCLUDES) -o t0 t0.c $(FLAGS)

t1: t1.c
	gcc -I $(INCLUDES) -o t1 t1.c $(FLAGS)
