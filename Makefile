ruta = /home/diego/SFML-2.5.1/include/
CC = g++
CFLAGS = -Wall -g

main: main.o RectangularBoundaryCollision.o
	$(CC) main.o -o pole-position -L$(ruta) -lsfml-graphics -lsfml-window -lsfml-system
# The main.o target can be written more simply
main.o: main.cpp RectangularBoundaryCollision.hpp
	$(CC) -c main.cpp -I$(ruta)
RectangularBoundaryCollision.o: RectangularBoundaryCollision.hpp

clean:
	$(RM) pole-position