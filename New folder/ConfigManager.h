#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <fstream>
#include "QBoard.h"

using namespace std;

/// \brief Creates models of all the objects that are later used in the session
/** That is achieved by loading the objects from the config file once and then 
* passing the parameters forward instead of opening files every time when we create a new instanse.
*/
class ConfigManager
{
    public:
        ConfigManager(); ///<The class constructor
        virtual ~ConfigManager(); ///<The class destructor

        QBoard m_qBoard;
        void init(string configFile); ///<Initializating function

    protected:

    private:
};

#endif // CONFIGMANAGER_H
