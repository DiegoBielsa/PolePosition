ruta = /home/diego/SFML-2.5.1/include/
route_functions = ./functions/functions
route_init = ./init/init
route_loopControl = ./loopControl/loopControl
route_score = ./score/score
route_pantallas = ./pantallas/Pantallaranking
RM = /bin/rm -f  # para limpiar
objects = main.o ${route_functions}.o ${route_init}.o ${route_loopControl}.o ${route_score}.o ${route_pantallas}.o
CC = g++
DIRS = -I. -I./functions -I./init -I./loopControl -I./score
CFLAGS = -Wall -g ${DIRS}


main: ${objects}
	$(CC) ${CFLAGS} ${objects} -o pole-position -L$(ruta) -lsfml-graphics -lsfml-window -lsfml-system
#---------------------------------------------------------
# The main.o target can be written more simply
main.o: main.cpp 
	$(CC) -c main.cpp -I$(ruta)
#---------------------------------------------------------
${route_functions}.o: ${route_functions}.cpp ${route_functions}.hpp
	${CC} -c ${CFLAGS} ${route_functions}.cpp -o ${route_functions}.o
#---------------------------------------------------------
${route_init}.o: ${route_init}.cpp ${route_init}.hpp
	${CC} -c ${CFLAGS} ${route_init}.cpp -o ${route_init}.o
#---------------------------------------------------------
${route_loopControl}.o: ${route_loopControl}.cpp ${route_loopControl}.hpp
	${CC} -c ${CFLAGS} ${route_loopControl}.cpp -o ${route_loopControl}.o
#---------------------------------------------------------
${route_score}.o: ${route_score}.cpp ${route_score}.hpp
	${CC} -c ${CFLAGS} ${route_score}.cpp -o ${route_score}.o
#---------------------------------------------------------
${route_pantallas}.o: ${route_pantallas}.cpp ${route_pantallas}.hpp
	${CC} -c ${CFLAGS} ${route_pantallas}.cpp -o ${route_pantallas}.o



clean:
	$(RM) ${objects} pole-position