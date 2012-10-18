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

#include <simgear/structure/subsystem_mgr.hxx>

class SGApplication {
public:

     /**
      * The constructor calls all the initialization functions. The derived
      * class just has to worry about implementing all the virtual functions it
      * needs so they are called from here.
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
     SGApplication(int argc, char **argv);

     virtual ~SGApplication();

     /**
      * \brief Runs the main application loop.
      *
      * This function isn't called internally by SGApplication, so you need to
      * call from outside (main() for example). If you want to define your
      * own methods here, make sure you don't override what it does by doing:
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
      * This function already does something, so if you want to redefine it in
      * your inherited class, don't forget to call this one from inside.
      */
     virtual void quit();

     SGSubsystemMgr *get_subsystem_mgr() {return m_subsystem_mgr;}

     SGSubsystem *get_subsystem(const char *name)
          {return m_subsystem_mgr->get_subsystem(name);}

protected:

     /**
      * Application will quit when this flag is true. It is recommended to use
      * the function quit() in order to quit the application.
      */
     bool            m_quit_flag;

     /**
      * The subsystem manager. Controls the life cycle of every subsystem,
      * manages addition and removal of subsystems and keeps them always
      * accessible.
      */
     SGSubsystemMgr *m_subsystem_mgr;

     virtual void init() {}
     virtual void parseCmdArguments(int argc, char **argv) {}
     virtual void createSubsystems() {}
};

#endif // __SGAPPLICATION_HXX
