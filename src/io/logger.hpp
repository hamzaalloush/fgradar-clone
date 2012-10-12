/**
 * \file logger.h
 * \brief Header for logger.cpp.
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

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <fstream>

#include "utils/singleton.hpp"

namespace fgradar {

     /**
      * \brief Log priority levels.
      *
      * Contains all the possible priority levels for the logger. Being the
      * first the less important priority, and the lest one the most important.
      */
     enum {
          LOG_INFO,
          LOG_WARN,
          LOG_ERROR,
          LOG_TOTAL_PRIORITIES
     };

     /**
      * Making a call to such a big function name everytime we want to make a
      * log entry is a bit repetitive, so we make a macro to save line writting.
      */
#define LOG(priority, message) {                                          \
          do {                                                            \
               Singleton<Logger>::GetInstance().Write(priority, message); \
          } while(0);                                                     \
     }

     /**
      * \brief Logger utility (singleton).
      *
      * Implements a logger class. It has several logging levels (INFO, WARNING,
      * ERROR), from less important to the most dangerous.
      *
      * It provides logging to a file and to the screen, only, for example,
      * outputting important errors on the screen.
      */
     class Logger {
     public:

          Logger();
          ~Logger();

          bool Init(const std::string &file_name, const int verbosity);
          void Write(const int priority, const std::string &message);

     private:

          /** Minimum priority level to be shown on the screen. By default, only
           *  WARNING and higher priority levels are shown on the screen. */
          int            m_verbosity;
          
          /** File where we will output all the debug information. (Apart from
           *  here, it will be outputed to the screen). */
          std::ofstream  m_log_file;
     };

} // namespace fgradar

#endif // _LOGGER_H_
