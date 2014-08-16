/*
 * Directory.cpp
 *
 *  Created on: 3 juil. 2012
 *      Author: Erwann
 */

#include "Directory.hpp"

namespace dr {

Directory::Directory(std::string path) {
	base_path=path;
	base_dir=opendir(base_path.c_str());
	if(base_dir!=0){
		dirent *temp_dirent;
		while((temp_dirent=readdir(base_dir))){
			std::string temp_file=temp_dirent->d_name;
			if(temp_file!="." && temp_file!=".."){
				std::string separator;
				if(path.find("\\")!=-1){separator="\\";}
				else{separator="/";}
				if(isDir(path+separator+temp_dirent->d_name)){dirs.push_back(temp_file);}
				else{files.push_back(temp_file);}
			}
		}
		//closedir(base_dir);
	}
	else{std::cout<<"Directory "<<path<<" not found"<<std::endl;}
}

Directory::~Directory() {
	if(base_dir!=0){delete base_dir;}
}

void Directory::refresh(){
	base_dir=opendir(base_path.c_str());
	if(base_dir!=0){
		dirent *temp_dirent;
		while((temp_dirent=readdir(base_dir))){
			std::string temp_file=temp_dirent->d_name;
			if(temp_file!="." && temp_file!=".."){
				std::string separator;
				if(base_path.find("\\")!=-1){separator="\\";}
				else{separator="/";}
				if(isDir(base_path+separator+temp_dirent->d_name)){dirs.push_back(temp_file);}
				else{files.push_back(temp_file);}
			}
		}
		//closedir(base_dir);
	}
	else{std::cout<<"Directory "<<base_path<<" not found"<<std::endl;}
}

bool Directory::isDir(std::string path){
	DIR* temp_dir=opendir(path.c_str());
	if(temp_dir!=0){closedir(temp_dir); return true;}
	else{return false;}
}

bool Directory::isFile(std::string path){
	DIR* temp_dir=opendir(path.c_str());
	if(temp_dir!=0){closedir(temp_dir); return false;}
	else{return true;}
}

std::vector<std::string>& Directory::find(std::string file){
	std::vector<std::string> founded;
	for(int i=0; i<file.size(); i++){if(files.at(i).find(file)){founded=files;}}
	return founded;
}

std::vector<std::string>& Directory::getFiles(){return files;}

std::vector<std::string>& Directory::getDirs(){return dirs;}

std::vector<std::string>& Directory::hasExt(std::string& ext){
	std::string _ext=ext;
	std::vector<std::string> ext_files;
	int pos=0;
	if((pos=_ext.find_last_of("."))!=-1){_ext.erase(pos,1);}
	for(int i=0; i<files.size(); i++){
		if(files[i].size()>_ext.size()+1 && files[i].substr(files[i].size()-(_ext.size()+1), _ext.size()+1).find("."+_ext)!=-1){ext_files.push_back(files[i]);}
	}
	return ext_files;
}

std::vector<std::string>& Directory::hasExt(std::string& ext, std::vector<std::string>& base_files){
	std::string _ext=ext;
	std::vector<std::string> ext_files;
	int pos=0;
	if((pos=_ext.find_last_of("."))!=-1){_ext.erase(pos,1);}
	for(int i=0; i<base_files.size(); i++){
		if(base_files[i].size()>_ext.size()+1 && base_files[i].substr(base_files[i].size()-(_ext.size()+1), _ext.size()+1).find("."+_ext)!=-1){ext_files.push_back(base_files[i]);}
	}
	return ext_files;
}

std::string& Directory::cleanPath(std::string& path, bool keep_ext){
	if(!path.empty()){
		if(path.find_last_of("/")!=-1){path.erase(0, path.find_last_of("/"));}
		else if(path.find_last_of("\\")!=-1){path.erase(0, path.find_last_of("\\"));}
		if(!keep_ext){if(path.find_last_of(".")!=-1){path.erase(path.find_last_of("."), path.size()-path.find_last_of("."));}}
	}
	return path;
}

} /* namespace dr */

