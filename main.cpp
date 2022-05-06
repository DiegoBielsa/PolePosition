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
int estado = 3;
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
int numCars;
int mediumSpeed;
int iaMode;
float off_road_allowed_cars;
int carPosition;
int startPos;
Clock actualizar;
Time tiempoFinal;
int posicionSalida = 0;//posicion desde la que saldremos
int bonus = 0;
bool noClasifica = false;



Time tiempoconseguido;
bool ultimotiempo = false;
int score = 0;
bool esPrimeravez = true; //para saber si hemos pasado la meta por primera vez
bool metacruz = false;
bool antmetacruz = false; //para ver si estamos parados en la meta
bool pulsada = 0; //letra pulsada
int posicionPuntuacion = 0; // posicion de nuestra puntuacion
bool prepare = true;

int mapa; //mapa a elegir

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
    string clasificaciones[8];

  

  
    int letra = 0; //para saber en que letra estamos
    int iterador = 0; //para saber en que posicion de AAA estamos
    int limite = 0;


    
    int lim = 0; //variable que iremos restando para no tener que volver a leer el fichero cuando hacemos vuelta

    Texture t[50];
    Sprite object[50];
    Texture ca;
    Texture marcha;
    //ca.loadFromFile("sprites/coches/carSpritesheet.png");
    //carSprite car;
    //car.init(IntRect(0, 0, car_width, car_height), ca); //Inicializar sprite coche
    carSprite car;
    int k = 0;

    for (int j = 0; j <= 11; j++) {
        car.texCar[k].loadFromFile("sprites/coches/DroveCar/tile" + std::to_string(j) + std::to_string(0) + ".png");
        k++;
        car.texCar[k].loadFromFile("sprites/coches/DroveCar/tile" + std::to_string(j) + std::to_string(1) + ".png");
        k++;
    }
    for (int j = 0; j < 12; j++) {
        car.texCarExp[j].loadFromFile("sprites/coches/Crash/crash" + std::to_string(j) + ".png");
    }

    car.init(); //Inicializar sprite coche
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
    t[16].loadFromFile("sprites/entorno/prepareto.png");
    t[16].setSmooth(true);
    object[16].setTexture(t[16]);
    object[16].setPosition(width,200);
    object[16].setScale(2,2);



    
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
    

  

    carSpriteIA car_arr[8];
    float XPos[8];
    int linePos[8];
    std::thread threads[8];
    int posIA = 0;
    float playerX = 0;
    int N = lines.size();
    int pos = 0;
    
    int H = 1500;
    for (int i = 0; i < numCars; i++) {
        if (i == carPosition) {
            if (posIA % 2 == 0) playerX = -0.5;
            else playerX = 0.6;
            pos = segL * (goalPosIni-20 - carPosition*7);
            posIA++;

        }
        int k = 0;

        for (int j = 0; j <= 11; j++) {
            car_arr[i].texCar[k].loadFromFile("sprites/coches/IACar" + std::to_string(i) + "/tile" + std::to_string(j) + std::to_string(0) + ".png");
            k++;
            car_arr[i].texCar[k].loadFromFile("sprites/coches/IACar" + std::to_string(i) + "/tile" + std::to_string(j) + std::to_string(1) + ".png");
            k++;
        }
        for (int j = 3; j <= 11; j++) {
            car_arr[i].texCarExp[j-3].loadFromFile("sprites/coches/Crash/crash" + std::to_string(j) + ".png");
        }
        car_arr[i].init();
        if (posIA % 2 == 0) {
            XPos[i] = -0.7;
            if(carPosition < 8 && carPosition%2 == 0) {
                car_arr[i].car_dir = 0;
                car_arr[i].actualTex = 0;
            }else{
                car_arr[i].car_dir = 1;
            }
            
        }
        else {
            XPos[i] = 0.4;
            if(carPosition < 8 && carPosition%2 != 0) {
                car_arr[i].car_dir = 0;
                car_arr[i].actualTex = 0;
            }else{
                car_arr[i].car_dir = -1;
                car_arr[i].car_inv = true;
            }
            
        }
        linePos[i] = (goalPosIni-2) - i * 7;
        posIA++;
    }
    

    IA_control(lines, linePos, XPos, car_arr, numCars, iaMode, threads);


    
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
            color = 0;
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


                int camH, maxy;
                float x, dx;
                updateVars(app, pos, startPos, camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground, car);
                if(prepare){
                    drawPrepare(app,object, prepare);
                }else{
                    manageKeys(playerX, speed, H, car, lines, startPos, sounds);
                }
                sf::Time elapsed = clock.getElapsedTime();
            
                comprobarMeta(startPos, goalPosIni, metacruz,speed);

                
                if (metacruz == true && antmetacruz==false) {
                    if (esPrimeravez==true) {
                        esPrimeravez = false;
                    }
                    else {
                        gameOver = true;
                    }
                }
                antmetacruz = metacruz;
                calcularScore(score, speed, lim, limite, gameOver,iaMode);


                drawRoad(app, startPos, playerX, lines, N, x, dx, maxy, camH);
                drawObjects(app, startPos, lines, N, car, sounds);
                drawLetters(app, puntuaciones, speed, score, elapsed, lim, gameOver,tiempoFinal,noClasifica);
                
                //std::cout<<startPos<<std::endl;
                //if (startPos >= 3500 && startPos <= 3550) {
                  //  gameOver = true;
                //}
                drawGear(app, marchaBaja, marcha);

                if (speed < 0) speed = 0;



                if (gameOver == true) {
                    drawGameOver(app);
                }


                if (gameOver == true && restart == false ) {
                    tiempoparafin.restart();
                    //escribirPuntuaciones(puntuaciones, score, mapa, posicionPuntuacion,iaMode);
                    calcularPosclasificacion(clasificaciones, tiempoFinal, posicionSalida,noClasifica);
                    calcularBonusExtra(posicionSalida, iaMode,bonus);
                    restart = true;
                }
                else if (gameOver == true && restart == true) {
                    if (posicionSalida > 7 ) {
                        estado = 2;
                    }else{
                        estado = 1;
                    }
                    
                    if (tiempoparafin.getElapsedTime().asSeconds() < 3) {
                        drawResultadosClas(app, tiempoFinal, posicionSalida,bonus, color,0);
                    }
                    else if (tiempoparafin.getElapsedTime().asSeconds() < 6) {
                        drawResultadosClas(app, tiempoFinal, posicionSalida,bonus, color,1);

                    }
                    else if(tiempoparafin.getElapsedTime().asSeconds() < 9) {
                        drawResultadosClas(app, tiempoFinal, posicionSalida,bonus, color, 2);
                    }
                    
                    
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
            restart = false;
            clock.restart();
            esPrimeravez = true;
            pos = 0;
            playerX = 0;
            speed = 0;
            terminar = false;
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
                updateVars(app, pos, startPos, camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground, car);
                manageKeys(playerX, speed, H, car, lines, startPos, sounds);
                sf::Time elapsed = clock.getElapsedTime();
                bool metacruz = false;
                comprobarMeta(startPos, goalPosIni, metacruz,speed);
                if (metacruz == true && antmetacruz == false) {
                    if (esPrimeravez == true) {
                        esPrimeravez = false;
                    }
                    else {
                        clock.restart();  //cuando hagamos vuelta
                        elapsed = clock.getElapsedTime();
                        lim = lim+limite;
                        lap++;
                        if (lap == 3) {
                            gameOver = true;
                        }
                    }
                }
                antmetacruz = metacruz;
                calcularScore(score, speed, lim, limite, gameOver,iaMode);



                drawRoad(app, startPos, playerX, lines, N, x, dx, maxy, camH);
                drawObjects(app, startPos, lines, N, car, sounds);
                drawLetters(app, puntuaciones, speed, score, elapsed, lim, gameOver,tiempoFinal,noClasifica);
                //std::cout<<startPos<<std::endl;

                drawGear(app, marchaBaja, marcha);

                if (speed < 0) speed = 0;



                if (gameOver == true) {
                    drawGameOver(app);
                }


                if (gameOver == true && restart == false) {
                    tiempoparafin.restart();
                    escribirPuntuaciones(puntuaciones, score, mapa,posicionPuntuacion,iaMode);
                    cout << "posicionPuntuacion " << posicionPuntuacion << endl;
                    restart = true;
                }
     
                
                
                else if (gameOver == true && restart == true) {
                    estado = 2;
 
                    if (tiempoparafin.getElapsedTime().asSeconds() > 5) {//esperamos 10 segundos para terminar
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
            actualizar.restart();
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

                    if (posicionPuntuacion >= 0 && posicionPuntuacion < 7) {
                        selectName(nombre, key, letra, iterador, terminar, haCambiado, actualizar);


                        nombres[posicionPuntuacion] = nombre[0] + nombre[1] + nombre[2];


                        if (haCambiado == 1) {
                            escribirNombres(nombres, mapa, iaMode);
                            leerNombres(nombres, mapa, iaMode);
                            haCambiado = 0;

                        }
                    }
                    drawRanking(app, puntuaciones,nombres ,lim, score,posicionPuntuacion,color);
                
                if(terminar==true) {
                    estado = 2;
                    terminar = true;
                    escribirNombres(nombres, mapa, iaMode);
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
                //std::cout << "a" << std::endl;
                    app.clear(Color(227, 187, 107));
                    
                    drawInicio(app,color);
                    
                }
                else {
                   std::cout << "a" << std::endl;
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
            actualizar.restart();
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
                    estado = 0;
                    leerPuntuaciones(puntuaciones, mapa,iaMode);
                    leerClasificaciones(clasificaciones, mapa, iaMode);
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