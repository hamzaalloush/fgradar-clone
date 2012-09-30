/**
 * \file vec2.hpp
 * \brief Coordinates on the screen.
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

#ifndef _VEC2_HPP_
#define _VEC2_HPP_

namespace fgradar {

     /**
      * \brief Represents a point on the screen.
      *
      * Using doubles as x and y positions on the screen is a bit repetitive, so
      * we use this to have a single variable controlling both values, x and y. It
      * also provides useful functions to work with them.
      */
     class Vec2 {
     public:

          /** Sets x and y to 0 when no parameters set. */
          Vec2() :
               m_x(0),
               m_y(0) {
          }

          /**
           * \param x Initial X pixels.
           * \param y Initial Y pixels.
           * Set X and Y to default values.
           */
          Vec2(int x, int y) :
               m_x(x),
               m_y(y) {
          }

          /** \return X pixels. */
          inline int get_x() const {return m_x;}

          /** \return Y pixels. */
          inline int get_y() const {return m_y;}


          /** \param x New X pixels. */
          inline void set_x(int x) {m_x = x;}

          /** \param y New Y pixels. */
          inline void set_y(int y) {m_y = y;}

          /**
           * \param vec2 Vector we want to compare.
           * \return If this vec2 is less than the other.
           */
          inline bool operator<(Vec2 &vec2)  const {
               return (m_x < vec2.m_x) &&
                    (m_y < vec2.m_y);
          }

          /**
           * \param vec2 Vector we want to compare.
           * \return If this vec2 is more than the other.
           */
          inline bool operator>(Vec2 &vec2)  const {
               return (m_x > vec2.m_x) &&
                    (m_y < vec2.m_y);
          }

          /**
           * \param vec2 Vec2 we want to compare with this one.
           * \return If they are equal or not.
           */
          inline bool operator==(Vec2 &vec2) const {
               return (m_x == vec2.m_x) &&
                    (m_y == vec2.m_y);
          }

     private:

          /** X axis position on the screen (horizontal). */
          int m_x;

          /** Y axis position on the screen (vertical). */
          int m_y;
     };

} // namespace fgradar

#endif // _VEC2_HPP_
