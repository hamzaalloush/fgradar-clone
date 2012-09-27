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

#include <vector>

#include <wx/frame.h>
#include <wx/menu.h>

namespace fgradar {

     enum {
          ID_FILE_CONNECT     = 1,
          ID_FILE_DISCONNECT  = 2,
          ID_FILE_QUIT        = wxID_EXIT,

          ID_VIEW_FULLSCREEN  = 3,

          ID_PREF_PREFERENCES = wxID_PREFERENCES,

          ID_HELP_HELP        = wxID_HELP,
          ID_HELP_ABOUT       = wxID_ABOUT
     };

     /**
      * \brief Program's main window.
      *
      * Main top-level window in the program. This window is the parent for all
      * children dialogs. If this window is closed, all the rest are closed.
      */
     class MainWin : public wxFrame {
     public:
          
          MainWin(const wxString &title);

          virtual ~MainWin();
          
          DECLARE_EVENT_TABLE()
          
     protected:
          
          virtual void OnClose(wxCloseEvent &WXUNUSED(event));

     private:

          /** If the user is connected to any multiplayer server. This variable
              is set by ToggleConnected. */
          bool        m_connected;

          /** Main window menubar. Contains all the menus. It is initialized in
              the BuildMenubar function. When initialized, it is set to the
              frame. */
          wxMenuBar  *menubar;

          /** File menu. Contains basic program feature such as connecting and
              disconnecting to the server or just quitting the program. */
          wxMenu     *m_file;

          wxMenu     *m_view;
          
          wxMenu     *m_pref;

          /** Help menu. Contains help and about windows. */
          wxMenu     *m_help;

          void BuildMenubar();

          // Signal managers...
          void OnFileConnect(wxCommandEvent &WXUNUSED(event));
          void OnFileDisconnect(wxCommandEvent &WXUNUSED(event));
          void OnFileQuit(wxCommandEvent &WXUNUSED(event));
          void OnViewFullscreen(wxCommandEvent &event);
          void OnPrefPreferences(wxCommandEvent &WXUNUSED(event));
          void OnHelpHelp(wxCommandEvent &WXUNUSED(event));
          void OnHelpAbout(wxCommandEvent &WXUNUSED(event));

          void ToggleConnected(bool connected);
     };

} // namespace fgradar

#endif // _MAINWIN_HPP_
