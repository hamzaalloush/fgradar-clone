/**
 * \file utils.cpp
 * \brief Several utilities to make programming easier.
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

#include <cmath>
#include <glibmm/fileutils.h>

#include "config/config.hpp"
#include "io/file_manager.hpp"
#include "io/logger.hpp"
#include "constants.hpp"
#include "utils.hpp"

namespace fgradar {

     namespace utils {

          /**
           * \param start_pos Starting position.
           * \param end_pos Ending position.
           * \param to_nm Optional. If we want the distance in miles.
           * \return Distance between the 2 points in miles.
           *
           * Computes the distance between 2 points in the Earth. Returns
           * the distance between them in miles or km.
           *
           * By default, algorithm returns the distance in kilometers, but
           * we need it in miles. And since latitude and longitude are
           * given in degrees, the functions needs to convert them into
           * radians.
           *
           * When the distance is computed, we check that altitudes aren't
           * the same. If they are, we just return the value previously
           * calculated. If they aren't, we need to do some pitagoras.
           *
           * Algorithm taken from:
           * <http://www.movable-type.co.uk/scripts/latlong.html>
           */
          double from_to(const Geod &start_pos, const Geod &end_pos,
                         const bool to_nm)
          {
               double lat_dist_rad = end_pos.get_lat_rad() - 
                    start_pos.get_lat_rad();
               double lon_dist_rad = end_pos.get_lon_rad() -
                    start_pos.get_lon_rad();

               double a = sin(lat_dist_rad / 2) * sin(lat_dist_rad / 2) +
                    sin(lon_dist_rad / 2) * sin(lon_dist_rad / 2) *
                    cos(start_pos.get_lat_rad()) *
                    cos(end_pos.get_lat_rad());

               double c = 2 * atan2(sqrt(a), sqrt(1 - a)); 

               double distance = EARTH_RADIUS * c;
                    
               if (to_nm)
                    distance *= KILOMETERS_TO_MILES;

               return distance;
          }

          /**
           * \param start_pos Starting position.
           * \param end_pos Ending position.
           * \return Bearing in degrees.
           *
           * Computes the bearing of an object based on its latitude and
           * longitude and its previous latitude and longitude.
           *
           * The algorithm needs the values in radians.
           *
           * Algorithm taken from:
           * <http://www.movable-type.co.uk/scripts/latlong.html>
           */
          int bearing(const Geod &start_pos, const Geod &end_pos)
          {
               double lon_dist_rad = start_pos.get_lon_rad() -
                    end_pos.get_lon_rad();
                    
               return (int)atan2(sin(lon_dist_rad) * cos(end_pos.get_lat_rad()),
                                 cos(start_pos.get_lat_rad()) *
                                 sin(end_pos.get_lat_rad()) -
                                 sin(start_pos.get_lat_rad()) *
                                 cos(end_pos.get_lat_rad()) *
                                 cos(lon_dist_rad)) / DEGREES_TO_RADIANS;
          }

          /**
           * \param start_pos Starting position.
           * \param bearing Object's bearing.
           * \param distance Distance the object has run.
           * \return Destination point.
           *
           * Computes the destination point given a distance, bearing and
           * starting point.
           *
           * Distance is given in nm but we need it in km.
           *
           * When both, destination longitude and latitude are computed, we
           * check the 'return_lon' value. If true, we return longitude. If
           * false, we return latitude. This is done because both algorithms
           * (latitude and longitude ones) need both starting latitude and
           * longitude. So instead of doing two duplicated functions, we
           * have a variable that returns one value or another.
           *
           * Algorithm taken from:
           * <http://www.movable-type.co.uk/scripts/latlong.html>
           */
          Geod dest_point(const Geod &start_pos, const int bearing,
                          const double distance)
          {
               double dst_km = distance / KILOMETERS_TO_MILES;
               double brng_rad = bearing * DEGREES_TO_RADIANS;

               double dest_lat = asin
                    (sin(start_pos.get_lat_rad()) * cos(dst_km / EARTH_RADIUS)
                     + cos(start_pos.get_lat_rad()) * sin(dst_km / EARTH_RADIUS)
                     * cos(brng_rad));

               double dest_lon = start_pos.get_lon_rad()
                    + atan2(sin(brng_rad) * sin(dst_km / EARTH_RADIUS)
                            * cos(start_pos.get_lat_rad()),
                            cos(dst_km / EARTH_RADIUS)
                            - sin(start_pos.get_lat_rad()) * sin(dest_lat));

               Geod dest_pos = Geod::from_rad_ft(dest_lat, dest_lon,
                                                 start_pos.get_alt_ft());

               return dest_pos;
          }

          /**
           * \param pos Geodesic position we want to translate on screen pos.
           * \param radar Radar to get properties from.
           * \return Screen position.
           *
           * Using mercator projection, translates geodesic position into screen
           * position, taking in count zoom and eye position.
           */
          Vec2 geod_to_vec2(const Geod &pos, const Radar &radar)
          {
               int zoom = pow(2.0, radar.get_zoom());

               int x = (((pos.get_lon_rad() - radar.get_eye_pos().get_lon_rad())
                         / M_PI) / DEGREES_TO_RADIANS) * zoom
                    + radar.get_width() / 2;

               int eye_y = (log(tan(radar.get_eye_pos().get_lat_rad()) + 1.0
                                / cos(radar.get_eye_pos().get_lat_rad())) / M_PI)
                    / DEGREES_TO_RADIANS * zoom;

               int y = ((-(log(tan(pos.get_lat_rad()) + 1.0
                               / cos(pos.get_lat_rad())) / M_PI)
                         / DEGREES_TO_RADIANS) * zoom) + radar.get_height() / 2
                    + eye_y;
               
               return Vec2(x, y);
          }
          
          /**
           * \param radius Circle radius.
           * \param angle Angle in degrees.
           * \param xorigin Circle center.
           * \return X position of a point in a circle.
           *
           * Computes the position of a point in the edge of a circle given
           * its radius, its origin and an angle.
           *
           * It needs the angle in radians, so we convert the angle in
           * degrees to radians.
           */
          double xpoint_on_circle(const double radius, const double angle,
                                  const int xorigin)
          {
               return (double)(radius * cos((angle - 90) * DEGREES_TO_RADIANS))
                    + xorigin;
          }

          /**
           * \param radius Circle radius.
           * \param angle Angle in degrees.
           * \param yorigin Circle center.
           * \return Y position of a point in a circle.
           *
           * Computes the position of a point in the edge of a circle given
           * its radius, its origin and an angle.
           *
           * It needs the angle in radians, so we convert the angle in
           * degrees to radians.
           */
          double ypoint_on_circle(const double radius, const double angle,
                                  const int yorigin)
          {
               return(double)(radius * sin((angle - 90) * DEGREES_TO_RADIANS))
                    + yorigin;
          }

          /**
           * \return The pixbuf loaded from a file.
           * Creates a Gdk::Pixbuf from the icon file and returns it.
           */
          Glib::RefPtr<Gdk::Pixbuf> &get_icon(int size)
          {
               static Glib::RefPtr<Gdk::Pixbuf> icon;

               char size_str[8];
               sprintf(size_str, "%d", size);

               try {
                    icon = Gdk::Pixbuf::create_from_file
                         (file_manager->get_datadir() + "/icons/icon" + size_str
                              + ".png");
               } catch (const Glib::Exception &ex) {
                    LOG(LOG_WARN, ex.what());
               }

               return icon;
          }

          /**
           * \param cr Cairo context to draw at.
           * \param text Text we are drawing.
           * \param pos Position on the screen.
           * \param char_size Character size in points.
           * \param centered If we want it centered or not.
           *
           * Draws text using Pango, and then prints the result in the cairo
           * context.
           */
          void draw_text(const Cairo::RefPtr<Cairo::Context>& cr,
                         std::string &text, Vec2 &pos, int char_size,
                         bool centered)
          {
               int text_width = 0, text_height = 0;
               char buffer[9];
               sprintf(buffer, "%d", char_size);

               std::string description = "Monospace normal ";
               description += buffer;

               Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(cr);
               Pango::FontDescription font(description.c_str());

               layout->set_text(text);
   
               font.set_weight(Pango::WEIGHT_ULTRALIGHT);
               font.set_stretch(Pango::STRETCH_EXTRA_CONDENSED);

               layout->set_font_description(font);
               layout->get_pixel_size(text_width, text_height);

               if (centered)
                    cr->move_to(pos.get_x() - (text_width / 2), pos.get_y());
               else
                    cr->move_to(pos.get_x(), pos.get_y());

               layout->show_in_cairo_context(cr);
          }

     } // namespace utils

} // namespace fgradar
