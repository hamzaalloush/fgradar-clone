/**
 * \file utils.h
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

#ifndef _UTILS_H_
#define _UTILS_H_

#include <glibmm/ustring.h>

#include "math/geod.hpp"
#include "math/vec2.hpp"

namespace fgradar {

     namespace utils {
          
          double from_to(const Geod &start_pos, const Geod &end_pos,
                         const bool to_nm = true);
          int bearing(const Geod &start_pos, const Geod &end_pos);
          Geod dest_point(const Geod &geod, const int bearing,
                          const double distance);

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

#endif // _UTILS_H_
