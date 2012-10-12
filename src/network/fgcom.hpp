/**
 * \file fgcom.cpp
 * \brief FGCom support management.
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

#ifndef _FGCOM_H_
#define _FGCOM_H_

namespace fgradar {

     const int ZERO = 0;
     const bool TRUE = true;

     const char ENDLINE_CHAR = '\n';
     const char VAR_SEPARATOR = ',';
     
     enum DataType {
          BOOL,
          INT,
          FLOAT,
          STRING
     };

     const std::string reference = "COM1_FRQ=121.800,COM1_SRV=1,COM2_FRQ=118.300,COM2_SRV=1,NAV1_FRQ=115.800,NAV1_SRV=1,NAV2_FRQ=116.800,NAV2_SRV=1,PTT=0,TRANSPONDER=0,IAS=00.0,GS=00.0,LON=-122.382133,LAT=37.616833,ALT=-9999,HEAD=0.0,CALLSIGN=icecode,MODEL=Aircraft/Cub/Models/Cub.xml";

     struct FgcomData {
          const char *name;
          char       *format;
          void       *var;
          DataType    type;
     };

     int test = 121.800;

     const static FgcomData fgcom_data_list[] {
          {"COM1_FREQ",   "%03.3f",      , FLOAT},
          {"COM1_SRV",    "%d",     &TRUE, BOOL},
          {"COM2_FREQ",   "%03.3f",      , FLOAT},
          {"COM2_SRV",    "%d",     &TRUE, BOOL},
               
          {"NAV1_FREQ",   "%03.3f",      , FLOAT},
          {"NAV1_SRV",    "%d",     &TRUE, BOOL},
          {"NAV2_FREQ",   "%03.3f",      , FLOAT},
          {"NAV2_SRV",    "%d",     &TRUE, BOOL},
               
          {"PTT",         "%d",          , INT},
          {"TRANSPONDER", "%d",     &ZERO, INT},
               
          {"IAS",         "%04.1f", &ZERO, FLOAT},
          {"GS",          "%04.1f", &ZERO, FLOAT},
          {"LON",         "%03.6f",      , FLOAT},
          {"LAT",         "%03.6f",      , FLOAT},
          {"ALT",         "%05.0f",      , FLOAT},
          {"HEAD",        "%03.1f", &ZERO, FLOAT},
               
          {"CALLSIGN",    "%s",          , STRING},
          {"MODEL",       "%s", "Aircraft/ufo/Models/ufo.xml", STRING},
          {NULL}
     };

     std::string &
     {
          std::string msg;

          int i = 0;

          while (i != NULL) {

               msg.append(fgcom_data_list[i].name);
               msg.append('=');
               
               switch (fgcom_data_list[i].type) {
               case INT:
               {
                    int var = *static_cast<int *>(fgcom_data_list[i].var);
                    char formatted_var[16];
                    
                    sprintf(formatted_var, fgcom_data_list[i].format, var);
                    msg.append(formatted_var);
                    
                    break;
               }
               case FLOAT:
               {
                    double var = *static_cast<double *>(fgcom_data_list[i].var);
                    char formatted_var[16];

                    sprintf(formatted_var, fgcom_data_list[i].format, var);
                    msg.append(formatted_var);

                    break;
               }
               case STRING:
               {
                    char *var = static_cast<char *>(fgcom_data_list[i].var);
                    char formatted_var[16];
                    
                    msg.append(var);

                    break;
               }
               default:
                    LOG(LOG_ERROR, "FGCom -- Unknown data type of "
                        << fgcom_data_list[i].name);
                    exit(1);
               }

               if (i != (fgcom_data_list_size - 1))
                    msg.append(VAR_SEPARATOR);
               else
                    msg.append(ENDLINE_CHAR);

               i++;
          }
     }
} // namespace fgradar

#endif // _FGCOM_H_
