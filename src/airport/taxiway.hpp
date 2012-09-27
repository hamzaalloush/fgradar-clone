/**
 * \file taxiway.hpp
 * \brief Header for taxiway.cpp.
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

#ifndef _TAXIWAY_HPP_
#define _TAXIWAY_HPP_

#include "util/geod.hpp"

namespace fgradar {

     /**
      * \brief Taxiway segment.
      *
      * Represents a taxiway. It is the base class for runway, since runway
      * shares the same info as a taxiway but with some extras.
      */
     class Taxiway {
     public:
          
          Taxiway(Geod &pos, double heading, int length, int width,
                  int lighting, int surface);

          virtual ~Taxiway();

          void draw();

          /** \return Geodesic position of the requested taxiway end. */
          Geod    get_pos(int end)     const {return m_pos[end];}

          /** \return Taxiway's heading in degrees. */
          int     get_heading(int end) const {return m_heading[end];}

          /** \return Length in feet. */
          int     get_length()         const {return m_length;}

          /** \return Width in feet. */
          int     get_width()          const {return m_width;}

          /** \return Raw lighting code. */
          int     get_lighting()       const {return m_lighting;}

          /** \return Raw surface code. */
          int     get_surface()        const {return m_surface;}

     protected:

          /** Geodesic position of both runway ends. */
          Geod    m_pos[2];

          /** Taxiway true heading in degrees. */
          double  m_heading[2];

          /** Taxiway length in feets. */
          int     m_length;

          /** Taxiway width in feets. */
          int     m_width;

          /** Digits representing the lights available for the taxiway. First
              three digits are the runway lighting code, while the final three
              digits are the opposite runway lighting code. */
          int     m_lighting;
          
          /** Surface code. Concrete, asphalt, etc. */
          int     m_surface;
     };

} // namespace fgradar

#endif // _TAXIWAY_HPP_

