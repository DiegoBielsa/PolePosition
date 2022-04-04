#include "score.hpp"

using namespace std;

bool control = false;
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



void leerPuntuaciones(string puntuaciones[]) {

    fstream f;
    f.open("puntuaciones.txt");
    if (f.is_open()) {
        int i = 0;
        string cadena;
        getline(f, cadena, '\n');
        while (!f.eof() && i < 7) {
            puntuaciones[i] = cadena;
            i++;
            getline(f, cadena, '\n');
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

int stringtoint(string s) {

    stringstream degree(s);

    int x = 0;
    degree >> x;
    return x;
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

void drawLetters(RenderWindow& app, string puntuaciones[], int velocidad, int puntu, Time& elapsed, int& limite,bool& gameOver) {
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
    int resta = limite - seconds;
    if (gameOver == true) {
        timenumber.setString("0");
    }
    else if (resta >= 0) {
        String lim = inttostring(resta);
        timenumber.setString(lim);
    }
    else {
        timenumber.setString("0");
        gameOver = true;
    }

    Time tiempo;
    int punt;
    if (gameOver == true && ultimotiempo==false) {
        ultimotiempo = true;
        tiempoconseguido = elapsed;
        tiempo = tiempoconseguido;
        
    }
    else if (gameOver == true) {
        tiempo = tiempoconseguido;
    }
    else { // no ha terminado
        tiempo = elapsed;

    }
    int seconds2 = tiempo.asSeconds();
    int mili = tiempo.asMilliseconds();
    while (mili > 1000) {
        mili = mili - 1000;
    }

    String minu = inttostring(mili);
    String sec = inttostring(seconds2);
    lapnumber.setString(sec + "''" + minu);
    score.setString("SCORE");
    String puntuacion= inttostring(puntu);
    scorenumber.setString(puntuacion);

  
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
void calcularScore(int& score, int velocidad,int lim,int limite,bool gameOver) {
    if (gameOver != true) {
        int v = velocidad - 50;
        if (v < 0) {
            v = 0;
        }
        int punt = 1 * v;
        score = score + punt;
    }
    else if (gameOver == true && control == false) {
        control = true;
        double multi= -1*(lim - limite) / 10;
        if (multi < 1.0) {
            multi = 1.0;
        }
        score = score * multi;
    }
}
void escribirPuntuaciones(string puntuaciones[],int puntuacion) {
    bool esMejor = false;
    int i = 0;
    while(!esMejor && i<7) {
        int c = stringtoint(puntuaciones[i]);
        if (puntuacion > c) {
            esMejor = true;
        }
        else {
            i++;
        }
    }
    if (esMejor == true) {
        for (int j = 6;j > i;j--) { //desplazamos todos a la derecha
            puntuaciones[j] = puntuaciones[j - 1];
        }
        puntuaciones[i] = inttostring(puntuacion);
        fstream f;
        f.open("puntuaciones.txt");
        if (f.is_open()) {
            int z = 0;
            while ( z < 7) {
                f << puntuaciones[z];
                f << '\n';
                z++;
            }
            

            f.close();

        }
        else {
            cerr << "no se ha podido abrir fichero puntuaciones" << endl;
        }
    }
   

}
