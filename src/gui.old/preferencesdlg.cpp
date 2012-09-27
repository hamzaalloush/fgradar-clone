/**
 * \file preferencesdlg.cpp
 * \brief Implements class PreferencesDlg.
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

#include <gtkmm/button.h>
#include <gtkmm/notebook.h>
#include <gtkmm/stock.h>

#include "include/config.h"
#include "preferencesdlg.hpp"

namespace fgradar {

     /** Constructor
      * Builds the Preferences dialog.
      */
     PreferencesDlg::PreferencesDlg()
     {
          set_title(std::string(PACKAGE) + " - Preferences");
          set_border_width(5);
          set_resizable(true);
          
          // Creates the notebook
          Gtk::Notebook *notebook = manage(new Gtk::Notebook);

          // Set the tabs position on the top, set border width (5 is OK) and
          // shows the widget
          notebook->set_tab_pos(Gtk::POS_TOP);
          notebook->set_border_width(5);
          notebook->show();

          // Get the dialog vbox and packs the notebook there
          get_vbox()->pack_start(*notebook, true, true, 0);

          // Creates a close button. All changes are saved, always
          Gtk::Button *button = manage
               (new Gtk::Button(Gtk::Stock::CLOSE));
          button->property_can_default().set_value(true);
          button->show();
          add_action_widget(*button, Gtk::RESPONSE_CLOSE);

          // Set the default response to CLOSE
          set_default_response(Gtk::RESPONSE_CLOSE);
     }

     PreferencesDlg::~PreferencesDlg()
     {
     }

} // namespace fgradar
