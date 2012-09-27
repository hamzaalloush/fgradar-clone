/**
 * \file flightplan.hpp
 * \brief Header for flightplan.cpp.
 */

// Copyright (C) 2012  Fernando García Liñán  <fernando.garli\gmail.com>

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

#ifndef _FLIGHTPLAN_HPP_
#define _FLIGHTPLAN_HPP_

#include <iostream>
#include <vector>

namespace fgradar {

     class Airport;
     class Entity;

     /**
      * \brief Keeps track of an aircraft's route.
      *
      * Stores departure/arrival airports as well as waypoints. Checks for their
      * existence and returns the flightplan in several ways.
      */
     class FlightPlan {
     public:

          FlightPlan();
          
          ~FlightPlan();

          // bool set_departure_apt(std::string &apt) {
          
          //      return true;
          // }

          // bool set_arrival_apt(std::string &apt) {


          //      return true;
          // }

          // bool set_alternate_apt(std::string &apt) {

          //      return true;
          // }

          void         clear();

          bool         append_waypoint(std::string &wpt);
          bool         remove_waypoint(std::string &wpt);

          int          find_waypoint_in_route(std::string &wpt);

          std::string  get_flightplan_str();
          /** \return Departure airport entity. */
          Airport     *get_departure_apt()   const  {return m_departure_apt;}
          /** \return Arrival airport entity. */
          Airport     *get_arrival_apt()     const  {return m_arrival_apt;}
          /** \return Alternate airport entity. */
          Airport     *get_alternate_apt()   const  {return m_alternate_apt;}

          /**
           * \param Position of the waypoint we want to retrieve. (Note: If you
           * want to get it by name, just use the find_waypoint_in_route method).
           * \return The waypoint (if it exists).
           */
          Entity      *get_waypoint(int pos) const  {
               if (pos < 0)
                    return NULL;
               return m_waypoints[pos];
          }

     private:

          /** Airport the plane will departure from. */
          Airport               *m_departure_apt;
          
          /** The airport the plane will arrive at. */
          Airport               *m_arrival_apt;

          /** Alternate airport. This is usually an optional setting, but
              anyway, it is always nice to have it. */
          Airport               *m_alternate_apt;

          /** The list of waypoints the aircraft will follow, that is,
              fixes, navaids and airports (but note departure and arrival
              airports are not defined here). */
          std::vector<Entity *>  m_waypoints;
     };

}

#endif // _FLIGHTPLAN_HPP_
