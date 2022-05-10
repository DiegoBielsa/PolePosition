#include "init.hpp"



void setConfig(){
  std::string file = "config/config.conf";
  std::ifstream f(file);
  std::string line;

  if(!f.is_open()){
    std::cout << "Error al abrir el fichero de configuracion " << file << std::endl;
  }

  while(std::getline(f, line)){
    std::size_t found = line.find("=");
    if(found!=std::string::npos){
      //std::cout << "hay un igual " << found << std::endl;
      // ahora hay que identificar la variable, pillar el valor y darselo con un switch
      // identificamos variable
      std::string var = "";
      for(long unsigned int i = 0; i < found; i++){
        if(line[i] == ' ' || line[i] == '=' || line[i] == '\t'){
          break;
        }else{
          var += line[i];
        }
      }
      
      
      std::string valueStr = "";
      for(long unsigned int i = found; i < line.size(); i++){
          if(line[i] == ' ' || line[i] == '=' || line[i] == '\t'){
            continue;
          }else if(line[i] == ';' || line[i] == '\n'){

          }
          else{
            valueStr += line[i];
          }
      }

      float value = std::stof(valueStr);
      if(var == "roadW"){
        roadW = value;
      }else if(var == "segL"){
        segL = value;
      }else if(var == "camD"){
        camD = value;
      }else if(var == "draw_distance"){
        draw_distance = value;
      }else if(var == "car_width"){
        car_width = value;
      }else if(var == "car_height"){
        car_height = value;
      }else if(var == "off_road_allowed"){
        off_road_allowed = value;
      }else if(var == "turn_power"){
        turn_power = value;
      }else if(var == "draft_power"){
        draft_power = value;
      }else if(var == "numMaps"){
        numMaps = value;
      }else if(var == "goalPosIni"){
        goalPosIni = value;
      }else if(var == "goalPosEnd"){
        goalPosEnd = value;
      }else if(var == "road_limit"){
        road_limit = value;
      }else if(var == "maxSpeed"){
        maxSpeed = value;
      }else if(var == "mapa"){
        mapa = value;
      }else if(var == "numCars"){
        numCars = value;
      }else if(var == "mediumSpeed"){
        mediumSpeed = value;
      }else if(var == "iaMode"){
        iaMode = value;
      }else if(var == "off_road_allowed_cars"){
        off_road_allowed_cars = value; 
      }else if(var == "carPosition"){
        carPosition = value; 
      }else{
        std::cout << "No existe la variable de configuracion " << var << std::endl;
      }
    }
    
  }

  f.close();

}

void setMaps(std::vector<std::vector<Line>>& maps, Sprite object[]){
  maps.resize(numMaps);
  for(int j = 0; j < numMaps; j++){
    std::vector<Line> lines;
    switch (j)
    {
    case 0:
      goalPosEnd = 3500;
      for(int i = 0; i < 3600; i++){
        // solo hay que poner los sprites y las curvas (y la meta)
        Line line;
        line.z = i * segL;
        line.sprite_type = 4; // por si acaso

        if(i == goalPosIni){
          line.isGoal = true;
          line.sprite = object[8];
          line.spriteX = -0.5;
          line.sprite_type = 2;//meta
        }
        

        if((i >= 500 && i <= 800) || (i >= 1000 && i <= 1300) || (i >= 2300 && i <= 2600) || (i >= 2800 && i <= 3100)){
          line.curve = 4* -1;
        }

        if(i>100 && i % 565 == 0 && line.curve == 0){//charco grande
          line.sprite = object[15];
          line.spriteX = 0;
          line.sprite_type = 3;
        }

        if(i>100 && i % 937 == 0 && line.curve == 0){//personas
          line.sprite = object[22];
          line.spriteX = -0.5;
          line.sprite_type = 2;
        }

        if(i>100 && i % 780 == 0 && line.curve == 0){//ruedaCarrera
          line.sprite = object[23];
          line.spriteX = -0.5;
          line.sprite_type = 2;
        }

        if(i>100 && i % 400 == 0){//cartel1
          line.sprite = object[9];
          line.spriteX = -2.5;
          line.sprite_type = 0;
        }
        if(i>100 && (i+200) % 400 == 0){//cartel2
          line.sprite = object[10];
          line.spriteX = 2;
          line.sprite_type = 0;
        }

        if(i>100 && (i+400) % 500 == 0 && line.curve < 0){//cartel3
          line.sprite = object[11];
          line.spriteX = -2.5;
          line.sprite_type = 0;
        }

        if(i>100 && (i+250) % 700 == 0){//cartel4
          line.sprite = object[12];
          line.spriteX = 1.5;
          line.sprite_type = 0;
        }

        if(i>100 && (i+250) % 450 == 0){//cartel5
          line.sprite = object[13];
          line.spriteX = 2;
          line.sprite_type = 0;
        }

        if(i>100 && (i+100) % 800 == 0){//cartel5
          line.sprite = object[14];
          line.spriteX = -2.6;
          line.sprite_type = 0;
        }

        lines.push_back(line);

      }
      break;
    
    case 1:
      for(int i = 0; i < 3700; i++){
        // solo hay que poner los sprites y las curvas (y la meta)
        Line line;
        line.z = i * segL;

        if(i == goalPosIni){
          line.isGoal = true;
          line.sprite = object[8];
          line.spriteX = -0.5;
          line.sprite_type = 2;//meta
        }

        if(i >= 500 && i <= 800){
          line.curve = 4* 2.5;
        }

        if(i >= 800 && i <= 1300){
          line.curve = 4* -0.5;
        }

        if(i >= 1300 && i <= 1600){
          line.curve = 4* 2.5;
        }

        if(i >= 1600 && i <= 1900){
          line.curve = 4* 0.2;
        }

        if(i >= 1900 && i <= 2300){
          line.curve = 4* -1.5;
        }

        if(i >= 2300 && i <= 2700){
          line.curve = 4* 0.3;
        }

        if(i >= 2700 && i <= 3700){
          line.curve = 4* 1;
        }

        if(i>100 && i % 565 == 0 && line.curve == 0){//charco grande
          line.sprite = object[15];
          line.spriteX = 0;
          line.sprite_type = 3;
        }

        
        if(i>100 && i % 400 == 0){//cartel1
          line.sprite = object[9];
          line.spriteX = -2.5;
          line.sprite_type = 0;
        }
        if(i>100 && (i+200) % 400 == 0){//cartel2
          line.sprite = object[10];
          line.spriteX = 2;
          line.sprite_type = 0;
        }

        if(i>100 && (i+400) % 500 == 0 && line.curve < 0){//cartel3
          line.sprite = object[11];
          line.spriteX = -2.5;
          line.sprite_type = 0;
        }

        if(i>100 && (i+250) % 700 == 0){//cartel4
          line.sprite = object[12];
          line.spriteX = 1.5;
          line.sprite_type = 0;
        }

        if(i>100 && (i+250) % 450 == 0){//cartel5
          line.sprite = object[13];
          line.spriteX = 2;
          line.sprite_type = 0;
        }

        if(i>100 && (i+100) % 800 == 0){//cartel5
          line.sprite = object[14];
          line.spriteX = -2.6;
          line.sprite_type = 0;
        }

        /*if(i>100 && (i+400) % 500 == 0 && line.curve > 0){//cartel7
          line.sprite = object[15];
          line.spriteX = -2.5;
          line.sprite_type = 0;
        }*/
        

        lines.push_back(line);

      }
      break;

    case 2:
      for(int i = 0; i < 7200; i++){
          // solo hay que poner los sprites y las curvas (y la meta)
          Line line;
          line.z = i * segL;

          if(i == goalPosIni){
          line.isGoal = true;
          line.sprite = object[8];
          line.spriteX = -0.5;
          line.sprite_type = 2;//meta
        }

          if(i >= 0 && i <= 1000){
            line.curve = 4* 0.5;
          }

          if(i >= 1000 && i <= 1200){
            line.curve = 4* -0.2;
          }

          if(i >= 1200 && i <= 1400){
            line.curve = 4* 2;
          }

          if(i >= 1600 && i <= 1800){
            line.curve = 4* -2;
          }

          if(i >= 2000 && i <= 2200){
            line.curve = 4* 2;
          }

          if(i >= 2300 && i <= 2400){
            line.curve = 4* 2;
          }

          if(i >= 2400 && i <= 2700){
            line.curve = 4* -0.4;
          }

          if(i >= 2700 && i <= 3000){
            line.curve = 4* 0.4;
          }

          if(i >= 3000 && i <= 3200){
            line.curve = 4* -0.7;
          }

          if(i >= 3300 && i <= 3400){
            line.curve = 4* 2;
          }

          if(i >= 4100 && i <= 4200){
            line.curve = 4* 1.7;
          }

          if(i >= 4350 && i <= 4500){
            line.curve = 4* -1.7;
          }

          if(i >= 4750 && i <= 4900){
            line.curve = 4* 1.4;
          }

          if(i >= 5100 && i <= 5250){
            line.curve = 4* -1.4;
          }

          if(i >= 5400 && i <= 5500){
            line.curve = 4* -1.5;
          }

          if(i >= 5800 && i <= 6000){
            line.curve = 4* 2;
          }

          if(i >= 6300 && i <= 6600){
            line.curve = 4* 1.5;
          }

          if(i >= 6600 && i <= 6900){
            line.curve = 4* -1.8;
          }

          if(i >= 6900 && i <= 7200){
            line.curve = 4* 0.5;
          }

          if(i>100 && i % 565 == 0 && line.curve == 0){//charco grande
            line.sprite = object[15];
            line.spriteX = 2;
            line.sprite_type = 3;
          }

          if(i>100 && i % 400 == 0){//cartel1
          line.sprite = object[9];
          line.spriteX = -2.5;
          line.sprite_type = 0;
        }
        if(i>100 && (i+200) % 400 == 0){//cartel2
          line.sprite = object[10];
          line.spriteX = 2;
          line.sprite_type = 0;
        }

        if(i>100 && (i+400) % 500 == 0 && line.curve < 0){//cartel3
          line.sprite = object[11];
          line.spriteX = -2.5;
          line.sprite_type = 0;
        }

        if(i>100 && (i+250) % 700 == 0){//cartel4
          line.sprite = object[12];
          line.spriteX = 1.5;
          line.sprite_type = 0;
        }

        if(i>100 && (i+250) % 450 == 0){//cartel5
          line.sprite = object[13];
          line.spriteX = 2;
          line.sprite_type = 0;
        }

        if(i>100 && (i+100) % 800 == 0){//cartel5
          line.sprite = object[14];
          line.spriteX = -2.6;
          line.sprite_type = 0;
        }

        /*if(i>100 && (i+400) % 500 == 0 && line.curve > 0){//cartel7
          line.sprite = object[15];
          line.spriteX = -2.5;
          line.sprite_type = 0;
        }*/

          lines.push_back(line);

      }
      break;
    
    case 3:
      for(int i = 0; i < 5100; i++){
        // solo hay que poner los sprites y las curvas (y la meta)
        Line line;
        line.z = i * segL;

        if(i == goalPosIni){
          line.isGoal = true;
          line.sprite = object[8];
          line.spriteX = -0.5;
          line.sprite_type = 2;//meta
        }
        

        if(i >= 400 && i <= 700){
            line.curve = 4* 2.5;
        }

        if(i >= 700 && i <= 800){
            line.curve = 4* 3;
        }

        if(i >= 800 && i <= 1000){
            line.curve = 4* -3;
        }

        if(i >= 1000 && i <= 1200){
            line.curve = 4* 3;
        }

        if(i >= 1200 && i <= 1400){
            line.curve = 4* -3;
        }

        if(i >= 1400 && i <= 1600){
            line.curve = 4* 3;
        }

        if(i >= 1600 && i <= 1800){
            line.curve = 4* -3;
        }

        if(i >= 2100 && i <= 2400){
            line.curve = 4* 2.5;
        }

        if(i >= 2500 && i <= 2650){
            line.curve = 4* -1.2;
        }

        if(i >= 2900 && i <= 3200){
            line.curve = 4* 2.7;
        }

        if(i >= 3200 && i <= 3400){
            line.curve = 4* -0.2;
        }

        if(i >= 3400 && i <= 3500){
            line.curve = 4* -2.4;
        }

        if(i >= 3500 && i <= 3750){
            line.curve = 4* 0.8;
        }

        if(i >= 3750 && i <= 3900){
            line.curve = 4* 2.5;
        }

        if(i >= 3900 && i <= 4100){
            line.curve = 4* -0.2;
        }

        if(i >= 4100 && i <= 4300){
            line.curve = 4* -2.2;
        }

        if(i >= 4600 && i <= 4700){
            line.curve = 4* 2.5;
        }

        if(i >= 4700 && i <= 4800){
            line.curve = 4* -2.5;
        }

        if(i >= 4800 && i <= 4900){
            line.curve = 4* 2.5;
        }

        if(i>100 && i % 565 == 0 && line.curve == 0){//charco grande
          line.sprite = object[15];
          line.spriteX = 0;
          line.sprite_type = 3;
        }

        if(i>100 && i % 400 == 0){//cartel1
          line.sprite = object[9];
          line.spriteX = -2.5;
          line.sprite_type = 0;
        }
        if(i>100 && (i+200) % 400 == 0){//cartel2
          line.sprite = object[10];
          line.spriteX = 2;
          line.sprite_type = 0;
        }

        if(i>100 && (i+400) % 500 == 0 && line.curve < 0){//cartel3
          line.sprite = object[11];
          line.spriteX = -2.5;
          line.sprite_type = 0;
        }

        if(i>100 && (i+250) % 700 == 0){//cartel4
          line.sprite = object[12];
          line.spriteX = 1.5;
          line.sprite_type = 0;
        }

        if(i>100 && (i+250) % 450 == 0){//cartel5
          line.sprite = object[13];
          line.spriteX = 2;
          line.sprite_type = 0;
        }

        if(i>100 && (i+100) % 800 == 0){//cartel5
          line.sprite = object[14];
          line.spriteX = -2.6;
          line.sprite_type = 0;
        }

        /*if(i>100 && (i+400) % 500 == 0 && line.curve > 0){//cartel7
          line.sprite = object[15];
          line.spriteX = -2.5;
          line.sprite_type = 0;
        }*/

        lines.push_back(line);

      }
      break;
    }
    
    maps[j] = lines;
  }
}

void loadTextures(){

}

