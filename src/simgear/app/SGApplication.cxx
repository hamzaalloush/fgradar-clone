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
 * Uses the calculateDeltaTime() function in order to throttle FPS and computing
 * delta time. This delta time is used by the subsystem manager while updating
 * its children.
 */
void
SGApplication::run()
{
    while (!m_quit_flag) {

        double dt = calculateDeltaTime(30);
        
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
SGApplication::calculateDeltaTime(int target_fps_sec)
{
    SGTimeStamp current_time;
    static SGTimeStamp prev_time;

    current_time.stamp();

    // Check if throttling frame rate is needed
    if (target_fps_sec > 0) {

        double elapsed_us = (current_time - prev_time).toUSecs();
        double fps_us = 1.0e6 / target_fps_sec; // FPS in microseconds

        // Program only sleeps when we have enough time. If not, keep running
        // as fast as it can!
        if (elapsed_us < fps_us) {
            double wait_time_us = fps_us - elapsed_us;
#ifdef _WIN32
            Sleep(wait_time_us / 1.0e3);
#else
            usleep(wait_time_us);
#endif
        }

        // Update the current time since we lost some with the previous stuff
        current_time.stamp();
    }

    double dt_sec = (current_time - prev_time).toSecs();
    prev_time = current_time;

    return dt_sec;
}
