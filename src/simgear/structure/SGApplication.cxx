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

#include "SGApplication.hxx"

/**
 * Parse command line arguments from main. Allocate memory to the subsystem
 * manager and create subsystems. Then call the init() function, implemented (or
 * not) by the derived class.
 */
SGApplication::SGApplication(int argc, char **argv) :
     m_subsystem_mgr(NULL)
{
     parseCmdArguments(argc, argv);
     
     m_subsystem_mgr = new SGSubsystemMgr;
     createSubsystems();
     
     init();
}

/**
 * Free previously allocated memory (check for NULL; only free if it is NOT
 * NULL). Cases where a pointer can still be new is when the user interrupted
 * the program before the constructor gets executed.
 */
SGApplication::~SGApplication()
{
     if (!m_subsystem_mgr) delete m_subsystem_mgr;
}
