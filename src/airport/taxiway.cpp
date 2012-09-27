/**
 * \file taxiway.cpp
 * \brief Implements class Taxiway.
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

#include <iostream>
#include "util/constants.hpp"
#include "util/utils.hpp"
#include "taxiway.hpp"

namespace fgradar {

     /** Constructor.
      * Initialize variables and convert some of them, perform neccesary
      * computations to have more useful data etc.
      */
     Taxiway::Taxiway(Geod &pos, double heading, int length, int width,
                      int lighting, int surface) :
          m_length(length),
          m_width(width),
          m_lighting(lighting),
          m_surface(surface)
     {
          int opposite_heading;

          // Compute opposite heading
          if (heading <= 180)
               opposite_heading = heading + 180;
          else
               opposite_heading = heading - 180;

          m_heading[0] = heading;
          m_heading[1] = opposite_heading;

          m_pos[0] = utils::dest_point(pos, opposite_heading, (length / 2)
                                       * FEETS_TO_MILES);
          m_pos[1] = utils::dest_point(pos, heading, (length / 2)
                                       * FEETS_TO_MILES);
     }

     /** Destructor.
      */
     Taxiway::~Taxiway()
     {
     }

     void Taxiway::draw()
     {
     }

} // namespace fgradar
