/**
 * \file utils.hpp
 * \brief Header for utils.cpp.
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

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <glibmm/ustring.h>

#include "gui/radar.hpp"
#include "geod.hpp"
#include "vec2.hpp"

namespace fgradar {

     namespace utils {
          
          double from_to(const Geod &start_pos, const Geod &end_pos,
                         const bool to_nm = true);
          int bearing(const Geod &start_pos, const Geod &end_pos);
          Geod dest_point(const Geod &geod, const int bearing,
                          const double distance);
          // int lon_to_screenx(const double lon, const double eye_lon,
          //                    const int zoom, const int screen_width);
          // int lat_to_screeny(const double lat, const double eye_lat,
          //                    const int zoom, const int screen_height);
          Vec2 geod_to_vec2(const Geod &pos, const Radar &radar);

          double xpoint_on_circle(const double radius, const double angle,
                                  const int xorigin);
          double ypoint_on_circle(const double radius, const double angle,
                                  const int xorigin);
          
          Glib::RefPtr<Gdk::Pixbuf> &get_icon(int size);

          void draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
                         std::string &text, Vec2 &pos, int char_size,
                         bool centered);

     } // namespace utils

} // namespace fgradar

#endif // _UTILS_HPP_
