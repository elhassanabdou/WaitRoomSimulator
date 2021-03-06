#include"logger.h"
#include <ios>
namespace accentlog{
    void CLogger::Log(std::string_view sMessage)
    {
        m_Logfile << sMessage << "\n";
        m_Logfile.flush();
    }

    CLogger& CLogger::operator<<(std::string sMessage)
    {
        m_Logfile.open(m_sFileName.c_str(), std::ios::out | std::ios::app);
        m_Logfile << sMessage << "\n";
        m_Logfile.close();
        return *this;   
    }

    CLogger::CLogger(std::string&& filename_)
    :m_sFileName(filename_){
        m_Logfile.open(m_sFileName.c_str(), std::ios::out | std::ios::app);
    }
    CLogger::~CLogger(){
        m_Logfile.close();
    }
}
