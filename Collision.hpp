/*
 * Cursor.h
 *
 *  Created on: 15 juil. 2012
 *      Author: Erwann
 */

#ifndef COLLISION_H_
#define COLLISION_H_

#include "Entity.hpp"
#include <vector>

//Collision default_collision

class Collision{
public:
	Collision(int max_size_x, int max_size_y, int ratio_x, int ratio_y);
	virtual ~Collision();
	void addEntity(std::vector<Entity*> entity);
	void update();
	Entity* detectCol(Entity* source);
protected:
    std::vector<Entity*> **entities;
    std::vector<Entity*> list_entities;
    int m_ratio_x, m_ratio_y, m_max_size_x, m_max_size_y;
    Node* node;
};

#endif
