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
#include <simgear/timing/timestamp.hxx>

#include "SGApplication.hxx"

std::string SGApplication::ROOTDIR(".");
SGSharedPtr<SGPropertyNode> SGApplication::m_property_tree = new SGPropertyNode;

/**
 * Initialize variables. Set SimGear log levels and check if the user
 * provided a data directory.
 */
SGApplication::SGApplication(const char *appname, bool datadir_required) :
    m_quit_flag(false),
    m_target_fps(0),
    m_subsystem_mgr(new SGSubsystemMgr),
    m_appname(appname)
{
    // Initializing the log should be the first thing to do, so other
    // subsystems can use it later
    sglog().setLogLevels(SG_ALL, SG_WARN);
     
    if (datadir_required && SGApplication::ROOTDIR.empty())
        throw sg_exception("Data directory required");

    SGPropertyNode_ptr target_fps = getNode("/target-fps", false);
    if (target_fps != NULL)
        m_target_fps = target_fps->getDoubleValue();
}

SGApplication::~SGApplication()
{
}

/**
 * Run the main loop until 'm_quit_flag' is true.
 * Uses the calculateDeltaTime() function in order to throttle FPS and computing
 * delta time. This delta time is used by the subsystem manager while updating
 * its children.
 */
void
SGApplication::run()
{
    while (!m_quit_flag) {

        double dt = calculateDeltaTime();
        
        // Update subsystems
        m_subsystem_mgr->update(dt);
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

/**
 * Calculates elased time between frames by substracting two time stamps, the
 * previous frame one, and the current frame one. This gives the time increment
 * from one frame to another.
 *
 * Apart from calculating delta time, also limit FPS if needed.
 *
 * @note prev_time is 0 at the first tick, it gets updated in the
 * 2nd. Therefore, program runs at max speed during 1st tick (nothing noticeable
 * though).
 */
double
SGApplication::calculateDeltaTime()
{
    SGTimeStamp current_time;
    static SGTimeStamp prev_time;

    current_time.stamp();

    SGTimeStamp dt = current_time - prev_time;
        
    if (m_target_fps > 0) {
        // Maximum time the frame should take to finish
        SGTimeStamp max_time = SGTimeStamp::fromUSec(1.0e6 / m_target_fps);

        // Check if we have enough time to sleep. If not, keep running until we
        // reach the target FPS.
        if (dt < max_time) {
            SGTimeStamp wait_time = max_time - dt;
            SGTimeStamp::sleepFor(wait_time);
        }

        // Update delta since the previous stuff took some time to do
        current_time.stamp();
        dt = current_time - prev_time;
    }

    prev_time = current_time;

    return dt.toSecs();
}
