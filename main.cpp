#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
//#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <stdarg.h>

#include "ImageManager.hpp"
#include "Player.hpp"
#include "Building.hpp"
#include "Cursor.hpp"
#include "Effect.hpp"
#include "System.hpp"
#include "Node.hpp"
#include "Collision.hpp"
#include "Terrain.hpp"
#include "SFGUI/SFGUI.hpp"
#include <time.h>
#include "Localization.h"

void buttonClickContinue(std::shared_ptr<sfg::Window> frame);

int main() {
    std::cout<<"Initialisation"<<std::endl;
    sf::Clock timer;
    Localization loc;
    loc.loadFromFile("locale.ini");
    loc.setLanguage("FR");
    srand(time(NULL));
    std::cout<<"Video.....";
    System window(sf::VideoMode(800,600,32), "Vendetta Reloaded", sf::Style::None);
    window.setFramerateLimit(60);
    window.setSystemCollision(800.f,600.f,8,6);
    sf::View custom_view(sf::FloatRect(0.f,0.f,window.getSize().x, window.getSize().y));
    std::cout<<" Reussite"<<std::endl;
    std::cout<<"Données..."<<std::endl;
    std::cout<<"    Races: ";
    std::map<string, Race> races;
    INIParser ini_donnees;
    ini_donnees.loadFromFile("races.ini");
    std::vector<string> race_names=ini_donnees.getSections();
    for(int i=0; i<race_names.size(); i++)
    {
        Race temp_race;
        temp_race.name=race_names[i];
        temp_race.base_attack=atof(ini_donnees.getValue(race_names[i], "base_attack").c_str());
        temp_race.base_defense=atof(ini_donnees.getValue(race_names[i], "base_defense").c_str());
        temp_race.base_life=atof(ini_donnees.getValue(race_names[i], "base_life").c_str());
        temp_race.base_stamina=atof(ini_donnees.getValue(race_names[i], "base_stamina").c_str());
        temp_race.base_mana=atof(ini_donnees.getValue(race_names[i], "base_mana").c_str());
        temp_race.base_speed=atof(ini_donnees.getValue(race_names[i], "base_speed").c_str());
        races[temp_race.name]=temp_race;
    }
    std::cout<<"OK"<<std::endl;
    std::cout<<" Reussite"<<std::endl;
    std::cout<<"Images....";
    ImageManager manager("vendetta.cfg");
    std::cout<<" Reussite"<<std::endl;
    std::cout<<"Sprites..."<<std::endl;

    std::cout<<"   Terrain: ";
    manager.setTextureRepeated("grass", true);
    Terrain terrain(manager.getPtrTexture("grass"), sf::Vector2f(5000,5000));
    std::cout<<"OK"<<std::endl;

    std::cout<<"   Effects: ";
    std::vector<Effect*> effects;
    effects.push_back(new Effect());
    std::cout<<"OK"<<std::endl;

    std::cout<<"   Cursor: ";
    Cursor curseur(manager.getTexture("fleche2"));
    std::cout<<"OK"<<std::endl;

    std::cout<<"   Characters: ";
    std::vector<Character> sprites;
    sprites.push_back(Character(manager.getTexture("white_boy")));
    sprites[0].setPosition(700.f,200.f);
    sprites[0].setRace(races["Humans"]);
    sprites.push_back(Character(manager.getTexture("black_officer")));
    sprites[1].setPosition(200.f,400.f);
    sprites[1].setRace(races["Humans"]);
    sprites.push_back(Character(manager.getTexture("farmer")));
    sprites[2].setPosition(400.f,200.f);
    sprites[2].setRace(races["Humans"]);
    sprites.push_back(Character(manager.getTexture("red_boy")));
    sprites[3].setPosition(400.f,400.f);
    sprites[3].setRace(races["Humans"]);
    std::cout<<"OK"<<std::endl;

    std::cout<<"   Players: ";
    std::vector<Player> players;
    players.push_back(Player(manager.getTexture("mysterious_blue_man")));
    players[0].setRace(races["Humans"]);
    std::cout<<"OK"<<std::endl;

    std::cout<<"   Buildings: ";
    std::vector<Building> buildings;
    buildings.push_back(Building(manager.getTexture("home1")));
    buildings[0].setPosition(300.f,300.f);
    buildings[0].setEntryPoint(buildings[0].getTextureRect().width/2, buildings[0].getTextureRect().height/2);
    players[0].setOwner(&buildings[0]);
    bool player_try_build=false;
    sf::RectangleShape build_surface;
    build_surface.setOutlineColor(sf::Color::Blue);
    build_surface.setOutlineThickness(3.);
    build_surface.setFillColor(sf::Color::Transparent);
    bool build_possible=true;
    std::cout<<"OK"<<std::endl;

    std::cout<<" Reussite"<<std::endl;
    std::cout<<"Nodes.....";
    Node n_buildings, n_characters, n_players, n_effects, n_interface;
    window.getRootNode()->addNode(&n_buildings);
    window.getRootNode()->addNode(&n_characters);
    window.getRootNode()->addNode(&n_players);
    window.getRootNode()->addNode(&n_effects);
    for(int i=0; i<buildings.size(); i++) {
        n_buildings.addEntity(&buildings[i]);
    }
    for(int i=0; i<sprites.size(); i++) {
        n_characters.addEntity(&sprites[i]);
    }
    for(int i=0; i<players.size(); i++) {
        n_players.addEntity(&players[i]);
    }
    for(int i=0; i<effects.size(); i++) {
        n_effects.addEntity(effects[i]);
    }
    std::cout<<" Reussite"<<std::endl;
    std::cout<<"Input.....";
    std::cout<<" Reussite"<<std::endl;
    std::cout<<"Gui......";

    sfg::SFGUI Gui;
    sfg::Desktop desktop;
    ///Perso GUI
    auto frame_perso=sfg::Window::Create();
    auto layout_v_perso = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    auto label_life = sfg::Label::Create("Life : ");
    auto label_stamina = sfg::Label::Create("Stamina : ");
    auto label_mana = sfg::Label::Create("Mana : ");
    layout_v_perso->Pack(label_life);
    layout_v_perso->Pack(label_stamina);
    layout_v_perso->Pack(label_mana);
    frame_perso->SetTitle( "Perso Stats" );
    frame_perso->Add(layout_v_perso);
    desktop.Add(frame_perso);
    ///Building GUI
    auto frame_building=sfg::Window::Create();
    auto layout_v_building = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    auto label_owner = sfg::Label::Create("[OWNER_NAME]");
    auto label_building_life = sfg::Label::Create("[BUILDING_LIFE]/[BUILDING_LIFE_MAX]");
    layout_v_building->Pack(label_owner);
    layout_v_building->Pack(label_building_life);
    frame_building->SetTitle( "[BUILDING_NAME]" );
    frame_building->Add(layout_v_building);
    frame_building->Show(false);
    desktop.Add(frame_building);
    ///Construction GUI
    auto frame_build=sfg::Window::Create();
    auto layout_table_build = sfg::Table::Create();
    frame_build->SetTitle( "List Constructions" );
    frame_build->Add(layout_table_build);
    desktop.Add(frame_build);
    ///Menu GUI
    auto frame_menu=sfg::Window::Create();
    auto layout_v_menu = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    auto button_continue = sfg::Button::Create(loc.tr("menu_continue"));
    auto button_options = sfg::Button::Create(loc.tr("menu_options"));
    auto button_quit = sfg::Button::Create(loc.tr("menu_quit"));
    layout_v_menu->Pack(button_continue);
    layout_v_menu->Pack(button_options);
    layout_v_menu->Pack(button_quit);
    button_continue->GetSignal( sfg::Button::OnLeftClick ).Connect(std::bind( &buttonClickContinue, frame_menu));
    button_quit->GetSignal( sfg::Button::OnLeftClick ).Connect(std::bind(&sf::RenderWindow::close, &window));
    frame_menu->SetTitle(loc.tr("menu_main"));
    frame_menu->Add(layout_v_menu);
    frame_menu->SetRequisition(sf::Vector2f(150., 250.));
    frame_menu->SetPosition(sf::Vector2f((float)(window.getVideoMode().width)/2-75, (float)(window.getVideoMode().height)/2-125));
    frame_menu->Show(false);
    desktop.Add(frame_menu);
    std::cout<<" Reussite"<<std::endl;
    std::cout<<"Fin Initialisation"<<std::endl;

    window.initializeCol();

    std::map<int, bool> keys_pressed_past;
    keys_pressed_past[sf::Keyboard::Escape]=false;

    while (window.isOpen()) {
        sf::Event event;
        ///Déplacement aléatoire de l'IA
        for(int i=0; i<sprites.size(); i++) {
            if(!sprites.at(i).isMoving()) {
                sprites.at(i).goTo(sf::Vector2f(float (rand() % 801), float (rand() % 601)));
            }
        }
        curseur.setIcon(manager.getTexture("fleche2"));
        curseur.setCursorPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        while (window.pollEvent(event)) {
            ///Ferme la fenetre quand on clique sur la croix
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            ///Génère un effet slash sur la map
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E) {
                effects.push_back(new Effect(manager.getTexture("slash"),6,5));
                effects[effects.size()-1]->attachEntity(&players[0]);
                n_effects.addEntity(effects[effects.size()-1]);
                std::cout<<"Effect created"<<std::endl;
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                frame_menu->Show(!frame_menu->IsGloballyVisible());
            }
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){curseur.setIcon(manager.getTexture("fleche1"));}
            else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                bool action=false;
                sf::Vector2f pos_click(curseur.getPosition());
                if(pos_click.x>0 && pos_click.y>0) {
                    ///try to build
                    bool onGui=false;
                    if(frame_perso->IsGloballyVisible() && !onGui){
                        sf::FloatRect frame_bounds(window.mapPixelToCoords((sf::Vector2i)(frame_perso->GetAbsolutePosition())).x,
                                                    window.mapPixelToCoords((sf::Vector2i)(frame_perso->GetAbsolutePosition())).y,
                                                    frame_perso->GetAllocation().width,
                                                    frame_perso->GetAllocation().height);
                        if(frame_bounds.contains(curseur.getPosition())){onGui=true;}
                    }
                    if(!onGui && !frame_menu->IsGloballyVisible()) {
                        if(player_try_build) {
                            if(build_possible) {
                                for(int i=0; i<buildings.size(); i++) {
                                    if(&buildings[i]==players[0].getOwner()) {
                                        n_buildings.remove(&buildings[i]);
                                        buildings.erase(buildings.begin()+i);
                                    }
                                }
                                buildings.push_back(Building(manager.getTexture("home1")));
                                buildings[buildings.size()-1].setPosition(curseur.getPosition());
                                buildings[buildings.size()-1].setEntryPoint(buildings[0].getTextureRect().width/2, buildings[0].getTextureRect().height/2);
                                n_buildings.addEntity(&buildings[buildings.size()-1]);
                                player_try_build=!player_try_build;
                                players[0].setOwner(&buildings[buildings.size()-1]);
                                players[0].orderToRepair(players[0].getOwner());
                            }
                        } else {
                            for(int i=0; i<sprites.size(); i++) {
                                if(sprites[i].getGlobalBounds().contains(curseur.getPosition().x, curseur.getPosition().y)) {
                                    players[0].orderToAttack(&sprites[i]);
                                    action=true;
                                    break;
                                }
                            }
                            if(!action) {
                                for(int i=0; i<buildings.size(); i++) {
                                    if(buildings[i].getGlobalBounds().contains(curseur.getPosition().x, curseur.getPosition().y)) {
                                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                                            players[0].orderToRepair(&buildings[i]);
                                            action=true;
                                        } else {
                                            players[0].orderToEnter(&buildings[i]);
                                            action=true;
                                        }
                                        break;
                                    }
                                }
                            }
                            if(!action) {
                                if(pos_click.x<0) {
                                    pos_click.x=0;
                                }
                                if(pos_click.y<0) {
                                    pos_click.y=0;
                                }
                                players[0].goTo(pos_click);
                            }
                        }
                    }
                }
            }
            desktop.HandleEvent( event );
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right) {
                if(!frame_menu->IsGloballyVisible()){
                    if(player_try_build) {
                    player_try_build=false;
                    }
                }
            }
            ///Remet le curseur à la position de la souris avec la texture normale
            if(!frame_menu->IsGloballyVisible()){
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B) {
                    /*build_surface.setSize(sf::Vector2f(buildings[0].getSize()));
                    player_try_build=true;*/
                    if(players[0].getBuildingIn()!=0 && !frame_building->IsGloballyVisible()){
                            frame_building->SetTitle("Building Test");
                            label_owner->SetText("Test Owner");
                            label_building_life->SetText("Integrity Owner");
                            frame_building->Show(true);
                    }
                    else{frame_building->Show(false);}
                }
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    players[0].setRace(races["Elves"]);
                }
                ///Deplace le joueur
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    if(players[0].getPosition().y>0) {
                    players[0].goUp();
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    if(players[0].getPosition().y<600) {
                        players[0].goDown();
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    if(players[0].getPosition().x>0) {
                        players[0].goLeft();
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    if(players[0].getPosition().x<800) {
                        players[0].goRight();
                    }
                }
            }
        }
        if(!frame_menu->IsGloballyVisible()){
            for(unsigned int i=0; i<buildings.size(); i++) {            ///Buildings update
                buildings[i].update();
            }
            for(unsigned int i=0; i<sprites.size(); i++) {              ///Characters update
                sprites[i].update();
            }
            for(unsigned int i=0; i<players.size(); i++) {              ///Players update
                players[i].update();
            }
            for(unsigned int i=0; i<effects.size(); i++) {              ///Effects update
                effects[i]->update();
                if(!effects[i]->getActive()) {
                    std::vector<Effect*>::iterator it_effect;
                    it_effect=effects.begin()+i;
                    effects.erase(it_effect);
                }
            }
        }
        else{player_try_build=false;} ///Annule la tentative de construction si il y a le menu principal
        window.clear();
        terrain.draw(&window);
        window.drawAll();
        if(player_try_build) {                                      ///Detection collisions pour construire + draw
            build_possible=true;
            for(int i=0; i<buildings.size(); i++) {
                if(build_surface.getGlobalBounds().intersects(buildings[i].getGlobalBounds())) {
                    build_possible=false;
                    build_surface.setOutlineColor(sf::Color::Red);
                }
            }
            if(build_possible && !terrain.getGlobalBounds().intersects(build_surface.getGlobalBounds())) {
                build_possible=false;
                build_surface.setOutlineColor(sf::Color::Red);
            }
            if(build_possible) {
                build_surface.setOutlineColor(sf::Color::Blue);
            }
            build_surface.setPosition(curseur.getPosition());
            window.draw(build_surface);
        }
        label_life->SetText("HP : "+std::to_string(players.at(0).getLife()));
        label_stamina->SetText("Stamina : "+std::to_string(players.at(0).getStamina()));
        label_mana->SetText("Mana : "+std::to_string(players.at(0).getMana()));
        desktop.Update( 1.0f );
        Gui.Display(window);

        curseur.draw(&window);
        custom_view.setCenter(players[0].getPosition());
        window.setView(custom_view);
        window.display();
    }
    effects.clear();
    std::cout<<"Fin du programme"<<std::endl;
    return 0;
}

void buttonClickContinue(std::shared_ptr<sfg::Window> frame) {
    frame->Show(!frame->IsGloballyVisible());
}
