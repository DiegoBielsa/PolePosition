#include "../globals/globals.hpp"
#include "../carSprite/carSprite.hpp"
#include "../init/init.hpp"
#include "../functions/functions.hpp"
#include <thread>


using namespace std;
using namespace sf;

void drawQuad(RenderWindow &w, Color c, int x1, int y1, int w1, int x2, int y2, int w2);

void manageKeys(float &playerX, int &speed, int &H, carSprite &car, std::vector<Line>& lines, int &startPos,  std::vector<Sound>& sounds, int volume);

void updateVars(RenderWindow& app, int &pos, int &startPos, int &camH, std::vector<Line>& lines, float &playerX , int &maxy, float& x, float& dx, int& speed, int N, int H, Sprite& sBackground, carSprite &car);

void drawRoad(RenderWindow& app, int& startPos, float& playerX, std::vector<Line>& lines, int& N, float& x, float& dx, int& maxy, int& camH);

void drawObjects(RenderWindow& app, int &startPos, std::vector<Line>& lines, int &N, carSprite &car, std::vector<Sound>& sounds, int volume);

void drawGear(RenderWindow& app, bool marcha_baja, Texture& marcha);

void comprobarMeta(int& startPos,  float& goalPosIni, bool& metacruz,int vel);

void IA_control(std::vector<Line>& lines, int linePos[], float XPos[], carSpriteIA cars[], int numCars, int iaMode, std::thread threads[]);
