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
      for(int i = 0; i < 3600; i++){
        // solo hay que poner los sprites y las curvas (y la meta)
        Line line;
        line.z = i * segL;

        if(i >= goalPosIni && i <= goalPosEnd){
          line.isGoal = true;
          line.sprite = object[7];
        }

        if((i >= 500 && i <= 800) || (i >= 1000 && i <= 1300) || (i >= 2300 && i <= 2600) || (i >= 2800 && i <= 3100)){
          line.curve = -1;
        }

        lines.push_back(line);

      }
      break;
    
    case 1:
      for(int i = 0; i < 3700; i++){
        // solo hay que poner los sprites y las curvas (y la meta)
        Line line;
        line.z = i * segL;

        if(i >= goalPosIni && i <= goalPosEnd){
          line.isGoal = true;
          line.sprite = object[7];
        }

        if(i >= 500 && i <= 800){
          line.curve = 2.5;
        }

        if(i >= 800 && i <= 1300){
          line.curve = -0.5;
        }

        if(i >= 1300 && i <= 1600){
          line.curve = 2.5;
        }

        if(i >= 1600 && i <= 1900){
          line.curve = 0.2;
        }

        if(i >= 1900 && i <= 2300){
          line.curve = -1.5;
        }

        if(i >= 2300 && i <= 2700){
          line.curve = 0.3;
        }

        if(i >= 2700 && i <= 3700){
          line.curve = 1;
        }
        

        lines.push_back(line);

      }
      break;

    case 2:
      for(int i = 0; i < 7200; i++){
          // solo hay que poner los sprites y las curvas (y la meta)
          Line line;
          line.z = i * segL;

          if(i >= goalPosIni && i <= goalPosEnd){
            line.isGoal = true;
            line.sprite = object[7];
          }

          if(i >= 0 && i <= 1000){
            line.curve = 0.5;
          }

          if(i >= 1000 && i <= 1200){
            line.curve = -0.2;
          }

          if(i >= 1200 && i <= 1400){
            line.curve = 2;
          }

          if(i >= 1600 && i <= 1800){
            line.curve = -2;
          }

          if(i >= 2000 && i <= 2200){
            line.curve = 2;
          }

          if(i >= 2300 && i <= 2400){
            line.curve = 2;
          }

          if(i >= 2400 && i <= 2700){
            line.curve = -0.4;
          }

          if(i >= 2700 && i <= 3000){
            line.curve = 0.4;
          }

          if(i >= 3000 && i <= 3200){
            line.curve = -0.7;
          }

          if(i >= 3300 && i <= 3400){
            line.curve = 2;
          }

          if(i >= 4100 && i <= 4200){
            line.curve = 1.7;
          }

          if(i >= 4350 && i <= 4500){
            line.curve = -1.7;
          }

          if(i >= 4750 && i <= 4900){
            line.curve = 1.4;
          }

          if(i >= 5100 && i <= 5250){
            line.curve = -1.4;
          }

          if(i >= 5400 && i <= 5500){
            line.curve = -1.5;
          }

          if(i >= 5800 && i <= 6000){
            line.curve = 2;
          }

          if(i >= 6300 && i <= 6600){
            line.curve = 1.5;
          }

          if(i >= 6600 && i <= 6900){
            line.curve = -1.8;
          }

          if(i >= 6900 && i <= 7200){
            line.curve = 0.5;
          }

          lines.push_back(line);

      }
      break;
    
    case 3:
      for(int i = 0; i < 5100; i++){
        // solo hay que poner los sprites y las curvas (y la meta)
        Line line;
        line.z = i * segL;

        if(i >= goalPosIni && i <= goalPosEnd){
          line.isGoal = true;
          line.sprite = object[7];
        }

        if(i >= 400 && i <= 700){
            line.curve = 2.5;
        }

        if(i >= 700 && i <= 800){
            line.curve = 3;
        }

        if(i >= 800 && i <= 1000){
            line.curve = -3;
        }

        if(i >= 1000 && i <= 1200){
            line.curve = 3;
        }

        if(i >= 1200 && i <= 1400){
            line.curve = -3;
        }

        if(i >= 1400 && i <= 1600){
            line.curve = 3;
        }

        if(i >= 1600 && i <= 1800){
            line.curve = -3;
        }

        if(i >= 2100 && i <= 2400){
            line.curve = 2.5;
        }

        if(i >= 2500 && i <= 2650){
            line.curve = -1.2;
        }

        if(i >= 2900 && i <= 3200){
            line.curve = 2.7;
        }

        if(i >= 3200 && i <= 3400){
            line.curve = -0.2;
        }

        if(i >= 3400 && i <= 3500){
            line.curve = -2.4;
        }

        if(i >= 3500 && i <= 3750){
            line.curve = 0.8;
        }

        if(i >= 3750 && i <= 3900){
            line.curve = 2.5;
        }

        if(i >= 3900 && i <= 4100){
            line.curve = -0.2;
        }

        if(i >= 4100 && i <= 4300){
            line.curve = -2.2;
        }

        if(i >= 4600 && i <= 4700){
            line.curve = 2.5;
        }

        if(i >= 4700 && i <= 4800){
            line.curve = -2.5;
        }

        if(i >= 4800 && i <= 4900){
            line.curve = 2.5;
        }

        lines.push_back(line);

      }
      break;
    }
    
    maps[j] = lines;
  }
}

void loadTextures(){

}