/**
 * \file map.h
 * \brief Header for map.cpp.
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

#ifndef _MAP_H_
#define _MAP_H_

#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include <iostream>

#include "projection.hpp"

namespace fgradar {

     class Map : public Gtk::DrawingArea {
     public:

          Map();
          virtual ~Map();

     protected:

          virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);
          
     private:

          /** Current projection. This projection is the one that are currently
              using to project things on the screen. To change the projection,
              just change the content of this variable to one of its derived
              classes. */
          Projection *m_projection;
     };
     
} // namespace fgradar

#endif // _MAP_H_
