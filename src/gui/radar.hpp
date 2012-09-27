/**
 * \file radar.hpp
 * \brief Header for radar.cpp.
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

#ifndef _RADAR_HPP_
#define _RADAR_HPP_

#include <gtkmm/drawingarea.h>

#include "util/geod.hpp"

namespace fgradar {

     /**
      * \brief Creates the radar widget.
      *
      * Builds a drawing area where we will draw all the aircrafts, navaids,
      * fixes etc.
      */
     class Radar : public Gtk::DrawingArea {
     public:

          Radar();

          virtual ~Radar();
          
          /** \return Geodesic eye position. */
          Geod  get_eye_pos() const {return m_eye_pos;}

          /** \return Radar zoom. */
          int   get_zoom()    const {return m_zoom;}

     protected:

          virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);
          virtual bool on_scroll_event(GdkEventScroll *event);

     private:

          /** Geodesic eye position. */
          Geod m_eye_pos;

          /** Radar zoom. */
          int  m_zoom;

          /** Radar allocation width in pixels. The same as
              get_allocation()->get_width() */
          int  m_width;

          /** Radar allocation height in pixels. The same as
              get_allocation()->get_height() */
          int  m_height;

          void redraw();
          void draw_distance_markers(const Cairo::RefPtr<Cairo::Context> &cr);
     };
     
} // namespace fgradar

#endif // _RADAR_HPP_
