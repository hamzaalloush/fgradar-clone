#include "SGApplication.hxx"

SGApplication::SGApplication(int argc, char **argv) :
     m_subsystem_mgr(NULL)
{
     parseCmdArguments(argc, argv);
     
     m_subsystem_mgr = new SGSubsystemMgr;
     createSubsystems();
     
     init();
}

SGApplication::~SGApplication()
{
     if (!m_subsystem_mgr) delete m_subsystem_mgr;
}
