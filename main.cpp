#pragma once
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
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
sf::Time antesdepausa;

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
int bonus = 0;
bool noClasifica = false;
bool derrape = false;



Time tiempoconseguido;
bool ultimotiempo = false;
int score = 0;
bool esPrimeravez = true; //para saber si hemos pasado la meta por primera vez
bool metacruz = false;
bool antmetacruz = false; //para ver si estamos parados en la meta
bool pulsada = 0; //letra pulsada
int posicionPuntuacion = 0; // posicion de nuestra puntuacion
bool prepare = true;
int semaforo = 0;
bool go = false;


int mapa; //mapa a elegir
bool atras = false;
bool salir = false;
bool pausa = false;
int posicionMenu = 0;
int posicionMenuOpciones = 0;
int teamNano = 1;
int posicionMenuvolumen = 0;

string nombre[] = { "A","A","A" };
string key[] = { "A","B","C","D", "E","F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

/*------------------------------- FIN FUNCIONES DE CONTROL DEL BUCLE PRINCIPAL -------------------------------*/

void updateSound(int& speed, vector<Sound>& sounds) {
    float pitch = ((float(speed) / maxSpeed));
    //cout<<pitch<<endl;
    if (pitch < 0.05) {
        sounds[5].setPitch(0.05f);
    }
    else {
        sounds[5].setPitch(pitch);
    }
}

void updateSoundIA(vector<Sound>& sounds, int linePos[], int miPos) {

    for (int i = 0; i < 8; i++) {
        int distancia = abs(miPos - linePos[i]);
        if (distancia < 30) {//coche i esta cerca
            //cout<<"coche "<<i<<" cerca, a "<<distancia<<endl;
            sounds[13+i].setVolume(60 - distancia);
            //sounds[13+i].play();
        }else{
            //sounds[13+i].pause();
            sounds[13+i].setVolume(0);
        }
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
    Sprite captura = Sprite();




    int letra = 0; //para saber en que letra estamos
    int iterador = 0; //para saber en que posicion de AAA estamos
    int limite = 0;



    int lim = 0; //variable que iremos restando para no tener que volver a leer el fichero cuando hacemos vuelta

    Texture t[50];
    Sprite object[50];
    Texture ca;
    Texture textureCaptura = Texture();
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
    object[16].setPosition(width, 200);
    object[16].setScale(2, 2);



    for (int i = 0; i < 5; i++) {
        t[17 + i].loadFromFile("sprites/entorno/sema" + to_string(i) + ".png");
        t[17 + i].setSmooth(true);
        object[17 + i].setTexture(t[17 + i]);
        object[17 + i].setPosition((width / 2) - 85, 100);
        object[17 + i].setScale(3, 3);
    }

    t[22].loadFromFile("sprites/entorno/personas.png");
    t[22].setSmooth(true);
    object[22].setTexture(t[22]);
    t[23].loadFromFile("sprites/entorno/ruedaCarrera.png");
    t[23].setSmooth(true);
    object[23].setTexture(t[23]);




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

    if (!buffer.loadFromFile("audio/audio2.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    Sound sound;
    sound.setBuffer(buffer);

    //playSound(sound);
    sounds.push_back(sound);
    SoundBuffer buffer2;
    Sound sound2;
    if (!buffer2.loadFromFile("audio/crash.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound2.setBuffer(buffer2);
    sounds.push_back(sound2);

    SoundBuffer buffer3;
    Sound sound3;
    if (!buffer3.loadFromFile("audio/prepare.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound3.setBuffer(buffer3);
    sounds.push_back(sound3);

    SoundBuffer buffer4;
    Sound sound4;
    if (!buffer4.loadFromFile("audio/derrape.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound4.setBuffer(buffer4);
    sounds.push_back(sound4);
    SoundBuffer buffer5;
    Sound sound5;
    if (!buffer5.loadFromFile("audio/carengine.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound5.setBuffer(buffer5);
    sounds.push_back(sound5);

    SoundBuffer buffer6;
    Sound sound6;
    if (!buffer6.loadFromFile("audio/f1sound1.ogg")) {
        std::cout << "error en audio" << std::endl;
    }
    sound6.setBuffer(buffer6);
    sounds.push_back(sound6);
    SoundBuffer buffer7;
    Sound sound7;
    if (!buffer7.loadFromFile("audio/skidding.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound7.setBuffer(buffer7);
    sounds.push_back(sound7);
    SoundBuffer buffer8;
    Sound sound8;
    if (!buffer8.loadFromFile("audio/eleccion.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound8.setBuffer(buffer8);
    sounds.push_back(sound8);
    SoundBuffer buffer9;
    Sound sound9;
    if (!buffer9.loadFromFile("audio/carga.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound9.setBuffer(buffer9);
    sounds.push_back(sound9);
    SoundBuffer buffer10;
    Sound sound10;
    if (!buffer10.loadFromFile("audio/qualify.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound10.setBuffer(buffer10);
    sounds.push_back(sound10);
    SoundBuffer buffer11;
    Sound sound11;
    if (!buffer11.loadFromFile("audio/semaforo.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound11.setBuffer(buffer11);
    sounds.push_back(sound11);
    SoundBuffer buffer12;
    Sound sound12;
    if (!buffer12.loadFromFile("audio/semaquali.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound12.setBuffer(buffer12);
    sounds.push_back(sound12);
    SoundBuffer buffer13;
    Sound sound13;
    if (!buffer13.loadFromFile("audio/charco.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound13.setBuffer(buffer13);
    sounds.push_back(sound13);

    SoundBuffer buffer14;
    Sound sound14;
    if (!buffer14.loadFromFile("audio/f1sound1.ogg")) {
        std::cout << "error en audio" << std::endl;
    }
    sound14.setBuffer(buffer14);
    sounds.push_back(sound14);

    SoundBuffer buffer15;
    Sound sound15;
    if (!buffer15.loadFromFile("audio/f1sound1.ogg")) {
        std::cout << "error en audio" << std::endl;
    }
    sound15.setBuffer(buffer15);
    sounds.push_back(sound15);

    SoundBuffer buffer16;
    Sound sound16;
    if (!buffer16.loadFromFile("audio/f1sound1.ogg")) {
        std::cout << "error en audio" << std::endl;
    }
    sound16.setBuffer(buffer16);
    sounds.push_back(sound16);

    SoundBuffer buffer17;
    Sound sound17;
    if (!buffer17.loadFromFile("audio/f1sound1.ogg")) {
        std::cout << "error en audio" << std::endl;
    }
    sound17.setBuffer(buffer17);
    sounds.push_back(sound17);

    SoundBuffer buffer18;
    Sound sound18;
    if (!buffer18.loadFromFile("audio/f1sound1.ogg")) {
        std::cout << "error en audio" << std::endl;
    }
    sound18.setBuffer(buffer18);
    sounds.push_back(sound18);

    SoundBuffer buffer19;
    Sound sound19;
    if (!buffer19.loadFromFile("audio/f1sound1.ogg")) {
        std::cout << "error en audio" << std::endl;
    }
    sound19.setBuffer(buffer19);
    sounds.push_back(sound19);

    SoundBuffer buffer20;
    Sound sound20;
    if (!buffer20.loadFromFile("audio/f1sound1.ogg")) {
        std::cout << "error en audio" << std::endl;
    }
    sound20.setBuffer(buffer20);
    sounds.push_back(sound20);

    SoundBuffer buffer21;
    Sound sound21;
    if (!buffer21.loadFromFile("audio/f1sound1.ogg")) {
        std::cout << "error en audio" << std::endl;
    }
    sound21.setBuffer(buffer21);
    sounds.push_back(sound21);

    SoundBuffer buffer22;
    Sound sound22;
    if (!buffer22.loadFromFile("audio/trasquali.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound22.setBuffer(buffer22);
    sounds.push_back(sound22);

    SoundBuffer buffer23;
    Sound sound23;
    if (!buffer23.loadFromFile("audio/results.wav")) {
        std::cout << "error en audio" << std::endl;
    }
    sound23.setBuffer(buffer23);
    sounds.push_back(sound23);
    
    





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
            pos = segL * (goalPosIni - 27 - carPosition * 7);
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
            car_arr[i].texCarExp[j - 3].loadFromFile("sprites/coches/Crash/crash" + std::to_string(j) + ".png");
        }
        car_arr[i].init();
        if (posIA % 2 == 0) {
            XPos[i] = -0.7;
            if (carPosition < 8 && carPosition % 2 == 0) {
                car_arr[i].car_dir = 0;
                car_arr[i].actualTex = 0;
            }
            else {
                car_arr[i].car_dir = 1;
            }

        }
        else {
            XPos[i] = 0.4;
            if (carPosition < 8 && carPosition % 2 != 0) {
                car_arr[i].car_dir = 0;
                car_arr[i].actualTex = 0;
            }
            else {
                car_arr[i].car_dir = -1;
                car_arr[i].car_inv = true;
            }

        }
        linePos[i] = 250 + 50 * i;
        posIA++;
    }


    bool doJoin = true;
    while (app.isOpen()) {
        switch (estado)
        {
        case 0://clasificacion
            for (int i=0; i<8; i++) {
                if(!posicionMenuvolumen){sounds[13+i].play();}
                sounds[13+i].setLoop(true);
                sounds[13+i].setPitch(0.7f);
                sounds[13+i].setVolume(0.0f);
                
            }
            

            metacruz = false;
            antmetacruz = false; //para ver si estamos parados en la meta
            terminar = false;
            gameOver = false;
            restart = false;
            pos = 0;
            carPosition = 8;
            speed = 0;
            startPos = 0;
            semaforo = 0;
            playerX = 0;
            car.colision = false;
            esPrimeravez = true;
            noClasifica = false;
            if(!posicionMenuvolumen){sounds[9].play();}
            sounds[5].setPitch(1.0f);
            sounds[5].setLoop(true);
            if(!posicionMenuvolumen){sounds[5].play();}
            terminar = false;
            tiempoparafin.restart();
            pausa = false;
            clock.restart();
            antesdepausa = clock.getElapsedTime();
            posicionPuntuacion = 0;
            color = 0;
            startPos = 0;
            score = 0;
            doJoin = true;
            go = false;

            IA_control(lines, linePos, XPos, car_arr, numCars, iaMode, threads);
            while (app.isOpen() && !terminar) {
                if (!pausa) {
                    Event e;
                    while (app.pollEvent(e)) {
                        if (e.type == Event::Closed) {
                            app.close();
                            gameOver = true;
                        }
                        if (e.type == sf::Event::Resized) {
                            sf::View view = app.getDefaultView();
                            view = getLetterboxView(view, e.size.width, e.size.height);
                            app.setView(view);
                        }

                        if (e.type == sf::Event::KeyPressed) {

                            if (e.key.code == sf::Keyboard::Escape) {
                                //textureCaptura.create(app.getSize().x, app.getSize().y);
                                textureCaptura.update(app, app.getSize().x, app.getSize().y);
                                captura.setTexture(textureCaptura);
                                cout << "set color" << endl;

                                captura.setColor(sf::Color::Blue);



                                pausa = true;

                            }
                            if (e.key.code == sf::Keyboard::LControl && !keyState[e.key.code]) {
                                marchaBaja = !marchaBaja;
                            }

                            keyState[e.key.code] = true;

                        }
                        else if (e.type == sf::Event::KeyReleased) {
                            // Update state of current key:
                            keyState[e.key.code] = false;
                        }
                    }






                    updateSound(speed, sounds);
                    updateSoundIA(sounds, linePos, startPos+16);


                    int camH, maxy;
                    float x = 0, dx = 0;
                    if (prepare) {
                        updateVars(app, pos, startPos, camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground, car);
                        drawPrepare(app, object, prepare);
                    }
                    else if (semaforo < 50)
                    {
                        updateVars(app, pos, startPos, camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground, car);
                        if (semaforo == 0) { if(!posicionMenuvolumen){sounds[11].play();} }
                        semaforo++;
                        if (semaforo < 25) {
                            app.draw(object[17]);
                        }
                        else {
                            app.draw(object[21]);
                        }
                    }
                    else {
                        go = true;
                        manageKeys(playerX, speed, H, car, lines, startPos, sounds, posicionMenuvolumen);
                        updateVars(app, pos, startPos, camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground, car);
                    }




                    comprobarMeta(startPos, goalPosIni, metacruz, speed);


                    if (metacruz == true && antmetacruz == false) {
                        if (esPrimeravez == true) {
                            esPrimeravez = false;
                            clock.restart();
                        }
                        else {
                            gameOver = true;
                        }
                    }
                    sf::Time elapsed = clock.getElapsedTime() + antesdepausa;
                    antmetacruz = metacruz;
                    calcularScore(score, speed, lim, limite, gameOver, iaMode);


                    drawRoad(app, startPos, playerX, lines, N, x, dx, maxy, camH);
                    drawObjects(app, startPos, lines, N, car, sounds, posicionMenuvolumen);
                    drawLetters(app, puntuaciones, speed, score, elapsed, lim, gameOver, tiempoFinal, noClasifica, esPrimeravez);

                    //std::cout<<startPos<<std::endl;
                    //if (startPos >= 3500 && startPos <= 3550) {
                      //  gameOver = true;
                    //}
                    drawGear(app, marchaBaja, marcha);

                    if (speed < 0) speed = 0;



                    if (gameOver == true || terminar == true) {
                        for (int i=0; i<8; i++) {
                            sounds[13+i].setVolume(0.0f);
                        }
                        if (noClasifica == true) {
                            drawGameOver(app);
                        }
                        // al ser un bucle se ejecuta muchas veces

                        if (doJoin) {
                            for (int i = 0; i < numCars; i++) {
                                //std::cout << "join " << i << std::endl;
                                threads[i].join();
                            }
                        }

                        doJoin = false;
                    }


                    if (gameOver == true && restart == false) {
                        for (int i=0; i<8; i++) {
                            sounds[13+i].pause();
                        }
                        tiempoparafin.restart();
                        //escribirPuntuaciones(puntuaciones, score, mapa, posicionPuntuacion,iaMode);
                        calcularPosclasificacion(clasificaciones, tiempoFinal, carPosition, noClasifica);
                        if (noClasifica == true) {
                            posicionPuntuacion = 10;
                        }
                        calcularBonusExtra(carPosition, iaMode, bonus);
                        score = score + bonus;
                        restart = true;
                    }
                    else if (gameOver == true && restart == true) {
                        for (int i=0; i<8; i++) {
                            sounds[13+i].pause();
                        }
                        if (carPosition > 7) {
                            estado = 2;
                        }
                        else {
                            estado = 1;
                        }

                        if (tiempoparafin.getElapsedTime().asSeconds() < 3) {
                            drawResultadosClas(app, tiempoFinal, carPosition, bonus, color, 0);
                        }
                        else if (tiempoparafin.getElapsedTime().asSeconds() < 6) {
                            drawResultadosClas(app, tiempoFinal, carPosition, bonus, color, 1);

                        }
                        else if (tiempoparafin.getElapsedTime().asSeconds() < 9) {
                            drawResultadosClas(app, tiempoFinal, carPosition, bonus, color, 2);
                        }


                        if (tiempoparafin.getElapsedTime().asSeconds() > 10) {//esperamos 10 segundos para terminar
                            terminar = true;
                        }
                    }
                    if (pausa == true && esPrimeravez==false) {
                        antesdepausa = elapsed;

                    }

                    app.display();
                }

                else {
                    Event e;
                    while (app.pollEvent(e)) {
                        if (e.type == Event::Closed) {
                            app.close();
                            gameOver = true;
                        }
                    }


                    if (e.type == sf::Event::Resized) {
                        sf::View view = app.getDefaultView();
                        view = getLetterboxView(view, e.size.width, e.size.height);
                        app.setView(view);
                    }

                    //Sprite captura(textureCaptura);
                    //cout<<"set color"<<endl;


                    app.draw(captura);
                    hacerPausa(app, salir, terminar, pausa, actualizar);
                    eleccionPausa(app, salir, color);
                    if (salir && terminar) {

                        if (doJoin) {
                            for (int i = 0; i < numCars; i++) {
                                //std::cout << "join " << i << std::endl;
                                threads[i].join();
                            }
                        }

                        doJoin = false;
                        estado = 6;
                        speed = 0;
                        updateSound(speed, sounds);
                        sounds[5].pause();
                        updateSoundIA(sounds, linePos, startPos+16);
                        prepare = true;
                    }

                    clock.restart();
                    app.display();
                }


            }

            break;

        case 1://carrera
            //setMaps(maps, object);
            //lines = maps[mapa];
            for (int i=0; i<8; i++) {
                if(!posicionMenuvolumen)sounds[13+i].play();
                sounds[13+i].setLoop(true);
                sounds[13+i].setPitch(0.7f);
                sounds[13+i].setVolume(0.0f);
                
            }
            go = false;
            semaforo = 0;
            sounds[5].setPitch(1.0f);
            sounds[5].setLoop(true);
            if(!posicionMenuvolumen){sounds[5].play();}
            //inicializamos todo
            int lap;
            lap = 0;
            gameOver = false;
            car.colision = false;
            restart = false;
            clock.restart();
            pausa = false;
            antesdepausa = clock.getElapsedTime();
            esPrimeravez = true;
            metacruz = false;
            pos = 0;
            playerX = 0;
            speed = 0;
            startPos = 0;
            doJoin = true;
            terminar = false;
            car.reinit();
            for (int i = 0; i < numCars; i++) {
                if (i == carPosition) {
                    if (posIA % 2 == 0) playerX = -0.5;
                    else playerX = 0.6;
                    pos = segL * (goalPosIni - 27 - carPosition * 7);
                    posIA++;

                }
                int k = 0;
                car_arr[i].init();
                if (posIA % 2 == 0) {
                    XPos[i] = -0.7;
                    if (carPosition < 8 && carPosition % 2 == 0) {
                        car_arr[i].car_dir = 0;
                        car_arr[i].actualTex = 0;
                    }
                    else {
                        car_arr[i].car_dir = 1;
                    }

                }
                else {
                    XPos[i] = 0.4;
                    if (carPosition < 8 && carPosition % 2 != 0) {
                        car_arr[i].car_dir = 0;
                        car_arr[i].actualTex = 0;
                    }
                    else {
                        car_arr[i].car_dir = -1;
                        car_arr[i].car_inv = true;
                    }

                }
                linePos[i] = (goalPosIni - 10) - i * 7;
                posIA++;
            }
            IA_control(lines, linePos, XPos, car_arr, numCars, iaMode, threads);
            while (app.isOpen() && !terminar) {
                if (!pausa) {
                    Event e;
                    while (app.pollEvent(e)) {
                        if (e.type == Event::Closed) {
                            app.close();
                            gameOver = true;
                        }

                        if (e.type == sf::Event::Resized) {
                            sf::View view = app.getDefaultView();
                            view = getLetterboxView(view, e.size.width, e.size.height);
                            app.setView(view);
                        }

                        if (e.type == sf::Event::KeyPressed) {

                            if (e.key.code == sf::Keyboard::Escape) {
                                //textureCaptura.create(app.getSize().x, app.getSize().y);
                                textureCaptura.update(app, app.getSize().x, app.getSize().y);
                                captura.setTexture(textureCaptura);
                                cout << "set color" << endl;

                                captura.setColor(sf::Color::Blue);



                                pausa = true;

                            }
                            if (e.key.code == sf::Keyboard::LControl && !keyState[e.key.code]) {
                                marchaBaja = !marchaBaja;
                            }

                            keyState[e.key.code] = true;

                        }
                        else if (e.type == sf::Event::KeyReleased) {
                            // Update state of current key:
                            keyState[e.key.code] = false;
                        }
                    }


                    

                    



                    int camH, maxy;
                    float x = 0, dx = 0;
                    updateSound(speed, sounds);
                    
                    //updateVars(app, pos, startPos, camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground, car);
                    if (semaforo < 250) {
                        if (semaforo == 0) { if(!posicionMenuvolumen){sounds[10].play();} }
                        updateVars(app, pos, startPos, camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground, car);
                        drawSemaphore(app, object, semaforo);
                    }
                    else {
                        updateSoundIA(sounds, linePos, startPos+16);
                        go = true;
                        manageKeys(playerX, speed, H, car, lines, startPos, sounds, posicionMenuvolumen);
                        updateVars(app, pos, startPos, camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground, car);
                    }

                    comprobarMeta(startPos, goalPosIni, metacruz, speed);
                    if (metacruz == true && antmetacruz == false) {
                        if (esPrimeravez == true) {
                            esPrimeravez = false;
                            clock.restart();
                        }
                        else {
                            clock.restart();  //cuando hagamos vuelta
                            lim = lim + limite / 3;
                            lap++;
                            if (lap == 3) {
                                gameOver = true;
                            }
                        }
                    }
                    sf::Time elapsed = clock.getElapsedTime() + antesdepausa;

                    antmetacruz = metacruz;
                    calcularScore(score, speed, lim, limite, gameOver, iaMode);




                    drawRoad(app, startPos, playerX, lines, N, x, dx, maxy, camH);
                    drawObjects(app, startPos, lines, N, car, sounds, posicionMenuvolumen);
                    drawLetters(app, puntuaciones, speed, score, elapsed, lim, gameOver, tiempoFinal, noClasifica, esPrimeravez);
                    //std::cout<<startPos<<std::endl;

                    drawGear(app, marchaBaja, marcha);

                    if (speed < 0) speed = 0;



                    if (gameOver == true) {
                        drawGameOver(app);
                        if (doJoin) {
                            for (int i = 0; i < numCars; i++) {
                                //std::cout << "join " << i << std::endl;
                                threads[i].join();
                            }
                        }

                        doJoin = false;
                    }


                    if (gameOver == true && restart == false) {
                        tiempoparafin.restart();
                        //score = 21;
                        for (int i=0; i<8; i++) {
                            sounds[13+i].pause();
                        }
                        escribirPuntuaciones(puntuaciones, score, mapa, posicionPuntuacion, iaMode);
                        cout << "posicionPuntuacion " << posicionPuntuacion << endl;
                        restart = true;
                    }



                    else if (gameOver == true && restart == true) {
                        estado = 2;

                        if (tiempoparafin.getElapsedTime().asSeconds() > 5) {//esperamos 10 segundos para terminar
                            terminar = true;
                        }
                    }
                    if (pausa == true && esPrimeravez == false) {
                        antesdepausa = elapsed;

                    }
                    app.display();
                }
                else {
                    Event e;
                    while (app.pollEvent(e)) {
                        if (e.type == Event::Closed) {
                            app.close();
                            gameOver = true;
                        }
                    }


                    if (e.type == sf::Event::Resized) {
                        sf::View view = app.getDefaultView();
                        view = getLetterboxView(view, e.size.width, e.size.height);
                        app.setView(view);
                    }
                    Texture capt;
                    capt.loadFromFile("images/captura.png");
                    Sprite captura(textureCaptura);

                    captura.setColor(sf::Color(0x00FF007F));
                    app.draw(captura);
                    hacerPausa(app, salir, terminar, pausa, actualizar);
                    eleccionPausa(app, salir, color);
                    if (salir && terminar) {
                        if (doJoin) {
                            for (int i = 0; i < numCars; i++) {
                                //std::cout << "join " << i << std::endl;
                                threads[i].join();
                            }
                        }

                        doJoin = false;
                        estado = 6;
                        speed = 0;
                        updateSound(speed, sounds);
                        sounds[5].pause();
                        updateSoundIA(sounds, linePos, startPos+16);
                        prepare = true;

                    }

                    clock.restart();
                    app.display();

                }


            }

            break;
        case 2: //resultados clas

            terminar = false;
            sounds[5].pause();
            if(!posicionMenuvolumen){sounds[22].play();}
            tiempoparafin.restart();
            letra = 0;
            color = 0;
            actualizar.restart();
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
                bool haCambiado = 0;
                if (noClasifica == true) {
                    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                        terminar = true;
                    }

                }

                if (posicionPuntuacion >= 0 && posicionPuntuacion < 7) {
                    selectName(nombre, key, letra, iterador, terminar, haCambiado, actualizar);

                    nombres[posicionPuntuacion] = nombre[0] + nombre[1] + nombre[2];


                    if (haCambiado == 1) {
                        escribirNombres(nombres, mapa, iaMode);
                        leerNombres(nombres, mapa, iaMode);
                        haCambiado = 0;

                    }
                }
                drawRanking(app, puntuaciones, nombres, lim, score, posicionPuntuacion, color);
                if (terminar == true) {

                    terminar = true;
                    escribirNombres(nombres, mapa, iaMode);
                    estado = 6;
                    sounds[22].stop();
                }
                app.display();
            }
            break;
        case 3: //pantalla inicio
            if(!posicionMenuvolumen){sounds[8].play();}
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

                    drawInicio(app, color);

                }
                else {
                    estado = 6;
                    terminar = true;
                }
                app.display();
            }
            break;
        case 4: //pantalla eleccioncircuito
            if(!posicionMenuvolumen){sounds[7].play();}
            terminar = false;
            atras = false;
            tiempoparafin.restart();
            actualizar.restart();
            color = 0; //color de los sprites
            mapa = 0;
            while (app.isOpen() && !terminar) {
                Event e;
                while (app.pollEvent(e)) {
                    if (e.type == Event::Closed) {
                        app.close();
                    }

                    manageKeysCircuito(mapa, terminar, atras, e);
                }


                if (e.type == sf::Event::Resized) {
                    sf::View view = app.getDefaultView();
                    view = getLetterboxView(view, e.size.width, e.size.height);
                    app.setView(view);
                }
                app.clear(Color(44, 76, 116));



                drawCircuito(app, color, mapa, atras);
                if (terminar == true) {
                    if (atras == true) {
                        estado = 3;
                    }
                    else {
                        estado = 5;

                        // eleccion del mapa
                        lines = maps[mapa];
                        N = lines.size();
                    }
                }


                app.display();
            }

            break;
        case 5: //pantalla eleccion ia
            if(!posicionMenuvolumen){sounds[7].play();}
            terminar = false;
            atras = false;
            actualizar.restart();
            tiempoparafin.restart();
            color = 0; //color de los sprites
            iaMode = 0;
            pulsada = 0;
            while (app.isOpen() && !terminar) {
                Event e;
                while (app.pollEvent(e)) {
                    if (e.type == Event::Closed) {
                        app.close();
                    }

                    manageKeysIa(iaMode, terminar, atras, e);
                }


                if (e.type == sf::Event::Resized) {
                    sf::View view = app.getDefaultView();
                    view = getLetterboxView(view, e.size.width, e.size.height);
                    app.setView(view);
                }
                app.clear(Color(44, 76, 116));


                drawIa(app, color, iaMode, atras);
                if (terminar == true) {
                    if (atras == true) {
                        estado = 4;
                    }
                    else {
                        estado = 0;
                        leerPuntuaciones(puntuaciones, mapa, iaMode);
                        leerClasificaciones(clasificaciones, mapa, iaMode);
                        leerNombres(nombres, mapa, iaMode);
                        leerLimite(limite, mapa);
                        lim = limite;
                    }

                }


                app.display();
            }
            break;
        case 6: //menu
            if(!posicionMenuvolumen){sounds[7].play();}
            terminar = false;
            atras = false;
            actualizar.restart();
            tiempoparafin.restart();
            color = 0; //color de los sprites
            iaMode = 0;
            pulsada = 0;
            posicionMenu = 0;
            while (app.isOpen() && !terminar) {
                Event e;
                while (app.pollEvent(e)) {
                    if (e.type == Event::Closed) {
                        app.close();
                    }
                    manageKeysMenu(terminar, e, posicionMenu);
                }


                if (e.type == sf::Event::Resized) {
                    sf::View view = app.getDefaultView();
                    view = getLetterboxView(view, e.size.width, e.size.height);
                    app.setView(view);
                }
                app.clear(Color(227, 187, 107));


                drawMenu(app, color, posicionMenu);
                if (terminar == true) {

                    if (posicionMenu == 0) {
                        estado = 4;

                    }
                    else if (posicionMenu == 1) {
                        estado = 7;
                    }
                    else {
                        app.close();
                    }

                }


                app.display();
            }

            break;


        case 7: //menu opciones
            if(!posicionMenuvolumen){sounds[7].play();}
            terminar = false;
            atras = false;
            actualizar.restart();
            tiempoparafin.restart();
            color = 0; //color de los sprites
            iaMode = 0;
            pulsada = 0;
            posicionMenu = 0;
            while (app.isOpen() && !terminar) {
                Event e;
                while (app.pollEvent(e)) {
                    if (e.type == Event::Closed) {
                        app.close();
                    }
                    manageKeysOptions(posicionMenuOpciones, terminar, e, atras);
                }


                if (e.type == sf::Event::Resized) {
                    sf::View view = app.getDefaultView();
                    view = getLetterboxView(view, e.size.width, e.size.height);
                    app.setView(view);
                }
                app.clear(Color(227, 187, 107));

                drawMenuOpciones(app, color, posicionMenuOpciones, atras);
                if (terminar == true) {
                    if (atras == true) {
                        estado = 6;
                    }
                    else {
                        if (posicionMenuOpciones == 0) {
                            estado = 8;

                        }
                        else if (posicionMenuOpciones == 1) {
                            estado = 9;
                        }
                        else if (posicionMenuOpciones == 2) {
                            estado = 10;
                        }
                    }
                    terminar = true;

                }

                app.display();
            }


            break;

        case 8: //elegir teclas
            if(!posicionMenuvolumen){sounds[7].play();}
            terminar = false;
            atras = true;
            actualizar.restart();
            tiempoparafin.restart();
            color = 0; //color de los sprites
            iaMode = 0;
            pulsada = 0;
            posicionMenuOpciones = 0;
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
                app.clear(Color(227, 187, 107));

                drawMenuteclas(app, color, posicionMenuOpciones, atras);
                if (actualizar.getElapsedTime().asSeconds() > 0.1f) { //sin esto se pasa de "estados"
                    actualizar.restart();
                    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                        terminar = true;
                    }

                }
                if (terminar == true) {
                    if (atras == true) {
                        estado = 7;
                    }

                }


                app.display();
            }


            break;
        case 9: //elegir nano
            if(!posicionMenuvolumen){sounds[7].play();}
            terminar = false;
            atras = false;
            actualizar.restart();
            tiempoparafin.restart();
            color = 0; //color de los sprites
            iaMode = 0;
            pulsada = 0;
            posicionMenuOpciones = 0;
            while (app.isOpen() && !terminar) {
                Event e;
                while (app.pollEvent(e)) {
                    if (e.type == Event::Closed) {
                        app.close();
                    }
                    elegirTeamNano(teamNano, terminar, atras, e);
                    
                }


                if (e.type == sf::Event::Resized) {
                    sf::View view = app.getDefaultView();
                    view = getLetterboxView(view, e.size.width, e.size.height);
                    app.setView(view);
                }
                app.clear(Color(227, 187, 107));

                
                drawNano(app, color, teamNano, atras);

                if (terminar == true) {
                    if (atras == true) {
                        estado = 7;
                    }
                    else if (teamNano == 0) {//ferrari
                        int k = 0;
                        estado = 6;

                        for (int j = 0; j <= 11; j++) {
                            car.texCar[k].loadFromFile("sprites/coches/DroveCar/ferrari/tile" + std::to_string(j) + std::to_string(0) + ".png");
                            k++;
                            car.texCar[k].loadFromFile("sprites/coches/DroveCar/ferrari/tile" + std::to_string(j) + std::to_string(1) + ".png");
                            k++;
                        }
                    }
                    else if (teamNano == 1) {//alpine
                        int k = 0;
                        estado = 6;

                        for (int j = 0; j <= 11; j++) {
                            car.texCar[k].loadFromFile("sprites/coches/DroveCar/alpine/tile" + std::to_string(j) + std::to_string(0) + ".png");
                            k++;
                            car.texCar[k].loadFromFile("sprites/coches/DroveCar/alpine/tile" + std::to_string(j) + std::to_string(1) + ".png");
                            k++;
                        }

                    }
                    else if (teamNano == 2) {//mclaren
                        int k = 0;
                        estado = 6;

                        for (int j = 0; j <= 11; j++) {
                            car.texCar[k].loadFromFile("sprites/coches/DroveCar/mclaren/tile" + std::to_string(j) + std::to_string(0) + ".png");
                            k++;
                            car.texCar[k].loadFromFile("sprites/coches/DroveCar/mclaren/tile" + std::to_string(j) + std::to_string(1) + ".png");
                            k++;
                        }

                    }
                    else {//renault
                        int k = 0;
                        estado = 6;

                        for (int j = 0; j <= 11; j++) {
                            car.texCar[k].loadFromFile("sprites/coches/DroveCar/renault/tile" + std::to_string(j) + std::to_string(0) + ".png");
                            k++;
                            car.texCar[k].loadFromFile("sprites/coches/DroveCar/renault/tile" + std::to_string(j) + std::to_string(1) + ".png");
                            k++;
                        }
                    }

                }


                app.display();
            }


            break;
        case 10: //elegir volumen
            if(!posicionMenuvolumen){sounds[7].play();}
            terminar = false;
            atras = false;
            actualizar.restart();
            tiempoparafin.restart();
            color = 0; //color de los sprites
            iaMode = 0;
            pulsada = 0;
            posicionMenuvolumen = 0;
            while (app.isOpen() && !terminar) {
                Event e;
                while (app.pollEvent(e)) {
                    if (e.type == Event::Closed)
                        app.close();
                    elegirVolumen(posicionMenuvolumen, terminar, e, atras);
                }


                if (e.type == sf::Event::Resized) {
                    sf::View view = app.getDefaultView();
                    view = getLetterboxView(view, e.size.width, e.size.height);
                    app.setView(view);
                }
                app.clear(Color(227, 187, 107));

                drawVol(app, color, posicionMenuvolumen, atras);

                if (terminar == true) {
                    if (atras == true) {
                        estado = 7;
                    }
                    estado = 7;
                }


                app.display();
            }


            break;
        default:
            break;


        }
        cout << endl;
    }


    return 0;
}