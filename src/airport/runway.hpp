/**
 * \file runway.h
 * \brief Header for runway.cpp.
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

#ifndef _RUNWAY_H_
#define _RUNWAY_H_

#include <iostream>
#include "utils/geod.hpp"
#include "taxiway.hpp"

namespace fgradar {

     /**
      * \brief Runway class.
      *
      * Inherits from Taxiway. It shares the same attributes as a taxiway, it
      * just adds some extra features.
      */
     class Runway : public Taxiway {
     public:
          
          Runway(Geod &pos, std::string &runway_number, double heading,
                 int length, double threshold, double stopway, int width,
                 int lighting, int surface, int shoulder, int markings,
                 bool distance_remaining);

          ~Runway();

          void draw();

          /** \return Runway number. */
          std::string  get_runway_number()      const {return m_runway_number;}

          /**
           * \param end Runway end threshold we want to retrieve.
           * \return Threshold of requested end.
           */
          int          get_threshold(int end)   const {return m_threshold[end];}

          /**
           * \param end Runway end stopway we want.
           * \return Stopway length for that end.
           */
          int          get_stopway(int end)     const {return m_stopway[end];}

          /** \return Shoulder code. */
          int          get_shoulder()           const {return m_shoulder;}

          /** \return Ground markings code. */
          int          get_markings()           const {return m_markings;}

          /** \return If distance remaining signs are available or not. */
          bool         has_distance_remaining() const
               {return m_distance_remaining;}

     private:

          /** Runway number. When there is no runway suffix, an x is displayed
              instead, but removed here. */
          std::string  m_runway_number;

          /** Threshold length for both ends of the runway. */
          int          m_threshold[2];

          /** Stopway length for both ends. */
          int          m_stopway[2];

          /** Runway shoulder code. 0 indicates there is no shoulder. */
          int          m_shoulder;

          /** Ground markings code. */
          int          m_markings;

          /** If the runway has distance remaining signs or not. */
          bool         m_distance_remaining;
     };

} // namespace fgradar

#endif // _RUNWAY_H_
