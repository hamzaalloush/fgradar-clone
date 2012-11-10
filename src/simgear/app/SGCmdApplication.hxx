/*
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

#ifndef __SGCMDAPPLICATION_HXX
#define __SGCMDAPPLICATION_HXX

#include "SGApplication.hxx"

/**
 * \brief Defines an application with command line options available.
 *
 * Inherits from SGApplication, that is, performs all the tasks already
 * performed by SGApplication PLUS command line utilities.
 *
 * It is recommended that you use this class instead of SGApplication, because
 * command line options are always useful.
 */
class SGCmdApplication : public SGApplication {
public:

     /**
      * \brief Defines the common command line callback.
      *
      * \param Extra content after the argument (everything after the '='). For
      *        example, "--cmd=extra", where "extra" is the extra content.
      * \return If we should exit the application after running the callback
      *         (false exits the application).
      */
     typedef bool (SGCmdApplication::*CmdCallback) (std::string);

     /**
      * \brief Defines a command line option.
      *
      * It has several attributes, like name, alias etc. and the callback
      * function, that is, the function that gets executed when the option is
      * issued.
      */
     struct CmdOption {
          std::string command;
          std::string alias;
          std::string description;
          SGCmdApplication::CmdCallback function;
     };

     /**
      * \brief Creates an application with command line options available.
      *
      * Apart from what SGApplication does, it recieves the command line
      * arguments, and parses them internally, so there is no need of calling it
      * in the inherited class constructor.
      *
      * \param appname Application name.
      * \param argc Number of arguments from main().
      * \param argv Arguments from main().
      * \param datadir_required If the data directory is required for the
      *        program to work.
      */
     SGCmdApplication(const char *appname, int argc, char **argv,
                      bool datadir_required = true);
     
     virtual ~SGCmdApplication();

protected:

     /**
      * \brief Adds a command line option to the list of known cmd options.
      *
      * \param command The command the user has to issue. (e.g. --example).
      * \param alias Alias to the command (e.g. -e).
      * \param description A brief description about what the command does.
      * \param func Function call when the command gets issued.
      */
     void addCmdOption(std::string command, std::string alias,
                       std::string description, CmdCallback func);

private:
     
     /**
      * A list of known command line options (filled by the addCmdOption()
      * method). This is used by the parseCmdOptions() method to check for
      * defined command line options and execute their respective callback.
      */
     std::vector<CmdOption>  m_cmd_options;
     
     /**
      * \brief Parse command line options.
      *
      * With the previously filled command line options vector, this function
      * compares the command line options given by the user with the ones in the
      * vector.
      *
      * You shouldn't call this method in your inherited class since it is
      * already called by default.
      *
      * \see addCmdOption for more information about adding command line
      * options.
      *
      * \param argc Number of arguments.
      * \param argv Contents of each argument.
      */
     void parseCmdOptions(int argc, char **argv);
     
     bool onData(std::string);
     bool onVersion(std::string);
     bool onHelp(std::string);
     bool onProp(std::string);
};

#endif // __SGCMDAPPLICATION_HXX
