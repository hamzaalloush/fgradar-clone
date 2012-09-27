/**
 * \file file_system.hpp
 * \brief Header for file_system.cpp.
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

#ifndef _FILE_MANAGER_HPP_
#define _FILE_MANAGER_HPP_

#include <iostream>

namespace fgradar {

     /**
      * \brief Handles files and paths.
      *
      * This class manages all the file operations performed on the hard
      * disk. It also manages paths, such as data directory, configuration
      * directory etc.
      */
     class FileManager {
     public:
          
          FileManager();
          ~FileManager();

          bool Init();

          /** \return Data directory location. */
          std::string get_datadir() const {return m_datadir;}

          /** \return Configuration directory location. */
          std::string get_confdir() const {return m_confdir;}

          /**
           * Append to the datadir path the images folder.
           * \return Images directory in datadir.
           */
          std::string get_imgsdir() const {return m_datadir + "/imgs";}
          
     private:

          /** Data directory. Obtained from config.h and CMake settings defined
              by the user. */
          std::string m_datadir;

          /** Configuration directory, where we store configuration and log
              files. See 'create_config_directory' in order to know how we get
              this value. */
          std::string m_confdir;

          bool CreateConfigDirectory();

          bool FileExists(std::string path);
          bool MakeDirectory(std::string path);
     };

     extern FileManager *file_manager;

} // namespace fgradar

#endif // _FILE_MANAGER_HPP_
