/*
 * ImageManager.cpp
 *
 *  Created on: 2 juil. 2012
 *      Author: Erwann
 */

#include "ImageManager.hpp"

ImageManager::ImageManager(const std::string filename) {
	loadTextures(filename);
}

ImageManager::~ImageManager() {

}

sf::Texture& ImageManager::getTexture(const std::string name){
	std::map<std::string, sf::Texture>::iterator it=_manager.find(name);
	if(it!=_manager.end()){return (*it).second;}
	else{sf::Texture temp_image; return temp_image;}
}

sf::Texture* ImageManager::getPtrTexture(const std::string name){
	std::map<std::string, sf::Texture>::iterator it=_manager.find(name);
	if(it!=_manager.end()){return &(*it).second;}
	else{sf::Texture temp_image; return 0;}
}

void ImageManager::loadTextures(const std::string filename){
	std::ifstream ress_file(filename.c_str(), std::ios::in);  // on ouvre le fichier en lecture
	if(ress_file){
		std::string content;
		while(getline(ress_file, content)){
			if(!content.empty() && content.find("//", 0, 2)==-1){
				dr::Directory current_dir(content);
				std::vector<std::string> files=current_dir.getFiles();
				for(int i=0; i<files.size(); i++){
					if(files.at(i)!=std::string("Thumbs.db")){
                        std::string separator;
                        sf::Texture temp_image;
                        if(content.find("\\")!=-1){separator="\\";}
                        else{separator="/";}
                        temp_image.loadFromFile(content+separator+files[i]);
                        _manager.insert(std::pair<std::string,sf::Texture>(dr::Directory::cleanPath(files.at(i), false),temp_image));}
				}
			}
	    }
		ress_file.close();
	}
}

void ImageManager::setTextureRepeated(const std::string name, bool state){
    std::map<std::string, sf::Texture>::iterator it=_manager.find(name);
	if(it!=_manager.end()){(*it).second.setRepeated(state);}
}
