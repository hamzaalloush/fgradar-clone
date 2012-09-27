/**
 * \file runway.cpp
 * \brief Implements class Runway.
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

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "runway.hpp"

namespace fgradar {

     /** Constructor.
      * \param pos Runway center position.
      * \param runway_number Runway number code.
      * \param heading Runway true heading.
      * \param length Length in feet.
      * \param threshold Threshold length.
      * \param stopway Stopway length.
      * \param width Runway width in feet.
      * \param lighting Lighting code.
      * \param shoulder Shoulder code.
      * \param markings Ground markings code.
      * \param distance_remaining If runway has distance remaining signs
      * available.
      * \param gs_angle Glideslope angle.
      */
     Runway::Runway(Geod &pos, std::string &runway_number, double heading,
                    int length, double threshold, double stopway, int width,
                    int lighting, int surface, int shoulder, int markings,
                    bool distance_remaining) :
          Taxiway(pos, heading, length, width, lighting, surface),
          m_runway_number(runway_number),
          m_shoulder(shoulder),
          m_markings(markings),
          m_distance_remaining(distance_remaining)
     {
          char threshold_str[16];
          sprintf(threshold_str, "%f", threshold);
          m_threshold[0] = atoi(strtok(threshold_str, ",."));
          m_threshold[1] = atoi(strtok(NULL, ",."));

          char stopway_str[16];
          sprintf(stopway_str, "%f", stopway);
          m_stopway[0] = atoi(strtok(stopway_str, ",."));
          m_stopway[1] = atoi(strtok(NULL, ",."));
     }

     /** Destructor.
      */
     Runway::~Runway()
     {

     }

     void draw()
     {

     }

} // namespace fgradar
