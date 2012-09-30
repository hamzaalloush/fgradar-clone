/**
 * \file projection.hpp
 * \brief Header for projection.cpp.
 */

// Copyright (C) 2012  Fernando García  <fernando.garli@gmail.com>

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

#ifndef _PROJECTION_HPP_
#define _PROJECTION_HPP_

#include <cmath>

#include "geod.hpp"
#include "vec2.hpp"

namespace fgradar {

     class Projection {
     public:

          virtual ~Projection() {}

          virtual Vec2 GeodToVec2(Geod &pos, Geod &eye_pos) = 0;
     };

     class MercatorProj : public Projection {
     public:
          
          virtual Vec2 GeodToVec2(Geod &pos, Geod &eye_pos) {

               double x = (pos.get_lon_rad() - eye_pos.get_lon_rad())
                    * pow(2.0, eye_pos.get_alt_ft());
               double y = (log(tan(pos.get_lat_rad()) + 1 / cos
                               (pos.get_lat_rad())))
                    * pow(2.0, eye_pos.get_alt_ft());

               std::cout << "x = " << x << " | y = " << y << std::endl;
               return Vec2(x, y);
          }
     };
     
} // namespace fgradar

#endif // _PROJECTION_HPP_
