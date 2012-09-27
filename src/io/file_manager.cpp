/**
 * \file file_system.cpp
 * \brief Manages file system utilities.
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

#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cstring>

#ifdef __unix__
#include <sys/stat.h>
#elif defined _WIN32
#include <windows.h>
#endif

#include "include/config.h"

#include "file_manager.hpp"

namespace fgradar {

     FileManager *file_manager = NULL;

     /** Constructor.
      *
      * NOTE: Since the file manager is the first thing we need to initialize,
      * the file manager can't use the logger, so it has to use screen
      * output without writting to logfile.
      */
     FileManager::FileManager()
     {
          if (!Init()) {
               std::cerr << "Aborting..." << std::endl;
               exit(1);
          }
     }

     /** Destructor. */
     FileManager::~FileManager()
     {
     }

     /**
      * Initializes the file manager.
      * Create directories and setup everything for later use.
      *
      * Gets datadir location and check and create configuration
      * directory. Exit if it couldn't be performed.
      */
     bool FileManager::Init()
     {
#ifdef DATADIR
          m_datadir = DATADIR;
#else
     std:cerr << "ERROR: DATADIR not defined while building. Please specify"
               "data directory manually by the command line." << std::endl;
          return false;
#endif
          
          // Check and create configuration directory, depending on platform
          if (!CreateConfigDirectory()) {
               std::cerr << "ERROR: Failed to create configuration directory."
                         << std::endl;
               return false;
          }

          return true;
     }

     /**
      * Tries to create the configuration directory depending on platform.
      *
      * If we are in an Unix derived system, we first try with XDG conf dir,
      * which corresponds to '$HOME/.config'. If it doesn't exist or it is not
      * defined, we try to create it. If we couldn't create it, we use HOME.
      *
      * In Windows we try with APPDATA. If that doesn't work, we use current
      * directory, '.'.
      *
      * If we are not in an unix derived system or Windows, we just exit since
      * we don't know where to store things.
      *
      * @todo Do some special things for MAC users.
      */
     bool FileManager::CreateConfigDirectory()
     {
#ifdef __unix__

          if (getenv("XDG_CONFIG_HOME") != NULL)
               m_confdir = getenv("XDG_CONFIG_HOME");
          else {

               std::cout << "INFO: Couldn't get XDG configuration directory, "
                    "trying to create it...";
               
               m_confdir = getenv("HOME");
               m_confdir += "/.config";

               if (!MakeDirectory(m_confdir)) {
                    std::cerr << std::endl << "WARNING: Couldn't create XDG"
                         ".config, using HOME." << std::endl;

                    // In a Linux system, HOME directory SHOULD be always
                    // available for each user...
                    m_confdir = getenv("HOME");
               } else
                    std::cout << " works!" << std::endl;
          }

#elif defined _WIN32
          
          if (getenv("APPDATA") != NULL)
               m_confdir = getenv("APPDATA");
          else {
               std::cerr << "WARNING: Can't locate APPDATA, using current"
                    "directory." << std::endl;
               m_confdir = ".";
          }

#else
          std::cerr << "Unsupported platform." << std::endl;
          return false;
#endif

          m_confdir += "/";
          m_confdir += PACKAGE_LOWER;
          
          if (!MakeDirectory(m_confdir)) {
               std::cerr << "ERROR: Can't create configuration directory."
                         << std::endl;
               return false;
          }

          return true;
     }

     /**
      * Checks a file exists depending on platform.
      *
      * With Unix derived systems, we use 'stat'. In Windows, we don't have a
      * function that really tells us if a file exists or not, so we use
      * GetFileAttributes, which returns, among other errors, if the file exists
      * or not.
      *
      * \param path File to check.
      * \return true when it exists, false when it doesn't.
      */
     bool FileManager::FileExists(std::string path)
     {
          bool result = false;
          
#ifdef __unix__
          struct stat st;

          result = stat(path.c_str(), &st);
#elif defined _WIN32
          DWORD file_attr;

          file_attr = GetFileAttributes(fileName);
          result = (file_attr == 0xFFFFFFFF);
#endif

          return result;
     }

     /**
      * Creates a directory depending on platform.
      *
      * When using an Unix derived system, we use 'mkdir'. Included in
      * sys/stat.h, it recieves the path and permissions, in this case,
      * 0775. When using Windows, we use CreateDirectory, which just recieves
      * the path.
      *
      * \param path Path where we want to create the directory.
      * \return true when it could be created, false it couldn't.
      */
     bool FileManager::MakeDirectory(std::string path)
     {
          bool result = false;
          
#ifdef __unix__
          result = mkdir(path.c_str(), 0775);
#elif defined _WIN32
          result = CreateDirectory(path.c_str());
#endif

          return result;
     }
     
} // namespace fgradar
