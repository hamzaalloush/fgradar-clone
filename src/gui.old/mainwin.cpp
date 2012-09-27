/**
 * \file mainwin.cpp
 * \brief Implements class MainWin.
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

#include <gtkmm/aboutdialog.h>
#include <iostream>

#include "include/config.h"
#include "util/utils.hpp"

#include "mainwin.hpp"
#include "preferencesdlg.hpp"
#include "radar.hpp"

namespace fgradar {
     
     /** Constructor.
      * Builds the main window.
      */
     MainWin::MainWin() :
          m_fullscreen(false),
          m_radar(NULL),
          m_prefsdlg(NULL)
     {
          set_title(std::string(PACKAGE) + " - " + VERSION);
          set_position(Gtk::WIN_POS_CENTER); // Better to have it centered on
                                             // the screen
          m_radar = new Radar;

          add(*m_radar);

          button.set_label("Preferences");
          button.signal_clicked().connect
               (sigc::mem_fun(*this, &MainWin::on_show_preferences_action));
          
          show_all_children();
     }

     /** Destructor. */
     MainWin::~MainWin()
     {
          delete m_radar;
     }

     /**
      * Toggles between fullscreen and windowed mode. Note: This doesn't always
      * work depending on the window manager.
      */
     void MainWin::on_toggle_fullscreen_action()
     {
          if (m_fullscreen) {
               unfullscreen();
               m_fullscreen = false;
          } else {
               fullscreen();
               m_fullscreen = true;
          }
     }

     /**
      * \param res Response from the preferences dialog.
      * Depending on the answer, performs an action or another. But it always
      * deletes the 'm_prefsdlg' dialog.
      */
     void MainWin::on_preferences_response(int res)
     {
          delete m_prefsdlg;
          m_prefsdlg = NULL;
     }

     /**
      * Shows the preferences dialog. Connects the response signal to a function
      * so it executes once the user has closed the preferences dialog.
      */
     void MainWin::on_show_preferences_action()
     {
          if (!m_prefsdlg) {
               m_prefsdlg = new PreferencesDlg;
               m_prefsdlg->signal_response().connect
                    (sigc::mem_fun(*this, &MainWin::on_preferences_response));
          }

          m_prefsdlg->present(); // Show it if it is hidden or minimized
     }

     /**
      * \brief Callback.
      * Shows a nice about dialog displaying authors, logo, program name and
      * some comments.
      */
     void MainWin::on_show_about_action()
     {
	  // Array with all the authors
	  std::vector<Glib::ustring> authors;
	  authors.push_back("Fernando Garcia <fernando.garli@gmail.com>");

	  // Finally create about dialog and set its attributes
	  Gtk::AboutDialog about;
	  about.set_name(PACKAGE);
	  about.set_program_name(PACKAGE);
	  about.set_version(VERSION);
	  about.set_logo(utils::get_icon(128));
	  about.set_copyright("Copyright \xc2\xa9 2012 Fernando Garcia");
	  about.set_comments("FGRadar is a stand-alone Air Traffic Control\n"
			     "client for the free and open-source FlightGear\n"
			     "flight simulator.");
	  about.set_license_type(Gtk::LICENSE_GPL_3_0);
	  about.set_authors(authors);
   
	  about.run(); // We don't care about the result
     }

} // namespace fgradar
