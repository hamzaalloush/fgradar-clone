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
#include <glibmm/main.h>
#include <glibmm/thread.h>
#include <gtkmm/application.h>

/**
 * \brief Allocate memory and starts running the main loop.
 *
 * It checks for errors and exit the program if there's one. Otherwise, just
 * return 0 for a normal program exit.
 */
int main(int argc, char *argv[])
{
   if (!Glib::thread_supported())
      Glib::thread_init();
   
   Glib::RefPtr<Gtk::Application> app = Gtk::Application::create
      (argc, argv, "org.fgradar");

   std::cout << "OH YEAH IT WORKS" << std::endl;
   
   return 0;
}
