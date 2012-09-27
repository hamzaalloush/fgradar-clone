/**
 * \file navaid.cpp
 * \brief Implements class Navaid.
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
#include "config/config.hpp"
#include "navaid.hpp"
#include "util/constants.hpp"
#include "util/utils.hpp"
#include "util/vec2.hpp"

namespace fgradar {

     /**
      * \param name Complete name.
      * \param pos Geodesic position on the Earth.
      * \param type Navaid type, eg. DME, VOR...
      * \param freq Frequecy * 100.
      * \param range Range until available to be intercepted.
      * \param multiuse Has a value or another depending on the type.
      * \param ident ICAO code of the navaid.
      *
      * Creates a new navaid.
      */
     Navaid::Navaid(std::string &name, Geod &pos, NavType type, int freq,
                    int range, double multiuse, std::string &ident) :
          Entity(name, pos),
          m_type(type),
          m_freq(freq),
          m_range(range),
          m_multiuse(multiuse),
          m_ident(ident)
     {
     }

     Navaid::~Navaid()
     {
     }

     /**
      * \param cr Cairo context where we will draw.
      * \param radar Radar to get properties from.
      *
      * Draws the navaid on the cairo context. Depending on the navaid type,
      * draws a stuff or another. Also, checks if the navaid is out of the
      * screen. If it is, we don't waste time and resources drawing them.
      */
     void Navaid::draw(const Cairo::RefPtr<Cairo::Context> &cr,
                       const Radar &radar)
     {
          Vec2 origin(0, 0);
          Vec2 radar_size(radar.get_width(), radar.get_height());

          Vec2 scr_pos = utils::geod_to_vec2(m_pos, radar);

          if (scr_pos < origin || scr_pos > radar_size)
               return;

          switch (m_type) {
          case VOR: // It is a VOR
          {
               cr->save();
               
               cr->set_source_rgba(0.5, 0.5, 0.5, 1.0);
               cr->set_line_width(0.5);

               cr->rectangle(scr_pos.get_x() - NAVAID_SIZE / 2, scr_pos.get_y()
                             - NAVAID_SIZE / 2, NAVAID_SIZE, NAVAID_SIZE);

               Vec2 text_pos(scr_pos.get_x(), scr_pos.get_y() + 6);
               utils::draw_text(cr, m_ident, text_pos, 6, true);

               cr->stroke();
               cr->restore();
          }
          default:
               // Since we haven't implemented all navaids types, we just ignore
               // the non-implemented ones
               break;
          }
     }

} // namespace fgradar
