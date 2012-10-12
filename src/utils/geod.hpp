/**
 * \file geod.h
 * \brief Geodesic coordinates.
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

#ifndef _GEOD_H_
#define _GEOD_H_

#include "constants.hpp"

namespace fgradar {

     /**
      * \brief Represent Geodesic coordinates.
      *
      * Moving around with doubles containing latitude and longitudes is very
      * repetitive, isn't it? This class contains latitude, longitude and
      * altitude and allows us to choose between units.
      */
     class Geod {
     public:

          Geod() :
               m_lat(0),
               m_lon(0),
               m_alt(0) {
          }
          
          /**
           * \param lat Latitude in radians.
           * \param lon Longitude in radians.
           * \return Newly created Geod.
           * Factory for lat and lon in radians. No alt, so set to 0.
           */
          static inline Geod from_rad(double lat, double lon) {
               return Geod(lat / DEGREES_TO_RADIANS,
                           lon / DEGREES_TO_RADIANS, 0);
          }

          /**
           * \param lat Latitude in degrees.
           * \param lon Longitude in degrees.
           * \return Newly created Geod.
           * Factory for lat and lon in degrees. No alt, so set to 0.
           */
          static inline Geod from_deg(double lat, double lon) {
               return Geod(lat, lon, 0);
          }

          /**
           * \param lat Latitude in radians.
           * \param lon Longitude in radians.
           * \param alt Altitude in feets.
           * \return Newly created Geod.
           * Factory for lat and lon in radians. Alt in feets.
           */ 
          static inline Geod from_rad_ft(double lat, double lon, double alt) {
               return Geod(lat / DEGREES_TO_RADIANS,
                           lon / DEGREES_TO_RADIANS, alt);
          }

          /**
           * \param lat Latitude in radians.
           * \param lon Longitude in radians.
           * \param alt Altitude in meters.
           * \return Newly created Geod.
           * Factory for lat and lon in radians. Alt in meters.
           */
          static inline Geod from_rad_m(double lat, double lon, double alt) {
               return Geod(lat / DEGREES_TO_RADIANS,
                           lon / DEGREES_TO_RADIANS,
                           alt / FEETS_TO_METERS);
          }
     
          /**
           * \param lat Latitude in degrees.
           * \param lon Longitude in degrees.
           * \param alt Altitude in feets.
           * \return Newly created Geod.
           * Factory for lat and lon in degrees. Alt in feets.
           */
          static inline Geod from_deg_ft(double lat, double lon, double alt) {
               return Geod(lat, lon, alt);
          }

          /**
           * \param lat Latitude in degrees.
           * \param lon Longitude in degrees.
           * \param alt Altitude in meters.
           * \return Newly created Geod.
           * Factory for lat and lon in degrees. Alt in meters.
           */
          static inline Geod from_deg_m(double lat, double lon, double alt) {
               return Geod(lat, lon, alt / FEETS_TO_METERS);
          }


          /** \return Latitude in degrees. */
          inline double get_lat_deg() const {return m_lat;}

          /** \return Longitude in degrees. */
          inline double get_lon_deg() const {return m_lon;}

          /** \return Altitude in feets. */
          inline double get_alt_ft()  const {return m_alt;}

          /** \return Latitude in radians. */
          inline double get_lat_rad() const {return m_lat * DEGREES_TO_RADIANS;}
          
          /** \return Longitude in radians. */
          inline double get_lon_rad() const {return m_lon * DEGREES_TO_RADIANS;}

          /** \return Altitude in radians. */
          inline double get_alt_m()   const {return m_alt * FEETS_TO_METERS;}


          /** \param lat New latitude in degrees (no conversion needed). */
          inline void set_lat_deg(double lat) {m_lat = lat;}

          /** \param lon New longitude in degrees (no conversion needed). */
          inline void set_lon_deg(double lon) {m_lon = lon;}

          /** \param alt New altitude in feets (no conversion needed). */
          inline void set_alt_ft(double alt)  {m_alt = alt;}

          /** \param lat New latitude in radians (conversion needed). */
          inline void set_lat_rad(double lat) {m_lat = lat / DEGREES_TO_RADIANS;}
          
          /** \param lon New longitude in radians (conversion needed). */
          inline void set_lon_rad(double lon) {m_lon = lon / DEGREES_TO_RADIANS;}

          /** \param alt New altitude in meters (conversion needed). */
          inline void set_alt_m(double alt)   {m_alt = alt / FEETS_TO_METERS;}

          /**
           * \param geod Geod class we want to compare with this one.
           * \return If they are equal or not.
           *
           * Compares this object's latitude, longitude and altitude with
           * another's same variables.
           */
          inline bool operator==(Geod &geod) const {
               return (m_lon == geod.m_lon &&
                       m_lat == geod.m_lat &&
                       m_alt == geod.m_alt);
          }
     
     private:

          /** We can't make this constructor public since we don't know the
              units the user wants, that's why we use the factory design pattern. */
          Geod(double lat, double lon, double alt) :
               m_lat(lat),
               m_lon(lon),
               m_alt(alt) {
          }

          /** Actual latitude stored internally. It is stored in degrees, but
              thanks to the factory method, it automagically transforms the given
              values to degrees. */
          double m_lat;

          /** Actual longitude. Stored in degrees. */
          double m_lon;

          /** Actual altitude. Stored in feets. */
          double m_alt;
     };

}

#endif // _GEOD_H_
