#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace sf;

int width = 1024;
int height = 768;
int roadW = 2000;
int segL = 200;    // segment length
float camD = 0.84; // camera depth
float draw_distance = 300; // empiezan a aparecer en pantalla en el 8
int car_width = 56;
int car_height = 33;
float off_road_allowed = 300;
float turn_power = 0.1;
float draft_power = 0.02;

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
  Sprite sprite;

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
    app.draw(s);
  }
};

//Control sprite coche
struct carSprite{
  int car_status; //-1 atras 0 quieto 1 alante
  int car_dir; //-1 izq 0 recto 1 dcha
  int spriteN; //Numero de sprite (columna)[0-7]
  bool car_inv; //false normal, true invertido
  bool colision; //colision detectada
  Texture tex;
  IntRect rectSrcSprite; 
  Sprite sprite;
  Clock clock;

  void init(IntRect rect, Texture t){
    car_status = 0;
    car_dir = 0;
    spriteN = 0;
    car_inv = false;
    colision = false;
    rectSrcSprite = rect;
    tex = t;
    sprite.setTexture(tex);
    sprite.setTextureRect(rectSrcSprite);
    sprite.setPosition(width/2-car_width*1.5,600);
    sprite.setScale(3,3);
  }
  void updateCarSprite(){
    float vel_refresco;
    if(car_status == 0)
      vel_refresco = 1.0f;
    else
      vel_refresco = 0.3f;
    if(clock.getElapsedTime().asSeconds() > 0.3f){
      if(colision){
        if(rectSrcSprite.top < 3*car_height){
          car_width = 61;
          rectSrcSprite = IntRect(0,3*car_height, car_width, car_height);
          spriteN = 0;
        }
        else if(spriteN < 2){
          rectSrcSprite.left += 3+car_width;
          spriteN++;
        }
        else if(spriteN == 2){
          rectSrcSprite.left += 5+car_width;
          spriteN++;
        }
        else if(spriteN == 3){
          rectSrcSprite.left += car_width;
          car_width = 54;
          rectSrcSprite.width = car_width;
          spriteN++;
        }
        else if(spriteN == 4){
          rectSrcSprite.left += car_width;
          spriteN++;
        }else if(spriteN == 5){
          rectSrcSprite.left += car_width;
          car_width = 58;
          rectSrcSprite.width = car_width;
          spriteN++;
        }else if(spriteN == 6){
          rectSrcSprite.left += car_width;
          car_width = 68;
          rectSrcSprite.width = car_width;
          spriteN++;
        }
        /*else{
          car_width = 61;
          rectSrcSprite.width = car_width;
          rectSrcSprite.left = 0;
          spriteN = 0;
        }*/
      }
      else{
        if(car_status == 0){
          //Quieto
          if(car_dir == 1){
            //Movimiento dcha
            if(car_inv){
              //Recuperando direccion del coche
              if(rectSrcSprite.left == car_width){
                car_inv = false;
                rectSrcSprite.left -= rectSrcSprite.width;
                rectSrcSprite.width = -rectSrcSprite.width;
              }
              else
                rectSrcSprite.left -= car_width;
            }else{
              //Giro a dcha
              if(rectSrcSprite.left < 7*car_width)
                rectSrcSprite.left += car_width;
            }
          }
          if(car_dir == -1){
            //Movimiento a izq
            if(!car_inv){
              //Recuperando direccion del coche
              if(rectSrcSprite.left == 0){
                car_inv = true;
                rectSrcSprite.left += car_width;
                rectSrcSprite.width = -rectSrcSprite.width;
              }
              else
                rectSrcSprite.left -= car_width; 
            }else{
              //Giro a izq
              if(rectSrcSprite.left < 7*car_width)
              rectSrcSprite.left += car_width;
            }
          }
        }
        if(car_status == 1){
          //Acelerando
          if(car_dir == 0){
            //Movimiento recto
            if(rectSrcSprite.left >= car_width){
              if(car_inv){
                //Recuperando direccion del coche
                if(rectSrcSprite.left == car_width){
                car_inv = false;
                rectSrcSprite.left -= rectSrcSprite.width;
                rectSrcSprite.width = -rectSrcSprite.width;
                }
              }
              rectSrcSprite.left -= car_width;
            }
            else
              rectSrcSprite.left += car_width;
          }
          if(car_dir == 1){
            //Movimiento dcha
            if(car_inv){
              //Recuperando direccion del coche
             if(rectSrcSprite.left == car_width){
                car_inv = false;
                rectSrcSprite.left -= rectSrcSprite.width;
                rectSrcSprite.width = -rectSrcSprite.width;
              }
              else
                rectSrcSprite.left -= car_width;
            }else{
              if(rectSrcSprite.left < 7*car_width)
                rectSrcSprite.left += car_width;
              else
                rectSrcSprite.left = 6*car_width;
            } 
          }
          if(car_dir == -1){
            //Movimiento a izq
            if(!car_inv){
              //Recuperando direccion del coche
              if(rectSrcSprite.left == 0){
                car_inv = true;
                rectSrcSprite.left += rectSrcSprite.width;
                rectSrcSprite.width = -rectSrcSprite.width;
              }
              else
                rectSrcSprite.left -= car_width;
            }else{
              if(rectSrcSprite.left < 8*car_width)
                rectSrcSprite.left += car_width;
              else
                rectSrcSprite.left = 7*car_width;
            }
            
          }
        }
      }
      clock.restart();
      sprite.setTextureRect(rectSrcSprite);
    }
  }
};


/*------------------------------- FUNCIONES DE CONTROL DEL BUCLE PRINCIPAL -------------------------------*/
void manageKeys(float &playerX, int &speed, int &H, carSprite &car){
  car.car_status = 0;
  car.car_dir = 0;
  if (Keyboard::isKeyPressed(Keyboard::Right) && ((playerX * roadW) < (roadW + off_road_allowed)) && (((playerX + turn_power) * roadW) < (roadW + off_road_allowed))){
    playerX += turn_power;
    car.car_dir = 1;
  }
  if (Keyboard::isKeyPressed(Keyboard::Left) && ((playerX * roadW) > (-roadW-off_road_allowed)) && (((playerX - turn_power) * roadW) > (-roadW-off_road_allowed))){
    playerX -= turn_power;
    car.car_dir = -1;
  }
    if (Keyboard::isKeyPressed(Keyboard::Up)){
    speed = 200;
    car.car_status = 1;
  }
  if (Keyboard::isKeyPressed(Keyboard::Down)){
    speed = -200;
    car.car_status = -1;
  }
  if (Keyboard::isKeyPressed(Keyboard::Tab)){
    speed *= 3;
  }
  if (Keyboard::isKeyPressed(Keyboard::W))
    H += 100;
  if (Keyboard::isKeyPressed(Keyboard::S))
    H -= 100;
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

void drawObjects(RenderWindow& app, int &startPos, std::vector<Line>& lines, int &N, carSprite &car){
  ////////draw objects////////
  for (int n = startPos + draw_distance; n > startPos; n--)
    lines[n % N].drawSprite(app);

  //actualizar sprite
  car.updateCarSprite();
  app.draw(car.sprite);
}

/*------------------------------- FIN FUNCIONES DE CONTROL DEL BUCLE PRINCIPAL -------------------------------*/

int main() {
  RenderWindow app(VideoMode(width, height), "Pole Position");
  app.setFramerateLimit(60);

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

    int speed = 0;

    manageKeys(playerX, speed, H, car);

    

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
