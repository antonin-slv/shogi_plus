#include "Menu.h"

Menu::Menu()
{
    m_param.blanc_bot = true;
    m_param.noir_bot = true;
    m_param.prof_blanc = 2;
    m_param.prof_noir = 2;
    m_param.algo_blanc = 0;
    m_param.algo_noir = 0;
    m_param.quit = false;

    font.loadFromFile("data/Consolas.ttf");
}

void initTexteCentre(RenderWindow & window, Text & texte, int y){
    texte.setFillColor(Color::White);
    texte.setPosition((window.getSize().x-texte.getLocalBounds().width)/2, y+15);
}
Parametre& Menu::boucleMenuPrincipal(sf::RenderWindow & win) {
    bool continuer = true;
    //tout les textes du menu
    Text titre("Shogi", font, 100);
    Text info("Appuyez sur", font, 50);
    Text jouer("1 pour Jouer", font, 50);
    Text simuler("2 pour Simuler", font, 50);
    Text quitter("Echap pour Quitter", font, 50);
    //on les places :
    initTexteCentre(win, titre, 100);
    initTexteCentre(win, info, 300);
    initTexteCentre(win, jouer, 400);
    initTexteCentre(win, simuler, 500);
    initTexteCentre(win, quitter, 600);
    
    do { 
        m_param.mode = 0;
        //affichage
        win.clear(Color::Black);
        win.draw(titre);
        win.draw(info);
        win.draw(jouer);
        win.draw(simuler);
        win.draw(quitter);
        win.display();
        //gestion des evenements
        sf::Event event;
        while (win.pollEvent(event)) {   
            if(event.type == sf::Event::Closed) {   
                continuer = false;
                m_param.quit = true;
                break;
            }
            if(event.type == sf::Event::KeyPressed)
            {   
                sf::Keyboard::Key code = event.key.code;
                
                if (code == sf::Keyboard::Escape) {
                    continuer = false;
                    m_param.quit = true;
                    break;
                }
                if (code == sf::Keyboard::Num1 || code == sf::Keyboard::Numpad1) {
                    //on vide les évènements
                    while(win.pollEvent(event));
                    continuer = boucleMenuJouer(win);
                    break;
                }
                else if (code == sf::Keyboard::Num2 || code == sf::Keyboard::Numpad2) {
                    while(win.pollEvent(event));
                    continuer = boucleMenuSimulation(win);
                    break;
                }
            }
        }
    } while (continuer);
    return m_param;
}

//retourne true si on reste dans le menu, false si on quitte le menu/joue
bool Menu::boucleMenuJouer(sf::RenderWindow & win) {
    //textes du menu
    Text titre("Jouer", font, 100);
    Text info("Appuyez sur", font, 50);
    Text un("1 pour jouer contre un ami", font, 50);
    Text deux("2 pour jouer contre l'ordinateur", font, 50);
    Text trois ("3 pour jouer à la variante", font, 50);
    Text echap("Echap pour retourner au menu Principal", font, 50);
    //on les centres
    initTexteCentre(win, titre, 100);
    initTexteCentre(win, info, 300);
    initTexteCentre(win, un, 400);
    initTexteCentre(win, deux, 500);
    initTexteCentre(win, trois, 600);
    initTexteCentre(win, echap, 700);
    m_param.blanc_bot = false;
    m_param.prof_noir = 3;
    do {
        Event event;
        while(win.pollEvent(event)) {
            if(event.type == Event::Closed) {//on quitte le jeu
                m_param.quit = true;
                return false;
            }
            if(event.type == Event::KeyPressed) {
                sf::Keyboard::Key code = event.key.code;
                
                if (code == sf::Keyboard::Escape) {
                    return true;
                }
                else if (code == sf::Keyboard::Num1 || code == sf::Keyboard::Numpad1) {
                    m_param.blanc_bot = false;
                    m_param.noir_bot = false;
                    return false;
                }
                else if (code == sf::Keyboard::Num2 || code == sf::Keyboard::Numpad2) {
                    m_param.blanc_bot = false;
                    m_param.noir_bot = true;
                    return false;
                }
                else if (code == sf::Keyboard::Num3 || code == sf::Keyboard::Numpad3) {
                    m_param.blanc_bot = false;
                    m_param.noir_bot = true;
                    m_param.mode = 1;
                    return false;
                }
            }
        }

        //affichage
        win.clear(Color::Black);
        win.draw(titre);
        win.draw(info);
        win.draw(un);
        win.draw(deux);
        win.draw(trois);
        win.draw(echap);
        win.display();

    } while(true);
}

bool Menu::boucleMenuSimulation(sf::RenderWindow & win) {

    //textes du menu
    Text titre("Paramétrage Ordinateurs", font, 100);
    Text info("Appuyez sur", font, 50);
    Text min_max_blanc("1 : blanc utilise le MIN_MAX", font, 50);
    Text alphabeta_blanc("2 : blanc utilise l'ALPHA_BETA", font, 50);
    Text min_max_noir("3 : noir utilise le MIN_MAX", font, 50);
    Text alphabeta_noir("4 : noir utilise l'ALPHA_BETA", font, 50);
    Text Lancer("Entrée pour lancer la simulation", font, 50);
    Text echap("Echap pour retourner au menu Principal", font, 50);
    //on les centres
    initTexteCentre(win, titre, 100);
    initTexteCentre(win, info, 300);
    initTexteCentre(win, min_max_blanc, 400);
    initTexteCentre(win, alphabeta_blanc, 500);
    initTexteCentre(win, min_max_noir, 600);
    initTexteCentre(win, alphabeta_noir, 700);
    initTexteCentre(win, Lancer, 800);
    initTexteCentre(win, echap, 900);
    
    //on initialise les paramètres
    m_param.blanc_bot = true;
    m_param.noir_bot = true;
    m_param.prof_blanc = 2;//2 par défaut : jouable
    m_param.prof_noir = 2;
    do {
        Event event;
        while (win.pollEvent(event)) {
            if(event.type == Event::Closed) {//on quitte le jeu
                m_param.quit = true;
                return false;
            }
            if(event.type == Event::KeyPressed) {
                sf::Keyboard::Key code = event.key.code;
                if (code == sf::Keyboard::Escape) {//on retourne au menu principal
                    return true;
                }
                else if (code == sf::Keyboard::Num1 || code == sf::Keyboard::Numpad1) {
                    m_param.algo_blanc = 0;
                }
                else if (code == sf::Keyboard::Num2 || code == sf::Keyboard::Numpad2) {
                    m_param.algo_blanc = 1;
                }
                else if (code == sf::Keyboard::Num3 || code == sf::Keyboard::Numpad3) {
                    m_param.algo_noir = 0;
                }
                else if (code == sf::Keyboard::Num4 || code == sf::Keyboard::Numpad4) {
                    m_param.algo_noir = 1;
                }
                else if (code == sf::Keyboard::Enter) {
                    cout<<"Entrée"<<endl;
                    return false;
                }
            }
        }
        //affichage
        win.clear(Color::Black);
        win.draw(titre);
        win.draw(info);
        win.draw(min_max_blanc);
        win.draw(alphabeta_blanc);
        win.draw(min_max_noir);
        win.draw(alphabeta_noir);
        win.draw(Lancer);
        win.draw(echap);
        win.display();
    } while (true);
    return false;
}
