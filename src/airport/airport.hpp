/**
 * \file airport.hpp
 * \brief Header for airport.cpp.
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

#ifndef _AIRPORT_HPP_
#define _AIRPORT_HPP_

#include "entity/entity.hpp"

namespace fgradar {

     /**
      * \brief A frequency structure.
      * Stores a frequency with its name. The frequency is multiplied by 100,
      * so it is declared as an integer.
      */
     struct Frequency {
          int          freq;
          std::string  name;
          
          Frequency(int nfreq, std::string nname) :
               freq(nfreq),
               name(nname) {};
     };

     /**
      * \brief A viewpoint structure.
      * Stores airport viewpoint location and its name.
      */
     struct Viewpoint {
          Geod         pos;
          std::string  name;
          
          Viewpoint(Geod &npos, std::string nname) :
               pos(npos),
               name(nname) {};
     };

     class Runway;
     class Taxiway;

     /**
      * \brief An airport.
      *
      * Inherits from Entity. Represents an airport on the radar. Also stores
      * runways, taxiways and all related airport features.
      */
     class Airport : public Entity {
     public:
          
          Airport(Geod &pos, bool has_tower, std::string icao_code,
                  std::string name);

          virtual ~Airport();

          virtual void draw(const Cairo::RefPtr<Cairo::Context> &cr,
                            const Radar &radar);

          /**
           * \param runway Runway to append.
           * Appends a runway to the airport.
           */
          void add_runway(Runway *runway)     {m_runways.push_back(runway);}

          /**
           * \param taxiway Taxiway to append.
           * Appends a taxiway to the airport.
           */
          void add_taxiway(Taxiway *taxiway)  {m_taxiways.push_back(taxiway);}

          /**
           * \param freq Frequency to append.
           * Appends a frequency to the airport.
           */
          void add_frequency(Frequency *freq) {m_frequencies.push_back(freq);}

          /**
           * \param viewpoint Viewpoint we want to set.
           * Sets the airport viewpoint. Only 1 per airport.
           */
          void set_viewpoint(Viewpoint *view) {m_viewpoint = view;}

          /** \return If the airport has a control tower or not. */
          bool has_control_tower() const {return m_has_tower;}

          /** \return ICAO code of the airport. */
          std::string get_icao_code() const {return m_icao_code;}

     private:

          /** If the airport has a control tower or not. */
          bool                      m_has_tower;

          /** ICAO code of the airport. */
          std::string               m_icao_code;

          Viewpoint                *m_viewpoint;

          /** Vector containing all the available runways in the airport */
          std::vector<Runway *>     m_runways;

          /** Vector containing all the taxiways on the airport. The bad thing
              is that apt.dat doesn't provide taxiways names. */
          std::vector<Taxiway *>    m_taxiways;

          /** Vector containing all the frequencies available on the airport. */
          std::vector<Frequency *>  m_frequencies;
     };

} // namespace fgradar

#endif // _AIRPORT_HPP_
