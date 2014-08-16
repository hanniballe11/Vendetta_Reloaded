/*
 * Node.cpp
 *
 *  Created on: 15 juil. 2012
 *      Author: Erwann
 */

#include "Node.hpp"
#include "Entity.hpp"
#include "System.hpp"

Node::Node(){
	m_sys=0;
	m_parent=0;
}
Node::Node(System *sys, Node *parent){
	m_sys=sys;
	m_parent=parent;
}
Node::~Node(){
	m_nodes.clear();
	m_entities.clear();
	m_priority.clear();
	m_sys=0;
	m_parent=0;
	delete m_sys;
	delete m_parent;
}
void Node::addNode(Node *node){
	m_nodes.push_back(node);
	node->setParent(this);
	m_priority.push_back(TypeNode);
}
void Node::addEntity(Entity *entity){
	m_entities.push_back(entity);
	entity->setParent(this);
	m_priority.push_back(TypeEntity);
}
void Node::clear(){
	m_nodes.clear();
	m_entities.clear();
	m_priority.clear();
}
bool Node::draw(){
	if(m_sys!=0 && m_priority.size()>0){
		int m_posN=0;
		int m_posE=0;
		for(int i=0; i<m_priority.size(); i++){
			switch(m_priority[i]){
				case TypeNode:
					m_nodes[m_posN]->draw();
					m_posN++;
					break;
				case TypeEntity:
					m_entities[m_posE]->draw(m_sys);
					m_posE++;
					break;
			}
		}
		return true;
	}
	else{return false;}
}
std::vector<Entity*> Node::getGlobalEntities(){
    std::vector<Entity*> global_entities;
    std::vector<Entity*> temp_entities;
    for(int i=0; i<m_nodes.size(); i++){
        temp_entities=m_nodes.at(i)->getGlobalEntities();
        for(int j=0; j<temp_entities.size(); j++){global_entities.push_back(temp_entities.at(j));}
    }
    for(int i=0; i<m_entities.size(); i++){global_entities.push_back(m_entities.at(i));}
    return global_entities;
}
int Node::getPriority(Node *node){
	if(node!=0){
        unsigned int counter=0;
        for(int i=0; i<m_priority.size(); i++){
            if(m_priority[i]==TypeNode){
                if(m_nodes[counter]==node){return i;}
                else{counter++;}
            }
        }
	}
	return -1;

}
int Node::getPriority(Entity *entity){
	if(entity!=0){
        unsigned int counter=0;
        for(int i=0; i<m_priority.size(); i++){
            if(m_priority[i]==TypeEntity){
                if(m_entities[counter]==entity){return i;}
                else{counter++;}
            }
        }
	}
	return -1;
}
System* Node::getWindow(){
    return m_sys;}
void Node::insertNode(Node *node, int pos){
	if(pos<m_priority.size()){
		std::vector<Node*>::iterator it_nodes;
		std::vector<typeInput>::iterator it_priority;

		unsigned int counter=0;

		it_priority=m_priority.begin()+pos;

		while(it_priority!=m_priority.begin()){
			--it_priority;
			if(*it_priority==TypeNode){counter++;}
		}
		it_nodes=m_nodes.begin()+counter;
		m_priority.insert(it_priority+pos, TypeNode);
		m_nodes.insert(it_nodes, node);
		node->setParent(this);
	}
}
void Node::insertEntity(Entity *entity, int pos){
	if(pos<m_priority.size()){
		std::vector<Entity*>::iterator it_entities;
		std::vector<typeInput>::iterator it_priority;

		unsigned int counter=0;

		it_priority=m_priority.begin()+pos;

		while(it_priority!=m_priority.begin()){
			--it_priority;
			if(*it_priority==TypeEntity){counter++;}
		}
		it_entities=m_entities.begin()+counter;
		m_priority.insert(it_priority+pos, TypeEntity);
		m_entities.insert(it_entities, entity);
	}
}
typeInput Node::isType(int pos){if(pos<m_priority.size()){return m_priority.at(pos);}}
void Node::remove(int pos){
	if(pos<m_priority.size()){
		std::vector<Entity*>::iterator it_entities;
		std::vector<Node*>::iterator it_nodes;
		std::vector<typeInput>::iterator it_priority;

		it_priority=m_priority.begin()+pos;
		it_nodes=m_nodes.begin();
		it_entities=m_entities.begin();
		int type=0;
		unsigned int counter=0;

		while(it_priority!=m_priority.begin()){
			if(*it_priority==type){counter++;}
			--it_priority;
		}
		m_priority.erase(it_priority);
		if(type==TypeNode){
			it_nodes+=counter;
			(*it_nodes)->setParent(this);
			m_nodes.erase(it_nodes+counter);
		}
		else{m_entities.erase(it_entities+counter);}
	}
}
void Node::remove(Entity* entity){
	if(getPriority(entity)!=-1){
	    int nb_priority=getPriority(entity);
		unsigned int counter=0;
		for(int i=0; i<nb_priority; i++){
			if(m_priority[i]==TypeEntity){counter++;}}

		m_priority.erase(m_priority.begin()+nb_priority);
		m_entities.erase(m_entities.begin()+counter);
	}
}
void Node::remove(Node* node){
	if(getPriority(node)!=0){
		std::vector<Node*>::iterator it_nodes;
		it_nodes=m_nodes.begin();
		unsigned int counter=0;

		for(int i=0; i<getPriority(node); i++){
			if(m_priority[i]==TypeNode){counter++;}}

		m_priority.erase(m_priority.begin()+getPriority(node));
		m_nodes[counter]->setParent(0);
        m_nodes.erase(it_nodes+counter);
	}
}
void Node::move(float x_pix, float y_pix){
	int it_nodes=0;
	int it_entities=0;
	for(int i=0; i<m_priority.size(); i++){
		if(m_priority.at(i)==TypeNode){m_nodes.at(it_nodes)->move(x_pix, y_pix); it_nodes++;}
		else if(m_priority.at(i)==TypeEntity){m_entities.at(it_entities)->move(x_pix, y_pix); it_entities++;}
		else{;}
	}
}
void Node::setParent(Node *parent){m_parent=parent;}
void Node::setPriority(Node *node, int pos){

}
void Node::setPriority(Entity *entity, int pos){

}
void Node::setRotation(float angle){
	unsigned int counter_nodes=0;
	unsigned int counter_entities=0;
	for(int i=0; i<m_priority.size(); i++){
		if(m_priority.at(i)==TypeNode){m_nodes[counter_nodes]->setRotation(angle); counter_nodes++;}
		else if(m_priority.at(i)==TypeEntity){m_entities[counter_entities]->setRotation(angle); counter_entities++;}
	}
}
void Node::setScale(float x, float y){
	unsigned int counter_nodes=0;
	unsigned int counter_entities=0;
	for(int i=0; i<m_priority.size(); i++){
		if(m_priority.at(i)==TypeNode){m_nodes[counter_nodes]->setScale(x,y); counter_nodes++;}
		else if(m_priority.at(i)==TypeEntity){m_entities[counter_entities]->setScale(x,y); counter_entities++;}
	}
}
void Node::setScale(sf::Vector2f scale){
	unsigned int counter_nodes=0;
	unsigned int counter_entities=0;
	for(int i=0; i<m_priority.size(); i++){
		if(m_priority.at(i)==TypeNode){m_nodes[counter_nodes]->setScale(scale); counter_nodes++;}
		else if(m_priority.at(i)==TypeEntity){m_entities[counter_entities]->setScale(scale); counter_entities++;}
	}
}
void Node::setWindow(System *sys){m_sys=sys;}
