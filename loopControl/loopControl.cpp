#include "loopControl.hpp"
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <random>

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

void manageKeys(float &playerX, int &speed, int &H, carSprite &car, std::vector<Line>& lines,  int &startPos,  std::vector<Sound>& sounds){
  static int n = 0;
  static int contadorDerrape = 0;
  static int dirDerrape = 0; // 0 derecha, 1 izquierda
  car.maxTex = car.maxTexNoKey;
  static int contadorDer;
  static int contadorIzq;
  if(speed == 0) car.car_status = 0;
  car.car_dir = 0;
  if(perderControl){
    contadorDerrape = 0;
    if(speed >= 100) speed -= 10;
    else if(speed - 1 > 0)speed -= 1;
    else speed = 0;
    animColision++;
    if(animColision == 150){
      //ponerlo en el medio
      perderControl = false;
      animColision = 0;
      car.reinit();
    }
  }else if(derrape){
    car.maxTex = 23;
    speed -= 3;
    float gone = 1.2 * turn_power * ((float(speed)/maxSpeed));
    if(dirDerrape == 0 && Keyboard::isKeyPressed(Keyboard::Left)){ //derrape a derechas pero tratamos de recuperar
      contadorDerrape += 1;
      car.maxTex = 17;
    }else if(dirDerrape == 1 && Keyboard::isKeyPressed(Keyboard::Right)){ //derrape a izquierdas pero tratamos de recuperar
      contadorDerrape += 1;
      car.maxTex = 17;
    }
    if(dirDerrape == 0 && ((playerX * roadW) > (-roadW-off_road_allowed)) && (((playerX - gone) * roadW) > (-roadW-off_road_allowed))){ // derrape a derechas
      playerX += gone;
      
      
    }else if(dirDerrape == 1 && ((playerX * roadW) > (-roadW-off_road_allowed)) && (((playerX - gone) * roadW) > (-roadW-off_road_allowed))){ // derrape a izquierdas
      playerX -= gone;
    }

    contadorDerrape++;
    if(contadorDerrape >= 80){ // paras de derrapar
      derrape = false;
      contadorDerrape = 0;
    }
  }else if(charco){
    contadorDerrape = 0;
    speed = 50;
    charco = false;
  }else{
    contadorDerrape = 0;
    if(((playerX * roadW) > (roadW + road_limit)) || ((playerX * roadW) < (-roadW-road_limit)) || (((playerX + turn_power) * roadW) > (roadW + road_limit)) || (((playerX - turn_power) * roadW) < (-roadW-road_limit)))
    {
      enHierba = true;
    }else{
      enHierba = false;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right) && ((playerX * roadW) < (roadW + off_road_allowed)) && (((playerX + turn_power) * roadW) < (roadW + off_road_allowed))){
      if(speed>0){
        car.maxTex = car.maxTexUsualTurn;
        if(!car.car_inv) playerX += turn_power * ((float(speed)/maxSpeed));
        if(speed > maxSpeed-150){
          float centripetal_force = ((float(speed)/float(maxSpeed))) * floatAbs(lines[startPos].curve);
          float actual_draft_power = draft_power * centripetal_force;
          if (actual_draft_power > 0.012){
            sounds[6].play();
            derrape = true;
            dirDerrape = 0;
            playerX += 1.5 * turn_power * ((float(speed)/maxSpeed));
            car.maxTex = 23;
          }else{
            playerX += turn_power * ((float(speed)/maxSpeed));
          }
          
        }else{
          playerX += turn_power * ((float(speed)/maxSpeed));
        }
        if(speed >= 20 && speed <= 50) contadorDer = 10;
        else if(speed > 50 && speed <= 100) contadorDer = 11;
        else if(speed > 100 && speed <= 150) contadorDer = 12;
        else if(speed > 150 && speed <= 200) contadorDer = 13;
        else if(speed > 200 && speed <= 250) contadorDer = 14;
        else if(speed > 250 && speed <= 300) contadorDer = 15;
        else if(speed > 300 && speed <= 380) contadorDer = 16;
        else if(speed > 380 && speed <= 440) contadorDer = 17;
        else if(speed > 440 && speed <= maxSpeed) contadorDer = 18;
      }
      car.car_dir = 1;
    }else{
      if (contadorDer > 0) {
        playerX += turn_power * sqrt((contadorDer) / (30*1.8));
        contadorDer--;
      }
      
    }
    if (Keyboard::isKeyPressed(Keyboard::Left) && ((playerX * roadW) > (-roadW-off_road_allowed)) && (((playerX - turn_power) * roadW) > (-roadW-off_road_allowed))){
      if(speed > 0){
        car.maxTex = car.maxTexUsualTurn;
        if(car.car_inv) playerX -= turn_power * ((float(speed)/maxSpeed));
        if(speed > maxSpeed-150){
          float centripetal_force = ((float(speed)/float(maxSpeed))) * floatAbs(lines[startPos].curve);
          float actual_draft_power = draft_power * centripetal_force;
          if (actual_draft_power > 0.012){
            sounds[6].play();
            derrape = true;
            dirDerrape = 1;
            playerX -= 1.5 * turn_power * ((float(speed)/maxSpeed));
            car.maxTex = 23;
          }else{
            playerX -= turn_power * ((float(speed)/maxSpeed));
          }
          
        }else{
          playerX -= turn_power * ((float(speed)/maxSpeed));
        }
        if(speed >= 20 && speed <= 50) contadorIzq = 10;
        else if(speed > 50 && speed <= 100) contadorIzq = 11;
        else if(speed > 100 && speed <= 150) contadorIzq = 12;
        else if(speed > 150 && speed <= 200) contadorIzq = 13;
        else if(speed > 200 && speed <= 250) contadorIzq = 14;
        else if(speed > 250 && speed <= 300) contadorIzq = 15;
        else if(speed > 300 && speed <= 380) contadorIzq = 16;
        else if(speed > 380 && speed <= 440) contadorIzq = 17;
        else if(speed > 440 && speed <= maxSpeed) contadorIzq = 18;
      }
      car.car_dir = -1;
    }else{
      if (contadorIzq > 0) {
        playerX -= turn_power * sqrt((contadorIzq) / (30*1.8));
        contadorIzq--;
      }
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)){
      car.car_status = 1;
      if(!enHierba){
        if(speed >= 0 && speed < 50){

          if(marchaBaja){
            speed+=2;
          }else{
            if(n%2 == 0){
              speed+=1;
            }
          }

        }else if(speed >= 50 && speed < 100){
          
          if(marchaBaja){
            speed+=3;
          }else{
            if(n%2 == 0){
              speed+=1;
            }
          }

        }else if(speed >= 100 && speed < 150){
          if(marchaBaja){
            speed+=4;
          }else{
            if(n%2 == 0){
              speed+=1;
            }
          }

        }else if(speed >= 150 && speed < mediumSpeed){
          if(marchaBaja){
            speed+=4;
          }else{
            speed+=1;
          }

        }else if(speed >= mediumSpeed && speed < 250){
          if(marchaBaja){
            if(n%5 == 0){
              speed+=2;
            }
          }else{
              speed+=1;
          }

        }else if(speed >= 250 && speed < 320){
          if(marchaBaja){
            if(n%5 == 0){
              speed+=1;
            }
          }else{
            if(n%2 == 0){
              speed+=1;
            }
          }

        }else if(speed >= 320 && speed < 430){
          if(marchaBaja){
            speed-=3;
          }else{
            if(n%3 == 0){
              speed+=1;
            }
          }

        }else if(speed >= 430 && speed < maxSpeed){
          if(marchaBaja){
            speed-=3;
          }else{
            if(n%10 == 0){
              speed+=1;
            }
          }

        }else if(speed >= maxSpeed){
          if(marchaBaja){
            speed-=3;
          }
        }
      }else{
        if (speed > 100) {
          if(speed-20 > 100){
            speed -= 20;
          }else{
            speed -= 1;
          }
        }else{
          speed += 1;
        }
      }
      
    }else{
      if(speed> 200){
        speed-=5;
      }else if(speed > 100){
        speed-=3;
      }else if(speed > 20){
        speed-=2;
      }else if(speed > 0){
        speed -=1;
      }else{
        speed = 0;
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
  n++;
}

void updateVars(RenderWindow& app, int &pos, int &startPos, int &camH, std::vector<Line>& lines, float &playerX , int &maxy, float& x, float& dx, int& speed, int N, int H, Sprite& sBackground, carSprite &car){
  pos += speed/2;
  while (pos >= N * segL)
    pos -= N * segL;
  while (pos < 0)
    pos += N * segL;
  
  if(car.colision && (lines[(startPos+20)%N].localBounds.intersects(car.sprite.getGlobalBounds()) || lines[(startPos+21)%N].localBounds.intersects(car.sprite.getGlobalBounds()))){
    pos += 2;
  }

  app.clear(Color(105, 205, 4));
  app.draw(sBackground);
  startPos = pos / segL;
  if(car.car_dir == 0 && lines[(startPos+20)%N].curve != 0){
    if(lines[(startPos+20)%N].curve > 0) car.car_dir = 1;
    else if(lines[(startPos+20)%N].curve < 0) {
      car.car_dir = -1;
    }
  }
  camH = lines[startPos].y + H;
  if (speed != 0 && !derrape){
    float varyng = 0;
    if(!car.colision){
      if(speed >= 0 && speed <= 50) {varyng = 0; car.updateTime = 0.04;}
      else if(speed > 50 && speed <= 100) {varyng = 0.2; car.updateTime = 0.037;}
      else if(speed > 100 && speed <= 150) {varyng = 0.4; car.updateTime = 0.033;}
      else if(speed > 150 && speed <= 200) {varyng = 0.6; car.updateTime = 0.03;}
      else if(speed > 200 && speed <= 250) {varyng = 0.8; car.updateTime = 0.027;}
      else if(speed > 250 && speed <= 300) {varyng = 0.9; car.updateTime = 0.024;}
      else if(speed > 300 && speed <= 380) {varyng = 1; car.updateTime = 0.02;}
      else if(speed > 380 && speed <= 440) {varyng = 1; car.updateTime = 0.02;}
      else if(speed > 440 && speed <= maxSpeed) {varyng = 1; car.updateTime = 0.02;}
    }
    float centripetal_force = ((speed/maxSpeed)+varyng) * floatAbs(lines[startPos].curve);//((speed * floatAbs(lines[startPos].curve)) / maxSpeed);
    float actual_draft_power = draft_power * centripetal_force;
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
    sBackground.move(-lines[startPos].curve * 0.2, 0);
  if (speed < 0)
    sBackground.move(lines[startPos].curve * 0.2, 0);

  maxy = height;
  x = 0, dx = 0;
  

  //if (startPos == 3500){//será goalposend
    //gameOver = true;
  //}
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
    if(mapa == 0){
      grass = (n / 3) % 2 ? Color(135, 86, 54) : Color(145, 96, 64);
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

void drawObjects(RenderWindow& app, int &startPos, std::vector<Line>& lines, int &N, carSprite &car, std::vector<Sound>& sounds){
  ////////draw objects//////// hay que hacer 2 bucles para que dibuje los coches siempre encima
  int upLimit = startPos + draw_distance -50;
  upLimit = upLimit%N;
  if(goalPosIni > startPos && goalPosIni < upLimit){ // si está la meta dibujamos antes los coches
    for (int n = startPos + draw_distance; n > startPos; n--){
      lines[n % N].drawSprite(app);
    }
    for (int n = startPos + draw_distance; n > startPos; n--){ 
      for(int i = 0; i < numCars; i++) lines[n % N].drawCars(app, i);
    }
  }else{ //si no dibujamos antes los carteles y demás
    for (int n = startPos + draw_distance; n > startPos; n--){ 
      for(int i = 0; i < numCars; i++) lines[n % N].drawCars(app, i);
    } 
    for (int n = startPos + draw_distance; n > startPos; n--){
      lines[n % N].drawSprite(app);
    }
    
  }
    
    


  car.updateCarSprite();
  
  bool colisiona = lines[(startPos+20)%N].localBounds.intersects(car.sprite.getGlobalBounds()) || lines[(startPos+21)%N].localBounds.intersects(car.sprite.getGlobalBounds());
  bool colisionaIa = lines[(startPos+20)%N].carLocalBounds.intersects(car.sprite.getGlobalBounds()) || lines[(startPos+21)%N].carLocalBounds.intersects(car.sprite.getGlobalBounds());

  int whocol=0;
  if(lines[(startPos+20)%N].localBounds.intersects(car.sprite.getGlobalBounds())){
    whocol = 0;
  }else if(lines[(startPos+21)%N].localBounds.intersects(car.sprite.getGlobalBounds())){
    whocol = 1;
  }
  //std::cout << lines[(startPos+20 + whocol)%N].sprite_type << std::endl;
  if(!colisiona && !colisionaIa){//no choca
      //actualizar sprite
    
    app.draw(car.sprite);
  }else if(colisionaIa){ // si da colision con ia miramos si de verdad hay un coche ahí
    derrape = false;
    app.draw(car.sprite);
    car.colision = true;
    perderControl = true;
    sf::SoundSource::Status status = sounds[1].getStatus();
    if(status != sf::Music::Playing){
      sounds[1].play();
    }

  }else if(colisiona){ // si colisiona con objeto getionamos
    if(lines[(startPos+20 + whocol)%N].sprite_type == 0){
      derrape = false;
      app.draw(car.sprite);
      car.colision = true;
      perderControl = true;
      sf::SoundSource::Status status = sounds[1].getStatus();
      if(status != sf::Music::Playing){
        sounds[1].play();
      }
      

    }else if(lines[(startPos+20 + whocol)%N].sprite_type == 2){//meta
      app.draw(car.sprite);
    }else if(lines[(startPos+20 + whocol)%N].sprite_type == 3){//charco
      derrape = false;
    //std::cout << "charco" << std::endl;
      charco = true;
      app.draw(car.sprite);
    }
  }else { //por si acaso mejor que no desaparezca
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
void comprobarMeta(int& startPos, float& goalPosIni, bool& metacruz,int vel) {
    if (vel > 50) {
        bool encontrado = false;
        int i = 0;
        while (!encontrado && i < 11) {
            if (startPos+i == goalPosIni && startPos+i <= goalPosIni) {
                metacruz = true;
                encontrado = true;
            }
            else {
                metacruz = false;


            }
            i++;
        }
    }
    else {
        if (startPos >= goalPosIni && startPos <= goalPosIni) {
            metacruz = true;

        }
        else {
            metacruz = false;

        }
    }
}


void IAeasy_control(std::vector<Line>& lines, int linePos[], float XPos[], carSpriteIA cars[], int numCars, int i){
  Clock clock;
  float speeds;
  float maxSpeeds;
  float drivingCarYPos = 600;
  float drivingCarXPos = width/2-car_width*1.5;
  float rebase = 0;
  bool charco = false;
  float posicionCharco = 0.0;
  int lineCharco = 0;
  float firstXPos = XPos[i];
  int contador = 0;


  speeds = 5.0f;
  maxSpeeds = (mediumSpeed - 100) - (i * 7);


  while(!gameOver){
    std::this_thread::sleep_for (std::chrono::milliseconds(int((1/speeds)*1000)));
    
    //if(!go) continue;
    int diff = linePos[i] - startPos;
    //std::cout << diff << std::endl;
    

    if(linePos[i]+1 >= lines.size()){
      lines[lines.size()-2].cars[i] = sf::Sprite();
      lines[lines.size()-2].carLocalBounds.height = 0;
      lines[lines.size()-2].carLocalBounds.width = 0;
      lines[lines.size()-2].carLocalBounds.top = 0;
      lines[lines.size()-2].carLocalBounds.left = 0;
      
      linePos[i] = 1;
      continue;
    } 
    float carsYpos = lines[linePos[i]-1].carsYPos[i];
    float carsXpos = lines[linePos[i]-1].carsXPos[i];
    

    float diffX = carsXpos - drivingCarXPos;
    float diffY = carsYpos - drivingCarYPos;
   
    if(cars[i].colision){ // si ha colisionado, gestionamos
      lines[linePos[i]].carExplosion[i] = true;
      if(cars[i].colisionSprite == 8){ // acaba de colisionar lo mandamos lejos
      //reseteamos para no volver a explotar
      lines[linePos[i]].carExplosion[i] = false;
      lines[linePos[i]-1].cars[i] = sf::Sprite();
      lines[linePos[i]-1].carLocalBounds.height = 0;
      lines[linePos[i]-1].carLocalBounds.width = 0;
      lines[linePos[i]-1].carLocalBounds.top = 0;
      lines[linePos[i]-1].carLocalBounds.left = 0;
      linePos[i] += 500;
      if(linePos[i]+1 >= lines.size()) linePos[i] -= lines.size(); // para cuando sea justo al dar vuelta
      cars[i].updateCarSprite();
      continue;
    }else if(diff < -20 && diff > -60){ // lo hemos dejado atras, lo reiniciamos y lo mandamos alante
        //reseteamos para no volver a explotar
        lines[linePos[i]].carExplosion[i] = false;
        lines[linePos[i] -1].cars[i] = sf::Sprite();
        lines[linePos[i]-1].carLocalBounds.height = 0;
        lines[linePos[i]-1].carLocalBounds.width = 0;
        lines[linePos[i]-1].carLocalBounds.top = 0;
        lines[linePos[i]-1].carLocalBounds.left = 0;
        linePos[i] += 500;
        if(linePos[i]+1 >= lines.size()) linePos[i] -= lines.size(); // para cuando sea justo al dar vuelta
        cars[i].colisionSprite = 8;
        cars[i].updateCarSprite();
        continue;
      }
    if(speeds-20 > 0) speeds -= 20;
      
    }else{
      if(contador > 0){ // si no está en su xpos habitual ni evitando un charco vuelve a ella
        if(contador < 100){
          if(XPos[i] < firstXPos){ // esta a la izquierda
            XPos[i] += 0.01;
            cars[i].car_dir = 1;
            cars[i].maxTex = 7;
          }else if(XPos[i] > firstXPos){ // esta a la derecha
            XPos[i] -= 0.01;
            cars[i].car_dir = -1;
            cars[i].maxTex = 7;
          }
        }
        contador--;
      }
      if(diff < -20 && diff > -60){ // lo hemos adelantado de sobra pues lo ponemos alante otra vez
        lines[linePos[i] -1].cars[i] = sf::Sprite();
        lines[linePos[i]-1].carLocalBounds.height = 0;
        lines[linePos[i]-1].carLocalBounds.width = 0;
        lines[linePos[i]-1].carLocalBounds.top = 0;
        lines[linePos[i]-1].carLocalBounds.left = 0;
        linePos[i] += 500;
        if(linePos[i]+1 >= lines.size()) linePos[i] -= lines.size(); // para cuando sea justo al dar vuelta
        continue;
      }
      if(diffX > -82 && diffX < 111 && diffY < 68 && diffY > -48){  //antes de nada comprobamos colision
        cars[i].colision = true;
        continue;
      }
      if((diffY > -200 && diffY < -0.1) || (diffY > 0.1 && diffY < 150) ){ // si no es un valor residual
        
        if(lines[linePos[i]].curve == 0){ // si es una recta hacemos perspectiva
          if(diffY < -150){ // lejos
            if(diffX < 20){
                cars[i].car_dir = 1;
                cars[i].maxTex = 5;
            }else if(diffX > 100){
              cars[i].car_dir = -1;
              cars[i].maxTex = 5;
            }else{
              cars[i].maxTex = 23;
              cars[i].car_dir = 0;
            }
          }else if(diffY < -100){ // medio lejos
            if(diffX < -10){
                cars[i].car_dir = 1;
                cars[i].maxTex = 9;
            }
            else if(diffX > 130){
              cars[i].car_dir = -1;
              cars[i].maxTex = 9;
            }else{
              cars[i].maxTex = 23;
              cars[i].car_dir = 0;
            }

          }else{ // medio cerca
              if(diffX < -50){
                  cars[i].car_dir = 1;
                  cars[i].maxTex = 13;
              }
              else if(diffX > 160){
                cars[i].car_dir = -1;
                cars[i].maxTex = 13;
              }else{
              cars[i].maxTex = 23;
              cars[i].car_dir = 0;
            }

          }
        }else if(lines[linePos[i]].curve > 0){
          cars[i].car_dir = 1;
          if(lines[linePos[i]].curve > 2.5){ 
            cars[i].maxTex = 23;
          }
          else if(lines[linePos[i]].curve > 1.5){ 
            cars[i].maxTex = 13;
          }else{
            cars[i].maxTex = 7;
          }
        }else if(lines[linePos[i]].curve < 0){
          cars[i].car_dir = -1;
          if(lines[linePos[i]].curve < -2.5){ 
            cars[i].maxTex = 23;
          }
          else if(lines[linePos[i]].curve < -1.5){ 
            cars[i].maxTex = 13;
          }else{
            cars[i].maxTex = 7;
          }
        }
      }
      
      if(speeds >= 0 && speeds <= maxSpeeds/3)  speeds += 2;
      else if(speeds > maxSpeeds/3 && speeds <= maxSpeeds/2)  speeds += 2;
      else if(speeds > maxSpeeds/2 && speeds <= maxSpeeds)  speeds += 3;

      
      

      if(diff < 20 && diff > -20){ //está detras tuyo se prepara para adelantar sin chocarte
          if((carsXpos >= drivingCarXPos - (car_width*3)) && (carsXpos <= drivingCarXPos + (car_width*2))){ // si se puede chocar conmigo
              if(rebase == 0){
                    if((XPos[i] - 0.5 > -off_road_allowed_cars-0.2)){ // intenta adelantar por la izquierda
                        XPos[i] -= 0.5;
                    }else{
                      rebase = 1; //si no puede lo intentará a derechas
                    }
              }else{
                    if((XPos[i] + 0.5 < off_road_allowed_cars)){ // intenta adelantar por la derecha
                      XPos[i] += 0.5;
                    }else{
                      rebase = 0; //si no puede lo intentará a izquierdas
                    }
                
              }
          }
      }
      if(lines[linePos[i]+100].sprite_type == 3 && !charco){ // establecemos donde está el charco y si nos lo vamos a comer
        
        posicionCharco = lines[linePos[i]+20].spriteX + 0.4;
        lineCharco = linePos[i]+100;
        //std::cout << "charco " << posicionCharco << std::endl;
        //std::cout << "yo " << XPos[i] << std::endl;
        if(XPos[i] > posicionCharco-0.7 && XPos[i] < posicionCharco+0.7){ // asumimos aqui nos lo comemos y lo vamos a querere evitar
          charco = true;
        }
        
        
        
      }else if(linePos[i] > lineCharco && charco){ // quitamos las variables para un uso posterior
        charco = false;
        posicionCharco = 0.0;
        lineCharco = 0;
        contador = 200;
      }else if(charco){ // esquivamos el charco
          cars[i].maxTex = 7;
          if((XPos[i] - 0.01 > -off_road_allowed_cars-0.2)){ 
              XPos[i] -= 0.01;
              cars[i].car_dir = -1;
          }
      }
    }
    
    
    cars[i].updateCarSprite();
    lines[linePos[i]-1].carLocalBounds.height = 0;
    lines[linePos[i]-1].carLocalBounds.width = 0;
    lines[linePos[i]-1].carLocalBounds.top = 0;
    lines[linePos[i]-1].carLocalBounds.left = 0;
    lines[linePos[i] -1].carExplosion[i] = false;
    lines[linePos[i] -1].cars[i] = sf::Sprite();
    lines[linePos[i]].cars[i] = cars[i].sprite;
    lines[linePos[i]].carsX[i] = XPos[i];
    linePos[i]++;
    clock.restart();
    while(!go){
      std::this_thread::sleep_for (std::chrono::milliseconds(20ms));
      clock.restart();
    }
    
    
    
  }
  

  lines[linePos[i]-1].carLocalBounds.height = 0;
  lines[linePos[i]-1].carLocalBounds.width = 0;
  lines[linePos[i]-1].carLocalBounds.top = 0;
  lines[linePos[i]-1].carLocalBounds.left = 0;
  lines[linePos[i] -1].cars[i] = sf::Sprite();
  if(linePos[i]+1 < lines.size()){
    lines[linePos[i] +1].cars[i] = sf::Sprite();
    lines[linePos[i]+1].carLocalBounds.height = 0;
    lines[linePos[i]+1].carLocalBounds.width = 0;
    lines[linePos[i]+1].carLocalBounds.top = 0;
    lines[linePos[i]+1].carLocalBounds.left = 0;
  }
  lines[linePos[i]].cars[i] = sf::Sprite();
  lines[lines.size()-1].cars[i] = sf::Sprite();
  lines[lines.size()-1].carLocalBounds.height = 0;
  lines[lines.size()-1].carLocalBounds.width = 0;
  lines[lines.size()-1].carLocalBounds.top = 0;
  lines[lines.size()-1].carLocalBounds.left = 0;
  lines[lines.size()-2].cars[i] = sf::Sprite();
  lines[lines.size()-2].carLocalBounds.height = 0;
  lines[lines.size()-2].carLocalBounds.width = 0;
  lines[lines.size()-2].carLocalBounds.top = 0;
  lines[lines.size()-2].carLocalBounds.left = 0;
}

void IAnormal_control(std::vector<Line>& lines, int linePos[], float XPos[], carSpriteIA cars[], int numCars, int i){
  Clock clock;
  float speeds;
  float maxSpeeds;
  float centripetal_force;
  float actual_draft_power;
  float drivingCarYPos = 600;
  float drivingCarXPos = width/2-car_width*1.5;
  int rebase = 0; // 0 rebasa por izquierda 1 por derecha
  bool charco = false;
  float posicionCharco = 0.0;
  int lineCharco = 0;
  int contador = 0;
  float firstXPos = XPos[i];
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(0,1); // distribution in range [1, 6]
  int zigzag = dist6(rng); // si 0 gira a izquierdas si 1 a derechas en su zigzag
  
  speeds = 5.0f;
  maxSpeeds = (mediumSpeed - 100) - (i * 7);
  

  while(!gameOver){
    std::this_thread::sleep_for (std::chrono::milliseconds(int((1/speeds)*1000)));

    int diff = linePos[i] - startPos;
    if(linePos[i]+1 >= lines.size()){
      lines[lines.size()-2].cars[i] = sf::Sprite();
      lines[lines.size()-2].carLocalBounds.height = 0;
      lines[lines.size()-2].carLocalBounds.width = 0;
      lines[lines.size()-2].carLocalBounds.top = 0;
      lines[lines.size()-2].carLocalBounds.left = 0;
      linePos[i] = 1;
      continue;
    } 
    float carsYpos = lines[linePos[i]-2].carsYPos[i];
    float carsXpos = lines[linePos[i]-2].carsXPos[i];

    
    
    float diffX = carsXpos - drivingCarXPos;
    float diffY = carsYpos - drivingCarYPos;
    if(cars[i].colision){ // si ha colisionado, gestionamos
      lines[linePos[i]].carExplosion[i] = true;
      if(cars[i].colisionSprite == 8){ // acaba de colisionar lo mandamos lejos
        lines[linePos[i]-1].cars[i] = sf::Sprite();
        lines[linePos[i]-1].carLocalBounds.height = 0;
        lines[linePos[i]-1].carLocalBounds.width = 0;
        lines[linePos[i]-1].carLocalBounds.top = 0;
        lines[linePos[i]-1].carLocalBounds.left = 0;
        linePos[i] += 500;
        if(linePos[i]+1 >= lines.size()) linePos[i] -= lines.size(); // para cuando sea justo al dar vuelta
        cars[i].updateCarSprite();
        continue;
    }else if(diff < -20 && diff > -60){ // lo hemos dejado atras, lo reiniciamos y lo mandamos alante
        lines[linePos[i] -1].cars[i] = sf::Sprite();
        lines[linePos[i]-1].carLocalBounds.height = 0;
        lines[linePos[i]-1].carLocalBounds.width = 0;
        lines[linePos[i]-1].carLocalBounds.top = 0;
        lines[linePos[i]-1].carLocalBounds.left = 0;
        linePos[i] += 500;
        if(linePos[i]+1 >= lines.size()) linePos[i] -= lines.size(); // para cuando sea justo al dar vuelta
        cars[i].colisionSprite = 8;
        cars[i].updateCarSprite();
        continue;
      }
    if(speeds-20 > 0) speeds -= 20;
      
    }else{
      if(!charco){ // hacemos zigzaf
        if(contador == 0){
          if(zigzag == 0){ // gira a la izquierda
              if((XPos[i] - 0.2 > -off_road_allowed_cars-0.2)){ // intenta adelantar por la izquierda
                  XPos[i] -= 0.01;
                  cars[i].car_dir = -1;
                  cars[i].maxTex = 7;
              }else{
                zigzag = 1; //si no puede lo intentará a derechas
              }
            
          }else{ // esta a la derecha
            if((XPos[i] + 0.2 < off_road_allowed_cars)){ // intenta adelantar por la izquierda
                  XPos[i] += 0.01;
                  cars[i].car_dir = 1;
                  cars[i].maxTex = 7;
              }else{
                zigzag = 0; //si no puede lo intentará a derechas
              }
          }
        }else{
          contador--;
        }
      }
      
        
      
      if(diff < -20 && diff > -60){ // lo hemos adelantado de sobra pues lo ponemos alante otra vez
        lines[linePos[i] -1].cars[i] = sf::Sprite();
        lines[linePos[i]-1].carLocalBounds.height = 0;
        lines[linePos[i]-1].carLocalBounds.width = 0;
        lines[linePos[i]-1].carLocalBounds.top = 0;
        lines[linePos[i]-1].carLocalBounds.left = 0;
        linePos[i] += 500;
        if(linePos[i]+1 >= lines.size()) linePos[i] -= lines.size(); // para cuando sea justo al dar vuelta
        continue;
      }
      if(diffX > -82 && diffX < 111 && diffY < 68 && diffY > -48){  //antes de nada comprobamos colision
        cars[i].colision = true;
        continue;
      }
      if((diffY > -200 && diffY < -0.1) || (diffY > 0.1 && diffY < 150) ){ // si no es un valor residual
        if(lines[linePos[i]].curve == 0){ // si es una recta hacemos perspectiva
          if(diffY < -150){ // lejos
            if(diffX < 20){
                cars[i].car_dir = 1;
                cars[i].maxTex = 5;
            }else if(diffX > 100){
              cars[i].car_dir = -1;
              cars[i].maxTex = 5;
            }else{
              cars[i].maxTex = 23;
              cars[i].car_dir = 0;
            }
          }else if(diffY < -100){ // medio lejos
            if(diffX < -10){
                cars[i].car_dir = 1;
                cars[i].maxTex = 9;
            }
            else if(diffX > 130){
              cars[i].car_dir = -1;
              cars[i].maxTex = 9;
            }else{
              cars[i].maxTex = 23;
              cars[i].car_dir = 0;
            }

          }else{ // medio cerca
              if(diffX < -50){
                  cars[i].car_dir = 1;
                  cars[i].maxTex = 13;
              }
              else if(diffX > 160){
                cars[i].car_dir = -1;
                cars[i].maxTex = 13;
              }else{
              cars[i].maxTex = 23;
              cars[i].car_dir = 0;
            }

          }
        }else if(lines[linePos[i]].curve > 0){
          cars[i].car_dir = 1;
          if(lines[linePos[i]].curve > 2.5){ 
            cars[i].maxTex = 23;
          }
          else if(lines[linePos[i]].curve > 1.5){ 
            cars[i].maxTex = 13;
          }else{
            cars[i].maxTex = 7;
          }
        }else if(lines[linePos[i]].curve < 0){
          cars[i].car_dir = -1;
          if(lines[linePos[i]].curve < -2.5){ 
            cars[i].maxTex = 23;
          }
          else if(lines[linePos[i]].curve < -1.5){ 
            cars[i].maxTex = 13;
          }else{
            cars[i].maxTex = 7;
          }
        }
      }
    
    

      centripetal_force = ((speeds/(mediumSpeed-70))) * floatAbs(lines[linePos[i]].curve);//((speed * floatAbs(lines[startPos].curve)) / maxSpeed);
      actual_draft_power = draft_power * centripetal_force; 


      

      if ((XPos[i] < off_road_allowed_cars) && (XPos[i]> -off_road_allowed_cars -0.2)){
        if(lines[linePos[i]].curve > 0 && (XPos[i] + actual_draft_power < off_road_allowed_cars)){
            XPos[i] += actual_draft_power;
        }
        if(lines[linePos[i]].curve < 0 && (XPos[i] - actual_draft_power > -off_road_allowed_cars-0.2)){
            XPos[i] -= actual_draft_power;
        }
      }

      
      if(speeds >= 0 && speeds <= maxSpeeds/3)  speeds += 2;
      else if(speeds > maxSpeeds/3 && speeds <= maxSpeeds/2)  speeds += 2;
      else if(speeds > maxSpeeds/2 && speeds <= maxSpeeds)  speeds += 3;

      
      if(diff < 0 && diff > -20){ //está detras tuyo se prepara para adelantar sin chocarte
          if((carsXpos >= drivingCarXPos - (car_width*3)) && (carsXpos <= drivingCarXPos + (car_width*2))){ // si se puede chocar conmigo
              if(rebase == 0){
                    if((XPos[i] - 0.5 > -off_road_allowed_cars-0.2)){ // intenta adelantar por la izquierda
                        XPos[i] -= 0.5;
                    }else{
                      rebase = 1; //si no puede lo intentará a derechas
                    }
              }else{
                    if((XPos[i] + 0.5 < off_road_allowed_cars)){ // intenta adelantar por la derecha
                      XPos[i] += 0.5;
                    }else{
                      rebase = 0; //si no puede lo intentará a izquierdas
                    }
                
              }
          }
      }
      if(lines[linePos[i]+100].sprite_type == 3 && !charco){ // establecemos donde está el charco y si nos lo vamos a comer
        
        posicionCharco = lines[linePos[i]+20].spriteX + 0.4;
        lineCharco = linePos[i]+100;
        //std::cout << "charco " << posicionCharco << std::endl;
        //std::cout << "yo " << XPos[i] << std::endl;
        if(XPos[i] > posicionCharco-0.7 && XPos[i] < posicionCharco+0.7){ // asumimos aqui nos lo comemos y lo vamos a querere evitar
          charco = true;
        }
        
        
        
      }else if(linePos[i] > lineCharco && charco){ // quitamos las variables para un uso posterior
        charco = false;
        posicionCharco = 0.0;
        lineCharco = 0;
        contador = 200;
      }else if(charco){ // esquivamos el charco
          cars[i].maxTex = 7;
          if((XPos[i] - 0.01 > -off_road_allowed_cars-0.2)){ 
              XPos[i] -= 0.01;
              cars[i].car_dir = -1;
          }
      }
    }

    cars[i].updateCarSprite();
    lines[linePos[i]-1].carLocalBounds.height = 0;
    lines[linePos[i]-1].carLocalBounds.width = 0;
    lines[linePos[i]-1].carLocalBounds.top = 0;
    lines[linePos[i]-1].carLocalBounds.left = 0;
    lines[linePos[i] -1].carExplosion[i] = false;
    lines[linePos[i] -1].cars[i] = sf::Sprite();
    lines[linePos[i]].cars[i] = cars[i].sprite;
    lines[linePos[i]].carsX[i] = XPos[i];
    linePos[i]++;
    clock.restart();
    while(!go){
      std::this_thread::sleep_for (std::chrono::milliseconds(20ms));
      clock.restart();
    }
    
    
  }
  lines[linePos[i]-1].carLocalBounds.height = 0;
  lines[linePos[i]-1].carLocalBounds.width = 0;
  lines[linePos[i]-1].carLocalBounds.top = 0;
  lines[linePos[i]-1].carLocalBounds.left = 0;
  lines[linePos[i] -1].cars[i] = sf::Sprite();
  if(linePos[i]+1 < lines.size()){
    lines[linePos[i] +1].cars[i] = sf::Sprite();
    lines[linePos[i]+1].carLocalBounds.height = 0;
    lines[linePos[i]+1].carLocalBounds.width = 0;
    lines[linePos[i]+1].carLocalBounds.top = 0;
    lines[linePos[i]+1].carLocalBounds.left = 0;
  }
  lines[linePos[i]].cars[i] = sf::Sprite();
  lines[lines.size()-1].cars[i] = sf::Sprite();
  lines[lines.size()-1].carLocalBounds.height = 0;
  lines[lines.size()-1].carLocalBounds.width = 0;
  lines[lines.size()-1].carLocalBounds.top = 0;
  lines[lines.size()-1].carLocalBounds.left = 0;
  lines[lines.size()-2].cars[i] = sf::Sprite();
  lines[lines.size()-2].carLocalBounds.height = 0;
  lines[lines.size()-2].carLocalBounds.width = 0;
  lines[lines.size()-2].carLocalBounds.top = 0;
  lines[lines.size()-2].carLocalBounds.left = 0;
}

void IAhard_control(std::vector<Line>& lines, int linePos[], float XPos[], carSpriteIA cars[], int numCars, int i){
  Clock clock;
  float speeds;
  float maxSpeeds;
  float centripetal_force;
  float actual_draft_power;
  float drivingCarYPos = 600;
  float drivingCarXPos = width/2-car_width*1.5;
  float rebase = 0;
  bool charco = false;
  float posicionCharco = 0.0;
  int lineCharco = 0;
  
  // sabes que el coche que controlas siempre está en la misma posición, X = 0, Y = nose
  // cuando estes cerca de esa Y siendo la tuya más arriba te acercas poco a poco a esa X = 0
  speeds = 5.0f;
  maxSpeeds = (mediumSpeed- 100) - (i * 7);

  while(!gameOver){
    std::this_thread::sleep_for (std::chrono::milliseconds(int((1/speeds)*1000)));

    int diff = linePos[i] - startPos;
    

    if(linePos[i]+1 >= lines.size()){
      lines[lines.size()-2].cars[i] = sf::Sprite();
      lines[lines.size()-2].carLocalBounds.height = 0;
      lines[lines.size()-2].carLocalBounds.width = 0;
      lines[lines.size()-2].carLocalBounds.top = 0;
      lines[lines.size()-2].carLocalBounds.left = 0;
      linePos[i] = 1;
      continue;
    } 
    float carsYpos = lines[linePos[i]-2].carsYPos[i];
    float carsXpos = lines[linePos[i]-2].carsXPos[i];
    
    float diffX = carsXpos - drivingCarXPos;
    float diffY = carsYpos - drivingCarYPos;
    if(cars[i].colision){ // si ha colisionado, gestionamos
      lines[linePos[i]].carExplosion[i] = true;
      if(cars[i].colisionSprite == 8){ // acaba de colisionar lo mandamos lejos
      lines[linePos[i]-1].cars[i] = sf::Sprite();
      lines[linePos[i]-1].carLocalBounds.height = 0;
      lines[linePos[i]-1].carLocalBounds.width = 0;
      lines[linePos[i]-1].carLocalBounds.top = 0;
      lines[linePos[i]-1].carLocalBounds.left = 0;
      linePos[i] += 500;
      if(linePos[i]+1 >= lines.size()) linePos[i] -= lines.size(); // para cuando sea justo al dar vuelta
      cars[i].updateCarSprite();
      continue;
    }else if(diff < -20 && diff > -60){ // lo hemos dejado atras, lo reiniciamos y lo mandamos alante
        lines[linePos[i] -1].cars[i] = sf::Sprite();
        lines[linePos[i]-1].carLocalBounds.height = 0;
        lines[linePos[i]-1].carLocalBounds.width = 0;
        lines[linePos[i]-1].carLocalBounds.top = 0;
        lines[linePos[i]-1].carLocalBounds.left = 0;
        linePos[i] += 500;
        if(linePos[i]+1 >= lines.size()) linePos[i] -= lines.size(); // para cuando sea justo al dar vuelta
        cars[i].colisionSprite = 8;
        cars[i].updateCarSprite();
        continue;
      }
    if(speeds-20 > 0) speeds -= 20;
      
    }else{
      if(diff < -20 && diff > -60){ // lo hemos adelantado de sobra pues lo ponemos alante otra vez
        lines[linePos[i] -1].cars[i] = sf::Sprite();
        lines[linePos[i]-1].carLocalBounds.height = 0;
        lines[linePos[i]-1].carLocalBounds.width = 0;
        lines[linePos[i]-1].carLocalBounds.top = 0;
        lines[linePos[i]-1].carLocalBounds.left = 0;
        linePos[i] += 500;
        if(linePos[i]+1 >= lines.size()) linePos[i] -= lines.size(); // para cuando sea justo al dar vuelta
        continue;
      }
      if(diffX > -82 && diffX < 111 && diffY < 68 && diffY > -48){  //antes de nada comprobamos colision
        cars[i].colision = true;
        continue;
      }
      if((diffY > -200 && diffY < -0.1) || (diffY > 0.1 && diffY < 150) ){ // si no es un valor residual
        if(lines[linePos[i]].curve == 0){ // si es una recta hacemos perspectiva
          if(diffY < -150){ // lejos
            if(diffX < 20){
                cars[i].car_dir = 1;
                cars[i].maxTex = 5;
            }else if(diffX > 100){
              cars[i].car_dir = -1;
              cars[i].maxTex = 5;
            }else{
              cars[i].maxTex = 23;
              cars[i].car_dir = 0;
            }
          }else if(diffY < -100){ // medio lejos
            if(diffX < -10){
                cars[i].car_dir = 1;
                cars[i].maxTex = 9;
            }
            else if(diffX > 130){
              cars[i].car_dir = -1;
              cars[i].maxTex = 9;
            }else{
              cars[i].maxTex = 23;
              cars[i].car_dir = 0;
            }

          }else{ // medio cerca
              if(diffX < -50){
                  cars[i].car_dir = 1;
                  cars[i].maxTex = 13;
              }
              else if(diffX > 160){
                cars[i].car_dir = -1;
                cars[i].maxTex = 13;
              }else{
              cars[i].maxTex = 23;
              cars[i].car_dir = 0;
            }

          }
          
        }else if(lines[linePos[i]].curve > 0){
          cars[i].car_dir = 1;
          if(lines[linePos[i]].curve > 2.5){ 
            cars[i].maxTex = 23;
          }
          else if(lines[linePos[i]].curve > 1.5){ 
            cars[i].maxTex = 13;
          }else{
            cars[i].maxTex = 7;
          }
        }else if(lines[linePos[i]].curve < 0){
          cars[i].car_dir = -1;
          if(lines[linePos[i]].curve < -2.5){ 
            cars[i].maxTex = 23;
          }
          else if(lines[linePos[i]].curve < -1.5){ 
            cars[i].maxTex = 13;
          }else{
            cars[i].maxTex = 7;
          }
        }
        if(carsYpos > 460 && carsYpos < 550 && !charco){ //aquí es cuando tiende a ponerse delante tuyo
            // tratas de igualar las X para molestar lo máximo posible
            if(carsXpos  > drivingCarXPos + (car_width-10) && XPos[i] - 0.02 > -off_road_allowed_cars-0.2){ 
                XPos[i] -= 0.03;
                if(lines[linePos[i]].curve == 0) {
                  cars[i].car_dir = -1;
                  if(cars[i].maxTex + 4 <= 23){
                    cars[i].maxTex += 4;
                  }else if(cars[i].maxTex + 1 <= 23){
                    cars[i].maxTex += 1;
                  } 
                }else{
                  if(cars[i].maxTex - 4 >= 0){
                    cars[i].maxTex -= 4;
                  }else if(cars[i].maxTex - 1 >= 0){
                    cars[i].maxTex -= 1;
                  } 
                }
            }else if(carsXpos  < drivingCarXPos - (car_width-10) && XPos[i] + 0.02 < off_road_allowed_cars){  
                XPos[i] += 0.03;
                if(lines[linePos[i]].curve == 0) {
                  cars[i].car_dir = 1;
                  if(cars[i].maxTex + 4 <= 23){
                    cars[i].maxTex += 4;
                  }else if(cars[i].maxTex + 1 <= 23){
                    cars[i].maxTex += 1;
                  } 
                }else{
                  if(cars[i].maxTex - 4 >= 0){
                    cars[i].maxTex -= 4;
                  }else if(cars[i].maxTex - 1 >= 0){
                    cars[i].maxTex -= 1;
                  } 
                }
            }

          }
      }
      

      centripetal_force = ((speeds/(mediumSpeed-60))) * floatAbs(lines[linePos[i]].curve);//((speed * floatAbs(lines[startPos].curve)) / maxSpeed);
      actual_draft_power = draft_power * centripetal_force; 


      

      if ((XPos[i] < off_road_allowed_cars) && (XPos[i]> -off_road_allowed_cars-0.2)){
        if(lines[linePos[i]].curve > 0 && (XPos[i] + actual_draft_power < off_road_allowed_cars)){
            XPos[i] += actual_draft_power;
        }
        if(lines[linePos[i]].curve < 0 && (XPos[i] - actual_draft_power > -off_road_allowed_cars-0.2)){
            XPos[i] -= actual_draft_power;
        }
      }

      
      if(speeds >= 0 && speeds <= maxSpeeds/3)  speeds += 2;
      else if(speeds > maxSpeeds/3 && speeds <= maxSpeeds/2)  speeds += 2;
      else if(speeds > maxSpeeds/2 && speeds <= maxSpeeds)  speeds += 3;

    
      
      if(diff < 10 && diff > -20){ //está detras tuyo se prepara para adelantar sin chocarte
          if((carsXpos >= drivingCarXPos - (car_width*3)) && (carsXpos <= drivingCarXPos + (car_width*2))){ // si se puede chocar conmigo
              if(rebase == 0){
                    if((XPos[i] - 0.5 > -off_road_allowed_cars-0.2)){ // intenta adelantar por la izquierda
                        XPos[i] -= 0.5;
                    }else{
                      rebase = 1; //si no puede lo intentará a derechas
                    }
              }else{
                    if((XPos[i] + 0.5 < off_road_allowed_cars)){ // intenta adelantar por la derecha
                      XPos[i] += 0.5;
                    }else{
                      rebase = 0; //si no puede lo intentará a izquierdas
                    }
                
              }
          }
      }

      if(lines[linePos[i]+100].sprite_type == 3 && !charco){ // establecemos donde está el charco y si nos lo vamos a comer
        
        posicionCharco = lines[linePos[i]+20].spriteX + 0.4;
        lineCharco = linePos[i]+100;
        //std::cout << "charco " << posicionCharco << std::endl;
        //std::cout << "yo " << XPos[i] << std::endl;
        if(XPos[i] > posicionCharco-0.7 && XPos[i] < posicionCharco+0.7){ // asumimos aqui nos lo comemos y lo vamos a querere evitar
          charco = true;
        }
        
        
        
      }else if(linePos[i] > lineCharco && charco){ // quitamos las variables para un uso posterior
        charco = false;
        posicionCharco = 0.0;
        lineCharco = 0;
      }else if(charco){ // esquivamos el charco
          cars[i].maxTex = 7;
          if((XPos[i] - 0.01 > -off_road_allowed_cars-0.2)){ 
              XPos[i] -= 0.01;
              cars[i].car_dir = -1;
          }
      }
    }

    cars[i].updateCarSprite();
    lines[linePos[i]-1].carLocalBounds.height = 0;
    lines[linePos[i]-1].carLocalBounds.width = 0;
    lines[linePos[i]-1].carLocalBounds.top = 0;
    lines[linePos[i]-1].carLocalBounds.left = 0;
    lines[linePos[i] -1].carExplosion[i] = false;
    lines[linePos[i] -1].cars[i] = sf::Sprite();
    lines[linePos[i]].cars[i] = cars[i].sprite;
    lines[linePos[i]].carsX[i] = XPos[i];
    linePos[i]++;
    clock.restart();
    while(!go){
      std::this_thread::sleep_for (std::chrono::milliseconds(20ms));
      clock.restart();
    }
      
      
      

      
    }
    
    
  lines[linePos[i]-1].carLocalBounds.height = 0;
  lines[linePos[i]-1].carLocalBounds.width = 0;
  lines[linePos[i]-1].carLocalBounds.top = 0;
  lines[linePos[i]-1].carLocalBounds.left = 0;
  lines[linePos[i] -1].cars[i] = sf::Sprite();
  if(linePos[i]+1 < lines.size()){
    lines[linePos[i] +1].cars[i] = sf::Sprite();
    lines[linePos[i]+1].carLocalBounds.height = 0;
    lines[linePos[i]+1].carLocalBounds.width = 0;
    lines[linePos[i]+1].carLocalBounds.top = 0;
    lines[linePos[i]+1].carLocalBounds.left = 0;
  }
  lines[linePos[i]].cars[i] = sf::Sprite();
  lines[lines.size()-1].cars[i] = sf::Sprite();
  lines[lines.size()-1].carLocalBounds.height = 0;
  lines[lines.size()-1].carLocalBounds.width = 0;
  lines[lines.size()-1].carLocalBounds.top = 0;
  lines[lines.size()-1].carLocalBounds.left = 0;
  lines[lines.size()-2].cars[i] = sf::Sprite();
  lines[lines.size()-2].carLocalBounds.height = 0;
  lines[lines.size()-2].carLocalBounds.width = 0;
  lines[lines.size()-2].carLocalBounds.top = 0;
  lines[lines.size()-2].carLocalBounds.left = 0;
  
}

// Creo que sería mejor meterlo directamente en un line, para que así los dibuje en la carretera
void IA_control(std::vector<Line>& lines, int linePos[], float XPos[], carSpriteIA cars[], int numCars, int iaMode, std::thread threads[]){

  switch (iaMode)
  {
  case 0: // easy
    for(int i = 0; i < numCars; i++) threads[i] = thread(&IAeasy_control, ref(lines), linePos, XPos, cars, numCars, i);
    break;
  
  case 1: // normal
    for(int i = 0; i < numCars; i++) threads[i] = thread(&IAnormal_control, ref(lines), linePos, XPos, cars, numCars, i);
    break;
  case 2: // hard
    for(int i = 0; i < numCars; i++) threads[i] = thread(&IAhard_control, ref(lines), linePos, XPos, cars, numCars, i);
    break;
  default:
    break;
  }
}

