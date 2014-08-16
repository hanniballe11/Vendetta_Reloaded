/*
 * Directory.h
 *
 *  Created on: 3 juil. 2012
 *      Author: Erwann
 */

#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include "dirent.h"
#include <iostream>
#include <vector>

#ifndef WIN32
    #include <sys/types.h>
#endif

namespace dr {

class Directory {
public:
	Directory(std::string path);
	virtual ~Directory();
	void refresh();
	static bool isDir(std::string path);
	static bool isFile(std::string path);
	std::vector<std::string>& find(std::string file);
	std::vector<std::string>& getFiles();
	std::vector<std::string>& getDirs();
	std::vector<std::string>& hasExt(std::string& ext);
	static std::vector<std::string>& hasExt(std::string& ext, std::vector<std::string>& base_files);
	static std::string& cleanPath(std::string& path, bool keep_ext=true);

private:
	std::vector<std::string> files;
	std::vector<std::string> dirs;
	DIR *base_dir;
	std::string base_path;
};

}
#endif
