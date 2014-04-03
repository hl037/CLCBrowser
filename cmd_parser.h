/*******************************************
 *
 * Copyright © 2014 Léo Flaventin Hauchecorne
 *
 * This file is part of CLCBrowser.
 *
 * CLCBrowser is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CLCBrowser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CLCBrowser. If not, see <http://www.gnu.org/licenses/>.
 *
 ********************************************/

/*
 * The code in this library is guaranteed without memory leak
 */

#ifndef CMD_PARSER_H
#define CMD_PARSER_H

#if defined(__cplusplus)
extern "C"
{
#endif


typedef struct Arguments
{
   int argc;
   char ** argv;
} Arguments;

Arguments * Arguments_ini(int argc, char ** argv);
void Arguments_destroy(Arguments * a);

Arguments * parse_commandline(const char * const cmd);


#if defined(__cplusplus)
}
#endif

#endif // CMD_PARSER_H
