/**
 * @file config.hpp
 * @brief Header for config.hpp.
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

#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include "util/geod.hpp"

namespace fgradar {

     /**
      * @brief Stores configuration.
      *
      * Stores all the configuration parameters, user and not user
      * dependant. When we init the program, it reads configuration file and
      * fill the variables. When we exit, it saves all the stored info.
      */
     class Config {
     public:

          Config();

          ~Config();

          /**
           * @param w New screen width in pixels.
           * @param h New screen height in pixels.
           */
          void set_screen_size(int w, int h)
               {m_screen_width = w; m_screen_height = h;}

          /** @param eye_pos New eye position to set. */
          void set_eye_pos(Geod &eye_pos) {m_eye_pos = eye_pos;}

          /** @param zoom New zoom. */
          void set_zoom(int zoom)         {m_zoom += zoom;}


          /** @return Screen width in pixels. */
          int  get_screen_width()  const {return m_screen_width;}

          /** @return Screen height in pixels. */
          int  get_screen_height() const {return m_screen_height;}

          /** @return Eye position in geodesic coordinates. */
          Geod get_eye_pos()       const {return m_eye_pos;}

          /** @return Zoom. */
          int  get_zoom()          const {return m_zoom;}

     private:

          /** Screen width in pixels. */
          int  m_screen_width;

          /** Screen height in pixels. */
          int  m_screen_height;

          /** Eye position in geodesic coordinates. Used to determine where to
              draw things on the screen. Here, the altitude represents the zoom
              level. */
          Geod m_eye_pos;

          /** Eye zoom. */
          int  m_zoom;
     };

     extern Config *config;
     
} // namespace fgradar

#endif // _CONFIG_HPP_
