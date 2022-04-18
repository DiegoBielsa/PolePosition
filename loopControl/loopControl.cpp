#include "loopControl.hpp"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace sf;

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
  }else if(charco){
    speed = 50;
    charco = false;
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
          if(speed < 200){
            speed += 2;
          }else if(speed > 200){
            speed -= 8;
          }
        }else{//marcha alta
          if(speed < 200){
            speed += 1;
          }else if(speed < maxSpeed){
            speed += 3;
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
        speed-=5;
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

void updateVars(RenderWindow& app, int &pos, int &startPos, int &camH, std::vector<Line>& lines, float &playerX , int &maxy, float& x, float& dx, int& speed, int N, int H, Sprite sBackground){
  pos += speed;
  while (pos >= N * segL)
    pos -= N * segL;
  while (pos < 0)
    pos += N * segL;

  app.clear(Color(105, 205, 4));
  app.draw(sBackground);
  startPos = pos / segL;
  camH = lines[startPos].y + H;
  if (speed != 0){
    float actual_draft_power = draft_power * floatAbs(lines[startPos].curve);
    if (((playerX * roadW) < (roadW + off_road_allowed)) && ((playerX * roadW) > (-roadW-off_road_allowed))
      && !Keyboard::isKeyPressed(Keyboard::Right) && !Keyboard::isKeyPressed(Keyboard::Left)){
      if(lines[startPos].curve > 0 && (((playerX - actual_draft_power) * roadW) > (-roadW-off_road_allowed))){
        playerX -= actual_draft_power;
      }
      if(lines[startPos].curve < 0 && (((playerX + actual_draft_power) * roadW) < (roadW + off_road_allowed))){
        playerX += actual_draft_power;
      }
    }
  }
  if (speed > 0)
    sBackground.move(-lines[startPos].curve * 2, 0);
  if (speed < 0)
    sBackground.move(lines[startPos].curve * 2, 0);

  maxy = height;
  x = 0, dx = 0;

  if (startPos == 3500){//será goalposend
    gameOver = true;
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
    Color grass = (n / 3) % 2 ? Color(16, 200, 16) : Color(0, 154, 0);;
    if(mapa == 1){
      grass = (n / 3) % 2 ? Color(16, 200, 16) : Color(0, 154, 0);
    }
    //Color grass = (n / 3) % 2 ? Color(16, 200, 16) : Color(0, 154, 0);

    Color rumble = (n / 3) % 2 ? Color(255, 255, 255) : Color(255, 0, 0);
    Color road = (n / 3) % 2 ? Color(107, 107, 107) : Color(105, 105, 105);
    Color whiteLine = (n / 3) % 4 ? Color(107, 107, 107) : Color(255, 255, 255);
    Color white = Color(255, 255, 255);

    // pilla la anterior que es la que ha modificado en la iteración anterior para diujar lo que hay puesto
    Line p = lines[(n - 1) % N]; // previous line

    // dibuja las lineas
    drawQuad(app, grass, 0, p.Y, width, 0, l.Y, width);
    drawQuad(app, rumble, p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W * 1.2);
    drawQuad(app, road, p.X, p.Y, p.W, l.X, l.Y, l.W);
    drawQuad(app, white, p.X, p.Y, p.W*0.93, l.X, l.Y, l.W*0.93);
    drawQuad(app, road, p.X, p.Y, p.W*0.9, l.X, l.Y, l.W*0.9);
    drawQuad(app, whiteLine, p.X, p.Y, p.W * 0.05, l.X, l.Y, l.W * 0.05);

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
  }else if(lines[(startPos+10)%N].sprite_type == 0){
    car.colision = true;
    perderControl = true;
  }else if(lines[(startPos+10)%N].sprite_type == 2){//meta
    app.draw(car.sprite);
  }else if(lines[(startPos+10)%N].sprite_type == 3){//charco
    charco = true;
    app.draw(car.sprite);
  }
}

void drawGear(RenderWindow& app, bool marcha_baja, Texture& marcha) {
    if (marchaBaja == true) {
        marcha.loadFromFile("images/marcha_baja.png");

    }
    else {
        marcha.loadFromFile("images/marcha_alta.png");

    }
    Sprite march(marcha);
    march.setPosition(width - 80, height - 200);
    app.draw(march);

}
void comprobarMeta(int& startPos, float& goalPosIni, bool& metacruz) {
    if ( startPos == goalPosIni) {
        metacruz = true;

    }
    else {
        metacruz = false;

    }
}