/*
 * System.h
 *
 *  Created on: 6 juil. 2012
 *      Author: Erwann
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include "Node.hpp"
#include "Collision.hpp"

class System : public sf::RenderWindow{
public:
	System();
	System(sf::VideoMode Mode, const std::string &Title, sf::Uint32 Style=sf::Style::Resize|sf::Style::Close, const sf::ContextSettings &Params=sf::ContextSettings());
	~System();
	void drawAll();
	Collision* getSystemCollision();
	Node* getRootNode();
	std::string getTitle() const;
	sf::VideoMode getVideoMode() const;
	unsigned long getWindowStyle() const;
	void initializeCol();
	void setSystemCollision(int max_size_x, int max_size_y, int ratio_x, int ratio_y);
	void setRootNode(Node *node);
	void setSettings(const sf::ContextSettings &params);
	void setTitle(const std::string &title);
	void setVideoMode(sf::VideoMode mode);
	void setWindowStyle(unsigned long window_style);

protected:
	sf::VideoMode m_mode;
	std::string m_title;
	unsigned long m_window_style;
	Node* root_node;
	Collision* base_col;
};

#endif /* SYSTEM_H_ */
