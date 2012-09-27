/**
 * \file aircraft.cpp
 * \brief Implements class Aircraft.
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

#include "aircraft.hpp"
#include "flightplan.hpp"
#include "utils.hpp"

const int MAX_HISTORY_ENTRIES = 5;

namespace fgradar {
     
     Aircraft::Aircraft(std::string callsign, std::string &type, Geod &pos)
     {
          m_voice_support = false;
          m_pos           = pos;
          m_heading       = 0;
          m_speed         = 0;
          m_name          = callsign;
          m_model         = type;
          m_flightrules   = UNKNOWN;
          m_flightplan    = NULL;
     }

     Aircraft::~Aircraft()
     {
          delete m_flightplan;
     }

     void Aircraft::update(double lat, double lon, int alt)
     {
          
     }

     void Aircraft::draw()
     {
          std::cout << "I AM DRAWING A PLANE!!!" << std::endl;
     }

     /**
      * \return True if it has moved, false if it hasn't moved.
      *
      * Checks if the aircraft has moved or not. Compares previous position
      * of the aircraft (first history entry) with the current one.
      */
     bool Aircraft::has_moved() const
     {
          if (m_pos == m_history.front())
               return false;

          return true;
     }

     /**
      * Computes the heading based on previous coordinates (first history entry)
      * and the current ones. (See 'bearing' method in utils for details).
      */
     void Aircraft::compute_heading()
     {
          if (!has_moved()) {
               m_heading = utils::geo::bearing
                    (m_history.front(), m_pos);
          } else
               m_heading = 0;
     }

     /**
      * Computes speed based on previous aircraft position and current
      * one. Then, we compute distance between those 2 positions and divide it
      * by the update rate.
      *
      * LOGIC NOTE: speed = distance / time
      */
     void Aircraft::compute_speed()
     {
          // Checks the aircraft hasn't moved. If it hasn't moved, we don't
          // waste resources calculating a speed that is 0
          if (!has_moved()) {
               m_speed = utils::geo::from_to
                    (m_history.front(), m_pos) / 0.00083;
          } else
               m_speed = 0;
     }

     /**
      * Appends a new History structure to the vector (see History struct for
      * details). Also checks for its size, since we don't want to keep more
      * than MAX_HISTORY_ENTRIES.
      */
     void Aircraft::append_history_entry()
     {
          Geod *history_entry;

          m_history.push_front(new Geod(m_lat, m_lon, m_alt));
          
          // Remove the oldest element
          if (m_history.size() > MAX_HISTORY_ENTRIES)
               m_history.pop_back();
     }

}
