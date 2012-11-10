/**
 * \file main.cxx
 * \brief Contains the main routine.
 */

/*
 * FGRadar - a stand-alone ATC client for FlightGear.
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

/**
 * \defgroup main
 *
 * The group main contains all the main files of FGRadar. It contains the basic
 * application (FGRadarApp), property manager, subsystem manager and other
 * top-level and important stuff.
 */

/**
 * \mainpage FGRadar developer documentation
 *
 * TODO when everything is mostly done!!
 */

#include <iostream>
#include <simgear/structure/exception.hxx>

#include "fgradar_app.hxx"

int
main(int argc, char **argv)
{
    using namespace fgradar;
     
    try {
        fgradar_app = new FgradarApp(argc, argv);
        fgradar_app->run();
    } catch (const sg_exception &e) {
        std::cerr << e.what() << "\nAborting..." << std::endl;
        return 1;
    }

    delete fgradar_app;
     
    return 0;
}
