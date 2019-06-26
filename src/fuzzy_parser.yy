/*
  fuzzy - The implementation of the FUZZY programming language

  File: fuzzy_parser.yy

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

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.4"
%defines
%define parser_class_name {fuzzy_parser}

%define parse.assert
%code requires
{
# include <string>
# include <math.h>   /* For pow, used in the grammar.  */
# include "classes.h"   /* Contains definition of 'symrec'.  */

  struct YYSTYPE {
	  bool bval;
	  long lval;
	  double dval;
	  NODE *Node_ptr;
	  NODETYPE Node_type;
	  std::string sval;
  };


#define append_right driver->append_r  
#define node driver->new_node  
  
  class fuzzy_driver;

}
// The parsing context.
%param { fuzzy_driver *driver }
%locations
%initial-action
{
  // Initialize the initial location.
  @$.begin.filename = @$.end.filename = &driver->file;
};
%define parse.trace
%define parse.error verbose
%code
{
# include "fuzzy_driver.hh"
# include <stdio.h>  /* For printf, etc. */

}
%define api.token.prefix {TOK_}
%token
  END  0  	"end of file"
  MINUS   	"-"
  PLUS    	"+"
  STAR    	"*"
  SLASH   	"/"
  MOD   	"%"
  LPAREN  	"("
  RPAREN  	")"
  POW     	"^"
  NEG	  	"NEG"
  COMMA	  	","	
  PRINT	  	"print"
  IF	  	"if"
  ELSE	  	"else"
  WHILE	  	"while"
  BREAK		"break"
  CONTINUE	"continue"
  LBRACE	"{"
  RBRACE	"}"
  STRUCT	"struct"
  TERM		"term"
  SEMI		";"
  DOT		"."
  SCOPE		"::"
  RETURN	"return"
  END_I_FILE	"end of include file"
  BOF		"switch to include file"
  LBRACKET	"["
  RBRACKET	"]"
  VOID		"void"
  NOT		"!"
  PLUSPLUS	"++"
  MINUSMINUS	"--"
  AND		"&&"
  OR		"||"
  EXIT		"exit"
  FOR		"for"
  SWITCH	"switch"
  CASE		"case"
  DEFAULT	"default"
  COLON		":"
  SYSTEM	"system"
  DISCRETE	"discrete"
  PUT		"put"
  PRINT_SET  	"prints"
  ASSIGN_FUZ	":="
  RULE		"rule"
  DEDUCE	"=>"
  AND_FUZ	"AND"
  OR_FUZ	"OR"
  NOT_FUZ	"NOT"
  VERY		"VERY"
  EXTREMELY	"EXTREMELY"
  SEEMED	"SEEMED"
  BIT	    "BIT"
  LITTLE	"LITTLE"
  REALLY	"REALLY"
;

%define api.value.type {struct YYSTYPE} 
%token 		<bval>  	BOOLEN
%token 		<dval>  	NUM "Number type"
%token 		<lval>  	INT "int type" 
%token 		<sval>  	STRING  NAME  STRING_KEY "String"  NUMBER_KEY	"Number"
%token 		<sval>  	BOOL_KEY "bool" FUZZY_KEY "fuzzy"  INT_KEY "int"
%token 		<sval>  	OPERATOR "operator" THIS "this"
%token 		<Node_type>   	ASSIGNOP "ASSIGN OPERATOR"
%token 		<Node_type>   	RELOP REDIRECT_OP

%type  <Node_ptr>  	exp conditional if_statement statements statement
%type  <Node_ptr>  	expression_list opt_expression_list declare declares 
%type  <Node_ptr>  	namespace namescope opt_param_list param_list opt_exp 
%type  <Node_ptr>  	function_define function_decl function_call action
%type  <Node_ptr>  	name variable_decl variable_decl_list name_general
%type  <Node_ptr>  	datatype simple_stmt opt_simple_stmt for_init_stmt
%type  <Node_ptr>  	declare_var case_statement case_statements
%type  <Node_ptr>  	redirection namespaces fuzzy_rule exp_fuzzy fuzzy_params 
%type  <Node_ptr>  	fuzzy_input 



%printer { yyoutput << $$; } <*>;

%right ASSIGNOP

%left "||"
%left "&&"
%left "OR"
%left "AND"
%precedence REALLY
%precedence LITTLE
%precedence SEEMED
%precedence VERY
%precedence EXTREMELY
%precedence BIT
%precedence "NOT"
%left RELOP
%left "+" "-"
%left "*" "/" "%"
%precedence NOT
%precedence "NEG" /* negation--unary minus */  

%right "^"

%precedence  STRING_KEY
%precedence  NUMBER_KEY
%precedence  BOOL_KEY
%precedence  FUZZY_KEY
%precedence  NAME

%precedence  OPERATOR

%right IF ELSE
%right SEMI

%%
%start unit;
unit
	:  statements	 
		{
		  driver->root = $1;
		};

statements
	: %empty { $$ = NULL; }
	//| statement	{ $$ = node ($1, Node_statements,(NODE *) NULL, @$); }
	| statements statement 	
		{
			if($1 == NULL)
				$$ = node ($2, Node_statements,(NODE *) NULL, @$);
			else	
				$$ = append_right($1, node($2, Node_statements,(NODE *) NULL, @2));
		}
	;

statement
	: simple_stmt SEMI { $$ = $1; }		
	| if_statement	{ $$ = node ($1, Node_statement,(NODE *) NULL, @$);}
	| WHILE "(" exp ")"  statement
		{ $$ = node ($3, Node_K_while, $5, @$); } 
	| FOR "(" for_init_stmt SEMI opt_exp SEMI opt_simple_stmt ")" statement
		{ 
			NODE *init = $3;
			NODE *expr = $5;
			NODE *incr = $7;
			NODE *body = $9;
			NODE *head = node (init, Node_illegal, NULL, @2 + @8);
			head = append_right(head, node(expr, Node_illegal, NULL, @5 + @7));
			head = append_right(head, node(incr, Node_illegal, NULL, @7));
			$$ = node (head, Node_K_for, body, @$);
			
		} 
	| SWITCH "(" exp ")" "{" case_statements "}"
		{ 
			$$ = node ($6, Node_switch, $3, @$);
		}	
	| BREAK SEMI
		{ $$ = node ((NODE *)NULL, Node_K_break, (NODE *)NULL, @$); }	
	| CONTINUE SEMI
		{ $$ = node ((NODE *)NULL, Node_K_continue, (NODE *)NULL, @$); }	
	| EXIT "(" exp ")" SEMI
		{ $$ = node ($3, Node_K_exit, (NODE *)NULL, @$); }	
	| action	{ $$ = $1; }	
  //	| error	{ $$ = NULL; yyerrok;}	
	| declare 	
		{ $$ = $1; }
	| namespace	SEMI
		{ $$ = $1; }
	| RETURN opt_exp SEMI
		{
		    $$ = node ($2, Node_return, NULL, @$);
		}
	| SYSTEM exp SEMI
		{
		    $$ = node ($2, Node_system, NULL, @$);
		}
	| ";" 	{}
	
	| END_I_FILE	
		{	
			include_data data = driver->list.RemoveTail();
			yyla.location = data.loc;
			yy_delete_buffer_();
			yy_switch_to_buffer_(data.buffer);
		}
	| BOF	{	
			string &newname = driver->filenames.GetTail();
			yyla.location.initialize(&newname);
			yy_switch_to_buffer_(yy_create_buffer_());
		}
		
	| fuzzy_rule SEMI	{ $$ = $1; }	
	| fuzzy_input SEMI	{ $$ = $1; }
	;

case_statements
	: %empty	{ $$ = NULL;	}
	| case_statements case_statement 	
		{ 
			if($1 == NULL)
			{
				$$ = node ($2, Node_illegal, NULL, @$);
			}
			else
			{
				$$ = append_right($1, node($2, Node_illegal, NULL, @$));
			}
		}	
	;
	
case_statement
	: CASE exp ":" statements		
		{
			$$ = node ($2, Node_case, $4, @$);
		}
	| DEFAULT ":" statements
		{ 
			$$ = node (NULL, Node_default, $3, @$); 	
		}	
	;	
	
for_init_stmt
	: declare_var		{ $$ = $1;	}
	| opt_simple_stmt 	{ $$ = $1; 	}	
	;	
	
simple_stmt
	: namespace ASSIGNOP exp 	{ $$ = node ($1, $2, $3, @$);	}	
	| PRINT 
		{ driver->want_redirect = true; }
		expression_list redirection 	
		{
			driver->want_redirect = false;
			$$ = node ($3, Node_K_print, $4, @$); 	
		}
	| PRINT_SET 
		{ driver->want_redirect = true; }
		expression_list redirection 	
		{
			driver->want_redirect = false;
			$$ = node ($3, Node_print_set, $4, @$); 	
		}	
	| namespace PLUSPLUS 		
		{ 
			NODE *one = node ((long)1, @2);
			$$ = node ($1, Node_assign_plus, one, @$);
		}
	| namespace MINUSMINUS		
		{ 
			NODE *one = node ((long)1, @2);
			$$ = node ($1, Node_assign_minus, one, @$);
		}
	;

redirection
	: %empty 	{ $$ = NULL;	}	
	| REDIRECT_OP STRING
		{
			NODE *filename = node ($2, @2);
			$$ = node (filename, $1, NULL, @$); 	
		}	
	;	
	
opt_simple_stmt
	: %empty 	{ $$ = NULL;	}	
	| simple_stmt 	{ $$ = $1; 	}	
	;
	
declares
	: %empty 	{ $$ = NULL;	}
	| declares declare 
		{
			if($1 == NULL)
				$$ = node ($2, Node_illegal, (NODE *) NULL, @$);
			else	
				$$ = append_right($1, node($2, Node_illegal,(NODE *) NULL, @2));
		}
	;
	
function_decl
	: VOID NAME "(" opt_param_list ")" 	
	  {
		NODE *func_name = node($2, @2);
		NODE *type = node(NULL, Node_type_void, NULL, @1);
		NODE *type_name = node(type, type->type, func_name, @1 + @2);
		NODE *params = $4;
		$$ = node(type_name, Node_function_decl, params, @$);
	  }
	| datatype NAME "(" opt_param_list ")" 	
	  {
		NODE *func_name = node($2, @2);
		NODE *type_name = node($1, $1->type, func_name, @1 + @2);
		NODE *params = $4;
		$$ = node(type_name, Node_function_decl, params, @$);
	  }
	| datatype OPERATOR ASSIGNOP "(" datatype name ")" 	
	  {
		NODE *func_name = node($2, @2);
		NODE *type_name = node($1, $1->type, func_name, @1 + @2);
		NODE *param = node($5, $5->type, $6, @5 + @6);
		param = node(param, Node_argument, NULL, @5 + @6);
		$$ = node(type_name, $3, param, @$);
	  }
	| VOID OPERATOR ASSIGNOP "(" datatype name ")" 	
	  {
		NODE *func_name = node($2, @2);
		NODE *type = node(NULL, Node_type_void, NULL, @1);
		NODE *type_name = node(type, type->type, func_name, @1 + @2);
		NODE *param = node($5, $5->type, $6, @5 + @6);
		param = node(param, Node_argument, NULL, @5 + @6);
		$$ = node(type_name, $3, param, @$);
	  }  
	| datatype OPERATOR "-" "(" ")" 	
	  {
		NODE *func_name = node($2, @2);
		NODE *type_name = node($1, $1->type, func_name, @1 + @2);
		NODE *param = NULL;
		$$ = node(type_name, Node_unary_minus, param, @$);
	  }  
	;
	
function_define
	: function_decl action	
	  {
		$$ = node($1, Node_function_define, $2, @$);
	  }
	;
	
function_call
	: NAME "(" opt_expression_list ")"
	  {
		NODE *namenode = node ($1, @1);
		//namenode = node (namenode, Node_illegal, NULL, @1);
		//NODE *namespace_node = namenode;
		NODE *exp_node = $3;
		$$ = node( namenode, Node_function, exp_node, @$);
	  }
	;	

opt_param_list
	: %empty	{ $$ = NULL; }
	| param_list	{ $$ = $1; }
	;
	
param_list
	: datatype name		
		{ 
		    $$ = node (node($1, $1->type, $2, @$), Node_argument, NULL, @$);
		}
	| param_list "," datatype name	
		{
		    $$ = append_right($1, node(node($3, $3->type, $4, @3 + @4),
				Node_argument, NULL, @$));
		}
	;	
	
datatype
	: namescope	{ $$ = $1; }	%prec STRING_KEY
	| NUMBER_KEY			
		{
		    $$ = node (node ($1, @1), Node_type_number, NULL, @$);
		}
	| INT_KEY			
		{
		    $$ = node (node ($1, @1), Node_type_interger, NULL, @$);
		}	
	| STRING_KEY			  
		{
		    $$ = node (node ($1, @1), Node_type_string, NULL, @$);
		}
	| BOOL_KEY			
		{
		    $$ = node (node ($1, @1), Node_type_bool, NULL, @$);
		}
	| FUZZY_KEY			
		{
		    $$ = node (node ($1, @1), Node_type_fuzzy, NULL, @$);
		}	
	;	
	
action
	: "{" statements "}" 
		{ 
			$$ = $2;
			if($$ != NULL)
			{
				$$->loc = @$; $$->type = Node_command_block;
			}
		}	
	;	
	
declare_var	
	: datatype variable_decl_list	
		{   
		    $$ = node ($1, Node_var_decl, $2, @$);
		}	
	;	
	
fuzzy_params	
	: exp "/" exp 
		{
			NODE *param = node ($1, Node_illegal, $3, @$);
			$$ = node (param, Node_illegal, NULL, @$);
		}	
	| fuzzy_params "," exp "/" exp 
		{
			NODE *param = node ($3, Node_illegal, $5, @3 + @5);
			$$ = append_right($1, node (param, Node_illegal, NULL, @3 + @5));
			$$->loc = @$;
		}	
	;	
	
fuzzy_input	
	: "put" namespace ":=" "(" fuzzy_params ")" 
		{
			$$ = node ($2, Node_fuzzy_input, $5, @$);
		}		
	;	
	
declare	
	: declare_var SEMI	
		{   
		    $$ = $1;
		}
	| FUZZY_KEY DISCRETE NAME  "("  fuzzy_params ")" SEMI	
		{
		    NODE *name = node ($3, @3);
		    $$ = node (name, Node_var_decl_fuzzy_discrete, $5, @$);
		}	
	| STRUCT NAME  "{"  declares "}" SEMI	
		{
		    $$ = node (node ($2, @2), Node_type_struct_declare, $4, @$);
		}
	| TERM NAME "(" exp "," exp "," INT ")"  "{"  declares "}" SEMI	
		{
		    NODE *name = node ($2, @2);
		    NODE *min_max = node ($4, Node_illegal, $6, @4 + @6);
		    NODE *size = node ($8, @8);
		    NODE *params = node (min_max, Node_illegal, size, @4 + @8);
		    NODE *header = node (name, Node_illegal, params, @2 + @9);
		    NODE *body = $11;
		    $$ = node (header, Node_type_struct_declare_fuzzy, body, @$);
		}
	| TERM NAME "(" INT ")"  "{"  declares "}" SEMI	
		{
		    NODE *name = node ($2, @2);
		    NODE *size = node ($4, @4);
		    NODE *header = node (name, Node_illegal, size, @2 + @5);
		    NODE *body = $7;
		    $$ = node (header, Node_type_struct_declare_fuzzy_discrete, body, @$);
		}	
	| function_define 
		{ $$ = $1; }	
	;	
	
if_statement
	: IF "(" exp ")"  statement	%prec ELSE
		{ $$ = node ($3, Node_K_if,
				node ($5, Node_if_branches, (NODE *)NULL, @5), @$); 
		}
	| IF "(" exp ")"  statement ELSE statement	
		{ $$ = node ($3, Node_K_if,
				node ($5, Node_if_branches, $7, @6 + @7), @$); 
		}	
	;

expression_list
	: exp { $$ = node ($1, Node_expression_list, (NODE *)NULL, @$); }
	| expression_list "," exp
		{ $$ = append_right($1, node( $3, Node_expression_list, (NODE *)NULL, @3)); }
	| "(" expression_list "," exp ")" 
		{ $$ = append_right($2, node( $4, Node_expression_list, (NODE *)NULL, @4)); }
	;
	
opt_expression_list
	: %empty		{ $$ = NULL; }
	| expression_list	{ $$ = $1; }
	;	
	
namescope
	: NAME	  { 	$$ = node (node ($1, @1), Node_type_var, (NODE *)NULL, @$);	}
	| "::" NAME	  
		  { 	
			$$ = node (node ($2, @2), Node_type_var_rootpath,
			(NODE *)NULL, @$);	
		  }
	| namescope "::" NAME
		  {
			$$ = append_right($1, node( node ($3, @3),
				Node_illegal, (NODE *)NULL, @3));
		  }
	;	

variable_decl
	: NAME ASSIGNOP exp	{ $$ = node (node ($1, @1), Node_assign, $3, @$);	}
	| name			{ $$ = $1; }
	;	
	
name
	: NAME			{ $$ = node ($1, @$);	$$->type = Node_name; } 
	| NAME "[" exp "]"	{ $$ = node (node ($1, @1), Node_array, $3, @$);	}	  
	;

variable_decl_list
	: variable_decl	  		{ $$ = node ($1, Node_illegal, NULL, @$);	}	  
	| variable_decl_list "," variable_decl	
		  {
			$$ = append_right($1, node ($3, Node_illegal, NULL, @3));
			$$->loc = @$;
		  }
	;
	
name_general
	: function_call		{ $$ = $1; }
	| name			{ $$ = $1; }
	;	
	
namespace
	: name_general	  		{ $$ = node ($1, Node_namespace, NULL, @$);	}	  
	| namespace "." name_general	
		  {
			$$ = append_right($1, node ($3, Node_namespace, NULL, @3));
			$$->loc = @$;
		  }
	;	

opt_exp
	: %empty
	  { $$ = NULL; }
	| exp
	  { $$ = $1; }
	;	

conditional
	: "!" exp			{ $$ = node ($2, Node_not, NULL, @$);	}
	
	
	| exp RELOP exp			{ $$ = node ($1, $2, $3, @$);		}	
	| exp "&&" exp			
		{
			$$ = node ($1, Node_and, $3, @$);	
		}
	| exp "||" exp			
		{
			$$ = node ($1, Node_or, $3, @$);	
		}
	;	

exp_fuzzy
	: namespaces			{ $$ = $1;					}	
	| exp_fuzzy "OR" exp_fuzzy 	{ $$ = node ($1, Node_or, $3, @$); 		}
	| exp_fuzzy "AND" exp_fuzzy 	{ $$ = node ($1, Node_and, $3, @$); 		}
	| "REALLY" exp_fuzzy 		{ $$ = node ($2, Node_really, NULL, @$);	}
	| "LITTLE" exp_fuzzy 		{ $$ = node ($2, Node_little, NULL, @$);	}
	| "VERY" exp_fuzzy 		{ $$ = node ($2, Node_very, NULL, @$);		}
	| "EXTREMELY" exp_fuzzy 		{ $$ = node ($2, Node_extremely, NULL, @$);		}
	| "SEEMED" exp_fuzzy 		{ $$ = node ($2, Node_seemed, NULL, @$);		}
	| "BIT" exp_fuzzy 		{ $$ = node ($2, Node_bit, NULL, @$);		}
	| "NOT" exp_fuzzy 		{ $$ = node ($2, Node_not, NULL, @$);		}
	| "(" exp_fuzzy ")" 		{ $$ = $2; $$->loc = @$;			}
	;	
	
fuzzy_rule
	: RULE exp_fuzzy "=>" namespace	
		{
			{ $$ = node ($2, Node_fuzzy_rule, $4, @$); 	}
		}	
	;	
	
namespaces
	: namespace ASSIGNOP exp	{ $$ = node ($1, $2, $3, @$);	}
	| namespace            		{ $$ = $1;			}
	| THIS               		
        { 
            NODE *this_node = node ($1, @1); this_node->type = Node_name;
            $$ = node (this_node, Node_namespace, NULL, @$);
        }
	;		
	
exp
	: NUM               	 	{ 
		  if($1 == HUGE_VALF)
		  {
		    error(@1,"compilation terminated.");
		    YYABORT;
		  }
		  $$ = node ($1, @$);
		}
	| INT               	 	{ $$ = node ($1, @$);		}	
	| STRING               	 	{ $$ = node ($1, @$);		}
	| BOOLEN			{ $$ = node ($1, @$);		}	
	| conditional	%prec RELOP	{ $$ = $1;			}
	| namespaces            	{ $$ = $1;			}
	| exp "+" exp        		{ $$ = node ($1, Node_plus, $3, @$); 			}
	| exp "-" exp        		{ $$ = node ($1, Node_minus, $3, @$); 			}
	| exp "*" exp        		{ $$ = node ($1, Node_multive, $3, @$); 		}
	| exp "/" exp        		{ $$ = node ($1, Node_quotient, $3, @$); 		}
	| exp "%" exp        		{ $$ = node ($1, Node_mod, $3, @$); 		}
	| "-" exp  %prec NEG 		{ $$ = node ($2, Node_unary_minus, (NODE *)NULL, @$); 	}
	| "(" exp ")"        		{ $$ = $2; $$->loc = @$;                     		   	}

;
/* End of grammar.  */

%%
void
yy::fuzzy_parser::error (const location_type& l,
                          const std::string& m)
{
  driver->error (l, m);
}
