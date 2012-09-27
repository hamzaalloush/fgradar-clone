/**
 * \file preferencesdlg.hpp
 * \brief Header for preferencesdlg.cpp.
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

#ifndef _PREFERENCESDLG_HPP_
#define _PREFERENCESDLG_HPP_

#include <gtkmm/dialog.h>
#include <gtkmm/window.h>

namespace fgradar {

     /**
      * \brief Preferences dialog.
      *
      * Builds a GTK dialog which will contain all the preferences. The
      * constructor takes the parent window.
      */
     class PreferencesDlg : public Gtk::Dialog {
     public:
          
          PreferencesDlg();
          
          virtual ~PreferencesDlg();
          
     private:

     };

} // namespace fgradar

#endif // _PREFERENCESDLG_HPP_
