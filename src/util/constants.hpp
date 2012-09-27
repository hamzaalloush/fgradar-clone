/**
 * \file constants.hpp
 * \brief Some useful constants.
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

#ifndef _CONSTANTS_HPP_
#define _CONSTANTS_HPP_

namespace fgradar {

     const int EARTH_RADIUS = 6378; // Equatorial, KM

     const double DEGREES_TO_MILES = 69.11;
     const double DEGREES_TO_RADIANS = 0.0174532925;
     const double KILOMETERS_TO_MILES = 0.53995;
     const double FEETS_TO_METERS = 0.3048;
     const double FEETS_TO_MILES = 0.000189393939;

     const int RING_RATE = 10;
     const int NAVAID_SIZE = 6; // pixels
}

#endif // _CONSTANTS_HPP_
