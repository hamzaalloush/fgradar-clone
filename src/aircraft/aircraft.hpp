/**
 * \file aircraft.h
 * \header for aircraft.cpp
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

#ifndef _AIRCRAFT_H_
#define _AIRCRAFT_H_

#include <iostream>
#include <list>
#include <vector>

#include "entity.hpp"

namespace fgradar {

     /** All the possible flight rules an aircraft can have. UNKNOWN means the
         aircraft didn't tell us its intentions. */
     enum FlightRules {
          UNKNOWN,
          VFR,
          IFR
     };

     class FlightPlan;

     /**
      * \brief Every pilot in the MPservers.
      *
      * Stores info about every pilot in the MPservers. Draws it, update
      * it... this class performs all that. Since it inherits from Entity,
      * basic info such coordinates and stuff are defined.
      */
     class Aircraft : public Entity {
     public:

          Aircraft(std::string callsign, std::string &model, Geod *pos);

          virtual       ~Aircraft();
          
          void          update(double lat, double lon, int alt);
          virtual void  draw();

          bool          has_moved()            const;

          /** \param v Set voice support true or false. */
          void          set_voice_support(bool v)       {m_voice_support = v;}

          /** \param v Set the comments by the ATC. */
          void          set_atc_comments(std::string v) {m_atc_comments = v;}

          /** \param v Set flightrules. UNKNOWN by default. */
          void          set_flightrules(FlightRules v)  {m_flightrules = v;}
          /** \param v Set the flightplan. */
          void          set_flightplan(FlightPlan *v)   {m_flightplan = v;}


          /** \return If the pilot has voice support or not. (Voice support
              means FGcom). */
          bool          has_voice_support()    const  {return m_voice_support;}

          /** \return Aircraft's heading in degrees. */
          int           get_heading()          const  {return m_heading;}
          /** \return Aircraft's speed in knots. */
          int           get_speed()            const  {return m_speed;}

          /** \return Aircraft model. */
          std::string   get_model()            const  {return m_model;}
          /** \return Comments made by the ATC, like notes or remarks. */
          std::string   get_atc_comments()     const  {return m_atc_comments;}
          
          /** \return The aircraft's flightrules. */
          FlightRules   get_flightrules()      const  {return m_flightrules;}
          /** \return Aircraft's flightplan (route). */
          FlightPlan   *get_flightplan()       const  {return m_flightplan;}

     private:

          /** If the pilot has voice support, that is, he can use FGcom. If
              false, it means the pilot is text-only. */
          bool                  m_voice_support;

          /** Aircraft's heading in degrees. It can be facing 0º (north),
              90º (east) etc. */
          int                   m_heading;

          /** Speed in knots(kts). */
          int                   m_speed;

          /** The aircraft model. It can be a 777-200, F-14 etc. */
          std::string           m_model;

          /** Controller may want to set some remarks to a specific
              aircrafts. Reminders or just notes for future reference. */
          std::string           m_atc_comments;

          /** Aircraft's history. Contains previous positions of the aircraft. */
          std::list<Geod *>     m_history;

          /** Flight rules the aircraft is following. See enum 'FlightRules' to
              see possible values. */
          FlightRules           m_flightrules;

          /** Aircraft's flightplan/route. This is set by the user, not
              automatically. */
          FlightPlan           *m_flightplan;

          void  compute_heading       ();
          void  compute_speed         ();
          void  append_history_entry  ();
     };

}

#endif // _AIRCRAFT_H_
