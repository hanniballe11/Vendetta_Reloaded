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

int main()
{
	std::cout<<"Initialisation"<<std::endl;
	std::cout<<"Video.....";
	System window(sf::VideoMode(800,600,32), "Vendetta Reloaded", sf::Style::None);
	window.setFramerateLimit(60);
	window.setSystemCollision(800.f,600.f,8,6);
	sf::View custom_view(sf::FloatRect(0.f,0.f,window.getSize().x, window.getSize().y));
	sf::Clock timer;
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
    //window.getRootNode()->addNode(&n_interface);
    for(int i=0; i<buildings.size(); i++){n_buildings.addEntity(&buildings[i]);}
    for(int i=0; i<sprites.size(); i++){n_characters.addEntity(&sprites[i]);}
    for(int i=0; i<players.size(); i++){n_players.addEntity(&players[i]);}
    for(int i=0; i<effects.size(); i++){n_effects.addEntity(effects[i]);}
    std::cout<<" Reussite"<<std::endl;
    std::cout<<"Input.....";
    std::cout<<" Reussite"<<std::endl;
    std::cout<<"Gui......";

    sfg::SFGUI Gui;
    auto frame=sfg::Window::Create();
    sfg::Desktop desktop;
    auto layout_v = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    auto label_life = sfg::Label::Create("Life : ");
    auto label_stamina = sfg::Label::Create("Stamina : ");
    auto label_mana = sfg::Label::Create("Mana : ");
    layout_v->Pack(label_life);
    layout_v->Pack(label_stamina);
    layout_v->Pack(label_mana);
    frame->SetTitle( "Perso Stats" );
    frame->Add(layout_v);
    desktop.Add(frame);
    //frame->GetSignal(sfg::Widget::OnMouseMove).Connect(std::bind( &test, label));
    //frame->GetSignal(sfg::Widget::OnMouseLeave).Connect(std::bind( &test2, label));
    std::cout<<" Reussite"<<std::endl;
    std::cout<<"Fin Initialisation"<<std::endl;

    window.initializeCol();

    while (window.isOpen()){
        sf::Event event;
        for(int i=0; i<sprites.size(); i++){if(!sprites.at(i).isMoving()){sprites.at(i).goTo(sf::Vector2f(float (rand() % 801), float (rand() % 601)));}}
        while (window.pollEvent(event)){
             desktop.HandleEvent( event );
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
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && timer.getElapsedTime().asMilliseconds()>500){
            timer.restart();
            bool action=false;
            sf::Vector2f pos_click(curseur.getPosition());
            curseur.setIcon(manager.getTexture("fleche1"));
            if(pos_click.x>0 && pos_click.y>0){
                ///try to build
                if(player_try_build)
                {
                    if(build_possible)
                    {
                        for(int i=0; i<buildings.size(); i++){if(&buildings[i]==players[0].getOwner()){n_buildings.remove(&buildings[i]); buildings.erase(buildings.begin()+i);}}
                        buildings.push_back(Building(manager.getTexture("home1")));
                        buildings[buildings.size()-1].setPosition(curseur.getPosition());
                        buildings[buildings.size()-1].setEntryPoint(buildings[0].getTextureRect().width/2, buildings[0].getTextureRect().height/2);
                        n_buildings.addEntity(&buildings[buildings.size()-1]);
                        player_try_build=!player_try_build;
                        players[0].setOwner(&buildings[buildings.size()-1]);
                        players[0].repair(players[0].getOwner());
                    }
                }
                else
                {
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
                    if(!action){
                        if(pos_click.x<0){pos_click.x=0;}
                        if(pos_click.y<0){pos_click.y=0;}
                        players[0].goTo(pos_click);}
                }
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        	if(player_try_build){player_try_build=false;}
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){players[0].setLife(players[0].getLife()-1);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){players[0].setLife(players[0].getLife()+1);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){buildings[0].setIntegrity(0);}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){players[0].attack(&buildings[0]);}
        ///Build Building
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        {
            build_surface.setSize(sf::Vector2f(buildings[0].getSize()));
            player_try_build=true;
        }

        for(unsigned int i=0; i<buildings.size(); i++){buildings[i].update();}
        for(unsigned int i=0; i<sprites.size(); i++){sprites[i].update();}
        for(unsigned int i=0; i<players.size(); i++){players[i].update();}
        for(unsigned int i=0; i<effects.size(); i++){
            effects[i]->update();
            if(!effects[i]->getActive()){
                std::vector<Effect*>::iterator it_effect;
                it_effect=effects.begin()+i;
                effects.erase(it_effect);}}
        if(player_try_build)
        {
            build_possible=true;
            for(int i=0; i<buildings.size(); i++)
            {
                if(build_surface.getGlobalBounds().intersects(buildings[i].getGlobalBounds())){build_possible=false; build_surface.setOutlineColor(sf::Color::Red);}
            }
            if(build_possible && !terrain.getGlobalBounds().intersects(build_surface.getGlobalBounds()))
                    {build_possible=false; build_surface.setOutlineColor(sf::Color::Red);}
            if(build_possible){build_surface.setOutlineColor(sf::Color::Blue);}
        }
        window.clear();
        terrain.draw(&window);
        window.drawAll();
        if(player_try_build){build_surface.setPosition(curseur.getPosition()); window.draw(build_surface);}
        label_life->SetText("HP : "+std::to_string(players.at(0).getLife()));
        label_stamina->SetText("Stamina : "+std::to_string(players.at(0).getStamina()));
        label_mana->SetText("Mana : "+std::to_string(players.at(0).getMana()));
        desktop.Update( 1.0f );
        Gui.Display(window);

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
