/**
 * \file navaid_manager.cpp
 * \brief Implements class NavaidManager.
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

#include <stdlib.h>
#include <fstream>
#include <vector>

#include "io/file_manager.hpp"
#include "io/logger.hpp"
#include "navaid.hpp"
#include "navaid_manager.hpp"

namespace fgradar {

     NavaidManager *navaid_manager = NULL;

     /** Constructor.
      */
     NavaidManager::NavaidManager()
     {
          
     }

     /** Destructor.
      */
     NavaidManager::~NavaidManager()
     {

     }

     /**
      * \return False when an error occurred.
      *
      * Inits the navaid manager. Reads nav.dat and store all the information in
      * memory for future display/usage.
      */
     bool NavaidManager::init()
     {
          std::string path = file_manager->get_datadir() + "/nav.dat";

          std::ifstream file(path.c_str(), std::ifstream::in);
          if (!file.is_open()) {
               LOG(LOG_ERROR, "Failed to open nav.dat.");
               return false;
          }

          // Skips first 2 comments, which is the SO name where the file was
          // generated and the copyright notice.
          std::string comments;
          getline(file, comments);
          getline(file, comments);

          while (!file.eof()) {
               
               Navaid *curr_nav = NULL;
               
               int raw_type;
               NavType type;
               double lat, lon, alt, multiuse;
               int freq, range;
               std::string ident, name;

               file >> raw_type;

               switch (raw_type) { // Set the type
               case 2:  type = NDB;     break;
               case 3:  type = VOR;     break;
               case 4:
               case 5:  type = LOC;     break;
               case 6:  type = GS;      break;
               case 7:
               case 8:
               case 9:  type = MARKER;  break;
               case 12:
               case 13: type = DME;     break;
               case 99: // Continue to the next round, where it will exit the
                        // loop (end file was reached).
                    type = INVALID;
                    continue;
               default: // Unknown navaid type... we let the user know that
                    LOG(LOG_WARN, "Unknown navaid type while reading nav.dat.");
               }

               file >> lat >> lon >> alt >> freq >> range >> multiuse >> ident;
               getline(file, name);
               
               Geod pos = Geod::from_deg_ft(lat, lon, alt);
               curr_nav = new Navaid
                    (name, pos, type, freq, range, multiuse, ident);
               
               switch (type) {
               case NDB:
               case VOR:    m_nav_list.push_back(curr_nav);    break;
               case LOC:    m_loc_list.push_back(curr_nav);    break;
               case GS:     m_gs_list.push_back(curr_nav);     break;
               case MARKER: m_marker_list.push_back(curr_nav); break;
               case DME:    m_dme_list.push_back(curr_nav);    break;
               default:
                    // We will never reach this point, but anyways, some
                    // compilers prefer defaults for enums.
                    break;
               }
          }

          file.close();
          return true;
     }

     /**
      * Reinit the navaid manager. Clears the list and parse the file to
      * retrieve all the info again.
      */
     void NavaidManager::reinit()
     {
          if (!init())
               exit(1);
     }

     /**
      * \param cr Cairo context to draw at.
      * \param radar Radar to get properties from.
      *
      * Draws all the navaids.
      */
     void NavaidManager::draw(const Cairo::RefPtr<Cairo::Context> &cr,
                              const Radar &radar)
     {
          // for (std::vector<Navaid *>::const_iterator i = m_navaid_list.begin();
          //      i != m_navaid_list.end(); i++)
          //      (*i)->draw(cr, radar);
     }

     /**
      * \param ident Identification code for the navaid we want to find.
      * \return The navaid when found, NULL when it couldn't be found.
      *
      * Tries to find a navaid. Goes through the navaid_list and compares the
      * ident we want to find with the current navaid's ident.
      */
     Navaid *NavaidManager::find_by_ident(std::string ident)
     {
          // for (std::vector<Navaid *>::const_iterator i = m_navaid_list.begin();
          //      i != m_navaid_list.end(); i++) {
          //      if (ident.compare((*i)->get_ident()) == 0)
          //           return *i;
          // }

          return NULL;
     }

     /**
      * \param name Name of the navaid we want to find.
      * \return Navaid when found, NULL when not found.
      *
      * Finds a navaid by name, comparing the name we want to find with the
      * current navaid's name.
      */
     Navaid *NavaidManager::find_by_name(std::string name)
     {
          // for (std::vector<Navaid *>::const_iterator i = m_navaid_list.begin();
          //      i != m_navaid_list.end(); i++) {
          //      if (name.compare((*i)->get_name()) == 0)
          //           return *i;
          // }

          return NULL;
     }

} // namespace fgradar
