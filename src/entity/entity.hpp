/**
 * \file entity.h
 * \brief Defines the base class for all the entities.
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

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <cairomm/context.h>
#include <iostream>
#include <vector>

#include "gui/radar.hpp"
#include "utils/geod.hpp"

namespace fgradar {
     
     /**
      * \brief Every single entity on the radar.
      *
      * Abstract class. We make classes that inherit from this one so we have
      * basic features already defined.
      */
     class Entity {
     public:
          
          Entity(std::string name, Geod &pos) : 
               m_is_shown(true),
               m_name(name),
               m_pos(pos) {
          }

          virtual ~Entity() {};

          virtual void draw(const Cairo::RefPtr<Cairo::Context> &cr,
                            const Radar &radar) = 0;
          
          /** \return Geodesic coordinates of the entity. */
          Geod         get_pos()          const  {return m_pos;}

          /** \return Entity's name. */
          std::string  get_name()         const  {return m_name;}

          /** \return Visibility of the entity. */
          bool         is_shown()         const  {return m_is_shown;}

     protected:
          
          /** Maybe the ATC doesn't want a navaid to be displayed or an aircraft
              to be disturbing! */
          bool         m_is_shown;
          
          /** Entity's name. Can be full or partial depending on the entity's
              type. */
          std::string  m_name;

          /** Entity's position (lat, lon and alt). */
          Geod         m_pos;
     };

} // namespace fgradar

#endif // _ENTITY_H_
