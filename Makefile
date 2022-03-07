ruta = /home/oscargo/Escritorio/SFML-2.5.1/include/
CC = g++
CFLAGS = -Wall -g

main: main.o
	$(CC) main.o -o sfml-app -L$(ruta) -lsfml-graphics -lsfml-window -lsfml-system
# The main.o target can be written more simply
main.o: main.cpp
	$(CC) -c main.cpp -I$(ruta)
clean:
	$(RM) sfml-app