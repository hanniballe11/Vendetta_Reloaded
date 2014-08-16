/*
 * ImageManager.h
 *
 *  Created on: 2 juil. 2012
 *      Author: Erwann
 */

#ifndef IMAGEMANAGER_H_
#define IMAGEMANAGER_H_

#include <SFML/Graphics.hpp>
#include <map>
#include <fstream>
#include <iostream>
#include "Directory.hpp"

class ImageManager {
public:
	ImageManager(const std::string filename);
	virtual ~ImageManager();
	void loadTextures(const std::string filename);
	sf::Texture& getTexture(const std::string name);
	sf::Texture* getPtrTexture(const std::string name);
	void setTextureRepeated(const std::string name, bool state);
private:
	std::map<std::string, sf::Texture> _manager;
};

#endif /* IMAGEMANAGER_H_ */
