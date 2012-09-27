/**
 * \file preferences_dialog.hpp
 * \brief Header for preferences_dialog.cpp.
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

#ifndef _PREFERENCES_DIALOG_HPP_
#define _PREFERENCES_DIALOG_HPP_

#include <wx/dialog.h>
#include <wx/notebook.h>

namespace fgradar {

     class PreferencesDialog : public wxDialog {
     public:

          PreferencesDialog(wxWindow *parent, const wxString &title);
          
          virtual ~PreferencesDialog();

          DECLARE_EVENT_TABLE()
          
     private:

          wxNotebook *m_notebook;

          wxWindow *BuildTabGeneral();

          void OnButtonClose(wxCommandEvent &WXUNUSED(event));
     };
     
} // namespace fgradar

#endif // _PREFERENCES_DIALOG_HPP_
