/**
 * \file fgradar.hpp
 * \brief Header for fgradar.cpp.
 */

// Copyright (C) 2012  Fernando García  <fernando.garli@gmail.com>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
   
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
   
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _FGRADAR_HPP_
#define _FGRADAR_HPP_

#include <simgear/structure/subsystem_mgr.hxx>

namespace fgradar {

     /**
      * \brief Main app class.
      *
      * Global class which contains the main loop, initializes everything and
      * deletes everything. This top-level class also manages the subsystem
      * manager.
      */
     class FgradarApp {
     public:

          FgradarApp(int argc, char **argv);
          virtual ~FgradarApp();

          void run();

          /**
           * \return A pointer to the subsystem manager.
           */
          SGSubsystemMgr *get_subsystem_mgr()       const {return m_subsystem_mgr;}

          /**
           * \param name The name of the subsystem we want to get.
           * \return The retrieved subsystem.
           */
          SGSubsystem    *get_subsystem(char *name) const
               {return m_subsystem_mgr->get_subsystem(name);}
          
     private:

          /** The SimGear subsystem manager. Manages all the subsystems by
              initializing, updating, removing them etc. */
          SGSubsystemMgr *m_subsystem_mgr;

          void init();
          void parseCmdArguments(int argc, char **argv);
          void createSubsystems();
     };

     extern FgradarApp *fgradar_app;
     
} // namespace fgradar

#endif // _FGRADAR_HPP_
