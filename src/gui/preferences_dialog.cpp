/**
 * \file preferences_dialog.cpp
 * \brief Implements class PreferencesDialog.
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

#include <wx/button.h>
#include <wx/panel.h>
#include <wx/sizer.h>

#include "preferences_dialog.hpp"

namespace fgradar {

     BEGIN_EVENT_TABLE(PreferencesDialog, wxDialog)

     EVT_BUTTON(wxID_CLOSE, PreferencesDialog::OnButtonClose)
     
     END_EVENT_TABLE()

     PreferencesDialog::PreferencesDialog(wxWindow *parent,
                                          const wxString &title) :
          wxDialog(parent, wxID_ANY, title)
          
     {
          m_notebook = new wxNotebook
               (this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);
          m_notebook->AddPage(BuildTabGeneral(), wxT("General"));

          wxButton *close = new wxButton(this, wxID_CLOSE);

          wxBoxSizer *button_hbox = new wxBoxSizer(wxHORIZONTAL);
          button_hbox->Add(close);

          wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
          vbox->Add(m_notebook,  1, wxALL | wxEXPAND,      20);
          vbox->Add(button_hbox, 0, wxALL | wxALIGN_RIGHT, 20);

          SetSizer(vbox);

          Centre();
     }

     PreferencesDialog::~PreferencesDialog()
     {

     }

     wxWindow *PreferencesDialog::BuildTabGeneral()
     {
          wxWindow *general = new wxWindow(this, wxID_ANY);

          return general;
     }

     void PreferencesDialog::OnButtonClose(wxCommandEvent &WXUNUSED(event))
     {
          Close(true);
     }
     
} // namespace fgradar
