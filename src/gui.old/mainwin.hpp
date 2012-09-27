/**
 * \file mainwin.hpp
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

#ifndef _MAINWIN_HPP_
#define _MAINWIN_HPP_

#include <gtkmm/grid.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>

namespace fgradar {

     class PreferencesDlg;
     class Radar;
     
     /**
      * \brief Program's main window.
      *
      * Creates a new GtkWindow. The main window contains basically all the most
      * important things such as the radar, text boxes etc. It is also parent of
      * all the rest of windows (childs).
      */
     class MainWin : public Gtk::Window {
     public:
          
          MainWin();

          virtual ~MainWin();

     private:

          Gtk::Button button;

          /** Whether if the window is in fullscreen or not. */
          bool            m_fullscreen;

          /** The main grid. We will store all the main window's widgets
           * here. Since it does have a fixed size, we must tell that to the
           * widgets or the window itself. */
          Gtk::Grid       m_grid;

          /** The radar widget (it is just a drawing area). */
          Radar          *m_radar;

          /** The preferences dialog. */
          PreferencesDlg *m_prefsdlg;

          void on_toggle_fullscreen_action();
          void on_preferences_response(int res);
          void on_show_preferences_action();
          void on_show_about_action();
     };

} // namespace fgradar

#endif // _MAINWIN_HPP_
