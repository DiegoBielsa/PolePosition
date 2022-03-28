#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>
#include "RectangularBoundaryCollision.hpp"

using namespace sf;

#define charco 0
#define spriteColisión 1

int width = 1024;
int height = 768;
int roadW = 2000;
int segL = 200;    // segment length
float camD = 0.84; // camera depth
float draw_distance = 300; // empiezan a aparecer en pantalla en el 8
int car_width = 56;
int car_height = 50;
float off_road_allowed = 700;
float road_limit = 700;
float turn_power = 0.1;
float draft_power = 0.02;
int speed = 0;
bool marchaBaja = true;
bool pressed = false;
int maxSpeed = 600;
bool enHierba = false;
std::array<bool, sf::Keyboard::KeyCount> keyState;

void drawQuad(RenderWindow &w, Color c, int x1, int y1, int w1, int x2, int y2,
              int w2) {
  ConvexShape shape(4);
  shape.setFillColor(c);
  shape.setPoint(0, Vector2f(x1 - w1, y1));
  shape.setPoint(1, Vector2f(x2 - w2, y2));
  shape.setPoint(2, Vector2f(x2 + w2, y2));
  shape.setPoint(3, Vector2f(x1 + w1, y1));
  w.draw(shape);
}

struct Line {
  float x, y, z; // 3d center of line
  float X, Y, W; // screen coord
  float curve, spriteX, clip, scale;
  FloatRect localBounds;
  Sprite sprite;
  int sprite_type;

  Line() { spriteX = curve = x = y = z = 0; }

  // decide las screen cord dependiendo de dónde está la cámara
  void project(int camX, int camY, int camZ) {
    scale = camD / (z - camZ);
    X = (1 + scale * (x - camX)) * width / 2;
    Y = (1 - scale * (y - camY)) * height / 2;
    W = scale * roadW * width / 2;
  }

  void drawSprite(RenderWindow &app) {
    Sprite s = sprite;
    int w = s.getTextureRect().width;
    int h = s.getTextureRect().height;

    float destX = X + scale * spriteX * width / 2;
    float destY = Y + 4;
    float destW = w * W / 266;
    float destH = h * W / 266;

    destX += destW * spriteX; // offsetX
    destY += destH * (-1);    // offsetY

    float clipH = destY + destH - clip;
    if (clipH < 0)
      clipH = 0;

    if (clipH >= destH)
      return;
    s.setTextureRect(IntRect(0, 0, w, h - h * clipH / destH));
    s.setScale(destW / w, destH / h);
    s.setPosition(destX, destY);
    
    localBounds = s.getGlobalBounds();
    
    //std::cout<<destX<<destY<<std::endl;
    app.draw(s);
  }
};


/*------------------------------- FUNCIONES DE CONTROL DEL BUCLE PRINCIPAL -------------------------------*/
void manageKeys(float &playerX, int &speed, int &H){
  if(((playerX * roadW) > (roadW + road_limit)) || ((playerX * roadW) < (-roadW-road_limit)) || (((playerX + turn_power) * roadW) > (roadW + road_limit)) || (((playerX - turn_power) * roadW) < (-roadW-road_limit)))
  {
    enHierba = true;
  }else{
    enHierba = false;
  }
  if (Keyboard::isKeyPressed(Keyboard::Right) && ((playerX * roadW) < (roadW + off_road_allowed)) && (((playerX + turn_power) * roadW) < (roadW + off_road_allowed)))
    if(speed>0){
      playerX += turn_power * ((float(speed)/maxSpeed));
    }
  if (Keyboard::isKeyPressed(Keyboard::Left) && ((playerX * roadW) > (-roadW-off_road_allowed)) && (((playerX - turn_power) * roadW) > (-roadW-off_road_allowed)))
    if(speed > 0){
      playerX -= turn_power * ((float(speed)/maxSpeed));
    }
  if (Keyboard::isKeyPressed(Keyboard::Up)){
    if(!enHierba){
      if(marchaBaja){
        if(speed < 100){
          speed += 10;
        }else if(speed < 300){
          speed += 20;
        }else{
          speed=300;
        }
      }else{//marcha alta
        if(speed < 300){
          speed += 5;
        }else if(speed < maxSpeed){
          speed += 30;
        }
      }
    }else{
      if (speed > 100) {
        speed -= 20;
      }else{
        speed += 5;
      }
    }
  }else{
    if(speed>0){
      speed-=10;
    }
  }
  
    
    
  if (Keyboard::isKeyPressed(Keyboard::Down)){
    if (speed > 10) {
      speed -= 20;
    }else if(speed == 10){
      speed = 0;
    }
  }
    
  
  /*if (Keyboard::isKeyPressed(Keyboard::W))
    H += 100;
  if (Keyboard::isKeyPressed(Keyboard::S))
    H -= 100;
*/
}

/**
 * @brief 
 * 
 * @param app       Pantalla en sí
 * @param startPos  Posición en la que se encuentra el coche dentro de la carretera  
 * @param playerX   Posición del jugador respecto al eje X
 * @param lines     Representación de la carretera
 * @param N         Número de lines (componenetes que representan el mapa)
 * @param x         anterior dx
 * @param dx        pronunciación de la curva
 * @param maxy      
 * @param camH      Altura de la cámara
 */
void drawRoad(RenderWindow& app, int& startPos, float& playerX, std::vector<Line>& lines, int& N, float& x, float& dx, int& maxy, int& camH){
  ///////draw road////////
  for (int n = startPos; n < startPos + draw_distance; n++) {
    Line &l = lines[n % N];

    // decidimos donde está la cámara y las coor de la pantalla que va a sacar
    l.project(playerX * roadW - x, camH,
              startPos * segL - (n >= N ? N * segL : 0));

   
    x += dx;
    dx += l.curve;
    


    // establece dónde esta el Y más alto de la carretera
    l.clip = maxy;
    if (l.Y >= maxy)
      continue;
    maxy = l.Y;

    // elige el color y da esa sensación de lineas
    Color grass = (n / 3) % 2 ? Color(16, 200, 16) : Color(0, 154, 0);
    Color rumble = (n / 3) % 2 ? Color(255, 255, 255) : Color(0, 0, 0);
    Color road = (n / 3) % 2 ? Color(107, 107, 107) : Color(105, 105, 105);

    // pilla la anterior que es la que ha modificado en la iteración anterior para diujar lo que hay puesto
    Line p = lines[(n - 1) % N]; // previous line

    // dibuja las lineas
    drawQuad(app, grass, 0, p.Y, width, 0, l.Y, width);
    drawQuad(app, rumble, p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W * 1.2);
    drawQuad(app, road, p.X, p.Y, p.W, l.X, l.Y, l.W);
  } 

}

void drawObjects(RenderWindow& app, int &startPos, std::vector<Line>& lines, int &N, Sprite &car){
  ////////draw objects////////
  for (int n = startPos + draw_distance; n > startPos; n--)
    lines[n % N].drawSprite(app);

  Texture exp;
  exp.loadFromFile("sprites/coches/tile207.png");
  Sprite expl(exp);
  expl.setTextureRect(IntRect(0, 0, car_width, car_height));
  expl.setPosition(width/2-car_width*1.5,600);
  expl.setScale(3,3);
  //std::cout<<"car: "<<car.getPosition().x<<std::endl;
  //std::cout<<"spr: "<<lines[(startPos+10)%N].localBounds.height<<std::endl;

  const bool areColliding{ collision::areColliding(lines[(startPos+10)%N].sprite, car )}; // this is the collision detection section
  if(!car.getGlobalBounds().intersects(lines[(startPos+10)%N].localBounds)){//no choca
    app.draw(car);
  }else{
    app.draw(expl);
  }
}

// in = ( scenew, sceneh ); clip = ( windoww, windowh )
sf::Vector2f scaleToFit( const sf::Vector2f& in, const sf::Vector2f& clip )
{
        sf::Vector2f ret( in );
        if ( ( clip.y * in.x ) / in.y >= clip.x )
        {
                ret.y = ( clip.x * in.y ) / in.x;
                ret.x = clip.x;
        }
        else if ( ( clip.x * in.y ) / in.x >= clip.y )
        {
                ret.x = ( clip.y * in.x ) / in.y;
                ret.y = clip.y;
        }
        else
                ret = clip;
        return ret;
}

/*------------------------------- FIN FUNCIONES DE CONTROL DEL BUCLE PRINCIPAL -------------------------------*/

int main() {
  RenderWindow app(VideoMode(width, height), "Pole Position");
  app.setKeyRepeatEnabled(false);
  app.setFramerateLimit(60);
  keyState.fill(false);


  Texture t[50];
  Sprite object[50];
  Texture ca;
  ca.loadFromFile("sprites/coches/tile300.png");
  Sprite car(ca);
  car.setTextureRect(IntRect(0, 0, car_width, car_height));
  car.setPosition(width/2-car_width*1.5,600);
  car.setScale(3,3);
  for (int i = 1; i <= 7; i++) {
    t[i].loadFromFile("images/" + std::to_string(i) + ".png");
    t[i].setSmooth(true);
    object[i].setTexture(t[i]);
  }

  Texture bg;
  bg.loadFromFile("images/bg.png");
  bg.setRepeated(true);
  Sprite sBackground(bg);
  sBackground.setTextureRect(IntRect(0, 0, 5000, 411));
  sBackground.setPosition(-2000, 0);

  std::vector<Line> lines; // esto es el mapa, 

  for (int i = 0; i < 1600; i++) {
    Line line;
    line.z = i * segL;

    if (i > 300 && i < 700)
      line.curve = 0.5;
    if (i > 1100)
      line.curve = -0.7;

    if (i < 300 && i % 20 == 0) {
      line.spriteX = -2.5;
      line.sprite = object[5];
    }
    if (i % 17 == 0) {
      line.spriteX = 2.0;
      line.sprite = object[6];
    }
    if (i > 300 && i % 20 == 0) {
      line.spriteX = -0.7;
      line.sprite = object[4];
    }
    if (i > 800 && i % 20 == 0) {
      line.spriteX = -1.2;
      line.sprite = object[1];
    }
    if (i == 400) {
      line.spriteX = -1.2;
      line.sprite = object[7];
    }

    if (i > 750)
      line.y = std::sin(i / 30.0) * 1500;

    lines.push_back(line);
  }

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

    // catch the resize events
    if (e.type == sf::Event::Resized)
    {
      sf::View v( sf::FloatRect( 0, 0, (float)e.size.width, (float)e.size.height ) );
      sf::FloatRect viewport( sf::Vector2f( 0, 0 ), scaleToFit( sf::Vector2f( (float)e.size.width, (float)e.size.height ), sf::Vector2f( (float)e.size.width, (float)e.size.height ) ) );
      viewport.width  = viewport.width  / width;
      viewport.height = viewport.height / height;
      viewport.left = ( 1.0 - viewport.width  ) * 0.5;
      viewport.top  = ( 1.0 - viewport.height ) * 0.5;
      v.setViewport( viewport );
      app.setView( v );
        // update the view to the new size of the window
        //sf::FloatRect visibleArea(0, 0, e.size.width, e.size.width*(4/3));
            //app.setView(sf::View(app.getView().getCenter(), sf::Vector2f((float)e.size.width, (float)e.size.height)));
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
    manageKeys(playerX, speed, H);

    

    pos += speed;
    while (pos >= N * segL)
      pos -= N * segL;
    while (pos < 0)
      pos += N * segL;

    app.clear(Color(105, 205, 4));
    app.draw(sBackground);
    int startPos = pos / segL;
    int camH = lines[startPos].y + H;
    if (speed != 0){
      if (((playerX * roadW) < (roadW + off_road_allowed)) && ((playerX * roadW) > (-roadW-off_road_allowed))
        && !Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left)){
        if(lines[startPos].curve > 0 && (((playerX - draft_power) * roadW) > (-roadW-off_road_allowed))){
          playerX -= draft_power;
        }
        if(lines[startPos].curve < 0 && (((playerX + draft_power) * roadW) < (roadW + off_road_allowed))){
          playerX += draft_power;
        }
      }
    }
    if (speed > 0)
      sBackground.move(-lines[startPos].curve * 2, 0);
    if (speed < 0)
      sBackground.move(lines[startPos].curve * 2, 0);

    int maxy = height;
    float x = 0, dx = 0;

    drawRoad(app, startPos, playerX, lines, N, x, dx, maxy, camH);
    drawObjects(app, startPos, lines, N, car);

    app.display();
    
  }

  return 0;
}
