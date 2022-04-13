#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

extern int width;
extern int height;
extern int roadW;
extern int segL;   // segment length
extern float camD; // camera depth
extern float draw_distance; // empiezan a aparecer en pantalla en el 8
extern int car_width;
extern int car_height;
extern float off_road_allowed;
extern float road_limit;
extern float turn_power;
extern float draft_power;
extern float goalPosIni;
extern float goalPosEnd;
extern int speed;
extern bool marchaBaja;
extern bool pressed;
extern int maxSpeed;
extern bool enHierba;
extern std::array<bool, sf::Keyboard::KeyCount> keyState;
extern int numMaps;
extern bool gameOver;
extern bool perderControl;
extern int animColision;

extern sf::Time tiempoconseguido;
extern bool ultimotiempo;
extern int score;

extern int mapa;