/*
  fuzzy - The implementation of the FUZZY programming language

  File: classes.cc

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

#include "fuzzy_driver.hh"

NODE *operator+(const NODE &t1, const NODE &t2)
{
	if (t1.data->GetClassId() == t2.data->GetClassId())
	{
		switch (t1.data->GetType())
		{
			case Type_number:
			{
				Number *pNumber_t1 = static_cast<Number *>(t1.data);
				Number *pNumber_t2 = static_cast<Number *>(t2.data);
				NODE *r = new NODE(*pNumber_t1, t1.loc);
				Number *pNumber_r = static_cast<Number *>(r->data);
				*pNumber_r += *pNumber_t2;
				return r;
			}
			case Type_interger:
			{
				INTERGER *pInterger_t1 = static_cast<INTERGER *>(t1.data);
				INTERGER *pInterger_t2 = static_cast<INTERGER *>(t2.data);
				NODE *r = new NODE(*pInterger_t1, t1.loc);
				INTERGER *pInterger_r = static_cast<INTERGER *>(r->data);
				*pInterger_r += *pInterger_t2;
				return r;
			}
			case Type_string:
			{
				String *pString_t1 = static_cast<String *>(t1.data);
				String *pString_t2 = static_cast<String *>(t2.data);
				NODE *r = new NODE(*pString_t1, t1.loc);
				String *pString_r = static_cast<String *>(r->data);
				*pString_r += *pString_t2;
				return r;
			}
			default:
			{
				string text = no_match_operator_msg(t1, t2, "+");
				NODE::driver->error(t1.loc + t2.loc, text);
				exit (EXIT_FAILURE);
			}
	   
		}
	}
	
	switch(t1.data->GetType())
	{
		case Type_number:
		{
			switch(t2.data->GetType())
			{
				case Type_interger:
					
					NODE *r = new NODE(t1.data->GetNumber(), t1.loc);
					r->data->GetNumber() += t2.data->GetInterger();
					return r;
			}
			break;
		}
		case Type_interger:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					NODE *r = new NODE(t1.data->GetInterger(), t1.loc);
					r->data->GetInterger() += (long)t2.data->GetNumber();
					return r;
			}
			break;
		}
	}

	string text = no_match_operator_msg(t1, t2, "+");
	NODE::driver->error(t1.loc + t2.loc, text);
	exit (EXIT_FAILURE);
} 

NODE *operator-(const NODE &t1, const NODE &t2)
{
	if (t1.data->GetClassId() == t2.data->GetClassId())
	{
		switch (t1.data->GetType())
		{
			case Type_number:
			{
				Number *pNumber_t1 = static_cast<Number *>(t1.data);
				Number *pNumber_t2 = static_cast<Number *>(t2.data);
				NODE *r = new NODE(*pNumber_t1, t1.loc);
				Number *pNumber_r = static_cast<Number *>(r->data);
				*pNumber_r -= *pNumber_t2;
				return r;
			}
			case Type_interger:
			{
				INTERGER *pInterger_t1 = static_cast<INTERGER *>(t1.data);
				INTERGER *pInterger_t2 = static_cast<INTERGER *>(t2.data);
				NODE *r = new NODE(*pInterger_t1, t1.loc);
				INTERGER *pInterger_r = static_cast<INTERGER *>(r->data);
				*pInterger_r -= *pInterger_t2;
				return r;
			}
			default:
			{
				string text = no_match_operator_msg(t1, t2, "-");
				NODE::driver->error(t1.loc + t2.loc, text);
				exit (EXIT_FAILURE);
			}
	   
		}
	}
	
	switch(t1.data->GetType())
	{
		case Type_number:
		{
			switch(t2.data->GetType())
			{
				case Type_interger:
					
					NODE *r = new NODE(t1.data->GetNumber(), t1.loc);
					r->data->GetNumber() -= t2.data->GetInterger();
					return r;
			}
			break;
		}
		case Type_interger:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					NODE *r = new NODE(t1.data->GetInterger(), t1.loc);
					r->data->GetInterger() -= (long)t2.data->GetNumber();
					return r;
			}
			break;
		}
	}
	
	string text = no_match_operator_msg(t1, t2, "-");
	NODE::driver->error(t1.loc + t2.loc, text);
	exit (EXIT_FAILURE);
} 

NODE *operator*(const NODE &t1, const NODE &t2)
{
	if (t1.data->GetClassId() == t2.data->GetClassId())
	{
		switch (t1.data->GetType())
		{
			case Type_number:
			{
				Number *pNumber_t1 = static_cast<Number *>(t1.data);
				Number *pNumber_t2 = static_cast<Number *>(t2.data);
				NODE *r = new NODE(*pNumber_t1, t1.loc);
				Number *pNumber_r = static_cast<Number *>(r->data);
				*pNumber_r *= *pNumber_t2;
				return r;
			}
			case Type_interger:
			{
				INTERGER *pInterger_t1 = static_cast<INTERGER *>(t1.data);
				INTERGER *pInterger_t2 = static_cast<INTERGER *>(t2.data);
				NODE *r = new NODE(*pInterger_t1, t1.loc);
				INTERGER *pInterger_r = static_cast<INTERGER *>(r->data);
				*pInterger_r *= *pInterger_t2;
				return r;
			}
			default:
			{
				string text = no_match_operator_msg(t1, t2, "*");
				NODE::driver->error(t1.loc + t2.loc, text);
				exit (EXIT_FAILURE);
			}
	   
		}
	}
	
	switch(t1.data->GetType())
	{
		case Type_number:
		{
			switch(t2.data->GetType())
			{
				case Type_interger:
					
					NODE *r = new NODE(t1.data->GetNumber(), t1.loc);
					r->data->GetNumber() *= t2.data->GetInterger();
					return r;
			}
			break;
		}
		case Type_interger:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					NODE *r = new NODE(t1.data->GetInterger(), t1.loc);
					r->data->GetInterger() *= (long)t2.data->GetNumber();
					return r;
			}
			break;
		}
	}
	
	string text = no_match_operator_msg(t1, t2, "*");
	NODE::driver->error(t1.loc + t2.loc, text);
	exit (EXIT_FAILURE);
} 

NODE *operator/(const NODE &t1, const NODE &t2)
{
	if (t1.data->GetClassId() == t2.data->GetClassId())
	{
		switch (t1.data->GetType())
		{
			case Type_number:
			{
				Number *pNumber_t1 = static_cast<Number *>(t1.data);
				Number *pNumber_t2 = static_cast<Number *>(t2.data);
				if(pNumber_t2->GetNumber() == 0.0)
				{
					NODE::driver->error(t2.loc,"division by zero attempted.");
					exit (EXIT_FAILURE);
				}
				
				NODE *r = new NODE(*pNumber_t1, t1.loc);
				Number *pNumber_r = static_cast<Number *>(r->data);
				*pNumber_r /= *pNumber_t2;
				return r;
			}
			case Type_interger:
			{
				INTERGER *pInterger_t1 = static_cast<INTERGER *>(t1.data);
				INTERGER *pInterger_t2 = static_cast<INTERGER *>(t2.data);
				if(pInterger_t2->GetInterger() == 0)
				{
					NODE::driver->error(t2.loc,"division by zero attempted.");
					exit (EXIT_FAILURE);
				}
				
				NODE *r = new NODE(*pInterger_t1, t1.loc);
				INTERGER *pInterger_r = static_cast<INTERGER *>(r->data);
				*pInterger_r /= *pInterger_t2;
				return r;
			}
			default:
			{
				string text = no_match_operator_msg(t1, t2, "/");
				NODE::driver->error(t1.loc + t2.loc, text);
				exit (EXIT_FAILURE);
			}
	   
		}
	}
	
	switch(t1.data->GetType())
	{
		case Type_number:
		{
			switch(t2.data->GetType())
			{
				case Type_interger:
					
					NODE *r = new NODE(t1.data->GetNumber(), t1.loc);
					if(t2.data->GetInterger() == 0)
					{
						NODE::driver->error(t2.loc,"division by zero attempted.");
						exit (EXIT_FAILURE);
					}
					r->data->GetNumber() /= t2.data->GetInterger();
					return r;
			}
			break;
		}
		case Type_interger:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					NODE *r = new NODE(t1.data->GetInterger(), t1.loc);
					if(t2.data->GetNumber() == 0.0)
					{
						NODE::driver->error(t2.loc,"division by zero attempted.");
						exit (EXIT_FAILURE);
					}
					r->data->GetInterger() /= (long)t2.data->GetNumber();
					return r;
			}
			break;
		}
	}
	
	string text = no_match_operator_msg(t1, t2, "/");
	NODE::driver->error(t1.loc + t2.loc, text);
	exit (EXIT_FAILURE);
} 

NODE *operator%(const NODE &t1, const NODE &t2)
{
	if (t1.data->GetClassId() == t2.data->GetClassId())
	{
		switch (t1.data->GetType())
		{
			case Type_number:
			{
				Number *pNumber_t1 = static_cast<Number *>(t1.data);
				Number *pNumber_t2 = static_cast<Number *>(t2.data);
				if(pNumber_t2->GetNumber() == 0.0)
				{
					NODE::driver->error(t2.loc,"division by zero attempted.");
					exit (EXIT_FAILURE);
				}
				
				long mod = (long)pNumber_t1->GetNumber() % (long)pNumber_t2->GetNumber();
				NODE *r = new NODE((double)mod, t1.loc);
				return r;
			}
			case Type_interger:
			{
				INTERGER *pInterger_t1 = static_cast<INTERGER *>(t1.data);
				INTERGER *pInterger_t2 = static_cast<INTERGER *>(t2.data);
				if(pInterger_t2->GetInterger() == 0)
				{
					NODE::driver->error(t2.loc,"division by zero attempted.");
					exit (EXIT_FAILURE);
				}
				
				long mod = pInterger_t1->GetInterger() % pInterger_t2->GetInterger();
				NODE *r = new NODE(mod, t1.loc);
				return r;
			}
			default:
			{
				string text = no_match_operator_msg(t1, t2, "%");
				NODE::driver->error(t1.loc + t2.loc, text);
				exit (EXIT_FAILURE);
			}
	   
		}
	}
	
	switch(t1.data->GetType())
	{
		case Type_number:
		{
			switch(t2.data->GetType())
			{
				case Type_interger:
					
					NODE *r = new NODE(t1.data->GetNumber(), t1.loc);
					if(t2.data->GetInterger() == 0)
					{
						NODE::driver->error(t2.loc,"division by zero attempted.");
						exit (EXIT_FAILURE);
					}
					long mod = (long)r->data->GetNumber() % t2.data->GetInterger();
					r->data->GetNumber() = mod;
					return r;
			}
			break;
		}
		case Type_interger:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					NODE *r = new NODE(t1.data->GetInterger(), t1.loc);
					if(t2.data->GetNumber() == 0.0)
					{
						NODE::driver->error(t2.loc,"division by zero attempted.");
						exit (EXIT_FAILURE);
					}
					long mod = r->data->GetInterger() % (long)t2.data->GetNumber();
					r->data->GetInterger() = mod;
					return r;
			}
			break;
		}
	}
	
	string text = no_match_operator_msg(t1, t2, "%");
	NODE::driver->error(t1.loc + t2.loc, text);
	exit (EXIT_FAILURE);
} 

bool operator>(const NODE &t1, const NODE &t2)
{
	
	if (t1.data->GetClassId() == t2.data->GetClassId())
	{
		switch (t1.data->GetType())
		{
			case Type_number:
			{
				Number *pNumber_t1 = static_cast<Number *>(t1.data);
				Number *pNumber_t2 = static_cast<Number *>(t2.data);
				return *pNumber_t1 > *pNumber_t2;
			}
			case Type_interger:
			{
				INTERGER *pInterger_t1 = static_cast<INTERGER *>(t1.data);
				INTERGER *pInterger_t2 = static_cast<INTERGER *>(t2.data);
				return *pInterger_t1 > *pInterger_t2;
			}
			case Type_string:
			{
				String *pString_t1 = static_cast<String *>(t1.data);
				String *pString_t2 = static_cast<String *>(t2.data);
				return *pString_t1 > *pString_t2;
			}
			case Type_fuzzy:
			{
				return t1.data->GetValue() > t2.data->GetValue();
			}
			case Type_struct:
				if(t1.data->IsFuzzy() && t2.data->IsFuzzy())
				{
					return t1.data->GetFuzzy()->GetValue() > 
					t2.data->GetFuzzy()->GetValue();
				}
				break;
			default:
			{
				string text = no_match_operator_msg(t1, t2, ">");
				NODE::driver->error(t1.loc + t2.loc, text);
				exit (EXIT_FAILURE);
			}
	   
		}
	}
	
	switch(t1.data->GetType())
	{
		case Type_number:
		{
			switch(t2.data->GetType())
			{
				case Type_interger:
					return t1.data->GetNumber() > t2.data->GetInterger();	
				case Type_struct:
					if(t2.data->IsFuzzy())
					{
						return t1.data->GetNumber() > 
						t2.data->GetFuzzy()->GetValue();
					}
					break;
			}
			break;
		}
		case Type_interger:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					return t1.data->GetInterger() > (long)t2.data->GetNumber();	
				case Type_struct:
					if(t2.data->IsFuzzy())
					{
						return t1.data->GetInterger() > 
						(long)t2.data->GetFuzzy()->GetValue();
					}
					break;
			}
			break;
		}
		case Type_fuzzy:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					return t1.data->GetValue() > t2.data->GetNumber();
				case Type_interger:
					return t1.data->GetValue() > t2.data->GetInterger();
			}
			break;
		}
		case Type_struct:
			if(t1.data->IsFuzzy())
			{
				switch(t2.data->GetType())
				{
					case Type_number:
						return t1.data->GetFuzzy()->GetValue() > 
						t2.data->GetNumber();	
					case Type_interger:
						return t1.data->GetFuzzy()->GetValue() > 
						t2.data->GetInterger();	
				}
			}
			break;
	}
	
	/*
	if(t1.data->GetType() & Type_array || t2.data->GetType() & Type_array)
		goto ERROR;
	*/
	
ERROR:	
	string text = no_match_operator_msg(t1, t2, ">");
	NODE::driver->error(t1.loc + t2.loc, text);
	exit (EXIT_FAILURE);
} 

bool operator<(const NODE &t1, const NODE &t2)
{
	if (t1.data->GetClassId() == t2.data->GetClassId())
	{
		switch (t1.data->GetType())
		{
			case Type_number:
			{
				Number *pNumber_t1 = static_cast<Number *>(t1.data);
				Number *pNumber_t2 = static_cast<Number *>(t2.data);
				return *pNumber_t1 < *pNumber_t2;
			}
			case Type_interger:
			{
				INTERGER *pInterger_t1 = static_cast<INTERGER *>(t1.data);
				INTERGER *pInterger_t2 = static_cast<INTERGER *>(t2.data);
				return *pInterger_t1 < *pInterger_t2;
			}
			case Type_string:
			{
				String *pString_t1 = static_cast<String *>(t1.data);
				String *pString_t2 = static_cast<String *>(t2.data);
				return *pString_t1 < *pString_t2;
			}
			case Type_fuzzy:
			{
				return t1.data->GetValue() < t2.data->GetValue();
			}
			case Type_struct:
				if(t1.data->IsFuzzy() && t2.data->IsFuzzy())
				{
					return t1.data->GetFuzzy()->GetValue() < 
					t2.data->GetFuzzy()->GetValue();
				}
				break;
			default:
			{
				string text = no_match_operator_msg(t1, t2, "<");
				NODE::driver->error(t1.loc + t2.loc, text);
				exit (EXIT_FAILURE);
			}
	   
		}
	}
	
	switch(t1.data->GetType())
	{
		case Type_number:
		{
			switch(t2.data->GetType())
			{
				case Type_interger:
					return t1.data->GetNumber() < t2.data->GetInterger();	
				case Type_struct:
					if(t2.data->IsFuzzy())
					{
						return t1.data->GetNumber() < 
						t2.data->GetFuzzy()->GetValue();
					}
					break;
			}
			break;
		}
		case Type_interger:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					return t1.data->GetInterger() < (long)t2.data->GetNumber();	
				case Type_struct:
					if(t2.data->IsFuzzy())
					{
						return t1.data->GetInterger() < 
						(long)t2.data->GetFuzzy()->GetValue();
					}
					break;
			}
			break;
		}
		case Type_fuzzy:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					return t1.data->GetValue() < t2.data->GetNumber();
				case Type_interger:
					return t1.data->GetValue() < t2.data->GetInterger();
			}
			break;
		}
		case Type_struct:
			if(t1.data->IsFuzzy())
			{
				switch(t2.data->GetType())
				{
					case Type_number:
						return t1.data->GetFuzzy()->GetValue() < 
						t2.data->GetNumber();	
					case Type_interger:
						return t1.data->GetFuzzy()->GetValue() < 
						t2.data->GetInterger();	
				}
			}
			break;
	}
	
	string text = no_match_operator_msg(t1, t2, "<");
	NODE::driver->error(t1.loc + t2.loc, text);
	exit (EXIT_FAILURE);
} 

bool operator>=(const NODE &t1, const NODE &t2)
{
	if (t1.data->GetClassId() == t2.data->GetClassId())
	{
		switch (t1.data->GetType())
		{
			case Type_number:
			{
				Number *pNumber_t1 = static_cast<Number *>(t1.data);
				Number *pNumber_t2 = static_cast<Number *>(t2.data);
				return *pNumber_t1 >= *pNumber_t2;
			}
			case Type_interger:
			{
				INTERGER *pInterger_t1 = static_cast<INTERGER *>(t1.data);
				INTERGER *pInterger_t2 = static_cast<INTERGER *>(t2.data);
				return *pInterger_t1 >= *pInterger_t2;
			}
			case Type_string:
			{
				String *pString_t1 = static_cast<String *>(t1.data);
				String *pString_t2 = static_cast<String *>(t2.data);
				return *pString_t1 >= *pString_t2;
			}
			case Type_fuzzy:
			{
				return t1.data->GetValue() >= t2.data->GetValue();
			}
			case Type_struct:
				if(t1.data->IsFuzzy() && t2.data->IsFuzzy())
				{
					return t1.data->GetFuzzy()->GetValue() >= 
					t2.data->GetFuzzy()->GetValue();
				}
				break;
			default:
			{
				string text = no_match_operator_msg(t1, t2, ">=");
				NODE::driver->error(t1.loc + t2.loc, text);
				exit (EXIT_FAILURE);
			}
	   
		}
	}
	
	switch(t1.data->GetType())
	{
		case Type_number:
		{
			switch(t2.data->GetType())
			{
				case Type_interger:
					return t1.data->GetNumber() >= t2.data->GetInterger();	
				case Type_struct:
					if(t2.data->IsFuzzy())
					{
						return t1.data->GetNumber() >= 
						t2.data->GetFuzzy()->GetValue();
					}
					break;
			}
			break;
		}
		case Type_interger:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					return t1.data->GetInterger() >= (long)t2.data->GetNumber();	
				case Type_struct:
					if(t2.data->IsFuzzy())
					{
						return t1.data->GetInterger() >= 
						(long)t2.data->GetFuzzy()->GetValue();
					}
					break;
			}
			break;
		}
		case Type_fuzzy:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					return t1.data->GetValue() >= t2.data->GetNumber();
				case Type_interger:
					return t1.data->GetValue() >= t2.data->GetInterger();
			}
			break;
		}
		case Type_struct:
			if(t1.data->IsFuzzy())
			{
				switch(t2.data->GetType())
				{
					case Type_number:
						return t1.data->GetFuzzy()->GetValue() >= 
						t2.data->GetNumber();	
					case Type_interger:
						return t1.data->GetFuzzy()->GetValue() >=
						t2.data->GetInterger();	
				}
			}
			break;
	}
	
	string text = no_match_operator_msg(t1, t2, ">=");
	NODE::driver->error(t1.loc + t2.loc, text);
	exit (EXIT_FAILURE);
} 

bool operator<=(const NODE &t1, const NODE &t2)
{
	if (t1.data->GetClassId() == t2.data->GetClassId())
	{
		switch (t1.data->GetType())
		{
			case Type_number:
			{
				Number *pNumber_t1 = static_cast<Number *>(t1.data);
				Number *pNumber_t2 = static_cast<Number *>(t2.data);
				return *pNumber_t1 <= *pNumber_t2;
			}
			case Type_interger:
			{
				INTERGER *pInterger_t1 = static_cast<INTERGER *>(t1.data);
				INTERGER *pInterger_t2 = static_cast<INTERGER *>(t2.data);
				return *pInterger_t1 <= *pInterger_t2;
			}
			case Type_string:
			{
				String *pString_t1 = static_cast<String *>(t1.data);
				String *pString_t2 = static_cast<String *>(t2.data);
				return *pString_t1 <= *pString_t2;
			}
			case Type_fuzzy:
			{
				return t1.data->GetValue() <= t2.data->GetValue();
			}
			case Type_struct:
				if(t1.data->IsFuzzy() && t2.data->IsFuzzy())
				{
					return t1.data->GetFuzzy()->GetValue() <= 
					t2.data->GetFuzzy()->GetValue();
				}
				break;
			default:
			{
				string text = no_match_operator_msg(t1, t2, "<=");
				NODE::driver->error(t1.loc + t2.loc, text);
				exit (EXIT_FAILURE);
			}
	   
		}
	}
	
	switch(t1.data->GetType())
	{
		case Type_number:
		{
			switch(t2.data->GetType())
			{
				case Type_interger:
					return t1.data->GetNumber() <= t2.data->GetInterger();	
				case Type_struct:
					if(t2.data->IsFuzzy())
					{
						return t1.data->GetNumber() <= 
						t2.data->GetFuzzy()->GetValue();
					}
					break;
			}
			break;
		}
		case Type_interger:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					return t1.data->GetInterger() <= (long)t2.data->GetNumber();	
				case Type_struct:
					if(t2.data->IsFuzzy())
					{
						return t1.data->GetInterger() <= 
						(long)t2.data->GetFuzzy()->GetValue();
					}
					break;
			}
			break;
		}
		case Type_fuzzy:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					return t1.data->GetValue() <= t2.data->GetNumber();
				case Type_interger:
					return t1.data->GetValue() <= t2.data->GetInterger();
			}
			break;
		}
		case Type_struct:
			if(t1.data->IsFuzzy())
			{
				switch(t2.data->GetType())
				{
					case Type_number:
						return t1.data->GetFuzzy()->GetValue() <= 
						t2.data->GetNumber();	
					case Type_interger:
						return t1.data->GetFuzzy()->GetValue() <=
						t2.data->GetInterger();	
				}
			}
			break;
	}
	
	string text = no_match_operator_msg(t1, t2, "<=");
	NODE::driver->error(t1.loc + t2.loc, text);
	exit (EXIT_FAILURE);
} 

bool operator != (const NODE &t1, const NODE &t2)
{
	if (t1.data->GetClassId() == t2.data->GetClassId())
	{
		switch (t1.data->GetType())
		{
			case Type_number:
			{
				Number *pNumber_t1 = static_cast<Number *>(t1.data);
				Number *pNumber_t2 = static_cast<Number *>(t2.data);
				return *pNumber_t1 != *pNumber_t2;
			}
			case Type_interger:
			{
				INTERGER *pInterger_t1 = static_cast<INTERGER *>(t1.data);
				INTERGER *pInterger_t2 = static_cast<INTERGER *>(t2.data);
				return *pInterger_t1 != *pInterger_t2;
			}
			case Type_string:
			{
				String *pString_t1 = static_cast<String *>(t1.data);
				String *pString_t2 = static_cast<String *>(t2.data);
				return *pString_t1 != *pString_t2;
			}
			case Type_bool:
			{
				return t1.data->GetFlag() != t2.data->GetFlag();
			}
			case Type_fuzzy:
			{
				return t1.data->GetValue() != t2.data->GetValue();
			}
			case Type_struct:
				if(t1.data->IsFuzzy() && t2.data->IsFuzzy())
				{
					return t1.data->GetFuzzy()->GetValue() != 
					t2.data->GetFuzzy()->GetValue();
				}
				break;
			default:
			{
				string text = no_match_operator_msg(t1, t2, "!=");
				NODE::driver->error(t1.loc + t2.loc, text);
				exit (EXIT_FAILURE);
			}
	   
		}
	}
	
	switch(t1.data->GetType())
	{
		case Type_number:
		{
			switch(t2.data->GetType())
			{
				case Type_interger:
					return t1.data->GetNumber() != t2.data->GetInterger();	
				case Type_struct:
					if(t2.data->IsFuzzy())
					{
						return t1.data->GetNumber() != 
						t2.data->GetFuzzy()->GetValue();
					}
					break;
			}
			break;
		}
		case Type_interger:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					return t1.data->GetInterger() != (long)t2.data->GetNumber();	
				case Type_struct:
					if(t2.data->IsFuzzy())
					{
						return t1.data->GetInterger() != 
						(long)t2.data->GetFuzzy()->GetValue();
					}
					break;
			}
			break;
		}
		case Type_fuzzy:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					return t1.data->GetValue() != t2.data->GetNumber();
				case Type_interger:
					return t1.data->GetValue() != t2.data->GetInterger();
			}
			break;
		}
		case Type_struct:
			if(t1.data->IsFuzzy())
			{
				switch(t2.data->GetType())
				{
					case Type_number:
						return t1.data->GetFuzzy()->GetValue() != 
						t2.data->GetNumber();	
					case Type_interger:
						return t1.data->GetFuzzy()->GetValue() !=
						t2.data->GetInterger();	
				}
			}
			break;
	}
	
	string text = no_match_operator_msg(t1, t2, "!=");
	NODE::driver->error(t1.loc + t2.loc, text);
	exit (EXIT_FAILURE);
} 

bool operator == (const NODE &t1, const NODE &t2)
{	
	if (t1.data->GetClassId() == t2.data->GetClassId())
	{
		switch (t1.data->GetType())
		{
			case Type_number:
			{
				Number *pNumber_t1 = static_cast<Number *>(t1.data);
				Number *pNumber_t2 = static_cast<Number *>(t2.data);
				return *pNumber_t1 == *pNumber_t2;
			}
			case Type_interger:
			{
				INTERGER *pInterger_t1 = static_cast<INTERGER *>(t1.data);
				INTERGER *pInterger_t2 = static_cast<INTERGER *>(t2.data);
				return *pInterger_t1 == *pInterger_t2;
			}
			case Type_string:
			{
				String *pString_t1 = static_cast<String *>(t1.data);
				String *pString_t2 = static_cast<String *>(t2.data);
				return *pString_t1 == *pString_t2;
			}
			case Type_bool:
			{
				return t1.data->GetFlag() == t2.data->GetFlag();
			}
			case Type_fuzzy:
			{
				return t1.data->GetValue() == t2.data->GetValue();
			}
			case Type_struct:
				if(t1.data->IsFuzzy() && t2.data->IsFuzzy())
				{
					return t1.data->GetFuzzy()->GetValue() == 
					t2.data->GetFuzzy()->GetValue();
				}
				break;
			default:
			{
				string text = no_match_operator_msg(t1, t2, "==");
				NODE::driver->error(t1.loc + t2.loc, text);
				exit (EXIT_FAILURE);
			}
	   
		}
	}
	
	switch(t1.data->GetType())
	{
		case Type_number:
		{
			switch(t2.data->GetType())
			{
				case Type_interger:
					return t1.data->GetNumber() == t2.data->GetInterger();	
				case Type_struct:
					if(t2.data->IsFuzzy())
					{
						return t1.data->GetNumber() == 
						t2.data->GetFuzzy()->GetValue();
					}
					break;
			}
			break;
		}
		case Type_interger:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					return t1.data->GetInterger() == (long)t2.data->GetNumber();	
				case Type_struct:
					if(t2.data->IsFuzzy())
					{
						return t1.data->GetInterger() == 
						(long)t2.data->GetFuzzy()->GetValue();
					}
					break;
			}
			break;
		}
		case Type_fuzzy:
		{
			switch(t2.data->GetType())
			{
				case Type_number:
					return t1.data->GetValue() == t2.data->GetNumber();
				case Type_interger:
					return t1.data->GetValue() == t2.data->GetInterger();
			}
			break;
		}
		case Type_struct:
			if(t1.data->IsFuzzy())
			{
				switch(t2.data->GetType())
				{
					case Type_number:
						return t1.data->GetFuzzy()->GetValue() == 
						t2.data->GetNumber();	
					case Type_interger:
						return t1.data->GetFuzzy()->GetValue() ==
						t2.data->GetInterger();	
				}
			}
			break;
	}
	
	string text = no_match_operator_msg(t1, t2, "==");
	NODE::driver->error(t1.loc + t2.loc, text);
	exit (EXIT_FAILURE);
} 

NODE NODE::operator-()
{
	if(data->GetType() == Type_struct)
	{
		Object *pFunction = NULL;
		VAR_MAP *pVarMap = data->GetVarMap();
		
		POSITION pos = pVarMap->FindFirstWithKey("operator-");
		if(pos)
		{
			pFunction = pVarMap->GetValueAt(pos);
			return *NODE::driver->call_function(pFunction, loc);
		}
	}
	switch(data->GetType())
	{
		case Type_number:
			return NODE(-data->GetNumber(), loc);
		case Type_interger:
			return NODE(-data->GetInterger(), loc);	
	}
	
	string text = no_match_operator_msg(*this, "-");
	NODE::driver->error(loc, text);
	exit (EXIT_FAILURE);
}

bool NODE::GetBoolen()
{
	switch(data->GetType())
	{
		case Type_bool:
			return data->GetFlag();
		case Type_number:
			return data->GetNumber() != 0.0 ? true : false;
		case Type_interger:
			return data->GetInterger() != 0 ? true : false;	
		case Type_string:
			return data->GetString().length() > 0 ? true : false;
		case Type_fuzzy:
			return data->GetValue() != 0.0 ? true : false;	
		case Type_struct:
			if(data->IsFuzzy())
				return data->GetFuzzy()->GetValue() != 0.0 ? true : false;
			break;
	}
	
	string text = cannot_convert_msg(*this, "bool");
	NODE::driver->error(loc, text);
	exit (EXIT_FAILURE);
}

inline bool IsConvertable_first(Object *dest, Object *src)
{
	if(dest->GetType() == Type_struct && dest->IsFuzzy())
		switch(src->GetType())
		{
			case Type_number:
			case Type_interger:
				return true;	
		}
		
	switch(dest->GetType())
	{
		case Type_number:
		{
			switch(src->GetType())
			{
				case Type_interger:
				case Type_fuzzy:
				case Type_struct:
					if(src->IsFuzzy())
						return true;
					break;
			}
			break;
		}
		case Type_interger:
		{
			switch(src->GetType())
			{
				case Type_number:
				case Type_fuzzy:
				case Type_struct:
					if(src->IsFuzzy())
						return true;
					break;
			}
			break;
		}
		case Type_fuzzy:	
		{
			switch(src->GetType())
			{
				case Type_number:
				case Type_interger:
					return true;
			}
			break;
		}
	}	
		
	return false;
}

inline bool IsConvertable(Object *dest, Object *src)
{
	if(dest->GetType() == Type_struct && dest->IsFuzzy())
		switch(src->GetType())
		{
			case Type_number:
			case Type_interger:
				return true;	
		}
		
	switch(dest->GetType())
	{
		case Type_number:
		{
			switch(src->GetType())
			{
				case Type_bool:
				case Type_interger:
				case Type_fuzzy:
				case Type_string:
					return true;
				case Type_struct:
					if(src->IsFuzzy())
						return true;
					break;
			}
			break;
		}
		case Type_interger:
		{
			switch(src->GetType())
			{
				case Type_bool:
				case Type_number:
				case Type_fuzzy:
				case Type_string:
					return true;
				case Type_struct:
					if(src->IsFuzzy())
						return true;
					break;
			}
			break;
		}
		case Type_string:
		case Type_bool:	
		case Type_fuzzy:	
		{
			switch(src->GetType())
			{
				case Type_number:
				case Type_interger:
					return true;
			}
			break;
		}
	}	
		
	return false;
}

NODE &NODE::assign(const NODE &t, Object *pFunction, bool bFunctionConvert)
{
	if(data->GetType() == Type_struct)
	{
		if(data->IsFuzzy())
		{
			switch(t.data->GetType())
			{
				case Type_number:
					data->GetFuzzy()->GetValue() = t.data->GetNumber();
					data->GetFuzzy()->InitBelong();
					return *this;
				case Type_interger:
					data->GetFuzzy()->GetValue() = t.data->GetInterger();
					data->GetFuzzy()->InitBelong();
					return *this;	
			}
		}
		Object *pFunction = NULL;
		Object *pParam = NULL;
		VAR_MAP *pVarMap = data->GetVarMap();
		
		POSITION pos, posOrigin = pVarMap->FindFirstWithKey("operator=");
		if(!posOrigin)
			goto CONTINUE;
		pos = posOrigin;
		while(pos)
		{
			pFunction = pVarMap->GetNextValueWithKey(pos, "operator=");
			pParam = (*pFunction->GetParamArray())[0];
			
			if(pParam->GetClassId() == t.data->GetClassId() &&
				pParam->GetType() == t.data->GetType())
				goto CONTINUE;
		}
		pos = posOrigin;
		while(pos)
		{
			pFunction = pVarMap->GetNextValueWithKey(pos, "operator=");
			pParam = (*pFunction->GetParamArray())[0];
			
			if(IsConvertable_first(pParam, t.data))
				goto CONTINUE;
		}
		pos = posOrigin;
		while(pos)
		{
			pFunction = pVarMap->GetNextValueWithKey(pos, "operator=");
			pParam = (*pFunction->GetParamArray())[0];
			
			if(IsConvertable(pParam, t.data))
				goto CONTINUE;
		}
		pos = posOrigin;
		while(pos)
		{
			pFunction = pVarMap->GetNextValueWithKey(pos, "operator=");
			pParam = (*pFunction->GetParamArray())[0];
			
			if(pParam->GetType() == t.data->GetType())
				goto CONTINUE;
		}
		pos = posOrigin;
		while(pos)
		{
			pFunction = pVarMap->GetNextValueWithKey(pos, "operator=");
			pParam = (*pFunction->GetParamArray())[0];
			
			if(!(pParam->GetType() & Type_array)	&&
				!(t.data->GetType() & Type_array))
				goto CONTINUE;
		}
		pos = posOrigin;
		while(pos)
		{
			pFunction = pVarMap->GetNextValueWithKey(pos, "operator=");
			pParam = (*pFunction->GetParamArray())[0];
			
			if(pParam->GetType() & Type_array	&&
				t.data->GetType() & Type_array)
				goto CONTINUE;
		}
	CONTINUE:	
		if(pFunction != NULL)
		{
			Object *origin_data = data;
			if(!pParam->IsCompleted())
			{
				if(pParam->GetType() & Type_array)
				{
					if(pParam->GetType() & Type_struct)
						pParam->init();
				}
				else
					pParam->init(*pParam->GetClassObject());
				pParam->SetCompleted();
			}
			if(pParam->GetClassId() == t.data->GetClassId() &&
				!(pParam->GetType() & Type_array)	&&
				!(t.data->GetType() & Type_array)
									)
				*pParam = *t.data;
			else
			{
				if(pParam->GetClassId() == data->GetClassId() &&
					pParam->GetType() == data->GetType())
					goto ERROR;
				data = pParam;
				assign(t, pFunction);
				data = origin_data;
			}
			NODE::driver->call_proc(pFunction);
			return *this;
		}
	}
	if(data->GetType() & Type_array || t.data->GetType() & Type_array)
	{
		if(data->GetType() == t.data->GetType() && 
			data->GetClassId() == t.data->GetClassId() &&
			data->GetArrayCount() == t.data->GetArrayCount())
		{
			for (int i = 0; i < data->GetArrayCount(); i++)
			{
				ARRAY *pArray = static_cast<ARRAY *>(data);
				const ARRAY *pArray_t = static_cast<const ARRAY *>(t.data);
				*pArray->data[i] = *pArray_t->data[i];
			}
			return *this;
		}
		goto ERROR;
	}
	
	if (data->GetClassId() == t.data->GetClassId())
	{
		*data = *t.data;
		return *this;
	}
	
	switch(data->GetType())
	{
		case Type_number:
		{
			switch(t.data->GetType())
			{
				case Type_bool:
					data->GetNumber() = t.data->GetFlag() ? 1 : 0;
					return *this;
				case Type_interger:
					data->GetNumber() = t.data->GetInterger();
					return *this;	
				case Type_fuzzy:
					data->GetNumber() = t.data->GetValue();
					return *this;	
				case Type_struct:
					if(t.data->IsFuzzy())
					{
						data->GetNumber() = t.data->GetFuzzy()->GetValue();
						return *this;
					}
					break;
				case Type_string:
					data->GetNumber() = strtod(t.data->GetString().data(), NULL);
					return *this;		
			}
			break;
		}
		case Type_interger:
		{
			switch(t.data->GetType())
			{
				case Type_bool:
					data->GetInterger() = t.data->GetFlag() ? 1 : 0;
					return *this;
				case Type_number:
					data->GetInterger() = (long)t.data->GetNumber();
					return *this;	
				case Type_fuzzy:
					data->GetInterger() = (long)t.data->GetValue();
					return *this;		
				case Type_struct:
					if(t.data->IsFuzzy())
					{
						data->GetInterger() = (long)t.data->GetFuzzy()->GetValue();
						return *this;
					}
					break;
				case Type_string:
					data->GetInterger() = atoi(t.data->GetString().data());
					return *this;		
			}
			break;
		}
		case Type_string:
		{
			switch(t.data->GetType())
			{
				case Type_number:
				{
					char text[1024];
					sprintf(text, "%g", t.data->GetNumber());
					data->GetString() = text;
					return *this;	
				}
				case Type_interger:
				{
					char text[1024];
					sprintf(text, "%d", t.data->GetInterger());
					data->GetString() = text;
					return *this;		
				}
			}
			break;
		}
		case Type_bool:
		{
			switch(t.data->GetType())
			{
				case Type_number:
					data->GetFlag() = t.data->GetNumber() != 0 ? true : false;
					return *this;
				case Type_interger:
					data->GetFlag() = t.data->GetInterger() != 0 ? true : false;
					return *this;		
			}
			break;
		}
		case Type_fuzzy:
		{
			switch(t.data->GetType())
			{
				case Type_number:
					data->GetValue() = t.data->GetNumber();
					data->InitBelong();
					return *this;
				case Type_interger:
					data->GetValue() = t.data->GetInterger();
					data->InitBelong();
					return *this;	
			}
			break;
		}
	}
	
ERROR:	
	string text;
	if(pFunction == NULL)
		text = "no match for `operator=' (operand types are `";
	else if(bFunctionConvert)
		text = "invalid conversion (from `";
	else
		text = "no match for arguments (argument types are `";
	text += t.data->GetTypename();
	if(t.data->GetType() & Type_array)
		text += NODE::driver->GetArrayName_bracket(t.data);
	if(bFunctionConvert)
		text += "' to `";
	else
		text += "' and `";
	text += data->GetTypename();
	if(data->GetType() & Type_array)
		text += NODE::driver->GetArrayName_bracket(data);
	text += "')";
	if(pFunction)
	{
		string function_name;
		NODE::driver->GetFunctionName(pFunction, function_name);
		text += "\n\t" + function_name;
	}
	driver->error(loc + t.loc, text);
	exit (EXIT_FAILURE);
} 


std::ostream & operator<<(std::ostream &os, const Number &t)
{
	os << t.m_number;
	return os;
}

std::ostream & operator<<(std::ostream &os, const INTERGER &t)
{
	os << t.m_interger;
	return os;
}

std::ostream & operator<<(std::ostream &os, const String &t)
{
	os << t.m_string;
	return os;
}

std::ostream & operator<<(std::ostream &os, const FUZZY &t)
{
	os << t.m_value;
	return os;
}

std::ostream & operator<<(std::ostream &os, const NODE &t)
{
	switch (t.data->GetType())
	{
		case Type_number:
		{
			Number *pNumber_t = static_cast<Number *>(t.data);
			os << *pNumber_t;
			return os;
		}
		case Type_interger:
		{
			INTERGER *pInterger_t = static_cast<INTERGER *>(t.data);
			os << *pInterger_t;
			return os;
		}
		case Type_string:
		{
			String *pString_t = static_cast<String *>(t.data);
			os << *pString_t;
			return os;
		}
		case Type_fuzzy:
		{
			FUZZY *pFuzzy_t = static_cast<FUZZY *>(t.data);
			os << *pFuzzy_t;
			return os;
		}
		case Type_struct:
		{
			if(!t.data->IsFuzzy())
				break;
			FUZZY *pFuzzy_t = static_cast<FUZZY *>(t.data->GetFuzzy());
			os << *pFuzzy_t;
			return os;
		}
		default:
		{
			
		}
	
	}
	
	string text = "no `print' function for type `";
	text += t.data->GetTypename();
	text += "'";
	NODE::driver->error(t.loc, text);
	exit (EXIT_FAILURE);
}

Object * FuzzyToArray (Object *fuzzy, Object *array, const yy::location &loc)
{
	if(!NODE::driver->CheckFuzzyObject_discrete(fuzzy, loc, "FuzzyToArray function"))
		exit(EXIT_FAILURE);
	if(array->GetClassId() != CLASS_ID_FUZZY_PAIR || !(array->GetType() & Type_array))
	{
		string msg = "no match type, second argument must be an array of FuzzyPair";
		NODE::driver->error(loc, msg);
		exit(EXIT_FAILURE);
	}
	
	Object *fuzzy_set;
		
	if(fuzzy->GetType() == Type_fuzzy)
		fuzzy_set = fuzzy;
	else
		fuzzy_set = fuzzy->GetFuzzy();
	
	if(array->GetArrayCount() < fuzzy_set->GetSize())
	{
		string msg = "array too small";
		NODE::driver->error(loc, msg);
		exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < fuzzy_set->GetSize(); i++)
	{
		Object *fuzzy_pair = array->GetArrayElement(i);
		POSITION pos;
		
		pos = fuzzy_pair->GetVarMap()->FindFirstWithKey("m_grade");
		Object *m_grade = fuzzy_pair->GetVarMap()->GetValueAt(pos);
		m_grade->GetNumber() = fuzzy_set->GetBelong()[i].m_grade;
		
		pos = fuzzy_pair->GetVarMap()->FindFirstWithKey("m_value");
		Object *m_value = fuzzy_pair->GetVarMap()->GetValueAt(pos);
		m_value->GetNumber() = fuzzy_set->GetBelong()[i].m_value;
	}
	
	return array;
}

Object * Defuzz (Object *fuzzy, const yy::location &loc)
{
	if(!NODE::driver->CheckFuzzyObject_discrete(fuzzy, loc, "Defuzz function"))
		exit(EXIT_FAILURE);
	
	fuzzy->MakeFuzzyClear();
	
	return fuzzy;
}

Object * ZeroFuzz (Object *fuzzy, const yy::location &loc)
{
	if(!NODE::driver->CheckFuzzyObject_discrete(fuzzy, loc, "ZeroFuzz function"))
		exit(EXIT_FAILURE);
	
	fuzzy->ZeroBelong();
	
	return fuzzy;
}

Object * PutReading (Object *fuzzy, Object *val, const yy::location &loc)
{
	if(!NODE::driver->CheckFuzzyObject_discrete(fuzzy, loc, "PutReading function"))
		exit(EXIT_FAILURE);
	if( !(val->GetType() == Type_number || val->GetType() == Type_interger) )
	{
		string msg = "no match type, second argument must be a number";
		NODE::driver->error(loc, msg);
		exit(EXIT_FAILURE);
	}
	
	Object *fuzzy_set;
		
	if(fuzzy->GetType() == Type_fuzzy)
		fuzzy_set = fuzzy;
	else
		fuzzy_set = fuzzy->GetFuzzy();
    
    bool bFuzzyInited = false;
    for (int i = 0; i < fuzzy_set->GetSize(); i++)
        if (fuzzy_set->GetBelong()[i].m_value != 0) {
            bFuzzyInited = true;
            break;
        }
    if( !bFuzzyInited ) {
        if( fuzzy->GetType() == Type_fuzzy ) {
            string msg = "Fuzzy set has not been initialized";
            NODE::driver->error(loc, msg);
            exit(EXIT_FAILURE);
        }
        
        bool bHasFuzzyVar = false;
        POSITION pos = fuzzy->GetVarMap()->GetHeadPosition();
        while(pos)
        {
            const TPair *p = fuzzy->GetVarMap()->GetNext(pos);
            if (p->m_value->GetType() == Type_fuzzy) {
                bHasFuzzyVar = true;
                *fuzzy_set = *p->m_value;
                break;
            }
            
        }
        if ( !bHasFuzzyVar ) {
            string msg = "Fuzzy set has not been initialized";
            NODE::driver->error(loc, msg);
            exit(EXIT_FAILURE);
        }
    }
    bFuzzyInited = false;
    for (int i = 0; i < fuzzy_set->GetSize(); i++)
        if (fuzzy_set->GetBelong()[i].m_value != 0) {
            bFuzzyInited = true;
            break;
        }
    if( !bFuzzyInited ) {
        string msg = "Fuzzy set has not been initialized";
        NODE::driver->error(loc, msg);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < fuzzy_set->GetSize(); i++)
        fuzzy_set->GetBelong()[i].m_grade = 0;
    
    double min_diff = 1.7e+308;
    double input;
    if (val->GetType() == Type_number)
        input = val->GetNumber();
    else
        input = val->GetInterger();
    
    int index_match;
    for (int i = 0; i < fuzzy_set->GetSize(); i++) {
        double diff = abs(fuzzy_set->GetBelong()[i].m_value - input);
        if ( diff < min_diff ) {
            min_diff = diff;
            index_match = i;
        }
    }
    
    input = fuzzy_set->GetBelong()[index_match].m_value;
    
    if (index_match == 0) {
        fuzzy_set->GetBelong()[0].m_grade = 1;
        fuzzy_set->GetBelong()[1].m_grade = 0.5;
    } 
    else if (index_match == fuzzy_set->GetSize() - 1) {
        fuzzy_set->GetBelong()[fuzzy_set->GetSize() - 1].m_grade = 1;
        fuzzy_set->GetBelong()[fuzzy_set->GetSize() - 2].m_grade = 0.5;
    }
    else {
        fuzzy_set->GetBelong()[index_match].m_grade = 1;
        fuzzy_set->GetBelong()[index_match - 1].m_grade = 0.5;
        fuzzy_set->GetBelong()[index_match + 1].m_grade = 0.5;
    }
    
    if (val->GetType() == Type_number)
        val->GetNumber() = input;
    else
        val->GetInterger() = input;
    
	return val;
}

Object * PutReading (Object *fuzzy, Object *val, Object *grade, Object *rate, Object *bClear, const yy::location &loc)
{
	if(!NODE::driver->CheckFuzzyObject_discrete(fuzzy, loc, "PutReading function"))
		exit(EXIT_FAILURE);
	if( !(val->GetType() == Type_number || val->GetType() == Type_interger) )
	{
		string msg = "no match type, second argument must be a number";
		NODE::driver->error(loc, msg);
		exit(EXIT_FAILURE);
	}
	if( !(grade->GetType() == Type_number || grade->GetType() == Type_interger) )
	{
		string msg = "no match type, third argument must be a number";
		NODE::driver->error(loc, msg);
		exit(EXIT_FAILURE);
	}
	if( !(rate->GetType() == Type_number || rate->GetType() == Type_interger) )
	{
		string msg = "no match type, fourth argument must be a number";
		NODE::driver->error(loc, msg);
		exit(EXIT_FAILURE);
	}
	if( !(bClear->GetType() == Type_bool || bClear->GetType() == Type_interger) )
	{
		string msg = "no match type, fifth argument must be a boolean value";
		NODE::driver->error(loc, msg);
		exit(EXIT_FAILURE);
	}
	
	double grade_val;
    if (grade->GetType() == Type_number)
        grade_val = grade->GetNumber();
    else
        grade_val = grade->GetInterger();
    if( grade_val > 1 || grade_val < 0 )
	{
		string msg = "the grade argument must be in the range from 0 to 1";
		NODE::driver->error(loc, msg);
		exit(EXIT_FAILURE);
	}
	
	double rate_val;
    if (rate->GetType() == Type_number)
        rate_val = rate->GetNumber();
    else
        rate_val = rate->GetInterger();
    if( rate_val > 1 || rate_val < 0 )
	{
		string msg = "the rate argument must be in the range from 0 to 1";
		NODE::driver->error(loc, msg);
		exit(EXIT_FAILURE);
	}
	
	int bClear_val;
    if (bClear->GetType() == Type_bool)
        bClear_val = bClear->GetFlag();
    else
        bClear_val = bClear->GetInterger();
	
	
	Object *fuzzy_set;
		
	if(fuzzy->GetType() == Type_fuzzy)
		fuzzy_set = fuzzy;
	else
		fuzzy_set = fuzzy->GetFuzzy();
    
    bool bFuzzyInited = false;
    for (int i = 0; i < fuzzy_set->GetSize(); i++)
        if (fuzzy_set->GetBelong()[i].m_value != 0) {
            bFuzzyInited = true;
            break;
        }
    if( !bFuzzyInited ) {
        if( fuzzy->GetType() == Type_fuzzy ) {
            string msg = "Fuzzy set has not been initialized";
            NODE::driver->error(loc, msg);
            exit(EXIT_FAILURE);
        }
        
        bool bHasFuzzyVar = false;
        POSITION pos = fuzzy->GetVarMap()->GetHeadPosition();
        while(pos)
        {
            const TPair *p = fuzzy->GetVarMap()->GetNext(pos);
            if (p->m_value->GetType() == Type_fuzzy) {
                bHasFuzzyVar = true;
                *fuzzy_set = *p->m_value;
                break;
            }
            
        }
        if ( !bHasFuzzyVar ) {
            string msg = "Fuzzy set has not been initialized";
            NODE::driver->error(loc, msg);
            exit(EXIT_FAILURE);
        }
    }
    bFuzzyInited = false;
    for (int i = 0; i < fuzzy_set->GetSize(); i++)
        if (fuzzy_set->GetBelong()[i].m_value != 0) {
            bFuzzyInited = true;
            break;
        }
    if( !bFuzzyInited ) {
        string msg = "Fuzzy set has not been initialized";
        NODE::driver->error(loc, msg);
        exit(EXIT_FAILURE);
    }

    if (bClear_val)
        for (int i = 0; i < fuzzy_set->GetSize(); i++)
            fuzzy_set->GetBelong()[i].m_grade = 0;
    
    double min_diff = 1.7e+308;
    double input;
    if (val->GetType() == Type_number)
        input = val->GetNumber();
    else
        input = val->GetInterger();
    
    int index_match;
    for (int i = 0; i < fuzzy_set->GetSize(); i++) {
        double diff = abs(fuzzy_set->GetBelong()[i].m_value - input);
        if ( diff < min_diff ) {
            min_diff = diff;
            index_match = i;
        }
    }
    
    input = fuzzy_set->GetBelong()[index_match].m_value;
    
    if (index_match == 0) {
        fuzzy_set->GetBelong()[0].m_grade = grade_val;
        fuzzy_set->GetBelong()[1].m_grade = grade_val * rate_val;
    } 
    else if (index_match == fuzzy_set->GetSize() - 1) {
        fuzzy_set->GetBelong()[fuzzy_set->GetSize() - 1].m_grade = grade_val;
        fuzzy_set->GetBelong()[fuzzy_set->GetSize() - 2].m_grade = grade_val * rate_val;
    }
    else {
        fuzzy_set->GetBelong()[index_match].m_grade = grade_val;
        fuzzy_set->GetBelong()[index_match - 1].m_grade = grade_val * rate_val;
        fuzzy_set->GetBelong()[index_match + 1].m_grade = grade_val * rate_val;
    }
    
    if (val->GetType() == Type_number)
        val->GetNumber() = input;
    else
        val->GetInterger() = input;
    
	return val;
}

void usage(int code)
{
	cout << endl;
	cout << VERSION << endl << endl;
	string msg = "Usage: fuzzy program-file\n";
	      msg += "       fuzzy -h\n";
          msg += "       fuzzy -r \"val1 val2 ...\" program-file\n\n";
	msg += "Written June, 2019 by Pham Thanh Tuyen\n";
	cout << msg;
	exit(code);
}

