#ifndef LOCALIZATION_H
#define LOCALIZATION_H
#include <map>
#include "INIParser.h"

using namespace std;

class Localization
{
    public:
        Localization();
        virtual ~Localization();
        void loadFromFile(string filename);
        void setLanguage(string language);
        string tr(string string_text, string str1=string(), string str2=string(), string str3=string());
    protected:
    private:
        map<string, map<string, string> > list_strings;
        string m_language="EN";
};

#endif // LOCALIZATION_H
