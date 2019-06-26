/*
  fuzzy - The implementation of the FUZZY programming language

  File: fuzzy_scanner.ll

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

%{ /* -*- C++ -*- */
# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include "fuzzy_driver.hh"
# include "fuzzy_parser.hh"
# include <assert.h>

# undef yywrap
# define yywrap() 1

// The location of the current token.

%}
%option noyywrap nounput batch debug

NAME		[a-z_A-Z]+[a-zA-Z_0-9]*
BLANK		[ \t]
STRING	 	\"
COMMENCE_C	"/*"
COMMENCE_CC	"//"
INTERGER	[0-9]+
DOUBLE   	[0-9]+"."[0-9]*

%x quote
%x comment
%x commentcc
%x incl

%{
	// Code run each time a pattern is matched.
	# define YY_USER_ACTION  YYLLOC->columns (yyleng);
	
	void yy_switch_to_buffer_ ( YY_BUFFER_STATE new_buffer )
	{
		yy_switch_to_buffer(new_buffer);
	}
	void yy_delete_buffer_()
	{
		yy_delete_buffer( YY_CURRENT_BUFFER );
	}
	YY_BUFFER_STATE yy_create_buffer_()
	{
		return yy_create_buffer( yyin, YY_BUF_SIZE );
	}
	
%}

%%

	char *string_buf;
	char *string_buf_ptr;
	

#include        BEGIN(incl);

<incl>[ \t]*    YYLLOC->step ();/* eat the whitespace */
<incl>[^ \t\n]+ { /* got the include file name */

			include_data data;
			data.loc = *YYLLOC;
			data.buffer = YY_CURRENT_BUFFER;
			driver->list.AddTail(data);
			
			string filename = yytext + 1;
			filename.resize(yyleng - 2);
			yyin = fopen( filename.data(), "r" );

			if ( ! yyin )
			{
				string notice = filename + ": No such file or directory";
				YYLLOC->begin += 1;
				YYLLOC->end -= 1;
				driver->error(*YYLLOC, notice);
				exit(EXIT_FAILURE);
			}

			driver->filenames.AddTail(filename);
			YYLLOC->step ();
			BEGIN(INITIAL);
			return yy::fuzzy_parser::token::TOK_BOF;
		}

%{
  // Code run each time yylex is called.
  YYLLOC->step ();
%}

{COMMENCE_CC}		BEGIN(commentcc);

<commentcc>{
	[^\n]*
	\n		{
			YYLLOC->lines (1); YYLLOC->step ();
			BEGIN(INITIAL);
			}
}

{COMMENCE_C}       	BEGIN(comment);

<comment>{
	[^*\n]*
	[^*\n]*\n      		YYLLOC->lines (1); YYLLOC->step ();
	"*"+[^*/\n]*
	"*"+[^*/\n]*\n 		YYLLOC->lines (1); YYLLOC->step ();
	"*"+"/"        		BEGIN(INITIAL);
}
 
{BLANK}+			YYLLOC->step ();
[\n]+   YYLLOC->lines (yyleng); YYLLOC->step ();
        /* \\\n  	YYLLOC->lines (1); YYLLOC->step ();*/
"-"     return yy::fuzzy_parser::token::TOK_MINUS;
"+"     return yy::fuzzy_parser::token::TOK_PLUS;
"*"     return yy::fuzzy_parser::token::TOK_STAR;
"/"     return yy::fuzzy_parser::token::TOK_SLASH;
"%"     return yy::fuzzy_parser::token::TOK_MOD;
"("     return yy::fuzzy_parser::token::TOK_LPAREN;
")"     return yy::fuzzy_parser::token::TOK_RPAREN;
"["     return yy::fuzzy_parser::token::TOK_LBRACKET;
"]"     return yy::fuzzy_parser::token::TOK_RBRACKET;
"^"     return yy::fuzzy_parser::token::TOK_POW;
","     return yy::fuzzy_parser::token::TOK_COMMA;
";"     return yy::fuzzy_parser::token::TOK_SEMI;
"."     return yy::fuzzy_parser::token::TOK_DOT;
"::"     return yy::fuzzy_parser::token::TOK_SCOPE;
":"     return yy::fuzzy_parser::token::TOK_COLON;
"!"     return yy::fuzzy_parser::token::TOK_NOT;
"++"     return yy::fuzzy_parser::token::TOK_PLUSPLUS;
"--"     return yy::fuzzy_parser::token::TOK_MINUSMINUS;
"="     {
  YYLVAL->Node_type = Node_assign;
  return yy::fuzzy_parser::token::TOK_ASSIGNOP;
}
"+="     {
  YYLVAL->Node_type = Node_assign_plus;
  return yy::fuzzy_parser::token::TOK_ASSIGNOP;
}
"-="     {
  YYLVAL->Node_type = Node_assign_minus;
  return yy::fuzzy_parser::token::TOK_ASSIGNOP;
}
"*="     {
  YYLVAL->Node_type = Node_assign_multive;
  return yy::fuzzy_parser::token::TOK_ASSIGNOP;
}
"/="     {
  YYLVAL->Node_type = Node_assign_quotient;
  return yy::fuzzy_parser::token::TOK_ASSIGNOP;
}
"%="     {
  YYLVAL->Node_type = Node_assign_mod;
  return yy::fuzzy_parser::token::TOK_ASSIGNOP;
}
">"     {
  if(driver->want_redirect)
  {
      YYLVAL->Node_type = Node_redirect_output;
      return yy::fuzzy_parser::token::TOK_REDIRECT_OP;
  }
  else
  {
      YYLVAL->Node_type = Node_greater;
      return yy::fuzzy_parser::token::TOK_RELOP;
  }
}
">>"     {
  YYLVAL->Node_type = Node_redirect_append;
  return yy::fuzzy_parser::token::TOK_REDIRECT_OP;
}
"<"     {
  YYLVAL->Node_type = Node_less;
  return yy::fuzzy_parser::token::TOK_RELOP;
}
">="     {
  YYLVAL->Node_type = Node_ge;
  return yy::fuzzy_parser::token::TOK_RELOP;
}
"<="     {
  YYLVAL->Node_type = Node_le;
  return yy::fuzzy_parser::token::TOK_RELOP;
}
"!="     {
  YYLVAL->Node_type = Node_notequal;
  return yy::fuzzy_parser::token::TOK_RELOP;
}
"=="     {
  YYLVAL->Node_type = Node_equal;
  return yy::fuzzy_parser::token::TOK_RELOP;
}
"&&"     {
  return yy::fuzzy_parser::token::TOK_AND;
}
"||"     {
  return yy::fuzzy_parser::token::TOK_OR;
}
"true"     {
  YYLVAL->bval = true;
  return yy::fuzzy_parser::token::TOK_BOOLEN;
}
"false"     {
  YYLVAL->bval = false;
  return yy::fuzzy_parser::token::TOK_BOOLEN;
}

"if"   	  	return yy::fuzzy_parser::token::TOK_IF;
"else"     	return yy::fuzzy_parser::token::TOK_ELSE;
"while"     	return yy::fuzzy_parser::token::TOK_WHILE;
"for"     	return yy::fuzzy_parser::token::TOK_FOR;
"break"     	return yy::fuzzy_parser::token::TOK_BREAK;
"continue"     	return yy::fuzzy_parser::token::TOK_CONTINUE;
"switch"     	return yy::fuzzy_parser::token::TOK_SWITCH;
"case"     	return yy::fuzzy_parser::token::TOK_CASE;
"default"     	return yy::fuzzy_parser::token::TOK_DEFAULT;
"exit"     	return yy::fuzzy_parser::token::TOK_EXIT;
"return"	return yy::fuzzy_parser::token::TOK_RETURN;
"{"     	return yy::fuzzy_parser::token::TOK_LBRACE;
"}"     	return yy::fuzzy_parser::token::TOK_RBRACE;
"void"     	return yy::fuzzy_parser::token::TOK_VOID;
"print"     	return yy::fuzzy_parser::token::TOK_PRINT;
"prints"     	return yy::fuzzy_parser::token::TOK_PRINT_SET;
"struct"     	return yy::fuzzy_parser::token::TOK_STRUCT;
"term"     	return yy::fuzzy_parser::token::TOK_TERM;
"String"     	YYLVAL->sval = yytext; return yy::fuzzy_parser::token::TOK_STRING_KEY;
"Number"     	YYLVAL->sval = yytext; return yy::fuzzy_parser::token::TOK_NUMBER_KEY;
"bool"     	YYLVAL->sval = yytext; return yy::fuzzy_parser::token::TOK_BOOL_KEY;
"fuzzy"     	YYLVAL->sval = yytext; return yy::fuzzy_parser::token::TOK_FUZZY_KEY;
"int"     	YYLVAL->sval = yytext; return yy::fuzzy_parser::token::TOK_INT_KEY;
"operator"     	YYLVAL->sval = yytext; return yy::fuzzy_parser::token::TOK_OPERATOR;
"this"     	YYLVAL->sval = yytext; return yy::fuzzy_parser::token::TOK_THIS;
"system"     	return yy::fuzzy_parser::token::TOK_SYSTEM;
            /* "system"    {
  driver->error (*YYLLOC, "Online version does not support the keyword `system'");
  exit(EXIT_FAILURE);
} */
"rule"     	return yy::fuzzy_parser::token::TOK_RULE;
"=>"     	return yy::fuzzy_parser::token::TOK_DEDUCE;
"discrete"  return yy::fuzzy_parser::token::TOK_DISCRETE;
"put"     	return yy::fuzzy_parser::token::TOK_PUT;
":="     	return yy::fuzzy_parser::token::TOK_ASSIGN_FUZ;
"VERY"     	return yy::fuzzy_parser::token::TOK_VERY;
"EXTREMELY" return yy::fuzzy_parser::token::TOK_EXTREMELY;
"SEEMED"    return yy::fuzzy_parser::token::TOK_SEEMED;
"BIT"    return yy::fuzzy_parser::token::TOK_BIT;
"LITTLE"    return yy::fuzzy_parser::token::TOK_LITTLE;
"REALLY"    return yy::fuzzy_parser::token::TOK_REALLY;
"AND"     	return yy::fuzzy_parser::token::TOK_AND_FUZ;
"OR"     	return yy::fuzzy_parser::token::TOK_OR_FUZ;
"NOT"     	return yy::fuzzy_parser::token::TOK_NOT_FUZ;
  
{DOUBLE}      {
  errno = 0;
  double val = strtod (yytext, NULL);
  if (! (val > -HUGE_VALF && val < HUGE_VALF && errno != ERANGE))
  {
    driver->error (*YYLLOC, "Number is out of range.");
    //yyterminate();
    //exit (EXIT_FAILURE);
  }
  
  YYLVAL->dval=val;
  return yy::fuzzy_parser::token::TOK_NUM;
}

{INTERGER}      {
  long val = atol (yytext);
  YYLVAL->lval=val;
  return yy::fuzzy_parser::token::TOK_INT;
}

{STRING}      {  
  char *p = yy_c_buf_p + 1;
  int i = 0;

  while((*p != '"' || *(p - 1) == '\\') && *p != 0)
  {
    p++;
    i++;
  }
  
  string_buf = new char[i + 1];
  string_buf_ptr = string_buf; 
  BEGIN(quote);
}

<quote>{
	{STRING}        { 
	/* saw closing quote - all done */
	BEGIN(INITIAL);
	*string_buf_ptr = '\0';
	YYLVAL->sval = string_buf;
	delete string_buf;
	return yy::fuzzy_parser::token::TOK_STRING;
	/* return string constant token type and
	* value to parser
	*/
	}

	\n        {
	driver->error (*YYLLOC, "unterminated string constant");
	exit(EXIT_FAILURE);
	/* error - unterminated string constant */
	/* generate error message */
	//YYLLOC->lines (1); YYLLOC->step ();
	}

	\\[0-7]{1,3} {
	/* octal escape sequence */
	int result;

	(void) sscanf( yytext + 1, "%o", &result );

	if ( result > 0xff )
		/* error, constant is out-of-bounds */
		{
		  driver->error (*YYLLOC, "constant is out-of-bounds");
		  exit(EXIT_FAILURE);
		}

	*string_buf_ptr++ = result;
	}

	\\[0-9]+ {
	/* generate error - bad escape sequence; something
	* like '\48' or '\0777777'
	*/
	driver->error (*YYLLOC, "bad escape sequence");
	exit(EXIT_FAILURE);
	}
	
	\\n  *string_buf_ptr++ = '\n';
	\\t  *string_buf_ptr++ = '\t';
	\\r  *string_buf_ptr++ = '\r';
	\\b  *string_buf_ptr++ = '\b';
	\\f  *string_buf_ptr++ = '\f';

	\\.  *string_buf_ptr++ = yytext[1];
	\\\n  YYLLOC->lines (1); YYLLOC->step ();
	
	[^\\\n\"]+        {
	char *yptr = yytext;

	while ( *yptr )
		*string_buf_ptr++ = *yptr++;
	}
}

{NAME}       {
  
	YYLVAL->sval = yytext;
	return yy::fuzzy_parser::token::TOK_NAME;
}

.	driver->error (*YYLLOC, "invalid character");

<<EOF>> 	{
	if ( driver->list.IsEmpty() )
	    return yy::fuzzy_parser::token::TOK_END;
	
	return yy::fuzzy_parser::token::TOK_END_I_FILE;
}
%%

void
fuzzy_driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      error ("cannot open " + file + ": " + strerror(errno));
      exit (EXIT_FAILURE);
    }
}

void
fuzzy_driver::scan_end ()
{
  fclose (yyin);
}

