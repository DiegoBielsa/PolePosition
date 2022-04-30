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

#define charco 0
#define spriteColision 1


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
int animColision = 0;


Time tiempoconseguido;
bool ultimotiempo = false;
int score = 0;

int mapa; //mapa a elegir

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
  leerPuntuaciones(puntuaciones);
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
  for(int i=0; i <6 ; i++){
    t[i+9].loadFromFile("sprites/entorno/cartel"+std::to_string(i+1)+".png");
    t[i+9].setSmooth(true);
    object[i+9].setTexture(t[i+9]);
  }



  Texture bg;
  bg.loadFromFile("images/bg.png");
  bg.setRepeated(true);
  Sprite sBackground(bg);
  sBackground.setTextureRect(IntRect(0, 0, 5000, 411));
  sBackground.setPosition(-2000, 0);

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

  sounds[5].setPitch(3.0f);
  sounds[5].setLoop(true);
  sounds[5].play();



  setMaps(maps, object);

  // eleccion del mapa
  lines = maps[mapa];

  //sounds[0].play();


  int N = lines.size();
  float playerX = 0;
  int pos = 0;
  int H = 1500;

  while (app.isOpen()) {
    Event e;
    while (app.pollEvent(e)) {
      if (e.type == Event::Closed)
        app.close();
    }


    if (e.type == sf::Event::Resized){
      sf::View view = app.getDefaultView();
      view = getLetterboxView( view, e.size.width, e.size.height );
      app.setView(view);
    }

    if (e.type == sf::Event::KeyPressed) {
      if (e.key.code == sf::Keyboard::LControl && !keyState[e.key.code]) {
        marchaBaja = !marchaBaja;
      }
      keyState[e.key.code] = true;

    } else if (e.type == sf::Event::KeyReleased) {
      // Update state of current key:
      keyState[e.key.code] = false;
    }
    manageKeys(playerX, speed, H, car);
    
    
    updateSound(speed,sounds);
    
    int startPos, camH, maxy;
    float x, dx;
    updateVars(app, pos, startPos,camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground);
    
    sf::Time elapsed = clock.getElapsedTime();
    bool metacruz = false;
    comprobarMeta(startPos,goalPosIni,metacruz);
    if (metacruz == true) {
        clock.restart();  //cuando hagamos vuelta
        elapsed= clock.getElapsedTime();
        lim = limite;
    }
    calcularScore(score,speed,lim,limite,gameOver);


    drawRoad(app, startPos, playerX, lines, N, x, dx, maxy, camH);
    drawObjects(app, startPos, lines, N, car, sounds);
    drawLetters(app, puntuaciones, speed,score ,elapsed, lim,gameOver);
    //std::cout<<startPos<<std::endl;
    if(startPos >= 3500 && startPos <= 3550){
      gameOver = true;
    }
    drawGear(app, marchaBaja, marcha);

    if(speed < 0) speed = 0;


    
    if (gameOver == true) {
        drawGameOver(app);
    }


    if (gameOver == true && restart == false) {
        tiempoparafin.restart();
        escribirPuntuaciones(puntuaciones, score);
        restart = true;
    }
    else if (gameOver == true && restart == true) {
        if (tiempoparafin.getElapsedTime().asSeconds() > 10) {//esperamos 10 segundos para terminar
             app.clear(Color(0, 0, 180));

            drawRanking(app,puntuaciones,lim,score);

        }
    }

    app.display();

    
  }

  return 0;
}
