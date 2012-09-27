/**
 * @file logger.cpp
 * @brief Implements class Logger.
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

#include <cstdlib>

#include "file_manager.hpp"
#include "logger.hpp"

namespace fgradar {

     /**
      * \brief Constructor.
      * Initialize variables.
      */
     Logger::Logger() :
          m_verbosity(0)
     {
     }

     /**
      * \brief Destructor.
      * Closes the log file if it is open.
      */
     Logger::~Logger()
     {
          if (m_log_file.is_open())
               m_log_file.close();
     }

     /**
      * Initializes the logger class. It basically opens the log file in the
      * user configuration directory appended to the file name.
      *
      * \param file_name Log file name.
      * \param verbosity Minimum priority level to be shown on the screen.
      * \return true when no error occurred, false when an error occurred.
      */
     bool Logger::Init(const std::string &file_name, const int verbosity)
     {
          std::string path = file_manager->get_confdir() + "/" + file_name;

          m_log_file.open(path.c_str());

          if (!m_log_file.is_open()) {
               std::cerr << "WARNING: Failed to open log file at "
                         << path << std::endl;
               return false;
          }

          // Check verbosity level is valid
          if (verbosity > 0 && verbosity < LOG_TOTAL_PRIORITIES)
               m_verbosity = verbosity;
          else {
               std::cerr << "ERROR: Invalid log verbosity." << std::endl;
               return false;
          }

          std::cout << "INFO: Log messages will be written in '"
                    << path << "'." << std::endl;

          return true;
     }
     
     /**
      * Write the log message to the log file and screen. Depending on the
      * verbosity level set on initialization, it is outputed on the screen or
      * not (default is >= WARNING).
      *
      * \param priority Priority level (see enum in header for a complete list).
      * \param message Message to output.
      */
     void Logger::Write(const int priority, const std::string &message)
     {
          if (m_log_file.is_open()) {

               std::string full_message;

               switch (priority) {
               case LOG_INFO:  full_message += "INFO: ";    break;
               case LOG_WARN:  full_message += "WARNING: "; break;
               case LOG_ERROR: full_message += "ERROR: ";   break;
               }

               full_message += message;

               // If priority is more or equal to the minimum priority to be
               // shown on screen, print it!
               if (priority >= m_verbosity)
                    std::cout << full_message << std::endl;

               m_log_file << full_message << std::endl;
          }
     }

} // namespace fgradar
