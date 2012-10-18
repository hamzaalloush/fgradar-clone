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

#include "props.hxx"

namespace fgradar {

     SGPropertyNode *Properties::m_property_tree = NULL;

     Properties::Properties()
     {
          m_property_tree = new SGPropertyNode;
     }

     Properties::~Properties()
     {
          if (!m_property_tree) delete m_property_tree;
     }

     void
     Properties::init()
     {

     }

     void
     Properties::update(double delta_time_sec)
     {

     }
     
} // namespace fgradar
