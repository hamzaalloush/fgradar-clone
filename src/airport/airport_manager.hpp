/**
 * \file airport_manager.hpp
 * \brief Header for airport_manager.cpp.
 */

// Copyright (C) 2012  Fernando García Liñán  <fernando.garli@gmail.com>

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

#ifndef _AIRPORT_MANAGER_HPP_
#define _AIRPORT_MANAGER_HPP_

#include <cairomm/context.h>
#include <vector>

#include "gui/radar.hpp"

namespace fgradar {

     class Airport;

     /**
      * \brief Manages airports.
      *
      * Keeps an organized list of airports and provides useful functions to
      * search or retrieve them.
      */
     class AirportManager {
     public:

          enum AptCodes {
               AIRPORT = 1,
               SEAPLANE_BASE = 16,
               HELIPORT = 17,
               RUNWAY_TAXIWAY = 10,
               VIEWPOINT = 14,
               ATIS = 50,
               UNICOM = 51,
               CLEARANCE = 52,
               GROUND = 53,
               TOWER = 54,
               APPROACH = 55,
               DEPARTURE = 56
          };

          AirportManager();

          ~AirportManager();

          bool init();
          void clear();
          void reinit();

          void draw(const Cairo::RefPtr<Cairo::Context> &cr,
                    const Radar &radar);

     private:

          /** Vector containing all the airports parsed in apt.dat. At the same
              time, Airport contains runways and taxiways so this class doesn't
              have to worry about them. */
          std::vector<Airport *> m_airport_list;
     };

     extern AirportManager *airport_manager;

} // namespace fgradar

#endif // _AIRPORT_MANAGER_HPP_
