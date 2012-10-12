/**
 * \file layer.h
 * \brief Interface for all map layers.
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

#ifndef _LAYER_H_
#define _LAYER_H_

namespace fgradar {

     /**
      * \brief Interface for all map layers.
      *
      * Simple class used as interface for all its derived classes. It just
      * manages the drawing and visibility of the layer.
      */
     class Layer {
     public:

          Layer();
          virtual ~Layer();

          virtual void draw(const Cairo::RefPtr<Cairo::Context> &cr) = 0;

          /** \return If the layer is visible or not (user toggled). */
          bool get_visible()            const {return m_is_visible;}

          /** \param value New visibility value for the layer. */
          void set_visible(bool value = true) {m_is_visible = value;}

     private:

          /** Whether the layer is visible or not. This is toggled manually by
              the user, and set to true by default. */
          bool m_is_visible;
     };

     /**
      * \brief Post processing layer.
      *
      * This layer should be always the last one to render (as it name
      * indicates). It draws extra radar features such as compass markers,
      * distance range rings etc.
      */
     class PostProcessLayer : public Layer {
     public:

          PostProcessLayer();
          virtual ~PostProcessLayer();

          virtual void draw(const Cairo::RefPtr<Cairo::Context> &cr);
     };
     
} // namespace fgradar

#endif // _MAP_LAYER_H_
