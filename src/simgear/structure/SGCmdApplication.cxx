/*
 * Copyright (C) 2012  Fernando García  <fernando.garli@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
   
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <algorithm>
#include <simgear/misc/ResourceManager.hxx>

#include "SGCmdApplication.hxx"

/**
 * Adds some default command line options and parses them. Since it inherits
 * from SGApplication, it FIRST does all the stuff done in SGApplication
 * constructor and then all of this.
 */
SGCmdApplication::SGCmdApplication(const char *appname, int argc, char **argv,
                                   bool datadir_required) :
     SGApplication(appname, datadir_required)
{
     addCmdOption("--data", "-d", "specify data directory location.",
                  &SGCmdApplication::onData);
     addCmdOption("--help", "-h", "shows the available command line options.",
                  &SGCmdApplication::onHelp);
     addCmdOption("--version", "-v", "shows version number.",
                  &SGCmdApplication::onVersion);
     addCmdOption("--prop", "-p", "set a value to a property tree node.",
                  &SGCmdApplication::onProp);

     parseCmdOptions(argc, argv);
}

SGCmdApplication::~SGCmdApplication()
{
}

/**
 * Add a new command line option. Creates a new CmdOption structure, fills it
 * with the function parameters and appends it to the command line options list.
 */
void
SGCmdApplication::addCmdOption(std::string command, std::string alias,
                            std::string description, CmdCallback func)
{
     CmdOption option;
     option.command     = command;
     option.alias       = alias;
     option.description = description;
     option.function    = func;

     m_cmd_options.push_back(option);
}

/**
 * Parse all the command line options. Compares them with the command line
 * options list. If one matches, execute its callback function and keep reading
 * until there are no command line options left to read.
 */
void
SGCmdApplication::parseCmdOptions(int argc, char **argv)
{
     for (int i = 1; i < argc; i++) {
          for(std::vector<CmdOption>::iterator j = m_cmd_options.begin();
              j != m_cmd_options.end(); j++) {
               
               std::string tok(argv[i]);
	       std::string cmd((*j).command);
	
               if (cmd.compare(tok.substr(0,cmd.size())) == 0) {
		    std::string arg = tok.substr(tok.find("=") + 1, tok.length());
		    SGCmdApplication::CmdCallback c = (*j).function;

                    // Check the return value of the callback. If false, exit
                    // program (useful for commands like --version or --help).
		    if(!(*this.*c)(arg) ) 
                         exit(0);
		    else break;
               }
          }
     }
}

/*******************************************************************************/
/********************************** CALLBACKS **********************************/
/*******************************************************************************/

bool
SGCmdApplication::
onData(std::string arg) {
 ROOTDIR=arg;
 simgear::ResourceManager::instance()->addBasePath(ROOTDIR);
 return true; // don't exit
}

bool
SGCmdApplication::
onVersion(std::string arg)
{
     std::cout << "I don't know!" << std::endl;
     return false; // exit
}

bool 
SGCmdApplication::
onHelp(std::string arg) 
{
     std::string appname_lower = m_appname;
     std::transform(appname_lower.begin(), appname_lower.end(),
                    appname_lower.begin(), ::tolower);
     
     std::cout << "Usage: " << appname_lower << " [OPTIONS]" << std::endl
               << std::endl;
     
     size_t longest_cmd_size = 0;
     for (std::vector<CmdOption>::iterator i = m_cmd_options.begin();
          i != m_cmd_options.end(); i++)
          if ((*i).command.size() > longest_cmd_size)
               longest_cmd_size = (*i).command.size();

     std::cout << "Options: " << std::endl;
     for (std::vector<CmdOption>::iterator i = m_cmd_options.begin();
          i != m_cmd_options.end(); i++) {

          std::cout << "  " << (*i).alias << ",  " << (*i).command
                    << std::string(longest_cmd_size - (*i).command.size(), ' ')
                    << "   " << (*i).description << std::endl;
     }
     
     return false; // exit
}

bool
SGCmdApplication::onProp(std::string arg) 
{
     // FIXME: this can't work because of the hard-coded argument separator 
     // TODO: Add support for other types, currently it always takes the value
     // as a string, when it can be a number (int, float, double) or a boolean.
     
     size_t colon_pos = arg.find(":");

     std::string prop = arg.substr(0, colon_pos);
     SGPropertyNode *node = getNode(prop.c_str(), true);

     std::string value = arg.substr(colon_pos + 1, arg.size());
     node->setStringValue(value);
     
     return true; // don't exit 
}
