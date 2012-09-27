/**
 * @file config.cpp
 * @brief Implements class Config.
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
#include "config.hpp"

namespace fgradar {

     Config *config = NULL;

     /** Constructor.
      */
     Config::Config()
     {
          m_screen_width  = 1024;
          m_screen_height = 768;
          m_eye_pos       = Geod::from_deg(37.6193, -122.3738);
          m_zoom          = 10;
     }

     /** Destructor.
      */
     Config::~Config()
     {

     }

} // namespace fgradar
