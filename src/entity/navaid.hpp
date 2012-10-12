/**
 * \file navaid.h
 * \brief Header for navaid.cpp.
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

#ifndef _NAVAID_H_
#define _NAVAID_H_

#include "entity.hpp"

namespace fgradar {

     /**
      * Since we have a single class for all the different types of
      * navaids, we use this enum to differenciate between them.
      */
     enum NavType {
          NDB,
          VOR,
          LOC,
          GS,
          MARKER,
          DME,
          INVALID,
          TOTAL_NAV_TYPES 
     };

     /**
      * \brief A navaid.
      *
      * Inherits from Entity. Represents a navaid of any type, such as LOC, GS,
      * VOR, DME etc. We have a variable storing that.
      */
     class Navaid : public Entity {
     public:

          Navaid(std::string &name, Geod &pos, NavType type, int freq,
                 int range, double multiuse, std::string &ident);

          virtual ~Navaid();

          virtual void draw(const Cairo::RefPtr<Cairo::Context> &cr,
                            const Radar &radar);
          
          /** \return Frequency * 100. */
          int          get_freq()      const  {return m_freq;}
          /** \return Range in miles. */
          int          get_range()     const  {return m_range;}

          /** \return A multiuse variable. */
          double       get_multiuse()  const  {return m_multiuse;}
          
          /** \return Identification. */
          std::string  get_ident()     const  {return m_ident;}

     private:

          NavType      m_type;

          /** Navaid's frequency multiplied by 100. So if the real one is
              110.60, the one saved is 11060. */
          int          m_freq;

          /** Range in miles until able to intercept. */
          int          m_range;
          
          /** Multiuse variable. Depending on the NavType, this value can
              contain one thing or another. */
          double       m_multiuse;

          /** Identification. It is not the full name. */
          std::string  m_ident;
     };

} // namespace fgradar

#endif // _NAVAID_H_
