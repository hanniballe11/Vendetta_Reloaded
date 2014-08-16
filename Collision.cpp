/*
 * Collision.cpp
 *
 *  Created on: 15 juil. 2012
 *      Author: Erwann
 */

#include "Collision.hpp"

Collision::Collision(int max_size_x, int max_size_y, int ratio_x, int ratio_y){
	if(ratio_x<2){m_ratio_x=1;}
	else{m_ratio_x=ratio_x;}
	if(ratio_y<2){m_ratio_y=1;}
	else{m_ratio_y=ratio_y;}
	m_max_size_x=max_size_x;
	m_max_size_y=max_size_y;
    entities= new std::vector<Entity*>* [m_ratio_x];
    for(int i=0; i<m_ratio_x; i++){
        entities[i]=new std::vector<Entity*>[m_ratio_y];}
}
Collision::~Collision() {
	for(int i=0; i<m_ratio_x; i++){
        delete[] entities[i];}
    delete[] entities;
}

void Collision::addEntity(std::vector<Entity*> entity){
    for(int i=0; i<entity.size(); i++){
        list_entities.push_back(entity.at(i));
        sf::Vector2f pos_entity=entity.at(i)->getPosition();
        sf::Vector2u size_entity(entity.at(i)->getTextureRect().width, entity.at(i)->getTextureRect().height);
        if(pos_entity.x<=m_max_size_x && pos_entity.y<=m_max_size_y){entities[(int)(pos_entity.x/(m_max_size_x/m_ratio_x))][(int)(pos_entity.y/(m_max_size_y/m_ratio_y))].push_back(entity.at(i));}
        if(pos_entity.x+size_entity.x<=m_max_size_x && pos_entity.y<=m_max_size_y){entities[(int)((pos_entity.x+size_entity.x)/(m_max_size_x/m_ratio_x))][(int)(pos_entity.y/(m_max_size_y/m_ratio_y))].push_back(entity.at(i));}
        if(pos_entity.x<=m_max_size_x && pos_entity.y+size_entity.y<=m_max_size_y){entities[(int)(pos_entity.x/(m_max_size_x/m_ratio_x))][(int)((pos_entity.y+size_entity.y)/(m_max_size_y/m_ratio_y))].push_back(entity.at(i));}
        if(pos_entity.x+size_entity.x<=m_max_size_x && pos_entity.y+size_entity.y<=m_max_size_y){entities[(int)((pos_entity.x+size_entity.x)/(m_max_size_x/m_ratio_x))][(int)((pos_entity.y+size_entity.y)/(m_max_size_y/m_ratio_y))].push_back(entity.at(i));}
        }}

Entity* Collision::detectCol(Entity* source){
    }
void Collision::update(){
    for(int i=0; i<m_ratio_x; i++){
        delete[] entities[i];}
    delete[] entities;
    entities= new std::vector<Entity*>* [m_ratio_x];
    for(int i=0; i<m_ratio_x; i++){
        entities[i]=new std::vector<Entity*>[m_ratio_y];}
    for(int i=0; i<list_entities.size(); i++){
        sf::Vector2f pos_entity=list_entities.at(i)->getPosition();
        sf::Vector2u size_entity(list_entities.at(i)->getTextureRect().width, list_entities.at(i)->getTextureRect().height);
        if(pos_entity.x<=m_max_size_x && pos_entity.y<=m_max_size_y){entities[(int)(pos_entity.x/(m_max_size_x/m_ratio_x))][(int)(pos_entity.y/(m_max_size_y/m_ratio_y))].push_back(list_entities.at(i));}
        if(pos_entity.x+size_entity.x<=m_max_size_x && pos_entity.y<=m_max_size_y){entities[(int)((pos_entity.x+size_entity.x)/(m_max_size_x/m_ratio_x))][(int)(pos_entity.y/(m_max_size_y/m_ratio_y))].push_back(list_entities.at(i));}
        if(pos_entity.x<=m_max_size_x && pos_entity.y+size_entity.y<=m_max_size_y){entities[(int)(pos_entity.x/(m_max_size_x/m_ratio_x))][(int)((pos_entity.y+size_entity.y)/(m_max_size_y/m_ratio_y))].push_back(list_entities.at(i));}
        if(pos_entity.x+size_entity.x<=m_max_size_x && pos_entity.y+size_entity.y<=m_max_size_y){entities[(int)((pos_entity.x+size_entity.x)/(m_max_size_x/m_ratio_x))][(int)((pos_entity.y+size_entity.y)/(m_max_size_y/m_ratio_y))].push_back(list_entities.at(i));}
    }
}
