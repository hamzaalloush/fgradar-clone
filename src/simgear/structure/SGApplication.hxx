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
      * needs so they get called once they are called.
      *
      * \param argc Number of arguments from main().
      * \param argv Arguments from main().
      */
     SGApplication(int argc, char **argv);

     virtual ~SGApplication();

     /**
      * \brief Runs the main application loop.
      *
      * This pure virtual function isn't called internally by
      * SGApplication. Instead, it is needed that it gets called outside the
      * class. Since it is a pure virtual function, it is required that it is
      * implemented on the derived class.
      */
     virtual void run() = 0;

     SGSubsystemMgr *get_subsystem_mgr() {return m_subsystem_mgr;}

     SGSubsystem *get_subsystem(const char *name)
          {return m_subsystem_mgr->get_subsystem(name);}

protected:

     /**
      * The subsystem manager. Controls the life cycle of every subsystem,
      * manages addition and removal of subsystems and keeps them always
      * accessible.
      */
     SGSubsystemMgr *m_subsystem_mgr;

     virtual void init() {};
     virtual void parseCmdArguments(int argc, char **argv) {};
     virtual void createSubsystems() {};
};

#endif // __SGAPPLICATION_HXX
