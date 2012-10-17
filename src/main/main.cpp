/**
 * \file main.cpp
 * \brief main file
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

#include <iostream>

#include "fgradar.hpp"
#include "i18n.hpp"

using namespace fgradar;

int main(int argc, char *argv[])
{
     setlocale(LC_ALL, "");
     bindtextdomain(PACKAGE_LOWER, "/usr/share/locale");
     textdomain(PACKAGE_LOWER);
     
     try {
          fgradar_app = new FgradarApp(argc, argv);
          fgradar_app->run();
     }
     catch (...) {
          std::cerr << "Something went wrong. Aborting..." << std::endl;
     }

     delete fgradar_app;
     
     return 0;
}
