/**
 * \file map_layer.cpp
 * \brief Implements several map layers.
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

#include "map_layer.hpp"

namespace fgradar {

     /**
      * \brief Constructor.
      * Default constructor for all map layers.
      */
     Layer::Layer() :
          m_is_visible(true) {}

     /// POST PROCESS LAYER ///

     /**
      * \brief Constructor.
      * Creates the post process layer.
      */
     PostProcessLayer::PostProcessLayer() :
          Layer() {}

     void PostProcessLayer::draw(const Cairo::RefPtr<Cairo::Context> &cr)
     {

     }
     
} // namespace fgradar
