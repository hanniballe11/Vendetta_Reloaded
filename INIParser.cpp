#include "INIParser.h"

INIParser::INIParser()
{
    //ctor
}

INIParser::~INIParser()
{
    //dtor
}

bool INIParser::loadFromFile(string filename)
{
    ifstream file(filename, ios::in);
    if(file.is_open())
    {
        m_filename=filename;
        string line;
        string current_section;
        while(getline(file, line))
        {
            if(!line.empty())
            {
                string result=extractSection(line);
                if(!result.empty()){current_section=result;}
                else if(!current_section.empty())
                {
                    pair<string, string> variable=extractVariable(line);
                    if(!variable.first.empty() && !variable.second.empty()){m_data[current_section][variable.first]=variable.second;}
                }

            }
        }
        file.close();
    }
    else{cerr<<"Open ini file failed : "<<filename<<endl;}
    return true;
}

string INIParser::extractSection(string content)
{
    string result;
    if(!content.empty() && content.length()>2)
    {
        if(content.find_first_of("[")==0)
        {
            if(content.find_last_of("]")==content.length()-1){result=content.substr(1,content.length()-2);}
        }
    }
    return result;
}

pair<string, string> INIParser::extractVariable(string content)
{
    pair<string, string> result;
    if(!content.empty() && content.length()>2)
    {
        size_t pos=content.find_first_of("=");
        if(pos!=string::npos && pos>0)
        {
            string field=content.substr(0, pos);
            ///Remove empty spaces before "="
            while(field.find_last_of(" ")==field.length()-1){field.erase(field.end()-1, field.end());}
            result.first=field;
            field=content.substr(pos+1, content.length()-pos+1);
            while(field.find_first_of(" ")==0){field.erase(0, 1);}
            result.second=field;
        }
    }
    return result;
}


map< string, map<string, string> > INIParser::getAllData()
{
    return m_data;
}
string INIParser::getValue(string section, string variable){return m_data[section][variable];}
vector<string> INIParser::getVariables(string section)
{
    vector<string> result;
    for(map<string, string>::iterator i=m_data[section].begin(); i!=m_data[section].end(); i++){result.push_back(i->first);}
    return result;
}
vector<string> INIParser::getSections()
{
    vector<string> result;
    for(map<string, map<string, string> >::iterator i=m_data.begin(); i!=m_data.end(); i++){result.push_back(i->first);}
    return result;
}

void INIParser::setValue(string section, string variable, string value){if(!m_data[section][variable].empty()){m_data[section][variable]=value;}}
void INIParser::modifyVariable(string section, string new_variable, string old_variable)
{
    if(!m_data[section][old_variable].empty() && m_data[section][new_variable].empty())
    {
        m_data[section][new_variable]=m_data[section][old_variable];
        m_data[section].erase(old_variable);
    }
}
void INIParser::modifySection(string new_section, string old_section)
{
    if(!m_data[old_section].empty() && m_data[new_section].empty())
    {
        m_data[new_section]=m_data[old_section];
        m_data.erase(old_section);
    }
}
void INIParser::createValue(string section, string variable, string value)
{
    if(m_data[section][variable].empty()){m_data[section][variable]=value;}
}

void INIParser::save(string filename)
{
    ofstream file(filename, ios::out | ios::trunc);
    if(file.is_open())
    {
        for(map< string, map<string, string> >::iterator i=m_data.begin(); i!=m_data.end(); i++)
        {
            file<<"["<<i->first<<"]"<<endl;
            for(map<string, string>::iterator j=m_data[i->first].begin(); j!=m_data[i->first].end(); j++)
                {file<<j->first<<" = "<<j->second<<endl;}
            file<<endl;
        }
        file.close();
    }
    else{cerr<<"Save ini file failed : "<<filename<<endl;}
}
void INIParser::saveOnLastFile()
{
    if(!m_filename.empty()){save(m_filename);}
}
