CC = gcc
CFLAGS = -Wall -Wextra -std=c99

semana12: semana12.o
	$(CC) $(CFLAGS) -o semana12 semana12.o

semana12.o: semana12.c
	$(CC) $(CFLAGS) -c semana12.c

clean:
	rm -f semana12 semana12.o
