/**
 * \file map.cpp
 * \brief Implements class Map.
 */

// Copyright (C) 2012  Fernando García  <fernando.garli@gmail.com>

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

#include "map.hpp"

namespace fgradar {

     Map::Map()
     {
          m_projection = new MercatorProj; // Use mercator by default
          
          // If default signal handlers aren't enabled by GLib, we connect the
          // draw signal to on_draw.
#ifndef GLIBMM_DEFAULT_SIGNAL_HANDLERS_ENABLED
          signal_draw().connect(sigc::mem_fun(*this, &Map::on_draw), false);
#endif
     }

     Map::~Map()
     {
          if (!m_projection) delete m_projection;
     }

     bool Map::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
     {
          std::cout << "I am drawing a map, yay!" << std::endl;

          return true;
     }
     
} // namespace fgradar
