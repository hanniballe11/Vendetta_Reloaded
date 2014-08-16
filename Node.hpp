/*
 * Node.h
 *
 *  Created on: 6 juil. 2012
 *      Author: Erwann
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <SFML/Graphics.hpp>

enum typeInput{TypeNode, TypeEntity};
class Entity;
class System;
class Node{
public:
	Node();
	Node(System *sys, Node *parent=0);
	~Node();
	void addNode(Node *node);
	void addEntity(Entity *entity);
 	void clear();
	bool draw();
	std::vector<Entity*> getGlobalEntities();
	int getPriority(Node *node);
	int getPriority(Entity *entity);
    System* getWindow();
	void insertNode(Node *node, int pos);
	void insertEntity(Entity *entity, int pos);
	typeInput isType(int pos);
	void move(float x_pix, float y_pix);
	void remove(int pos);
	void remove(Entity* entity);
	void remove(Node* node);
	void setParent(Node *parent);
	void setPriority(Node *node, int pos);
	void setPriority(Entity *entity, int pos);
	void setRotation(float angle);
	void setScale(float x, float y);
	void setScale(sf::Vector2f scale);
	void setWindow(System *sys);

protected:
	Node *m_parent;
	System *m_sys;
	std::vector<Entity*> m_entities;
	std::vector<Node*> m_nodes;
	std::vector<typeInput> m_priority;
};

#endif /* NODE_H_ */
