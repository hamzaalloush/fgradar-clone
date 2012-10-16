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

#include "i18n.hpp"

#include "io/file_manager.hpp"
#include "io/logger.hpp"

#include "FGRadarApplication.hxx"

using namespace fgradar;

namespace {

     /**
      * Initialize program.
      * Allocate memory for some modules, initialize singletons etc.
      */
     void Init()
     {
          file_manager = new FileManager;

          if (!Singleton<Logger>::GetInstance().Init("log.txt", LOG_WARN)) {
               std::cerr << "Failed to initialize log, no log messages will"
                    "be outputted." << std::endl;
          }
     }

     /**
      * Shutdown program.
      * Free previously allocated memory. Some modules get free automagically,
      * so we don't need to add them here (for example, singletons).
      */
     void Shutdown()
     {
          if (!file_manager) delete file_manager;
     }

}

int main(int argc, char *argv[])
{
     using namespace std;

     setlocale(LC_ALL, "");
     bindtextdomain(PACKAGE_LOWER, "/usr/share/locale");
     textdomain(PACKAGE_LOWER);
     
     Init();
     try {
      FGRadarApplication app(argc,argv);
      app.Run();
      return 0;
     }
     catch( ... ) {
      cerr << "Sorry, your program terminated." << endl;
     }
     Shutdown();
     
     return 0;
}
