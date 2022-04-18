#include "../globals/globals.hpp"
#include "../Line/Line.hpp"
#include <SFML/Audio.hpp>
#include <fstream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

void setConfig();

void setMaps(std::vector<std::vector<Line>>& maps, Sprite object[]);

void setSounds(std::vector<Sound>& sounds);