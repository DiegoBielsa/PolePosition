#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>
#include "RectangularBoundaryCollision.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "score/score.hpp"
#include "globals/globals.hpp"
#include "pantallas/Pantallaranking.hpp"



using namespace sf;
using namespace std;

#define spriteColision 1
int estado = 0;
bool terminar = false; //para salir de los bucles de estados

int width = 1024;
int height = 768;
int roadW;
int segL;   // segment length
float camD; // camera depth
float draw_distance; // empiezan a aparecer en pantalla en el 8
int car_width;
int car_height;
float off_road_allowed;
float road_limit;
float turn_power;
float draft_power;
float goalPosIni;
float goalPosEnd;

int speed = 0;
bool marchaBaja = true;
bool pressed = false;
int maxSpeed;
bool enHierba = false;
std::array<bool, sf::Keyboard::KeyCount> keyState;
int numMaps;
bool gameOver = false;
bool perderControl = false;
bool charco = false;
int animColision = 0;


Time tiempoconseguido;
bool ultimotiempo = false;
int score = 0;
bool esPrimeravez = true; //para saber si hemos pasado la meta por primera vez
bool metacruz = false;
bool antmetacruz = false; //para ver si estamos parados en la meta

int mapa; //mapa a elegir

/*------------------------------- FIN FUNCIONES DE CONTROL DEL BUCLE PRINCIPAL -------------------------------*/

int main() {
    //INICIALIZANDO EL JUEGO
    setConfig();
    RenderWindow app(VideoMode(width, height), "Pole Position");
    app.setKeyRepeatEnabled(false);
    app.setFramerateLimit(60);
    keyState.fill(false);

    Clock clock;
    Clock tiempoparafin;
    bool restart = false;

    string puntuaciones[7];
    leerPuntuaciones(puntuaciones, mapa);
    int limite = 0;


    leerLimite(limite, mapa);
    int lim = limite; //variable que iremos restando para no tener que volver a leer el fichero cuando hacemos vuelta

    Texture t[50];
    Sprite object[50];
    Texture ca;
    Texture marcha;
    ca.loadFromFile("sprites/coches/carSpritesheet.png");
    carSprite car;
    car.init(IntRect(0, 0, car_width, car_height), ca); //Inicializar sprite coche
    for (int i = 1; i <= 7; i++) {
        t[i].loadFromFile("images/" + std::to_string(i) + ".png");
        t[i].setSmooth(true);
        object[i].setTexture(t[i]);
    }
    t[8].loadFromFile("sprites/entorno/meta.png");
    t[8].setSmooth(true);
    object[8].setTexture(t[8]);
    for (int i = 0; i < 6; i++) {
        t[i + 9].loadFromFile("sprites/entorno/cartel" + std::to_string(i + 1) + ".png");
        t[i + 9].setSmooth(true);
        object[i + 9].setTexture(t[i + 9]);
    }
    t[15].loadFromFile("sprites/entorno/charcogrande.png");
    t[15].setSmooth(true);
    object[15].setTexture(t[15]);



    Texture bg;
    bg.loadFromFile("sprites/entorno/backgroundMountains.png");
    bg.setRepeated(false);
    Sprite sBackground(bg);
    sBackground.setTextureRect(IntRect(0, 0, 30000, 411));
    sBackground.setPosition(-5000, 0);

    std::vector<std::vector<Line>> maps; // esto es el conjunto de mapas
    std::vector<Line> lines; // esto es el mapa, 

    setMaps(maps, object);

    // eleccion del mapa
    lines = maps[mapa];


    int N = lines.size();
    float playerX = 0;
    int pos = 0;
    int H = 1500;
    while (true) {
        switch (estado)
        {
        case 0://clasificacion
           

            while (app.isOpen() && !terminar) {
                Event e;
                while (app.pollEvent(e)) {
                    if (e.type == Event::Closed)
                        app.close();
                }


                if (e.type == sf::Event::Resized) {
                    sf::View view = app.getDefaultView();
                    view = getLetterboxView(view, e.size.width, e.size.height);
                    app.setView(view);
                }

                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::LControl && !keyState[e.key.code]) {
                        marchaBaja = !marchaBaja;
                    }
                    keyState[e.key.code] = true;

                }
                else if (e.type == sf::Event::KeyReleased) {
                    // Update state of current key:
                    keyState[e.key.code] = false;
                }
                


                int startPos, camH, maxy;
                float x, dx;
                updateVars(app, pos, startPos, camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground);
                manageKeys(playerX, speed, H, car, lines, startPos);
                sf::Time elapsed = clock.getElapsedTime();
            
                comprobarMeta(startPos, goalPosIni, metacruz);
                if (metacruz == true && antmetacruz==false) {
                    if (esPrimeravez==true) {
                        esPrimeravez = false;
                    }
                    else {
                        clock.restart();  //cuando hagamos vuelta
                        elapsed = clock.getElapsedTime();
                        lim = limite;
                    }
                }
                antmetacruz = metacruz;
                calcularScore(score, speed, lim, limite, gameOver);



                drawRoad(app, startPos, playerX, lines, N, x, dx, maxy, camH);
                drawObjects(app, startPos, lines, N, car);
                drawLetters(app, puntuaciones, speed, score, elapsed, lim, gameOver);
                //std::cout<<startPos<<std::endl;
                if (startPos >= 3500 && startPos <= 3550) {
                    gameOver = true;
                }
                drawGear(app, marchaBaja, marcha);

                if (speed < 0) speed = 0;



                if (gameOver == true) {
                    drawGameOver(app);
                }


                if (gameOver == true && restart == false) {
                    tiempoparafin.restart();
                    escribirPuntuaciones(puntuaciones, score, mapa);
                    restart = true;
                }
                else if (gameOver == true && restart == true) {
                    estado = 2;
                    if (tiempoparafin.getElapsedTime().asSeconds() > 10) {//esperamos 10 segundos para terminar
                        terminar = true;
                    }
                }

                app.display();


            }

            break;

        case 1://carrera

            //inicializamos todo
            int lap;
            lap = 0;
            gameOver = false;
            clock.restart();
            esPrimeravez = true;
            pos = 0;
            playerX = 0;
            speed = 0;
            while (app.isOpen()) {
                Event e;
                while (app.pollEvent(e)) {
                    if (e.type == Event::Closed)
                        app.close();
                }


                if (e.type == sf::Event::Resized) {
                    sf::View view = app.getDefaultView();
                    view = getLetterboxView(view, e.size.width, e.size.height);
                    app.setView(view);
                }

                if (e.type == sf::Event::KeyPressed) {
                    if (e.key.code == sf::Keyboard::LControl && !keyState[e.key.code]) {
                        marchaBaja = !marchaBaja;
                    }
                    keyState[e.key.code] = true;

                }
                else if (e.type == sf::Event::KeyReleased) {
                    // Update state of current key:
                    keyState[e.key.code] = false;
                }
                


                int startPos, camH, maxy;
                float x, dx;
                updateVars(app, pos, startPos, camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground);
                manageKeys(playerX, speed, H, car, lines, startPos);
                sf::Time elapsed = clock.getElapsedTime();
                bool metacruz = false;
                comprobarMeta(startPos, goalPosIni, metacruz);
                if (metacruz == true && antmetacruz == false) {
                    if (esPrimeravez==true) {
                        esPrimeravez = false;
                    }
                    else {
                        clock.restart();  //cuando hagamos vuelta
                        elapsed = clock.getElapsedTime();
                        lim = limite;
                        lap++;
                        if (lap == 3) {
                            gameOver = true;
                        }
                    }
                }
                antmetacruz = metacruz;
                calcularScore(score, speed, lim, limite, gameOver);



                drawRoad(app, startPos, playerX, lines, N, x, dx, maxy, camH);
                drawObjects(app, startPos, lines, N, car);
                drawLetters(app, puntuaciones, speed, score, elapsed, lim, gameOver);
                //std::cout<<startPos<<std::endl;
               
                drawGear(app, marchaBaja, marcha);

                if (speed < 0) speed = 0;



                if (gameOver == true) {
                    drawGameOver(app);
                }


                if (gameOver == true && restart == false) {
                    tiempoparafin.restart();
                    escribirPuntuaciones(puntuaciones, score, mapa);
                    restart = true;
                }
                else if (gameOver == true && restart == true) {
                    estado = 2;
                    if (tiempoparafin.getElapsedTime().asSeconds() > 10) {//esperamos 10 segundos para terminar
                        app.clear(Color(0, 0, 180));

                        drawRanking(app, puntuaciones, lim, score);

                    }
                }

                app.display();


            }

            break;
        case 2: //resultados clas
            terminar = false;
            tiempoparafin.restart();
            while (app.isOpen()&& !terminar) {
                Event e;
                while (app.pollEvent(e)) {
                    if (e.type == Event::Closed)
                        app.close();
                }


                if (e.type == sf::Event::Resized) {
                    sf::View view = app.getDefaultView();
                    view = getLetterboxView(view, e.size.width, e.size.height);
                    app.setView(view);
                }
                if (tiempoparafin.getElapsedTime().asSeconds() < 5) {//esperamos 10 segundos para terminar
                    app.clear(Color(0, 0, 180));

                    drawRanking(app, puntuaciones, lim, score);
                }
                else {
                    estado = 1;
                    terminar = true;
                }
                app.display();
            }
            break;
        default:
            break;


        }
    }
    

    return 0;
}