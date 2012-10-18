 /**
 * \file fgradar_app.hxx
 * \brief Header file for fgradar_app.cxx.
 *
 * \ingroup main
 */

/*
 * FGRadar - a stand-alone ATC client for FlightGear.
 * Copyright (C) 2012  Fernando García  <fernando.garli@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
   
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _FGRADAR_APP_HXX_
#define _FGRADAR_APP_HXX_

#include <simgear/structure/SGApplication.hxx>

namespace fgradar {

     class FgradarApp : public SGApplication {
     public:

          FgradarApp(int argc, char **argv);
          virtual ~FgradarApp();

     protected:

          virtual void init();

     private:

          void createSubsystems();
     };

     extern FgradarApp *fgradar_app;
     
} // namespace fgradar

#endif // _FGRADAR_APP_HPP_
