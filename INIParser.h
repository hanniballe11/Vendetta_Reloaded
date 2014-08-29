#ifndef INIPARSER_H
#define INIPARSER_H

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class INIParser
{
    public:
        INIParser();
        bool loadFromFile(string filename);
        virtual ~INIParser();

        map< string, map<string, string> > getAllData();
        string getValue(string section, string variable);
        vector<string> getVariables(string section);
        vector<string> getSections();

        void setValue(string section, string variable, string value);
        void modifyVariable(string section, string new_variable, string old_variable);
        void modifySection(string new_section, string old_section);
        void createValue(string section, string variable, string value);

        void save(string filename);
        void saveOnLastFile();
    protected:
    private:
        string extractSection(string content);
        pair<string, string> extractVariable(string content);
        map< string, map<string, string> > m_data;
        string m_filename;
};

#endif // INIPARSER_H
