/**
 * \file airport.cpp
 * \brief Implements class Airport.
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

#include "airport.hpp"
#include "config/config.h"
#include "runway.hpp"
#include "taxiway.hpp"
#include "utils/utils.hpp"
#include "utils/vec2.hpp"

namespace fgradar {

     /** Constructor.
      * \param pos Airport position.
      * \param has_tower If the airport has a control tower or not.
      * \param icao_code ICAO code of the airport.
      * \param name Airport full name.
      */
     Airport::Airport(Geod &pos, bool has_tower, std::string icao_code,
                      std::string name) :
          Entity(name, pos),
          m_has_tower(has_tower),
          m_icao_code(icao_code),
          m_viewpoint(NULL)
     {
     }

     /** Destructor.
      */
     Airport::~Airport()
     {
     }

     /**
      * \param cr Cairo context where we will draw at.
      *
      * Draws an airport. Draws runways, taxiways etc. ILS centerlines are
      * treated as navaids, so they get drawn on the navaid_manager.
      */
     void Airport::draw(const Cairo::RefPtr<Cairo::Context> &cr,
                        const Radar &radar)
     {
          // // Draw runways
          // for (std::vector<Runway *>::const_iterator i = m_runways.begin();
          //      i != m_runways.end(); i++) {

          //      Vec2 end[2];

          //      Vec2 origin(0.0, 0.0);
          //      Vec2 screen_size(radar.get_width(), radar.get_height());
               
          //      for (int j = 0; j < 2; j++)
          //           end[j] = utils::geod_to_vec2((*i)->get_pos(j), radar);
               
          //      if ((end[0] < origin && end[1] < origin)
          //          || (end[0] > screen_size && end[1] > screen_size))
          //          continue;

          //      cr->save();
          //      cr->set_source_rgba(0.0, 1.0, 0.0, 1.0);
          //      cr->move_to(end[0].get_x(), end[0].get_y());
          //      cr->line_to(end[1].get_y(), end[1].get_y());
          //      cr->stroke();
          //      cr->restore();
          // }
     }

} // namespace fgradar
