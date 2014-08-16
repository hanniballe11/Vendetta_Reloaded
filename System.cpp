/*
 * System.cpp
 *
 *  Created on: 15 juil. 2012
 *      Author: Erwann
 */

#include "System.hpp"

System::System() : sf::RenderWindow(){
	m_mode=sf::VideoMode();
	m_window_style=0;
	setMouseCursorVisible(false);
	root_node=new Node(this);
	base_col=0;
}
System::System(sf::VideoMode Mode, const std::string &Title, sf::Uint32 Style, const sf::ContextSettings &Params) : sf::RenderWindow(Mode, Title, Style, Params){
	m_mode=Mode;
	m_title=Title;
	m_window_style=Style;
	setMouseCursorVisible(false);
	root_node=new Node(this);
	base_col=0;
}
System::~System(){
    root_node=0;
	delete root_node;
	if(base_col){delete base_col;}
}
void System::draw(){root_node->draw();}
Collision* System::getSystemCollision(){
    return base_col;}
Node* System::getRootNode(){return root_node;}
std::string System::getTitle() const{return m_title;}
sf::VideoMode System::getVideoMode() const{return m_mode;}
unsigned long System::getWindowStyle() const{return m_window_style;}
void System::initializeCol(){
    base_col->addEntity(root_node->getGlobalEntities());}
void System::setRootNode(Node *node){if(node!=0){root_node=node;}}
void System::setSettings(const sf::ContextSettings &params){
	sf::ContextSettings settings=getSettings();
	if(params.antialiasingLevel!=settings.antialiasingLevel
		|| params.depthBits!=settings.depthBits
		|| params.stencilBits!=settings.stencilBits){create(m_mode, m_title, m_window_style, params);}
}
void System::setSystemCollision(int max_size_x, int max_size_y, int ratio_x, int ratio_y){
    if(base_col){delete base_col;}
    base_col=new Collision(max_size_x, max_size_y, ratio_x, ratio_y);}
void System::setTitle(const std::string &title){
	if(title!=m_title){
		create(m_mode, title, m_window_style, getSettings());
		m_title=title;
	}
}
void System::setVideoMode(sf::VideoMode mode){
	if(mode.isValid() && mode!=m_mode){
		create(mode, m_title, m_window_style, getSettings());
		m_mode=mode;
	}
	else{;}
}
void System::setWindowStyle(unsigned long window_style){
	if(window_style!=m_window_style){
		create(m_mode, m_title, window_style, getSettings());
		m_window_style=window_style;
	}
}
