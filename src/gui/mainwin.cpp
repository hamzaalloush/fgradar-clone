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

#include <iostream>

#include <wx/msgdlg.h>
#include <wx/statusbr.h>
#include <wx/stattext.h>

#include "include/config.h"

#include "io/file_manager.hpp"

#include "mainwin.hpp"
#include "preferences_dialog.hpp"

namespace fgradar {

     BEGIN_EVENT_TABLE(MainWin, wxFrame)
     
     EVT_MENU(ID_FILE_CONNECT,     MainWin::OnFileConnect)
     EVT_MENU(ID_FILE_DISCONNECT,  MainWin::OnFileDisconnect)
     EVT_MENU(ID_FILE_QUIT,        MainWin::OnFileQuit)

     EVT_MENU(ID_VIEW_FULLSCREEN,  MainWin::OnViewFullscreen)

     EVT_MENU(ID_PREF_PREFERENCES, MainWin::OnPrefPreferences)

     EVT_MENU(ID_HELP_HELP,        MainWin::OnHelpHelp)
     EVT_MENU(ID_HELP_ABOUT,       MainWin::OnHelpAbout)

     EVT_CLOSE(MainWin::OnClose)
     END_EVENT_TABLE()

     /**
      * \brief Constructor.
      *
      * Create layout and view of the window. Setup container widgets and fill
      * them. Signal managers are implemented in separate functions.
      */
     MainWin::MainWin(const wxString &title) :
     wxFrame(NULL, wxID_ANY, title),
          m_file(NULL),
          m_help(NULL)
     {
          CreateStatusBar(2);
          
          int statusbar_size[2] = {-4, -1};
          SetStatusWidths(GetStatusBar()->GetFieldsCount(),
                          statusbar_size);
          
          BuildMenubar();

          ToggleConnected(false);
          
          Centre();
     }

     /**
      * \brief Destructor.
      */
     MainWin::~MainWin()
     {

     }

     /**
      * \brief Event manager.
      *
      * Gets called everytime the virtual function 'Close' is issued.
      *
      * Double check if the user really wants to close the program, since we
      * don't want the ATC to accidentally close the window and lose all the
      * non-saved info!
      */
     void MainWin::OnClose(wxCloseEvent &WXUNUSED(event))
     {
          wxMessageDialog *message_dialog = new wxMessageDialog
               (this, wxT("Are you sure you want to quit?"), wxT("Message"),
                wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION | wxCENTRE);
          
          // WXWIDGETS 2.9.0 ONLY, DEBIAN REPOSITORIES HAVE 2.8
          // message_dialog->SetExtendedMessage
          //      (wxT("Closing your ATC session without noticing pilots is not"
          //           "a good idea."));

          int result = message_dialog->ShowModal();
          message_dialog->Destroy();

          switch (result) {
          case wxID_YES: Destroy(); break;
          case wxID_NO:             break;
          default:
               // Unknown result (well, actually this can't be never reached
               // since the only possibilities are yes and no, but some
               // compilers complain about no-defaults in switches).
               break;
          }
     }

     /**
      * Build the main window menubar.
      *
      * Create all the menus (file, help etc.), append their respective items
      * defined in an enum, and append all the menus to the menubar.
      *
      * To see the event table, scroll up to the beginning of the current file.
      */
     void MainWin::BuildMenubar()
     {
          m_file = new wxMenu;
          m_file->Append(ID_FILE_CONNECT, wxT("&Connect"),
                wxT("Connect to any multiplayer server"));
          m_file->Append(ID_FILE_DISCONNECT, wxT("&Disconnect"),
                         wxT("Disconnect from the current server"));
          m_file->AppendSeparator();
          m_file->Append(ID_FILE_QUIT);

          m_view = new wxMenu;
          m_view->Append(ID_VIEW_FULLSCREEN, wxT("&Fullscreen"),
                         wxT("Toggle fullscreen mode"), wxITEM_CHECK);

          m_pref = new wxMenu;
          m_pref->Append(ID_PREF_PREFERENCES);

          m_help = new wxMenu;
          m_help->Append(ID_HELP_HELP);
          m_help->AppendSeparator();
          m_help->Append(ID_HELP_ABOUT);

          menubar = new wxMenuBar;
          menubar->Append(m_file, wxT("&File"));
          menubar->Append(m_view, wxT("&View"));
          menubar->Append(m_pref, wxT("&Preferences"));
          menubar->Append(m_help, wxT("&Help"));

          SetMenuBar(menubar);
     }
     
     void MainWin::OnFileConnect(wxCommandEvent &WXUNUSED(event))
     {
          ToggleConnected(true);
     }

     /**
      * \brief Event manager.
      *
      * Double check if the user really wants to quit from the server. If so,
      * disconnect from server.
      */
     void MainWin::OnFileDisconnect(wxCommandEvent &WXUNUSED(event))
     {
          wxMessageDialog *question_dialog = new wxMessageDialog
               (this, wxT("Do you really want to disconnect from the server?"),
                wxT("Message"), wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION
                | wxCENTRE);

          int result = question_dialog->ShowModal();
          question_dialog->Destroy();

          switch (result) {
          case wxID_YES: ToggleConnected(false); break;
          case wxID_NO:                          break;
          default:
               // Do nothing... same as if the user answered no to the
               // question. This default is reached when, for example, Alt+F4 is
               // issued.
               break;
          }
     }

     /**
      * \brief Event handler.
      *
      * Closes the application by menu. We call the virtual overriden method
      * 'Close' that sends an event, executing OnClose where we make sure the
      * user really wants to quit.
      */
     void MainWin::OnFileQuit(wxCommandEvent &WXUNUSED(event))
     {
          Close(true);
     }

     void MainWin::OnViewFullscreen(wxCommandEvent &event)
     {
          ShowFullScreen(event.IsChecked(), wxFULLSCREEN_NOBORDER
                         | wxFULLSCREEN_NOCAPTION );
     }

     void MainWin::OnPrefPreferences(wxCommandEvent &WXUNUSED(event))
     {
          PreferencesDialog *pref_dlg = new PreferencesDialog
               (this, wxT("Preferences"));

          pref_dlg->Show(true);
          
          pref_dlg->ShowModal();
          pref_dlg->Destroy();
     }

     void MainWin::OnHelpHelp(wxCommandEvent &WXUNUSED(event))
     {
          std::cout << "HELP" << std::endl;
     }

     void MainWin::OnHelpAbout(wxCommandEvent &WXUNUSED(event))
     {
          std::cout << "ABOUT" << std::endl;
     }

     /**
      * Toggle menu items Connect and Disconnect. When you are connected,
      * disable the Connect item and enable Disconnect, and viceversa when
      * disconnected.
      *
      * \param connected If we are connected or not.
      */
     void MainWin::ToggleConnected(bool connected)
     {
          wxMenuItem *connect = m_file->FindItem(ID_FILE_CONNECT);
          wxMenuItem *disconnect = m_file->FindItem(ID_FILE_DISCONNECT);

          m_connected = connected;

          if (connected) {
               connect->Enable(false);
               disconnect->Enable(true);
               
               SetStatusText(wxT("Online"), 1);
          } else {
               connect->Enable(true);
               disconnect->Enable(false);

               SetStatusText(wxT("Offline"), 1);
          }
     }

} // namespace fgradar
