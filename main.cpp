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

using namespace sf;
using namespace std;

#define charco 0
#define spriteColision 1


int width = 1024;
int height = 768;
int roadW = 2000;
int segL = 200;    // segment length
float camD = 0.84; // camera depth
float draw_distance = 300; // empiezan a aparecer en pantalla en el 8
int car_width = 56;
int car_height = 33;
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
int numMaps = 5;
bool gameOver = false;
bool perderControl = false;
int animColision = 0;

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
  void reinit(){
    car_width = 56;
    car_height = 33;
    car_status = 0;
    car_dir = 0;
    spriteN = 0;
    car_inv = false;
    colision = false;
    rectSrcSprite = IntRect(0, 0, car_width, car_height);
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
    if(clock.getElapsedTime().asSeconds() > 0.03f){
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
  if(perderControl){
    speed = 50;
    animColision++;
    if(animColision == 150){
      //ponerlo en el medio
      perderControl = false;
      animColision = 0;
      car.reinit();
    }
  }else{
    if(((playerX * roadW) > (roadW + road_limit)) || ((playerX * roadW) < (-roadW-road_limit)) || (((playerX + turn_power) * roadW) > (roadW + road_limit)) || (((playerX - turn_power) * roadW) < (-roadW-road_limit)))
    {
      enHierba = true;
    }else{
      enHierba = false;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && ((playerX * roadW) < (roadW + off_road_allowed)) && (((playerX + turn_power) * roadW) < (roadW + off_road_allowed))){
      if(speed>0){
        playerX += turn_power * ((float(speed)/maxSpeed));
      }
      car.car_dir = 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) && ((playerX * roadW) > (-roadW-off_road_allowed)) && (((playerX - turn_power) * roadW) > (-roadW-off_road_allowed))){
      if(speed > 0){
        playerX -= turn_power * ((float(speed)/maxSpeed));
      }
      car.car_dir = -1;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)){
      car.car_status = 1;
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
      if(speed == 5){
        speed = 0;
      }else if(speed>0){
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
  }
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

  //std::cout<<"car: "<<car.getPosition().x<<std::endl;
  //std::cout<<"spr: "<<lines[(startPos+10)%N].localBounds.height<<std::endl;

  car.updateCarSprite();
  if(!car.sprite.getGlobalBounds().intersects(lines[(startPos+10)%N].localBounds)){//no choca
      //actualizar sprite
    
    app.draw(car.sprite);
  }else{
    car.colision = true;
    perderControl = true;
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

// in = ( scenew, sceneh ); clip = ( windoww, windowh )



void leerPuntuaciones(String puntuaciones[]) {

    fstream f;
    f.open("puntuaciones.txt");
    if (f.is_open()) {
        int i = 0;
        string cadena;
        getline(f, cadena, '\n');
        puntuaciones[i] = cadena;
        i++;
        while (!f.eof() || i < 7) {
            getline(f, cadena, '\n');
            puntuaciones[i] = cadena;
            i++;
        }
        if (i < 7) {
            while (i < 7) {
                puntuaciones[i] = "0";
                i++;
                f << "0000" << endl;
            }
        }

        f.close();

    }
    else {
        cerr << "no se ha podido abrir fichero puntuaciones" << endl;
    }

}


String inttostring(int entero) {
    stringstream ss;
    ss << entero;
    string s;
    ss >> s;
    return s;
}

void leerLimite(int &limite, int numero) {

    fstream f;
    f.open("limites.txt");
    if (f.is_open()) {
        int i = 0;
        string cadena;
        getline(f, cadena, '\n');
        if (numero == i) {
            limite = stoi(cadena);
        }
        else {
            i++;
            while (!f.eof() || i < numMaps) {
                getline(f, cadena, '\n');
                if (i == numero) {
                    limite=stoi(cadena);
                    break;
                }
                i++;
            }
        }
        f.close();

    }
    else {
        cerr << "no se ha podido abrir fichero limites" << endl;
    }

}

void drawLetters(RenderWindow& app, String puntuaciones[], int velocidad, Time& elapsed, int &limite,bool &gameOver) {
    sf::Text top;
    sf::Text topnumber;
    sf::Text score;
    sf::Text scorenumber;
    sf::Text time;
    sf::Text timenumber;
    sf::Text lap;
    sf::Text lapnumber;
    sf::Text speed;
    sf::Text speednumber;


    sf::Font font;
    font.loadFromFile("letra.ttf");
    // select the font
    top.setFont(font); // font is a sf::Font
    topnumber.setFont(font);
    time.setFont(font);
    lap.setFont(font);
    lapnumber.setFont(font);
    score.setFont(font);
    scorenumber.setFont(font);
    timenumber.setFont(font);
    speed.setFont(font);
    speednumber.setFont(font);



    // set the string to display
    top.setString("TOP");


    topnumber.setString(puntuaciones[0]);
    time.setString("TIME");
    lap.setString("LAP");

    int seconds = elapsed.asSeconds();
    int mili = elapsed.asMilliseconds();
    while (mili > 1000) {
        mili = mili - 1000;
    }

    String minu = inttostring(mili);
    String sec = inttostring(seconds);
    lapnumber.setString(sec + "''" + minu);
    score.setString("SCORE");
    scorenumber.setString("0000");

    int resta = limite - seconds;
    if (resta >=0) {
        String lim = inttostring(resta);
        timenumber.setString(lim);
    }
    else {
        timenumber.setString("0");
        gameOver = true;
    }
    speed.setString("SPEED");
    String s = inttostring(velocidad);
    speednumber.setString(s + "km");
    //int width = 1024;
  //int height = 768;


    top.setPosition(55, 0);
    topnumber.setPosition(150, 0);
    time.setPosition(340, 0);
    lap.setPosition(700, 0);
    lapnumber.setPosition(850, 0);
    score.setPosition(10, 60);
    scorenumber.setPosition(150, 60);

    timenumber.setPosition(340, 60);
    speednumber.setPosition(870, 60);
    speed.setPosition(650, 60);



    // set the character size
    top.setCharacterSize(50); // in pixels, not points!
    topnumber.setCharacterSize(50);
    time.setCharacterSize(50);
    lap.setCharacterSize(50);
    lapnumber.setCharacterSize(50);
    score.setCharacterSize(50);
    scorenumber.setCharacterSize(50);
    timenumber.setCharacterSize(50);
    speed.setCharacterSize(50);
    speednumber.setCharacterSize(50);

    // set the color
    top.setFillColor(sf::Color::Red);
    topnumber.setFillColor(sf::Color::Red);
    time.setFillColor(sf::Color::Yellow);
    timenumber.setFillColor(sf::Color::Yellow);
    lap.setFillColor(sf::Color::Green);
    lapnumber.setFillColor(sf::Color::Green);

    score.setFillColor(sf::Color::White);
    scorenumber.setFillColor(sf::Color::White);
    speed.setFillColor(sf::Color::White);
    speednumber.setFillColor(sf::Color::White);
    // set the text style




        // inside the main loop, between window.clear() and window.display()
    app.draw(top);
    app.draw(topnumber);
    app.draw(time);
    app.draw(timenumber);
    app.draw(lap);
    app.draw(lapnumber);
    app.draw(score);
    app.draw(scorenumber);
    app.draw(speed);
    app.draw(speednumber);
}

void drawGameOver(RenderWindow& app) {
    sf::Text gameOvertext;
    sf::Font font;
    font.loadFromFile("letra.ttf");
    gameOvertext.setFont(font);
    gameOvertext.setString(" GAME OVER");
    gameOvertext.setPosition(300, 340);
    gameOvertext.setCharacterSize(80);
    gameOvertext.setFillColor(sf::Color::Magenta);
    app.draw(gameOvertext);
}
/*++++++++++++*/
sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight) {

    // Compares the aspect ratio of the window to the aspect ratio of the view,
    // and sets the view's viewport accordingly in order to archieve a letterbox effect.
    // A new view (with a new viewport set) is returned.

    float windowRatio = windowWidth / (float) windowHeight;
    float viewRatio = view.getSize().x / (float) view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;

    bool horizontalSpacing = true;
    if (windowRatio < viewRatio)
        horizontalSpacing = false;

    // If horizontalSpacing is true, the black bars will appear on the left and right side.
    // Otherwise, the black bars will appear on the top and bottom.

    if (horizontalSpacing) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    }

    else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }

    view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );

    return view;

}

/*------------------------------- FIN FUNCIONES DE CONTROL DEL BUCLE PRINCIPAL -------------------------------*/

int main() {
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

    /*if (i < 300 && i % 20 == 0) {
      line.spriteX = -2.5;
      line.sprite = object[5];
    }
    if (i % 17 == 0) {
      line.spriteX = 2.0;
      line.sprite = object[6];
    }*/
    if (i > 300 && i % 20 == 0) {
      if (i==320){
        line.spriteX = -0.7;
        line.sprite = object[4];
      }
    }
    /*if (i > 800 && i % 20 == 0) {
      line.spriteX = -1.2;
      line.sprite = object[1];
    }
    if (i == 400) {
      line.spriteX = -1.2;
      line.sprite = object[7];
    }*/

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
