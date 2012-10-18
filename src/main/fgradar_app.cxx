/**
 * \file fgradar.cxx
 * \brief Implements class FgradarApp.
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

#include "fgradar_app.hxx"

namespace fgradar {

     FgradarApp *fgradar_app = NULL;

     FgradarApp::FgradarApp(int argc, char **argv) :
          SGApplication(argc, argv)
     {
          init();
     }

     FgradarApp::~FgradarApp()
     {

     }

     void
     FgradarApp::init()
     {
          createSubsystems();

          m_subsystem_mgr->init();
     }

     void FgradarApp::createSubsystems()
     {

     }

} // namespace fgradar
