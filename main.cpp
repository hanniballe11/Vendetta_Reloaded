#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cstdlib>
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

sf::VideoMode loadVideoMode();

int main()
{
	std::cout<<"Initialisation"<<std::endl;
	std::cout<<"Video.....";
	System window(sf::VideoMode(800,600,32), "Vendetta Reloaded", sf::Style::None);
	window.setFramerateLimit(60);
	window.setSystemCollision(800.f,600.f,8,6);
	sf::View custom_view(sf::FloatRect(0.f,0.f,window.getSize().x, window.getSize().y));
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
    sprites.push_back(Character(manager.getTexture("black_officer")));
    sprites[1].setPosition(200.f,400.f);
    sprites.push_back(Character(manager.getTexture("farmer")));
    sprites[2].setPosition(400.f,200.f);
    sprites.push_back(Character(manager.getTexture("red_boy")));
    sprites[3].setPosition(400.f,400.f);
    std::cout<<"OK"<<std::endl;

    std::cout<<"   Players: ";
    std::vector<Player> players;
    players.push_back(Player(manager.getTexture("mysterious_blue_man")));
    std::cout<<"OK"<<std::endl;

    std::cout<<"   Buildings: ";
    std::vector<Building> buildings;
    buildings.push_back(Building(manager.getTexture("home1")));
    buildings[0].setPosition(300.f,300.f);
    buildings[0].setEntryPoint(buildings[0].getTextureRect().width/2, buildings[0].getTextureRect().height/2);
    buildings[0].setOwner(&players[0]);
    std::cout<<"OK"<<std::endl;

    std::cout<<" Reussite"<<std::endl;
    std::cout<<"Nodes.....";
    Node n_buildings(&window), n_characters(&window), n_players(&window), n_effects(&window), n_interface(&window);
    window.getRootNode()->addNode(&n_buildings);
    window.getRootNode()->addNode(&n_characters);
    window.getRootNode()->addNode(&n_players);
    window.getRootNode()->addNode(&n_effects);
    //window.getRootNode()->addNode(&n_interface);
    for(int i=0; i<buildings.size(); i++){n_buildings.addEntity(&buildings[i]);}
    for(int i=0; i<sprites.size(); i++){n_characters.addEntity(&sprites[i]);}
    for(int i=0; i<players.size(); i++){n_players.addEntity(&players[i]);}
    for(int i=0; i<effects.size(); i++){n_effects.addEntity(effects[i]);}
    std::cout<<" Reussite"<<std::endl;
    std::cout<<"Input.....";
    std::cout<<" Reussite"<<std::endl;

    std::cout<<"Fin Initialisation"<<std::endl;

    window.initializeCol();

    while (window.isOpen()){
        sf::Event event;
        for(int i=0; i<sprites.size(); i++){if(!sprites.at(i).isMoving()){sprites.at(i).goTo(sf::Vector2f(float (rand() % 801), float (rand() % 601)));}}
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){window.close();}
            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::E)){
            	effects.push_back(new Effect(manager.getTexture("slash"),6,5, sf::Vector2f(250.f,250.f)));
            	n_effects.addEntity(effects[effects.size()-1]);
            	std::cout<<"Effect created"<<std::endl;
            }
        }
        curseur.setIcon(manager.getTexture("fleche2"));
        //curseur.setCursorPosition(input.GetMouseX(), input.GetMouseY());
        curseur.setCursorPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){window.close();}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){if(players[0].getPosition().y>0){players[0].goUp();}}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){if(players[0].getPosition().y<600){players[0].goDown();}}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){if(players[0].getPosition().x>0){players[0].goLeft();}}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){if(players[0].getPosition().x<800){players[0].goRight();}}
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            bool action=false;
            sf::Vector2f pos_click(curseur.getPosition());
            curseur.setIcon(manager.getTexture("fleche1"));
            if(pos_click.x>0 && pos_click.y>0){
                for(int i=0; i<sprites.size(); i++){
                    if(sprites[i].getGlobalBounds().contains(curseur.getPosition().x, curseur.getPosition().y)){
                        players[0].attack(&sprites[i]);
                        action=true;
                        break;}
                }
                if(!action){
                    for(int i=0; i<buildings.size(); i++){
                        if(buildings[i].getGlobalBounds().contains(curseur.getPosition().x, curseur.getPosition().y)){
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                                players[0].repair(&buildings[i]);
                                action=true;}
                            else{
                                players[0].enter(&buildings[i]);
                                action=true;}
                            break;}
                    }
                }
            }
            if(!action){
                if(pos_click.x<0){pos_click.x=0;}
                if(pos_click.y<0){pos_click.y=0;}
                players[0].goTo(pos_click);}

        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        	sf::Vector2f pos_click(curseur.getPosition().x, curseur.getPosition().y);
            players[0].setPosition(pos_click);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){players[0].setLife(players[0].getLife()-1);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){players[0].setLife(players[0].getLife()+1);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){buildings[0].setIntegrity(0);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){players[0].attack(&buildings[0]);}

        for(unsigned int i=0; i<buildings.size(); i++){buildings[i].update();}
        for(unsigned int i=0; i<sprites.size(); i++){sprites[i].update();}
        for(unsigned int i=0; i<players.size(); i++){players[i].update();}
        for(unsigned int i=0; i<effects.size(); i++){
            effects[i]->update();
            if(!effects[i]->getActive()){
                std::vector<Effect*>::iterator it_effect;
                it_effect=effects.begin()+i;
                effects.erase(it_effect);}}
        window.clear();
        terrain.draw(&window);
        window.draw();
        curseur.draw(&window);
        //sf::View=window.getDefaultView().setCenter(players[0].getPosition());
        custom_view.setCenter(players[0].getPosition());
        window.setView(custom_view);
        window.display();
    }
    window.getSystemCollision()->update();
    effects.clear();
    std::cout<<"Fin du programme"<<std::endl;
    return 0;
}

sf::VideoMode loadVideoMode(){
	std::ifstream config_file("config.ini", std::ios::in);  // on ouvre le fichier en lecture
	if(config_file){
		std::string content;
		while(getline(config_file, content)){;}
		config_file.close();
	}
	return sf::VideoMode();

}
