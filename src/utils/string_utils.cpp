/**
 * \file string_utils.cpp
 * \brief Describes some useful functions for manipulating strings.
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

#include "string_utils.hpp"

namespace fgradar {

     namespace utils {

          /**
           * Trims a string by removing white spaces, tabs, endlines etc. from
           * left and right sides. Then creates a sub string with the trimmed
           * content.
           *
           * \param str String to trim.
           * \return Trimmed string.
           */
          std::string &trim(std::string &str)
          {
               size_t s = str.find_first_not_of(" \n\r\t");
               size_t e = str.find_last_not_of(" \n\r\t") + 1;
               str = str.substr(s, e - s);

               return str;
          }

          /**
           * Convert (almost) anything to string using string streams. What can
           * be converted or not depends on string stream.
           *
           * \param value What we want to convert to string.
           * \return The converted string.
           */
          template <typename T>
          std::string toString(const T &value)
          {
               std::stringstream ss;
               ss << value;
               
               return ss.str();
          }

     } // namespace utils
     
} // namespace fgradar
