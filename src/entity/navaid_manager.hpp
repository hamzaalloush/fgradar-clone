/**
 * \file navaid_manager.h
 * \brief Header for navaid_manager.cpp.
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

#ifndef _NAVAID_MANAGER_H_
#define _NAVAID_MANAGER_H_

#include <iostream>
#include "gui/radar.hpp"

namespace fgradar {

     class Navaid;

     /**
      * \brief Manages navaids.
      *
      * Handles all the navaids, without caring about their type. It provides
      * useful search functions as well as an ordered list from where we can
      * retrieve any navaid we want.
      */
     class NavaidManager {
     public:

          typedef std::vector<Navaid *> NavaidList;
          
          NavaidManager();

          ~NavaidManager();

          bool    init();
          void    reinit();

          void draw(const Cairo::RefPtr<Cairo::Context> &cr,
                    const Radar &radar);

          Navaid *find_by_ident(std::string ident);
          Navaid *find_by_name(std::string name);
          
     private:

          /** Nav list. Includes VORs and DMEs. */
          NavaidList m_nav_list;

          /** LOC list (includes localisers, LDAs and SDFs. */
          NavaidList m_loc_list;

          /** Glideslope list, associated with an ILS. */
          NavaidList m_gs_list;

          /** Marker beacons. Includes Outer Markers, Middle Markers and Inner
              Markers (OM, MM, IM). */
          NavaidList m_marker_list;

          /** DME list (distance measuring equipment. */
          NavaidList m_dme_list;
     };

     extern NavaidManager *navaid_manager;

} // namespace fgradar

#endif // _NAVAID_MANAGER_H_
