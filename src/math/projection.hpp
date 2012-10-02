/**
 * \file projection.hpp
 * \brief Manages map projections.
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

     /**
      * \brief Every map projection base class.
      *
      * This abstract class just holds the function all map projections need to
      * implement. We use an abstract class so we can hold a 'Projection' type
      * class, that can be any of its derived classes (all the different
      * projections).
      */
     class Projection {
     public:

          virtual ~Projection() {}

          /**
           * \param pos Geodesic position of the point we want to transform.
           * \param eye_pos Eye's geodesic position.
           * \return 2D point on the screen, result of the projection performed.
           *
           * Takes the geodesic position and eye's geodesic position and
           * computes the 2D position on the screen of the point. It has in
           * mind zoom level too (contained in eye position's altitude).
           */
          virtual Vec2 Transform(const Geod &pos, const Geod &eye_pos) = 0;
     };

     /**
      * \brief Implements Mercator map projection.
      *
      * This class implements the Mercator projection. This is a really basic
      * and cheap projection that is actually really useful for ATCing. The only
      * disadvange is the distortion produced in really high latitudes.
      */
     class MercatorProj : public Projection {
     public:

          virtual Vec2 Transform(const Geod &pos, const Geod &eye_pos) {

               int zoom = pow(2.0, eye_pos.get_alt_ft());
               
               double x = (pos.get_lon_rad() - eye_pos.get_lon_rad()) * zoom;
               double y = log(tan(pos.get_lat_rad()) + 1 / cos
                              (pos.get_lat_rad())) * zoom;

               return Vec2(x, y);
          }
     };
     
} // namespace fgradar

#endif // _PROJECTION_HPP_
