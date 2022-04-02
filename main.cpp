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



/*------------------------------- FIN FUNCIONES DE CONTROL DEL BUCLE PRINCIPAL -------------------------------*/

int main() {
  //INICIALIZANDO EL JUEGO
  setConfig();
  RenderWindow app(VideoMode(width, height), "Pole Position");
  app.setKeyRepeatEnabled(false);
  app.setFramerateLimit(60);
  keyState.fill(false);

  Clock clock;

  String puntuaciones[7];
  leerPuntuaciones(puntuaciones);
  int limite = 0;

  leerLimite(limite, 0);

  Texture t[50];
  Sprite object[50];
  Texture ca;
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

  setMaps(maps, object);

  // eleccion del mapa
  lines = maps[0];
  

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

    
    int startPos, camH, maxy;
    float x, dx;
    updateVars(app, pos, startPos, camH, lines, playerX, maxy, x, dx, speed, N, H, sBackground);
    
    sf::Time elapsed = clock.getElapsedTime();
    //clock.restart() cuando hagamos vuelta

  

    drawRoad(app, startPos, playerX, lines, N, x, dx, maxy, camH);
    drawObjects(app, startPos, lines, N, car);
    drawLetters(app, puntuaciones, speed, elapsed, limite,gameOver);

    if (gameOver == true) {
        drawGameOver(app);
    }

    app.display();
    
  }

  return 0;
}
