#ifndef __SGAPPLICATION_HXX
#define __SGAPPLICATION_HXX

#include <simgear/structure/subsystem_mgr.hxx>

class SGApplication {
public:

     SGApplication(int argc, char **argv) :
          m_subsystem_mgr(NULL) {

          parseCmdArguments(argc, argv);

          m_subsystem_mgr = new SGSubsystemMgr;
          createSubsystems();

          init();
     }
     
     virtual ~SGApplication() {
          if (!m_subsystem_mgr) delete m_subsystem_mgr;
     }

     virtual void run() = 0;

     SGSubsystemMgr *get_subsystem_mgr()       const {return m_subsystem_mgr;}

     SGSubsystem    *get_subsystem(char *name) const
          {return m_subsystem_mgr->get_subsystem(name);}

protected:

     SGSubsystemMgr *m_subsystem_mgr;

     virtual void init() {};
     virtual void parseCmdArguments(int argc, char **argv) {};
     virtual void createSubsystems() {};
};

#endif // __SGAPPLICATION_HXX
