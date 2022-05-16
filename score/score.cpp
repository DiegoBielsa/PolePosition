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



void leerPuntuaciones(string puntuaciones[], int numero,int iaMode) {
    int j = iaMode;
    fstream f;
    string number = inttostring(numero);
    f.open("ficheros/puntuaciones"+number+".txt");
    if (f.is_open()) {
        int i = 0;
        string cadena;
        while (j > 0) {
            getline(f, cadena, '\n');       //leemos las anteriores ias
            j--;
        }
        getline(f, cadena, ' ');
        while (!f.eof() && i < 6) {
            puntuaciones[i] = cadena;
            if (i == 5) {
                getline(f, cadena, '\n');

            }
            else {
                getline(f, cadena, ' ');
            }
            i++;

        }
        puntuaciones[6] = cadena;
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
    f.open("ficheros/limites.txt");
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

void drawLetters(RenderWindow& app, string puntuaciones[], int velocidad, int puntu, Time& elapsed, int& limite,bool& gameOver, Time& final, bool& noClasifica,bool primeravez) {
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
        noClasifica = true;
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
    final = tiempo;
    int seconds2 = tiempo.asSeconds();
    int mili = tiempo.asMilliseconds();
    while (mili > 1000) {
        mili = mili - 1000;
    }

    String minu = inttostring(mili);
    String sec = inttostring(seconds2);
    lapnumber.setString(sec + ". " + minu);
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
    if (primeravez == true) {
        lapnumber.setString("0. 0");
        String cadena = inttostring(limite);
        timenumber.setString(cadena);

    }



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
void calcularScore(int& score, int velocidad,int lim,int limite,bool gameOver,int iaMode) {
    int multiIa = iaMode + 1;
    if (gameOver != true) {
        int v = velocidad - 50;
        if (v < 0) {
            v = 0;
        }
        int punt = 1 * v/10;
        score = score + punt;
    }
    else if (gameOver == true && control == false) {
        control = true;
        double multi= -1*(double(lim) - double(limite)) / 10;
        if (multi < 1.0) {
            multi = 1.0;
        }
        score = score * multi * multiIa;
    }
}
void escribirPuntuaciones(string puntuaciones[],int puntuacion,int numero,int& posicionPuntuacion,int iaMode) {
    string number = inttostring(numero);
    std::vector<std::string> copia;
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
    posicionPuntuacion = i;
    if (esMejor == true) {
        for (int j = 6;j > i;j--) { //desplazamos todos a la derecha
            puntuaciones[j] = puntuaciones[j - 1];
        }
        puntuaciones[i] = inttostring(puntuacion);
        int j = iaMode;
        fstream f;
        f.open("ficheros/puntuaciones" + number + ".txt");
        if (f.is_open()) {
            string cadena = "";
            getline(f, cadena, '\n');
            while (!f.eof()) {
                copia.push_back(cadena);
                getline(f, cadena, '\n');
            }
            copia.push_back(cadena);


            f.close();

        }
        else {
            cerr << "no se ha podido abrir fichero puntuaciones" << endl;
        }

        copia.size();
        copia[iaMode] = puntuaciones[0] + " " + puntuaciones[1] + " " + puntuaciones[2] + " " + puntuaciones[3] + " " + puntuaciones[4] + " " + puntuaciones[5] + " " + puntuaciones[6];

        ofstream ofs;
        ofs.open("ficheros/puntuaciones" + number + ".txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();

        fstream f2;
        f2.open("ficheros/puntuaciones" + number + ".txt");
        if (f2.is_open()) {

            f2 << copia[0] << "\n";
            f2 << copia[1] << "\n";
            f2 << copia[2] << "\n";



            f2.close();
        }
        else { cerr << "no se ha podido abrir fichero puntuaciones" << endl; }
 
    }
   

}

void escribirNombres(string nombres[], int numero,int iaMode) {
    int j = iaMode;
    std::vector<std::string> copia;
    string number = inttostring(numero);
        fstream f;
        f.open("ficheros/nombres" + number + ".txt");
        if (f.is_open()) {
            string cadena = "";
                getline(f, cadena, '\n');
                while (!f.eof()) {
                    copia.push_back(cadena);
                    getline(f, cadena, '\n');
                }
                copia.push_back(cadena);

               
            f.close();
            
        }
        else {
            cerr << "no se ha podido abrir fichero nombres" << endl;
        }
      
        copia.size();
        copia[iaMode] = nombres[0] + " " + nombres[1] + " " + nombres[2] + " " + nombres[3] + " " + nombres[4] + " " + nombres[5] + " " + nombres[6];
    
        ofstream ofs;
        ofs.open("ficheros/nombres" + number + ".txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();

        fstream f2;
        f2.open("ficheros/nombres" + number + ".txt");
        if (f2.is_open()) {
            
            f2 << copia[0] << "\n";
            f2 << copia[1] << "\n";
            f2 << copia[2] << "\n";



            f2.close();
        }
        else { cerr << "no se ha podido abrir fichero nombres2" << endl; }


}

void leerNombres(string nombres[], int numero,int iaMode) {
    int j = iaMode;
    fstream f;
    string number = inttostring(numero);
    f.open("ficheros/nombres" + number + ".txt");
    if (f.is_open()) {
        int i = 0;
        string cadena;
        while (j > 0) {
            getline(f, cadena, '\n');       //leemos las anteriores ias
            j--;
        }
        getline(f, cadena, ' ');
        while (!f.eof() && i < 6) {
            nombres[i] = cadena;
            if (i == 5) {
                getline(f, cadena, '\n');

            }
            else{
                getline(f, cadena, ' ');
            }
            i++;
            
        }
        nombres[6] = cadena;
       
        f.close();

    }
    else {
        cerr << "no se ha podido abrir fichero nombres3" << endl;
    }

}


void leerClasificaciones(string clas[], int numero, int iaMode) {
    int j = iaMode;
    fstream f;
    string number = inttostring(numero);
    f.open("ficheros/clasificaciones" + number + ".txt");
    if (f.is_open()) {
        int i = 0;
        string cadena;
        while (j > 0) {
            getline(f, cadena, '\n');       //leemos las anteriores ias
            j--;
        }
        getline(f, cadena, ' ');
        while (!f.eof() && i < 7) {
            clas[i] = cadena;
            if (i == 6) {
                getline(f, cadena, '\n');

            }
            else {
                getline(f, cadena, ' ');
            }
            i++;

        }
        clas[7] = cadena;

        f.close();

    }
    else {
        cerr << "no se ha podido abrir fichero clasificaciones" << endl;
    }

}

void calcularPosclasificacion(string clas[], Time tiempo, int& posicionClasi, bool noClasifica) {
    if (noClasifica == true) {
        posicionClasi = 8;
    }
    else {
        bool esMejor = false;
        int i = 0;
        int seconds2 = tiempo.asSeconds();
        int mili = tiempo.asMilliseconds();
        while (mili > 1000) {
            mili = mili - 1000;
        }

        string minu = inttostring(mili);
        string sec = inttostring(seconds2);
        string mix = (sec + "," + minu);
        int puntuacion = stringtoint(mix);
        while (!esMejor && i < 7) {
            int c = stringtoint(clas[i]);
            if (puntuacion < c) {
                esMejor = true;

            }
            else {
                i++;
            }
        }
        posicionClasi = i;

    }
}

void calcularBonusExtra(int posicionSalida, int iaMode,int& bonus) {
    bonus = 0;
    if (posicionSalida < 7) {
        int i = posicionSalida;
        while (i < 7) {
            bonus = bonus + 1000;
            i++;
        }
        bonus = bonus * (iaMode + 1);
    }
    else {
        bonus = 0;
    }
}

void hacerPausa(RenderWindow& app, bool& salir, bool& terminar,bool& pausa,Clock& clock) {
  
    sf::Text texto1;

    sf::Font font;
    font.loadFromFile("retro.ttf");
    texto1.setFont(font);
    texto1.setString("ARE YOU SURE YOU WANT TO EXIT?");
    texto1.setCharacterSize(30);
    texto1.setPosition(350, 350);
    texto1.setFillColor(sf::Color::White);
    Vector2f tamayo(700, 300);
    RectangleShape botonatras(tamayo);
    botonatras.setPosition(200, 300);
    botonatras.setFillColor(Color(44, 76, 116));
    botonatras.setOutlineThickness(1.5);

    bool fin = false;

    if (clock.getElapsedTime().asSeconds() > 0.1f) { //sin esto se pasa de "estados"
        clock.restart();
        if (salir == 0) { //NO
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                salir = 1;

            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                fin = true;
            }
        }
        else if (salir == 1) {//yes
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                salir = 0;

            }
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                fin = true;
            }
        }
    }
        app.draw(botonatras);
        app.draw(texto1);
        if (fin == true) {
            if (salir == true) {
                terminar = true;
            }
            else { //NO
                terminar = false;
                pausa = false;
            }
        }
    
}

void eleccionPausa(RenderWindow& app, bool& salir,int& color) {
    sf::Text texto1;
    sf::Text texto2;

    sf::Font font;
    font.loadFromFile("retro.ttf");
    texto1.setFont(font);
    texto1.setString("YES");
    texto1.setCharacterSize(60);
    texto1.setPosition(360, 470);
    texto1.setFillColor(sf::Color::White);

    texto2.setFont(font);
    texto2.setString("NO");
    texto2.setCharacterSize(60);
    texto2.setPosition(670, 470);
    texto2.setFillColor(sf::Color::White);

    Vector2f tamayo(200, 100);
    RectangleShape botonyes(tamayo);
    botonyes.setPosition(300, 450);
    botonyes.setFillColor(Color(44, 76, 116));
    botonyes.setOutlineThickness(1.5);

    RectangleShape botonno(tamayo);
    botonno.setPosition(590, 450);
    botonno.setFillColor(Color(44, 76, 116));
    botonno.setOutlineThickness(1.5);

        if (salir == 1) {//yes
            if (color == 0 || color == 1) {
                texto1.setFillColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                texto1.setFillColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                texto1.setFillColor(sf::Color::White);
                color++;
            }
            else { //rojo
                color = 0;
            }
        }
        else {//no
            if (color == 0 || color == 1) {
                texto2.setFillColor(sf::Color::Blue);
                color++;
            }

            else if (color == 2 || color == 3) {
                texto2.setFillColor(sf::Color::Yellow);
                color++;
            }
            else if (color == 4 || color == 5 || color == 6) {
                texto2.setFillColor(sf::Color::White);
                color++;
            }
            else { //rojo
                color = 0;
            }

        }
  
    app.draw(botonyes);
    app.draw(botonno);
    app.draw(texto1);
    app.draw(texto2);
}