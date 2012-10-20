/*
 * Copyright (C) 2012  Fernando García  <fernando.garli@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *   
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <simgear/debug/logstream.hxx>
#include <simgear/misc/ResourceManager.hxx>

#include "SGApplication.hxx"

std::string SGApplication::ROOTDIR(".");
SGSharedPtr<SGPropertyNode> SGApplication::m_property_tree = new SGPropertyNode;

/**
 * Allocate memory and initialize variables. argc and argv are given so the user
 * can use them or not, but it is not compulsory.
 */
SGApplication::SGApplication(int argc, char **argv, const char* appname, bool datadir_required):
     m_quit_flag(false),
     m_subsystem_mgr(new SGSubsystemMgr),
     m_datafolder_param("data"),
     m_appname(appname),
     m_version_filename("version")
{
     // Initializing the log should be the first thing we do, so other
     // subsystems can use it later
     sglog().setLogLevels(SG_ALL, SG_WARN);

     addCmdOption(std::string("--"+ m_datafolder_param), &SGApplication::onData);
     addCmdOption(std::string("--help"), &SGApplication::onHelp);
     addCmdOption(std::string("--version"), &SGApplication::onVersion);
     addCmdOption(std::string("--prop"), &SGApplication::onProp);

     parseCmdOptions(argc, argv);
     if (datadir_required && SGApplication::ROOTDIR=="")
	throw("Data directory required");
}

/**
 * Free previously allocated memory.
 */
SGApplication::~SGApplication()
{
}

/**
 * Run the main loop until 'm_quit_flag' is true.
 * This simple main loop updates all the subsystems (by updating the subsystem
 * manager). The update function actually needs the delta time, but FGRadar
 * doesn't need a lot of resources and it isn't a heavy 3D program, so passing 0
 * is a good solution.
 */
void
SGApplication::run()
{
     while (!m_quit_flag) {

          // Update subsystems
          m_subsystem_mgr->update(0.1);
     }
}

/**
 * Quit the program by setthing 'm_quit_flag' to true.
 * In the future, some things might be added, that's why it is recommended to
 * call this function instead of changing 'm_quit_flag' manually.
 */
void
SGApplication::quit()
{
     SG_LOG(SG_GENERAL, SG_INFO, "SGApplication quit signal");
     m_quit_flag = true;
}

bool
SGApplication::checkVersion() {
  SGPath BaseCheck(SGApplication::ROOTDIR);
  BaseCheck.append(m_version_filename);
  if (!BaseCheck.exists())
  {
      std::cerr << m_appname << ":Missing base package. Use --"<< m_datafolder_param <<"=path_to_fgradar_data" << std::endl;
      throw ("data directory missin");
  }
  return true;
}

void
SGApplication::parseCmdOptions(int argc, char **argv)
{
     for (int i = 1; i < argc; i++) {
          for(std::vector<CmdOption>::iterator j = m_cmd_options.begin();
              j != m_cmd_options.end(); j++) {
               std::string tok(argv[i]);
	       std::string cmd( (*j).cmd_name );
	
               if (cmd.compare( tok.substr(0,cmd.size() ))  == 0) {
		    std::string arg = tok.substr(tok.find("=")+1, tok.length());
		    SGApplication::CmdCallback c = (*j).function;
		    if(! (*this.*c) (arg) ) 
			exit(0);
		    else break;
               }
          }
     }
}

void
SGApplication::addCmdOption(std::string name, CmdCallback func)
{
     CmdOption option;
     option.cmd_name = name;
     option.function = func;

     m_cmd_options.push_back(option);
}

bool
SGApplication::
onData(std::string arg) {
 ROOTDIR=arg;
 simgear::ResourceManager::instance()->addBasePath( ROOTDIR );
 return true; // don't exit
}

bool
SGApplication::
onVersion(std::string arg)
{
     std::cout << "I don't know!" << std::endl;
     return false; // exit
}

bool 
SGApplication::
onHelp(std::string arg) 
{
 std::cout << "Help ..." << std::endl;
 return false; // exit
}

bool
SGApplication::
onProp(std::string arg) 
{

  return true; // don't exit 
}

