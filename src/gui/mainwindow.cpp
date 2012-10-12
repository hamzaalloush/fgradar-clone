/**
 * \file mainwindow.cpp
 * \brief Implements class MainWindow.
 */

// Copyright (C) 2012  Fernando García  <fernando.garli@gmail.com>

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

#include "mainwindow.hpp"

#include "include/config.h"

namespace fgradar {

     MainWindow::MainWindow()
     {
          set_title(std::string(PACKAGE) + " - " + VERSION);
     }

     MainWindow::~MainWindow()
     {

     }
     
} // namespace fgradar
