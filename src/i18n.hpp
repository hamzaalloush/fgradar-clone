/**
 * \file i18n.hpp
 * \brief Adds i18n support.
 */

// Copyright (C) 2012  Fernando García  <fernando.garli@gmail.com>

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

#ifndef _I18N_HPP_
#define _I18N_HPP_

#ifdef I18N_ENABLED

#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)

#else

#define setlocale(OVERRIDE, OVERRIDE2)
#define bindtextdomain(OVERRIDE, OVERRIDE2)
#define textdomain(OVERRIDE)
#define _(STRING)

#endif

#endif // _I18N_HPP_
