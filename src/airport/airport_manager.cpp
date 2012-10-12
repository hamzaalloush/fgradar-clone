/**
 * \file airport_manager.cpp
 * \brief Implements class AirportManager.
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

#include <unistd.h>
#include <cstdlib>
#include <fstream>

#include "airport.hpp"
#include "airport_manager.hpp"
#include "runway.hpp"
#include "taxiway.hpp"
#include "io/file_manager.hpp"
#include "io/logger.hpp"
#include "utils/geod.hpp"

namespace fgradar {

     AirportManager *airport_manager = NULL;

     AirportManager::AirportManager()
     {
          reinit();
     }

     AirportManager::~AirportManager()
     {
          clear();
     }

     bool AirportManager::init()
     {
          std::string path = file_manager->get_datadir() + "/apt.dat";

          std::ifstream file(path.c_str(), std::ifstream::in);
          if (!file.is_open()) {
               LOG(LOG_ERROR, "Failed to open apt.dat.");
               return false;
          }

          // Skips first two comments
          std::string unused;
          getline(file, unused);
          getline(file, unused);

          while (!file.eof()) {

               int raw_type;
               file >> raw_type;

               switch (raw_type) {
               case AIRPORT:
               case SEAPLANE_BASE:
               case HELIPORT: // We don't care about the airport type (we will
                              // in the future though)
               {
                    double elevation;
                    bool has_tower;
                    std::string icao_code, name;

                    file >> elevation >> has_tower >> unused >> icao_code;
                    getline(file, name);

                    Geod pos = Geod::from_deg_ft(0.0, 0.0, elevation);

                    Airport *airport = new Airport
                         (pos, has_tower, icao_code, name);

                    m_airport_list.push_back(airport);

                    break;
               }
               case RUNWAY_TAXIWAY: // It is a runway or a taxiway
               {
                    double lat, lon, heading, threshold, stopway;
                    int length, width, lighting, surface, shoulder, markings;
                    bool distance_remaining;
                    std::string runway_number;

                    file >> lat >> lon >> runway_number >> heading >> length >>
                         threshold >> stopway >> width >> lighting >> surface >>
                         shoulder >> markings >> unused >> distance_remaining;

                    file.ignore(32, '\n'); // Ignore GS angle, we use ignore
                                           // because it is not always
                                           // displayed.

                    Geod pos = Geod::from_deg(lat, lon);

                    Airport *current_airport = m_airport_list.back();

                    // Taxiways have "xxx" instead of runway number, check if it
                    // is a taxiway
                    if (runway_number.compare("xxx") == 0) {
                         Taxiway *taxiway = new Taxiway
                              (pos, heading, length, width, lighting, surface);

                         current_airport->add_taxiway(taxiway);

                    } else { // It is not a taxiway, then it is a runway

                         Runway *runway = new Runway
                              (pos, runway_number, heading, length, threshold,
                               stopway, width, lighting, surface, shoulder,
                               markings, distance_remaining);

                         current_airport->add_runway(runway);
                    }

                    break;
               }
               case VIEWPOINT:
               {
                    double lat, lon;
                    int height; // Above ground level
                    std::string name;

                    file >> lat >> lon >> height >> unused;
                    getline(file, name);

                    Geod pos = Geod::from_deg_ft(lat, lon, height);

                    Airport *current_airport = m_airport_list.back();

                    Viewpoint *viewpoint = new Viewpoint(pos, name);
                    current_airport->set_viewpoint(viewpoint);

                    break;
               }
               case ATIS:
               case UNICOM:
               case CLEARANCE:
               case GROUND:
               case TOWER:
               case APPROACH:
               case DEPARTURE: // We don't care about the frequency type
               {
                    int freq;
                    std::string name;

                    file >> freq;
                    getline(file, name);

                    Airport *current_airport = m_airport_list.back();

                    Frequency *frequency = new Frequency(freq, name);
                    current_airport->add_frequency(frequency);

                    break;
               }
               default:
                    // While we are working on fully support for apt.dat, we
                    // will keep this empty, cause we haven't fully implemented
                    // all types.
                    std::string not_implemented;
                    getline(file, not_implemented);
               }
          }

          file.close();

          return true;
     }
     
     void AirportManager::clear()
     {
          m_airport_list.clear();
     }

     void AirportManager::reinit()
     {
          clear();

          if (!init())
               exit(1);
     }

     /**
      * \param cr Cairo context where we will draw at.
      * Draws all the airports.
      */
     void AirportManager::draw(const Cairo::RefPtr<Cairo::Context> &cr,
                               const Radar &radar)
     {
          for (std::vector<Airport *>::const_iterator i = m_airport_list.begin();
               i != m_airport_list.end(); i++)
               (*i)->draw(cr, radar);
     }

} // namespace fgradar
