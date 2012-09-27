/**
 * \file app.cpp
 * \brief Implements wxWidgets Application.
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

#include "include/config.h"

#include "gui/mainwin.hpp"

#include "io/file_manager.hpp"
#include "io/logger.hpp"

#include "app.hpp"

IMPLEMENT_APP(fgradar::FgradarApp)

using namespace fgradar;

/**
 * Overrides default application OnInit.
 *
 * Initialize modules and create main top level window. Basically, it is
 * overriding C/C++ app, since wxWidgets provides 'main' with IMPLEMENT_APP
 * macro.
 *
 * \return true when everything ok.
 */
bool FgradarApp::OnInit()
{
     if (!wxApp::OnInit())
          return false;

     file_manager = new FileManager;

     if (!Singleton<Logger>::GetInstance().Init("log.txt", LOG_WARN)) {
          std::cerr << "Failed to initialize log. No log messages are going "
               "to be outputted." << std::endl;
     }

     // navaid_manager  = new NavaidManager;
     // airport_manager = new AirportManager;

     MainWin *mainwin = new MainWin(wxT(PACKAGE));
     mainwin->Show(true);
     SetTopWindow(mainwin);

     return true;
}

int FgradarApp::OnExit()
{
     // if (!airport_manager) delete airport_manager;
     // if (!navaid_manager)  delete navaid_manager;
     if (!file_manager) delete file_manager;

     return 0;
}
