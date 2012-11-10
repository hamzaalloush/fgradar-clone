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

#include <algorithm>
#include <simgear/debug/logstream.hxx>
#include <simgear/misc/ResourceManager.hxx>
#include <simgear/structure/exception.hxx>

#include "SGApplication.hxx"

std::string SGApplication::ROOTDIR(".");
SGSharedPtr<SGPropertyNode> SGApplication::m_property_tree = new SGPropertyNode;

/**
 * Initialize variables. Set SimGear log levels and check if the user
 * provided a data directory.
 */
SGApplication::SGApplication(const char *appname, bool datadir_required) :
    m_quit_flag(false),
    m_subsystem_mgr(new SGSubsystemMgr),
    m_appname(appname)
{
    // Initializing the log should be the first thing to do, so other
    // subsystems can use it later
    sglog().setLogLevels(SG_ALL, SG_WARN);
     
    if (datadir_required && SGApplication::ROOTDIR.empty())
        throw sg_exception("Data directory required");
}

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

/**
 * Checks if the 'version' file exists inside the provided data directory. If it
 * exists, it means the correct directory was provided.
 *
 * This isn't a really exact way of checking it (you can have another directory
 * with a 'version' file on it), but it is the only way of doing this without
 * checking the directory name.
 */
void
SGApplication::checkDataDirectoryExists()
{
    SGPath base_check(SGApplication::ROOTDIR);
    base_check.append("version");
     
    if (!base_check.exists())
        throw sg_io_exception("Invalid data directory", base_check.c_str());
}
