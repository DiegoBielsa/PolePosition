#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
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
int estado = 5;
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
int color = 0;

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
Clock actualizar;


Time tiempoconseguido;
bool ultimotiempo = false;
int score = 0;
bool esPrimeravez = true; //para saber si hemos pasado la meta por primera vez
bool metacruz = false;
bool antmetacruz = false; //para ver si estamos parados en la meta
bool pulsada = 0; //letra pulsada
int posicionPuntuacion = 0; // posicion de nuestra puntuacion

int mapa; //mapa a elegir
int iaMode = 0; //ia a elegir

string nombre[] = { "A","A","A" };
string key[] = {"A","B","C","D", "E","F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

/*------------------------------- FIN FUNCIONES DE CONTROL DEL BUCLE PRINCIPAL -------------------------------*/

void updateSound(int& speed,   vector<Sound>& sounds ){
    float pitch = ((float(speed)/maxSpeed));
    cout<<pitch<<endl;
    if(pitch < 0.05){
        sounds[5].setPitch(0.05f);
    }
    else{
        sounds[5].setPitch(pitch);
    }
}

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
    string nombres[7];

  
    int letra = 0; //para saber en que letra estamos
    int iterador = 0; //para saber en que posicion de AAA estamos
    int limite = 0;


    
    int lim = 0; //variable que iremos restando para no tener que volver a leer el fichero cuando hacemos vuelta

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
    vector<Sound> sounds;

    SoundBuffer buffer;

    if(!buffer.loadFromFile("audio/audio2.wav")) {
        std::cout<<"error en audio"<<std::endl;
    }
    Sound sound;
    sound.setBuffer(buffer);

    //playSound(sound);
    sounds.push_back(sound);
    SoundBuffer buffer2;
    Sound sound2;
    if(!buffer2.loadFromFile("audio/crash.wav")) {
        std::cout<<"error en audio"<<std::endl;
    }
    sound2.setBuffer(buffer2);
    sounds.push_back(sound2);

    SoundBuffer buffer3;
    Sound sound3;
    if(!buffer3.loadFromFile("audio/prepare.wav")) {
        std::cout<<"error en audio"<<std::endl;
    }
    sound3.setBuffer(buffer3);
    sounds.push_back(sound3);

    SoundBuffer buffer4;
    Sound sound4;
    if(!buffer4.loadFromFile("audio/derrape.wav")) {
        std::cout<<"error en audio"<<std::endl;
    }
    sound4.setBuffer(buffer4);
    sounds.push_back(sound4);
    SoundBuffer buffer5;
    Sound sound5;
    if(!buffer5.loadFromFile("audio/carengine.wav")) {
        std::cout<<"error en audio"<<std::endl;
    }
    sound5.setBuffer(buffer5);
    sounds.push_back(sound5);

    SoundBuffer buffer6;
    Sound sound6;
    if(!buffer6.loadFromFile("audio/f1sound1.ogg")) {
        std::cout<<"error en audio"<<std::endl;
    }
    sound6.setBuffer(buffer6);
    sounds.push_back(sound6);
    SoundBuffer buffer7;
    Sound sound7;
    if(!buffer7.loadFromFile("audio/skidding.wav")) {
        std::cout<<"error en audio"<<std::endl;
    }
    sound7.setBuffer(buffer7);
    sounds.push_back(sound7);
    SoundBuffer buffer8;
    Sound sound8;
    if(!buffer8.loadFromFile("audio/eleccion.wav")) {
        std::cout<<"error en audio"<<std::endl;
    }
    sound8.setBuffer(buffer8);
    sounds.push_back(sound8);
    SoundBuffer buffer9;
    Sound sound9;
    if(!buffer9.loadFromFile("audio/carga.wav")) {
        std::cout<<"error en audio"<<std::endl;
    }
    sound9.setBuffer(buffer9);
    sounds.push_back(sound9);
    SoundBuffer buffer10;
    Sound sound10;
    if(!buffer10.loadFromFile("audio/qualify.wav")) {
        std::cout<<"error en audio"<<std::endl;
    }
    sound10.setBuffer(buffer10);
    sounds.push_back(sound10);
    

    

    setMaps(maps, object);

  


    int N = lines.size();
    float playerX = 0;
    int pos = 0;
    int H = 1500;
    while (true) {
        switch (estado)
        {
        case 0://clasificacion
            sounds[9].play();
            sounds[5].setPitch(1.0f);
            sounds[5].setLoop(true);
            sounds[5].play();
            terminar = false;
            tiempoparafin.restart();
            posicionPuntuacion = 0;
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
                


                updateSound(speed, sounds);


                int startPos, camH, maxy;
                float x, dx;
                updateVars(app, pos, startPos, camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground);
                manageKeys(playerX, speed, H, car, lines, startPos, sounds);
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
                drawObjects(app, startPos, lines, N, car, sounds);
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
                    escribirPuntuaciones(puntuaciones, score, mapa, posicionPuntuacion,iaMode);
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
                manageKeys(playerX, speed, H, car, lines, startPos, sounds);
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
                drawObjects(app, startPos, lines, N, car, sounds);
                drawLetters(app, puntuaciones, speed, score, elapsed, lim, gameOver);
                //std::cout<<startPos<<std::endl;
               
                drawGear(app, marchaBaja, marcha);

                if (speed < 0) speed = 0;



                if (gameOver == true) {
                    drawGameOver(app);
                }


                if (gameOver == true && restart == false) {
                    tiempoparafin.restart();
                    escribirPuntuaciones(puntuaciones, score, mapa,posicionPuntuacion,iaMode);
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
        case 2: //resultados clas
            terminar = false;
            tiempoparafin.restart();
            letra = 0;
            color = 0;
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
                    app.clear(Color(44, 76, 116));
                    bool haCambiado = 0;
                    selectName(nombre,key,letra,iterador,terminar,haCambiado,actualizar);
                    nombres[posicionPuntuacion] = nombre[0]+nombre[1]+nombre[2];

                    if (haCambiado == 1) {

                        escribirNombres(nombres, mapa,iaMode);
                        leerNombres(nombres, mapa,iaMode);
                        haCambiado = 0;
                    }

                    drawRanking(app, puntuaciones,nombres ,lim, score,posicionPuntuacion,color);
                
                if(terminar==true) {
                    estado = 1;
                    terminar = true;
                }
                app.display();
            }
            break;
        case 3: //pantalla inicio
            sounds[8].play();
            terminar = false;
            tiempoparafin.restart();
            color = 0; //color de los sprites
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
                if (tiempoparafin.getElapsedTime().asSeconds() < 10) {//esperamos 10 segundos para terminar
                    app.clear(Color(227, 187, 107));
                    
                    drawInicio(app,color);
                    
                }
                else {
                    cout<<"pasamos"<<endl;
                    estado = 4;
                    terminar = true;
                }
                app.display();
            }
            break;
        case 4: //pantalla eleccioncircuito
            sounds[7].play();
            terminar = false;
            tiempoparafin.restart();
            color = 0; //color de los sprites
            mapa = 0;
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
                app.clear(Color(44, 76, 116));

                manageKeysCircuito(mapa,terminar);

                drawCircuito(app, color,mapa);
                if (terminar == true) {
                    estado = 5;
                    // eleccion del mapa
                    lines = maps[mapa];
                     N = lines.size();
                }

                
                app.display();
            }

            break;
        case 5: //pantalla eleccion ia
            sounds[7].play();
            terminar = false;
            tiempoparafin.restart();
            color = 0; //color de los sprites
            iaMode = 0;
            pulsada = 0;
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
                app.clear(Color(44, 76, 116));
                manageKeysIa(iaMode,terminar,actualizar);

                drawIa(app, color,iaMode);
                if (terminar == true) {
                    estado = 2;
                    leerPuntuaciones(puntuaciones, mapa,iaMode);

                    leerNombres(nombres, mapa,iaMode);
                    leerLimite(limite, mapa);
                    lim = limite;

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