/*
  fuzzy - The implementation of the FUZZY programming language

  File: fuzzy.cc

  Copyright (C) 2016-2018 Omarine <phamtyn@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

# include <iostream>
# include "fuzzy_driver.hh"
# include <assert.h>
# include <getopt.h>

int
main (int argc, char *argv[])
{
	int res = 0, opt;
	fuzzy_driver driver;
	
	while ((opt = getopt(argc, argv, "h")) != EOF)
		switch (opt)
		{
			case 'h':
				usage(0);
				break;
			default:
				usage(1);
				break;
		}

	if (argc - optind == 1)
	{
		if (!driver.parse (argv[optind]))
			driver.interpret(driver.root);
		else res = 1;
	}
	else
		usage(1);
	
	return res;
}

