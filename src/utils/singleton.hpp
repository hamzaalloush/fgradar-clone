/**
 * \file singleton.h
 * \brief Singleton design pattern template.
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

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

namespace fgradar {

     /**
      * \brief Template for a singleton.
      *
      * We have some singletons in the program. Using a template to represent
      * each of them is a good idea.
      *
      * We make constructor and copy operators private, so we make sure that it
      * can't be duplicated or copied, and that it can only be accessed by
      * GetInstance().
      */
     template <typename T>
     class Singleton {
     public:

          /**
           * Returns the single class instance.
           * @return Class instance.
           */
          static T &GetInstance() {
               
               // Create single instance if it isn't already created
               static T instance;
               return instance;
          }
          
     private:

          Singleton() {};
          ~Singleton() {};

          Singleton(const Singleton &);
          Singleton &operator=(const Singleton &);
     };
     
} // namespace fgradar

#endif // _SINGLETON_H_
