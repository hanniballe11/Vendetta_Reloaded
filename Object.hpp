/*
 * Object.h
 *
 *  Created on: 6 juil. 2012
 *      Author: Erwann
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "Character.hpp"
#include <string>

class Object: public Entity {
public:
	Object();
	Object(const sf::Texture &Img, std::string data, const sf::Vector2f &Position=sf::Vector2f(0, 0));
	virtual ~Object();
	bool isInfinite();
	void setInfinite(bool value);
	unsigned int getUse();
	void setUse(unsigned int value);
	unsigned int getUseMax();
	void setUseMax(unsigned int value);
	bool use(Character *user, Character *opponent=0);
protected:
	bool infinite;
	unsigned int nb_use, max_use;
	std::string name, data_values;
};

#endif /* OBJECT_H_ */

/*
Paramètre Data Values :
Type(ID)][power(INT)][[Competence(ID)][Facteur(FLOAT)][Effect(ID)]
Exemple potion de soin ( ex Type_Soin=13 )
13|50|3|1.5|10
Type 13
Puissance 50
Compétence 3
Facteur 1.5
Effet 10
*/
