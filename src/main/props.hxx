/**
 * \file props.hxx
 * \brief Header for props.cxx.
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

#ifndef _PROPS_HXX_
#define _PROPS_HXX_

#include <simgear/props/props.hxx>
#include <simgear/structure/subsystem_mgr.hxx>

namespace fgradar {

     /**
      * \brief Property tree subsystem.
      *
      * Provides a property-like tree, which can be accessed by the getNode()
      * function. Once you have the node, you can access its value. The property
      * tree is used as the internal data storage.
      */
     class Properties : public SGSubsystem {
     public:

          Properties();
          virtual ~Properties();

          virtual void init();
          virtual void update(double delta_time_sec);
          
          /**
           * Get a property tree node. Once you have the node, you can access
           * its value by calling 'get<type>Value', where in type you specify
           * the type you want to get.
           *
           * You can also specify if you want the node to be created if it
           * doesn't exist.
           *
           * \param path Path to the node relative to root.
           * \param create If the node should be created if it doesn't exist.
           * \return The node.
           */
          static SGPropertyNode *getNode(const char *path, bool create) {
               return m_property_tree->getNode(path, create);
          }

     private:

          /**
           * This is the property tree. It is just a node to the root of the
           * property tree, so all the property tree is a child of it. We make
           * it static so there is only one property tree in the whole program,
           * even if by accident there are two subsystems.
           */
          static SGPropertyNode *m_property_tree;
     };
     
} // namespace fgradar

#endif // _PROPS_HXX_
