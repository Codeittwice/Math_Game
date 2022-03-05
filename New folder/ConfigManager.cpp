#include "ConfigManager.h"

#include "World.h"
extern World world;

ConfigManager::ConfigManager()
{
    //ctor
}

ConfigManager::~ConfigManager()
{
    //dtor
}

void ConfigManager::init(string configFile)
{
    ///Opening a stream and calling the load function for every object and configuration file found.
    configFile = "config\\" + configFile;

    fstream stream;
    string tmp;

    stream.open(configFile);

    stream >> tmp;
    m_qBoard.init(tmp);

    stream.close();
}
