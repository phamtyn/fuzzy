/*
  fuzzy - The implementation of the FUZZY programming language

  File: fuzzy_driver.hh

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

#ifndef CALCXX_DRIVER_HH
# define CALCXX_DRIVER_HH

#ifndef ERROR_NAMESPACE_
#define ERROR_NAMESPACE_

#define ERROR_OBJECT_OK			0
#define ERROR_OBJECT_NOT_FOUND		1
#define ERROR_OBJECT_NOT_FOUND_AT_ROOT	2
#define ERROR_TOO_FEW_PARAMS		3
#define ERROR_TOO_MANY_PARAMS		4
#define ERROR_VAR_USE_AS_FUNCTION	5
#define ERROR_VAR_USE_AS_ARRAY		6
#define ERROR_ARRAY_USE_AS_FUNCTION	7
#define ERROR_ARRAY_USE_AS_STRUCT	8
#define ERROR_FUNCTION_USE_AS_VAR	9
#define ERROR_FUNCTION_USE_AS_ARRAY	10
#define ERROR_INVALID_INDEX		11
#define ERROR_INDEX_EXCEED_SIZE		12
#define ERROR_BASICTYPE_CALL_MEMBER	13

#endif	// end ERROR_NAMESPACE_

# include <string>
# include "fuzzy_parser.hh"
// Tell Flex the lexer's prototype ...
# define YY_DECL \
  int yylex (yy::fuzzy_parser::semantic_type* YYLVAL, \
yy::fuzzy_parser::location_type *YYLLOC, fuzzy_driver *driver)
  
// ... and declare it for the parser's sake.
YY_DECL;
// Conducting the whole scanning and parsing of Calc++.

#include <setjmp.h>

#ifndef YY_TYPEDEF_YY_SIZE_T
#define YY_TYPEDEF_YY_SIZE_T
typedef size_t yy_size_t;
#endif

#ifndef YY_STRUCT_YY_BUFFER_STATE
#define YY_STRUCT_YY_BUFFER_STATE
struct yy_buffer_state
{

	FILE *yy_input_file;


	char *yy_ch_buf;		/* input buffer */
	char *yy_buf_pos;		/* current position in input buffer */

	/* Size of input buffer in bytes, not including room for EOB
	 * characters.
	 */
	yy_size_t yy_buf_size;

	/* Number of characters read into yy_ch_buf, not including EOB
	 * characters.
	 */
	yy_size_t yy_n_chars;

	/* Whether we "own" the buffer - i.e., we know we created it,
	 * and can realloc() it to grow it, and should free() it to
	 * delete it.
	 */
	int yy_is_our_buffer;

	/* Whether this is an "interactive" input source; if so, and
	 * if we're using stdio for input, then we want to use getc()
	 * instead of fread(), to make sure we stop fetching input after
	 * each newline.
	 */
	int yy_is_interactive;

	/* Whether we're considered to be at the beginning of a line.
	 * If so, '^' rules will be active on the next match, otherwise
	 * not.
	 */
	int yy_at_bol;

	int yy_bs_lineno; /**< The line count. */
	int yy_bs_column; /**< The column count. */
    
	/* Whether to try to fill the input buffer when we reach the
	 * end of it.
	 */
	int yy_fill_buffer;

	int yy_buffer_status;

  #define YY_BUFFER_NEW 0
  #define YY_BUFFER_NORMAL 1
	  /* When an EOF's been seen but there's still some text to process
	  * then we mark the buffer as YY_EOF_PENDING, to indicate that we
	  * shouldn't try reading from the input source any more.  We might
	  * still have a bunch of tokens to match, though, because of
	  * possible backing-up.
	  *
	  * When we actually see the EOF, we change the status to "new"
	  * (via yyrestart()), so that the user can continue scanning by
	  * just pointing yyin at a new input file.
	  */
  #define YY_BUFFER_EOF_PENDING 2

};
#endif

#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif

struct include_data {
	yy::location loc;
	YY_BUFFER_STATE buffer;
};
			
void yy_switch_to_buffer_ (YY_BUFFER_STATE new_buffer  );
void yy_delete_buffer_();
YY_BUFFER_STATE yy_create_buffer_();

#ifndef __JMP__
#define __JMP__
//#ifdef SYSV
#define _setjmp setjmp
#define _longjmp longjmp
//#endif


/* longjmp return codes, must be nonzero */
/* Continue means either for loop/while continue, or next input record */
#define TAG_CONTINUE 	1
#define TAG_BREAK 	2
#define TAG_RETURN 	3

/* the loop_tag_valid variable allows continue/break-out-of-context
 * to be caught and diagnosed (jfw) */

#define PUSH_BINDING(stack, x) (memcpy ((char *)(stack), (const char *)(x), sizeof (jmp_buf)), loop_tag_valid++)
#define RESTORE_BINDING(stack, x) (memcpy ((char *)(x), (const char *)(stack), sizeof (jmp_buf)), loop_tag_valid--)

#endif //end __JMP__



class fuzzy_driver
{
  NODE *result;
  jmp_buf loop_tag;	/* always the current binding */
  int loop_tag_valid;/* nonzero when loop_tag valid (jfw) */	
  
  void init_functions();
public:
		
  fuzzy_driver ();
  virtual ~fuzzy_driver ();

  FuzMap<string, NODE> functions1;
  FuzMap<string, NODE> functions2;
  FuzMap<string, FNCT_BUILDIN2> functions_buildin2;
  FuzMap<string, FNCT_BUILDIN1> functions_buildin1;
  FuzMap<string, FNCT_BUILDIN5> functions_buildin5;
  
  NODE *root;
  FuzList<include_data> list;
  FuzList<string> filenames;
  bool want_redirect;
  
  NODE *new_node (NODE *left, NODETYPE op, NODE *right, const yy::location &loc);
  
  template<typename T>
  NODE *new_node (const T &t, const yy::location &loc);
  
  NODE *append_r(NODE *list, NODE *newNode);
  
  int interpret (NODE *tree, STRUCT *parentStruct = STRUCT::root);
  NODE *tree_eval (NODE *tree, STRUCT *parentStruct);
  int eval_condition (NODE *tree, STRUCT *parentStruct);
  
  STRUCT *Check_type(STRUCT *parentStruct, NODE *tree, bool bCompletionRequire, string *ptypename = 0);
  bool Check_var(STRUCT *parentStruct, NODE *tree);
  bool Check_function(STRUCT *parentStruct, NODE *tree, const string &functionname);
  bool Check_params(STRUCT *parentStruct, NODE *tree);
  void GetFunctionName(Object *pvar, string &name);
  
  void call_proc(Object *pvar);
  NODE *call_function(Object *pvar, const yy::location &loc);
  int GetItemCount(const NODE *tree);
  bool MatchParams(Object *pFunction, const FuzArray<NODE *> &ParamNodeArray);
  
  Object *FindFunction(STRUCT *parentStruct, const string &name, 
		       const FuzArray<NODE *> &ParamNodeArray, int &code_out);
  
  int check_return(Object *pFunction, const yy::location &loc, NODE *return_value);
  
  Object *do_namespace(NODE *tree, STRUCT *parentStruct);
  void GetNamespaceText(NODE *tree, STRUCT *parentStruct, string &text);
  string GetArrayFullName(Object *pArray);
  
  void GetItemName(NODE *tree, string &name);
  
  void do_params(NODE *tree, STRUCT *parentStruct, FuzList<NODE *> &nodelist,
					FuzArray<NODE *> &ParamNodeArray);
  void assign_params(Object *pObject, FuzList<NODE *> &nodelist,
					FuzArray<NODE *> &ParamNodeArray);
  
  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  bool trace_scanning;
  // Run the parser on file F.
  // Return 0 on success.
  int parse (const std::string& f);
  // The name of the file being parsed.
  // Used later to pass the file name to the location tracker.
  std::string file;
  // Whether parser traces should be generated.
  bool trace_parsing;
  // Error handling.
  void error (const yy::location& l, const std::string& m);
  void error (const std::string& m);
  
  bool lookup_params(NODE *tree, STRUCT *parent_current, STRUCT *parent_origin, Object *&pObject, 
					const string &name, int &error_code);
  string GetArrayName_bracket(Object *pArray);
  string GetArrayFullTypename(Object *pArray);
  
  Object *do_buildin_functions(const NODE *tree, const FuzArray<NODE *> &ParamNodeArray,
			       int param_count, const Object *pUserFunction, const string &name);
  bool CheckFuzzyObject(Object *pObject, const yy::location &loc);
  bool CheckFuzzyObject_discrete(Object *pObject, const yy::location &loc, const string &statement);
  
  FUZZY *eval_fuzzy_rule(NODE *tree, FUZZY *dest, STRUCT *parentStruct);
  
  void set_reading(const string &arg);
  
};

inline bool fuzzy_driver::CheckFuzzyObject_discrete(Object *pObject, 
						     const yy::location &loc, const string &statement)
{
	if(!(pObject->GetType() == Type_struct && pObject->IsFuzzy() == 2 ||
		pObject->GetType() == Type_fuzzy && pObject->GetParent()->IsFuzzy() == 2
		))
	{
		string msg = "this " + statement + " can only be used for discrete fuzzy sets";
		error(loc, msg);
		return false;
	}
	return true;
}

inline bool fuzzy_driver::CheckFuzzyObject(Object *pObject, const yy::location &loc)
{
	if(pObject->GetType() != Type_fuzzy)
	{
		string msg = "unexpected type `" + pObject->GetTypename() + "'";
		msg += ", expecting type `fuzzy'";
		error(loc, msg);
		return false;
	}
	STRUCT *parent = pObject->GetParent();
	if(parent == NULL || parent != NULL && !parent->IsFuzzy())
	{
		string msg = "fuzzy object must be inside a fuzzy term";
		error(loc, msg);
		return false;
	}
	return true;
}

inline bool fuzzy_driver::lookup_params(NODE *tree, STRUCT *parent_current, STRUCT *parent_origin,
					 Object *&pObject, const string &name, int &error_code)
{
	for (int i = 0; i < parent_current->ParamArray.GetCount(); i++)
	{
		if (parent_current->ParamArray[i]->GetName() == name)
		{
			pObject = parent_current->ParamArray[i];
			
			if(tree->left->type == Node_array)
			{
				if(pObject->GetType() & Type_array)
				{
					NODE temp(Type_interger, tree->left->right->loc);
					temp.assign(*tree_eval(tree->left->right,
								parent_origin));
					INTERGER *pIndex = static_cast<INTERGER *>(temp.data);
					if(pIndex->GetInterger() < 0)
					{
						error_code = ERROR_INVALID_INDEX;
						return false;
					}
					Object *pTemp = pObject->GetArrayElement(*pIndex);
					if(pTemp == NULL)
					{
						error_code = ERROR_INDEX_EXCEED_SIZE;
						return false;
					}
					else
						pObject = pTemp;	
				}
				
				else
				{
					error_code = ERROR_VAR_USE_AS_ARRAY;
					return false;
				}
			}
			
			return true;
		}
	}	
	
	return false;
}

inline void fuzzy_driver::assign_params(Object *pObject, FuzList<NODE *> &nodelist, FuzArray<NODE *> &ParamNodeArray)
{
	PARAM_ARRAY *pParamArray = pObject->GetParamArray();
	
	POSITION pos = nodelist.GetHeadPosition();
	int i = 0;
	while (pos)
	{
		Object *param = (*pParamArray)[i];
		if(param->GetType() & Type_struct)
		{
			if(!param->IsCompleted())
			{
				if(param->GetType() & Type_array)
					param->init();
				else
					param->init(*param->GetClassObject());
				param->SetCompleted();
			}
		}
		NODE *p = nodelist.GetNext(pos);
		p->attach(param);
		p->assign (*ParamNodeArray[i], pObject);
		i++;
	}
	return;
}

inline void fuzzy_driver::do_params(NODE *tree, STRUCT *parentStruct, FuzList<NODE *> &nodelist,
					FuzArray<NODE *> &ParamNodeArray)
{
	for (NODE *t = tree->left->right; t != NULL; t = t->right)
			nodelist.AddTail(t);
		
	ParamNodeArray.SetCount(0, 10);
	
	POSITION pos = nodelist.GetHeadPosition();
	while (pos)
	{
		NODE *p = nodelist.GetNext(pos);
		ParamNodeArray.Add(tree_eval(p->left, parentStruct));
	}
	
	return;
}

inline Object *fuzzy_driver::do_buildin_functions(const NODE *tree, const FuzArray<NODE *> &ParamNodeArray,
			       int param_count, const Object *pUserFunction, const string &name)
{
	NPair *p;
	switch(param_count)
	{
		case 1:
			p = functions1.Lookup(name);
			break;
		case 2:
			p = functions2.Lookup(name);
			break;	
	}
	
	if(p)
	{
		string msg;
		int count = ParamNodeArray.GetCount();
		if(count != param_count && pUserFunction)
			return NULL;
		if(count > param_count)
			msg = "too many arguments to function `Number " + name;
		if(count < param_count)
			msg = "too few arguments to function `Number " + name;
		if(count != param_count)
		{
			msg += "(";
			
			switch(param_count)
			{
				case 1:
					msg += "Number";
					break;
				case 2:
					msg += "Number, Number";
					break;
			}
			
			msg += ")'";
			error(tree->loc, msg.data());
			exit(EXIT_FAILURE);
		}
		else
		{
			NODE &function_buildin_node = p->m_value;
			if(!function_buildin_node.data)
				function_buildin_node.attach(new Number);
			
			switch(param_count)
			{
				case 1:
				{
					NODE *node_param1;
					node_param1 = new NODE(Type_number, tree->loc);					
					node_param1->assign(*ParamNodeArray[0]);
					double &number = function_buildin_node.data->GetNumber();
					double &number_param1 = node_param1->data->GetNumber();
					number = function_buildin_node.value.fnct1(number_param1);
					delete node_param1;
					break;
				}
				case 2:
				{
					NODE *node_param1;
					NODE *node_param2;
					node_param1 = new NODE(Type_number, tree->loc);
					node_param2 = new NODE(Type_number, tree->loc);
					node_param1->assign(*ParamNodeArray[0]);
					node_param2->assign(*ParamNodeArray[1]);
					double &number = function_buildin_node.data->GetNumber();
					double &number_param1 = node_param1->data->GetNumber();
					double &number_param2 = node_param2->data->GetNumber();
					number = function_buildin_node.value.fnct2(
						number_param1, number_param2);
					delete node_param1;
					delete node_param2;
					break;
				}
			}
			return function_buildin_node.data;
		}
	}
	
	return NULL;
}

inline void fuzzy_driver::GetItemName(NODE *tree, string &name)
{
	switch(tree->left->type)
	{
		case Node_name:
			name = tree->left->data->GetString();
			break;
		default:
			name = tree->left->left->data->GetString();
			break;
	}
	return;
}

inline string fuzzy_driver::GetArrayName_bracket(Object *pArray)
{
	string name = "[";
	char text_index[32];
	sprintf(text_index, "%d", pArray->GetArrayCount());
	name += text_index;
	name += "]";
	return name;
}

inline string fuzzy_driver::GetArrayFullTypename(Object *pArray)
{
	string name = pArray->GetTypename() + GetArrayName_bracket(pArray);
	return name;
}

inline string fuzzy_driver::GetArrayFullName(Object *pArray)
{
	string name = pArray->GetName() + GetArrayName_bracket(pArray);
	return name;
}

template<typename T>
inline NODE *fuzzy_driver::new_node (const T &t, const yy::location &loc)
{
  return new NODE(t, loc);
}

inline string no_match_operator_msg(const NODE &t1, const NODE &t2, const string &op)
{
	string text = "no match for `operator" + op +"' (operand types are `";
	text += t1.data->GetTypename();
	if(t1.data->GetType() & Type_array)
		text += NODE::driver->GetArrayName_bracket(t1.data);
	text += "' and `";
	text += t2.data->GetTypename();
	if(t2.data->GetType() & Type_array)
		text += NODE::driver->GetArrayName_bracket(t2.data);
	text += "')";
	return text;
}

inline string no_match_operator_msg(const NODE &t1, const string &op)
{
	string text = "no match for `operator" + op +"' (operand type is `";
	text += t1.data->GetTypename();
	if(t1.data->GetType() & Type_array)
		text += NODE::driver->GetArrayName_bracket(t1.data);
	text += "')";
	return text;
}

inline string cannot_convert_msg(const NODE &t1, const string &type)
{
	string text = "cannot convert `";
	text += t1.data->GetTypename();
	if(t1.data->GetType() & Type_array)
		text += NODE::driver->GetArrayName_bracket(t1.data);
	text += "' to `" + type +"'";
	return text;
}



#endif // ! CALCXX_DRIVER_HH
