#include "Localization.h"

Localization::Localization()
{
    //ctor
}

Localization::~Localization()
{
    //dtor
}

void Localization::loadFromFile(string filename)
{
    INIParser ini_data;
    ini_data.loadFromFile(filename);
    list_strings=ini_data.getAllData();
}
void Localization::setLanguage(string language)
{
    m_language=language;
}
string Localization::tr(string string_text, string str1, string str2, string str3)
{
    string text=list_strings[m_language][string_text];
    return text;
}
