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

#ifndef __SGAPPLICATION_HXX
#define __SGAPPLICATION_HXX

#include <string>

#include <simgear/misc/sg_path.hxx>
#include <simgear/props/props.hxx>
#include <simgear/structure/SGSharedPtr.hxx>
#include <simgear/structure/subsystem_mgr.hxx>

/**
 * \brief Defines a base application class.
 *
 * This class is intended to be derived into another type of application. There
 * are another alternatives you can choose from. For example, SG_OSGApplication
 * is good for OSG usage, or SG_GLApplication for OpenGL/GLUT applications.
 *
 * If you want to use another library or it is a CLI application, it is
 * recommended that you use this one directly.
 */
class SGApplication {
public:
     typedef bool (SGApplication::*CmdCallback) (std::string);
     
     struct CmdOption {
          std::string command;
          std::string alias;
          std::string description;
          SGApplication::CmdCallback function;
     };

     /**
      * This constructor performs all the initialization code (only memory
      * allocation and variable initialization, other things should go in
      * init()).
      *
      * Don't forget to call this constructor from the derived class by doing:
      *
      * \code
      *   MyApplication(int argc, char **argv) :
      *       SGApplication(argc, argv)
      * \endcode
      *
      * \param argc Number of arguments from main().
      * \param argv Arguments from main().
      */
     SGApplication(int argc, char **argv, const char*, bool datadir_required=true);

     virtual ~SGApplication();

     /**
      * \brief Runs the main application loop.
      *
      * This function should be called from outside the derived class, from
      * main() for example. To exit the loop, use the 'quit' function.
      *
      * If you plan adding other stuff that isn't done in the SGApplication
      * implementation, make sure you add this in your derived class run():
      *
      * \code
      *   SGApplication::run();
      * \endcode
      */
     virtual void run();

     /**
      * \brief Quits the application.
      *
      * This should be called when you want to exit the application, instead of
      * making 'm_quit_flag' true. This allows other stuff to be done here.
      *
      * Don't forget to call this function from your derived class if you plan
      * adding custom stuff.
      */
     virtual void quit();

     /**
      * Get a property tree node. Once you have the node, you can access
      * its value by calling 'get<type>Value', where in type you specify
      * the type you want to get.
      *
      * You can also specify if you want the node to be created if it
      * doesn't exist.
      *
      * \param path Path to the node relative to root.
      * \param create If the node should be created if it doesn't exist.
      * \return The node.
      */
     static SGPropertyNode *getNode(const char *path, bool create) {
          return m_property_tree->getNode(path, create);
     }

     bool checkVersion();

     SGSubsystemMgr *get_subsystem_mgr() {return m_subsystem_mgr;}

     SGSubsystem *get_subsystem(const char *name)
          {return m_subsystem_mgr->get_subsystem(name);}


     static std::string ROOTDIR;
protected:
     std::string m_datafolder_param;
     std::string m_appname;
     std::string m_version_filename;
     /**
      * Application will quit when this flag is true. It is recommended to use
      * the function quit() in order to quit the application.
      */
     bool                               m_quit_flag;

     /**
      * The subsystem manager. Controls the life cycle of every subsystem,
      * manages addition and removal of subsystems and keeps them always
      * accessible.
      */
     SGSharedPtr<SGSubsystemMgr>        m_subsystem_mgr;

     /**
      * This is the property tree. It is just a node to the root of the
      * property tree, so all the property tree is a child of it. We make
      * it static so there is only one property tree in the whole program,
      * even if by accident there are two subsystems.
      */
     static SGSharedPtr<SGPropertyNode> m_property_tree;

     /**
      * \brief Initialization code should be placed here.
      *
      * Memory allocation and variable initialization should be placed in
      * constructor, other stuff should be here.
      *
      * This function is not called by SGApplication, so you need to call it
      * from a derived class, preferably in the end of the constructor, after
      * all memory allocation.
      */
     virtual void init() {}

     bool onData(std::string);
     bool onVersion(std::string);
     bool onHelp(std::string);
     bool onProp(std::string);
    
     void parseCmdOptions(int argc, char **argv);

     void addCmdOption(std::string command, std::string alias,
                       std::string description, CmdCallback func);

     std::vector<CmdOption> m_cmd_options;

};

#endif // __SGAPPLICATION_HXX
