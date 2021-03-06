#ifndef CUSTOM_CLogger_H
#define CUSTOM_CLogger_H
#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string_view>
#include <string>
namespace accentlog{
class CLogger
{
public:
   
    void Log(std::string_view sMessage);
    
    CLogger& operator<<(std::string sMessage);
    /**
    *    Default constructor for the Logger class.
    */
    CLogger(){}
    
    CLogger(std::string&& filename_);
    ~CLogger();
    CLogger& operator = (CLogger logger){
        m_sFileName = logger.m_sFileName;
        return *this;
    }
    
private:
    
   
    std::string m_sFileName;
    std::ofstream m_Logfile;
};
}

#endif