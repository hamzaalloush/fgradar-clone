/**
 * \file radar.cpp
 * \brief Implements class Radar.
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

#include "airport/airport_manager.hpp"
#include "config/config.hpp"
#include "entity/navaid_manager.hpp"
#include "radar.hpp"
#include "util/utils.hpp"

namespace fgradar {

     Radar::Radar() :
          m_zoom(10),
          m_width(0),
          m_height(0)
     {
#ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
          signal_draw().connect(sigc::mem_fun(*this, &Radar::on_draw), false);
#endif
          
          m_eye_pos = Geod::from_deg(37.3938, -122.3938);

          add_events(Gdk::BUTTON_PRESS_MASK | Gdk::SCROLL_MASK);
     }

     Radar::~Radar()
     {
     }
     
     /**
      * \param Cairo context where we will draw in.
      * \return If we could manage the whole signal (draw signal).
      *
      * Overrides the default signal manager for the draw signal. This function
      * gets called when there is a change in window's size, position etc.
      */
     bool Radar::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
     {
          Gtk::Allocation allocation = get_allocation();

          m_width  = allocation.get_width();
          m_height = allocation.get_height();

          cr->set_line_width(0.5);

          cr->save();
          cr->set_source_rgba(0.0, 0.0, 0.0, 1.0);
          cr->paint();
          cr->restore();

          navaid_manager->draw(cr, *this);
          airport_manager->draw(cr, *this);

          draw_distance_markers(cr);

          return true;
     }

     bool Radar::on_scroll_event(GdkEventScroll *event)
     {
          if (event->direction == GDK_SCROLL_UP) {
               m_zoom++;
               redraw();
               return true;
          } else if (event->direction == GDK_SCROLL_DOWN) {
               m_zoom--;
               redraw();
               return true;
          }
   
          return Gtk::DrawingArea::on_scroll_event(event);
     }

     /**
      * Since we can't call 'on_draw' function directly because it is a signal
      * manager, we make a function that cleans the drawing area so 'on_draw' is
      * forced to draw everything again.
      */
     void Radar::redraw()
     {
          Glib::RefPtr<Gdk::Window> win = get_window();
   
          if (win) {
               Gdk::Rectangle r(0, 0, m_width, m_height);
               win->invalidate_rect(r, false);
          }
     }

     /**
      * \param cr Cairo context where we will draw in.
      *
      * Draw the distance markers, that is, the rings that go from the center to
      * the exterior of the radar every 5 miles.
      */
     void Radar::draw_distance_markers(const Cairo::RefPtr<Cairo::Context> &cr)
     {
          for (int i = 0; i < 12; i++) {
               cr->save();
               cr->set_source_rgba(0.3, 0.3, 0.3, 1.0);

               // Alternate continuous lines and pointed lines
               if (i % 2 != 0) {
                    std::valarray<double> dashes(2);
                    dashes[0] = 4.0;
                    dashes[1] = 4.0;
                    cr->set_dash(dashes, 0.0);
               }

               Geod ring_pos = Geod::from_deg
                    (m_eye_pos.get_lat_deg(), m_eye_pos.get_lon_deg() + i
                     / (DEGREES_TO_MILES / RING_RATE));

               cr->arc(m_width / 2, m_height / 2, utils::geod_to_vec2
                       (ring_pos, *this).get_x() - m_width
                       / 2, 0, 2 * M_PI);
      
               cr->stroke();
               cr->restore();
          }
     }

} // namespace fgradar
