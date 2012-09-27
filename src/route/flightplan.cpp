/**
 * \file flightplan.cpp
 * \brief Implements class FlightPlan.
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

#include "airport.hpp"
#include "flightplan.hpp"

namespace fgradar {

     FlightPlan::FlightPlan() :
          m_departure_apt(NULL),
          m_arrival_apt(NULL),
          m_alternate_apt(NULL)
     {
     }
     
     FlightPlan::~FlightPlan()
     {
          m_waypoints.clear();
     }

     /**
      * Clears the flightplan by removing all the waypoints and
      * departure/arrival/alternate airports.
      */
     void FlightPlan::clear()
     {
          if (!m_waypoints.empty())
               m_waypoints.clear();

          m_departure_apt = NULL;
          m_arrival_apt   = NULL;
          m_alternate_apt = NULL;
     }
     
     /**
      * \return A string containing the whole flightplan as a whole string.
      *
      * Joins in a single string all the flightplan. That is, departure
      * airport, waypoints and arrival airport. This is used mostly for
      * display tasks.
      */
     std::string FlightPlan::get_flightplan_str()
     {
          std::string fp = m_departure_apt->get_icao() + " ";

          for (std::vector<Entity *>::iterator i = m_waypoints.begin();
               i != m_waypoints.end(); i++)
               fp.append((*i)->get_name() + " ");
          fp += m_arrival_apt->get_icao();
               
          return fp;
     }

     /**
      * \param wpt The fix/navaid/airport... we will add to the waypoint
      * list.
      * \return False when the suggested waypoint wasn't found.
      *
      * Tries to append a fix/navaid/airport... to the flightplan
      * (route). Checks for the existence of the wpt. If it couldn't be
      * found, returns false.
      */
     bool FlightPlan::append_waypoint(std::string &wpt)
     {
          //m_waypoints.push_back(wpt);
               
          return true;
     }

     /**
      * \param wpt Waypoint we want to remove.
      * \return If we could remove the waypoint or not.
      *
      * First, tries to find the position on the vector of the
      * waypoint. Then knowing its position, we can erase it.
      */
     bool FlightPlan::remove_waypoint(std::string &wpt)
     {
          int pos = find_waypoint_in_route(wpt);
               
          if (pos < 0)
               return false;

          m_waypoints.erase(m_waypoints.begin() + pos);

          return true;
     }

     /**
      * \param wpt The waypoint we want to find on the list.
      * \return Position of the waypoint (if found).
      *
      * Compare every vector entry with the waypoint we want to find. If
      * they are equal, return its position. If not, return -1.
      */
     int FlightPlan::find_waypoint_in_route(std::string &wpt)
     {
          for (int i = 0; i < m_waypoints.size(); i++) {
               if (wpt.compare(m_waypoints[i]->get_name()) == 0)
                    return i;
          }

          return -1;
     }

}
