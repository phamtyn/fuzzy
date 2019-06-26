/*
  fuzzy - The implementation of the FUZZY programming language

  File: fuzzy_driver.cc

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
#include "fuzzy_parser.hh"
 
 
STRUCT *STRUCT::root = NULL;
UINT Object::CurrentId = BASETYPE_ID_LIMIT;
fuzzy_driver *NODE::driver = NULL;

fuzzy_driver::fuzzy_driver ()
  : trace_scanning (false), trace_parsing (false), root(NULL)
{
	
	init_functions();
	loop_tag_valid = 0;
	NODE::driver = this;
	STRUCT::root = new STRUCT;
	want_redirect = false;
	result = NULL;
	
	STRUCT *FuzzyPair = new STRUCT("FuzzyPair", STRUCT::root);
	STRUCT::root->Add_type(FuzzyPair, "FuzzyPair");
	Object *m_grade = new Number;
	m_grade->SetName("m_grade");
	FuzzyPair->Add_var(m_grade, "m_grade");
	
	Object *m_value = new Number;
	m_value->SetName("m_value");
	FuzzyPair->Add_var(m_value, "m_value");
	
	FuzzyPair->SetCompleted();
    
}

void fuzzy_driver::set_reading(const string &arg) {

    if (! arg.length())
        return;
    
    FuzList <string> list;
    
    char *reading = new char[arg.length() + 1];
    char *p = reading;
    strcpy(reading, arg.data());
    
    while (reading != NULL) {
        char *word = strsep (&reading, " ");
        if (strlen(word) == 0)
            continue;
        list.AddTail(word);
    }
    
    delete p;
    
    int count = list.GetCount();
    Object *system_reading_count = new INTERGER(count);
    STRUCT::root->Add_var(system_reading_count, "system_reading_count");
    
    ARRAY *system_reading_array = new ARRAY(Type_string, count);
    
    int i = 0;
    POSITION pos = list.GetHeadPosition();
    while(pos)
    {
        const string &item = list.GetNext(pos);
        *system_reading_array->GetArrayElement(i) = String(item);
        i++;
    }
    
    STRUCT::root->Add_var(system_reading_array, "system_reading_array");
}

fuzzy_driver::~fuzzy_driver ()
{
	delete STRUCT::root;
	if(root)
		delete root;
}

int
fuzzy_driver::parse (const std::string &f)
{
    file = f;
    scan_begin ();
    yy::fuzzy_parser parser (this);
    parser.set_debug_level (trace_parsing);
    int res = parser.parse ();
    scan_end ();
    return res;
}

void
fuzzy_driver::error (const yy::location& l, const std::string& m)
{
  std::cerr << error_prefix << l << ": " << m << std::endl;
}

void
fuzzy_driver::error (const std::string& m)
{
  std::cerr << error_prefix << m << std::endl;
}

void
fuzzy_driver::init_functions()
{
  functions1["sin"] = NODE(sin, yy::location());
  functions1["cos"] = NODE(cos, yy::location());
  functions1["atan"] = NODE(atan, yy::location());
  functions1["ln"] = NODE(log, yy::location());
  functions1["exp"] = NODE(exp, yy::location());
  functions1["sqrt"] = NODE(sqrt, yy::location());
  functions1["tan"] = NODE(tan, yy::location());
  functions1["log10"] = NODE(log10, yy::location());
  functions1["floor"] = NODE(floor, yy::location());
  functions1["round"] = NODE(round, yy::location());
  functions1["abs"] = NODE(fabs, yy::location());
  
  functions2["pow"] = NODE(pow, yy::location());
  functions2["min"] = NODE(min, yy::location());
  functions2["max"] = NODE(max, yy::location());
  
  functions_buildin2["FuzzyToArray"] = FuzzyToArray;
  functions_buildin2["PutReading"] = PutReading;
  functions_buildin5["PutReading"] = PutReading;
  
  functions_buildin2["Defuzz"] = Defuzz;
  
  functions_buildin1["ZeroFuzz"] = ZeroFuzz;
  functions_buildin1["Classify"] = Classify;
}

NODE *fuzzy_driver::new_node (NODE *left, NODETYPE op, NODE *right, const yy::location &loc)
{
  register NODE *r = new NODE(op, loc);
  r->left = left;
  r->right = right;
  return r;
}

NODE *fuzzy_driver::append_r(NODE *list, NODE *newNode)
{
  register NODE *oldlist;

  oldlist = list;
  list->loc += newNode->loc;
  while(list->right != NULL)
  {
    list = list->right;
    list->loc += newNode->loc;
  }
  list->right = newNode;
  
  return oldlist;
}

bool fuzzy_driver::Check_var(STRUCT *parentStruct, NODE *tree)
{
	int iRet;
	if((iRet = parentStruct->CheckName_var_decl(tree->data->GetString())) != 1)
	{
		string text;
		if (iRet == 0)
		{
			text = "conflicting declaration `";
			text += tree->data->GetString();
			text += "'";
		}
		else if (iRet == 2)
		{
			text = "declaration of `";
			text += tree->data->GetString();
			text += "'";
			text += " shadows a function parameter";
		}
		error(tree->loc, text);
		return false;
	}
	return true;
}

bool fuzzy_driver::Check_function(STRUCT *parentStruct, NODE *tree, const string &functionname)
{
	int iRet;
	Object *pFunction;
	if((iRet = parentStruct->CheckName_var_decl(
		functionname, tree->left->right, pFunction)) != 1)
	{
		string text;
		string name;
		switch (iRet) {
		case 0:
			GetFunctionName(pFunction, name);
			break;
		case 2:
			name = pFunction->GetTypename() + " " + pFunction->GetName();
			break;
		}
		text = "conflicting declaration `";
		text += name;
		text += "'";
		error(tree->left->loc, text);
		return false;
	}
	return true;
}

bool fuzzy_driver::Check_params(STRUCT *parentStruct, NODE *tree)
{
	for (int i = 0; i<parentStruct->ParamArray.GetCount(); i++)
		if (parentStruct->ParamArray[i]->GetName() == tree->right->data->GetString())
		{
			string text = "conflicting declaration `";
			text += tree->right->data->GetString();
			text += "'";
			error(tree->loc, text);
			return false;
		}
	return true;
}

STRUCT *fuzzy_driver::Check_type(STRUCT *parentStruct, NODE *tree, bool bCompletionRequire,
					string *ptypename)
{
	NODE *t;
	if (tree->type == Node_type_var_rootpath && ptypename)
		*ptypename = "::";
	FuzList<string> list;
	for (t = tree; t != NULL; t = t->right)
	{
		list.AddTail(t->left->data->GetString());
		if (ptypename)
		{
			*ptypename += t->left->data->GetString();
			if (t->right != NULL)
				*ptypename += "::";
		}	
	}
	
	STRUCT *ClassObject = parentStruct->FindClass(list, tree->type); 
	if(!ClassObject)
	{
		string text="`";
		if (ptypename)
			text += *ptypename;
		else
		{
			if (tree->type == Node_type_var_rootpath)
				text += "::";
			POSITION pos = list.GetHeadPosition();
			while (pos)
			{
				const string &name = list.GetNext(pos);
				text += name;
				if (pos)
				text += "::";
			}
		}
		text += "' was not declared in this scope";
		error(tree->loc, text.data());
		return NULL;
	}
	if(bCompletionRequire && !ClassObject->IsCompleted())
	{
		string text="`";
		string typename_;
		if (ptypename)
			typename_ = *ptypename;
		else
		{
			if (tree->type == Node_type_var_rootpath)
				typename_ += "::";
			POSITION pos = list.GetHeadPosition();
			while (pos)
			{
				const string &name = list.GetNext(pos);
				typename_ += name;
				if (pos)
				typename_ += "::";
			}
		}
		text += typename_;
		text += "' is an incomplete type";
		/*
		text += "' is an incomplete type\n\t";
		text += typename_ + " " + tree->right->data->GetString() + ";";
		*/
		error(tree->loc, text.data());
		return NULL;
	}
	return ClassObject;
}
void fuzzy_driver::GetFunctionName(Object *pvar, string &name) {
	
	STRUCT *pStruct = static_cast<STRUCT *>(pvar);
	
	name += pStruct->GetTypename() + " " + pStruct->GetName() + "(";
	for (int i = 0; i < pStruct->ParamArray.GetCount(); i++)
	{
		name += pStruct->ParamArray[i]->GetTypename();
		if(pStruct->ParamArray[i]->GetType() & Type_array)
		{
			char text_index[32];
			sprintf(text_index, "%d", pStruct->ParamArray[i]->GetArrayCount());
			name += "[";
			name += text_index;
			name += "]";
		}
		if (i < pStruct->ParamArray.GetCount()-1)
		name += ", ";
	}
	name += ")";
	return;
	
}
void fuzzy_driver::call_proc(Object *pvar)
{
	volatile jmp_buf loop_tag_stack;
	/*
	VAR_MAP *pVarMap = pvar->GetVarMap();
	POSITION pos;
	*/
	PUSH_BINDING (loop_tag_stack, loop_tag);
	
	switch (_setjmp (loop_tag)) {
	case 0:			/* normal non-jump */
		(void)interpret(pvar->GetFunctionBody(), (STRUCT*)pvar);
		break;
	case TAG_CONTINUE:	/* continue statement */
	case TAG_BREAK:		/* break statement */
		break;
	case TAG_RETURN:		/* break statement */
		/*
		pos = pVarMap->GetHeadPosition();
		while(pos)
		{
			TPair *p = pVarMap->GetNext(pos);
			delete p->m_value;
		}
		pVarMap->RemoveAll();
		*/
		RESTORE_BINDING (loop_tag_stack, loop_tag);
		if(result->type == Node_return_null)
			delete result;
		return;	  
	}
	/*
	pos = pVarMap->GetHeadPosition();
	while(pos)
	{
		TPair *p = pVarMap->GetNext(pos);
		delete p->m_value;
	}
	pVarMap->RemoveAll();
	*/
	RESTORE_BINDING (loop_tag_stack, loop_tag);
	return;
}

NODE *fuzzy_driver::call_function(Object *pvar, const yy::location &loc)
{
	volatile jmp_buf loop_tag_stack;
	
	PUSH_BINDING (loop_tag_stack, loop_tag);
		
	switch (_setjmp (loop_tag)) {
	case 0:			/* normal non-jump */
		(void)interpret(pvar->GetFunctionBody(), (STRUCT*)pvar);
		break;
	case TAG_CONTINUE:	/* continue statement */
	case TAG_BREAK:		/* break statement */
		break;
	case TAG_RETURN:		/* break statement */
		
		RESTORE_BINDING (loop_tag_stack, loop_tag);
		if(check_return(pvar, loc, result))
			return pvar->GetFunctionValue();
		else
			exit(EXIT_FAILURE);
	}
	
	RESTORE_BINDING (loop_tag_stack, loop_tag);
	string text = "function without return-statement";
	string function_name;
	GetFunctionName(pvar, function_name);
	text += "\n\t" + function_name;
	error(loc, text);
	exit(EXIT_FAILURE);
}

int fuzzy_driver::check_return(Object *pFunction, const yy::location &loc, NODE *return_value)
{
	if(return_value->type == Node_return_null)
	{
		string text = "a function call invoking value";
		error(loc, text);
		
		text = "return-statement is void";
		string function_name;
		GetFunctionName(pFunction, function_name);
		text += "\n\t" + function_name;
		error(return_value->loc, text);
		
		delete return_value;
		return 0;
	}
	/*
	if(pFunction->GetClassId() == return_value->data->GetClassId())
		return 1;
	*/
	switch(pFunction->GetClassId())
	{
		case CLASS_ID_VOID:
		{
			string text = "returning type of function is void";
			string function_name;
			GetFunctionName(pFunction, function_name);
			text += "\n\t" + function_name;
			error(loc, text);
			text = "return-statement with a value";
			error(return_value->loc, text);
			return 0;
		}
		default:
		{
			if(pFunction->GetFunctionValue()->data->GetType() == Type_struct)
			{
				NODE *pFunctionValue = pFunction->GetFunctionValue();
				Object *FunctionData = pFunctionValue->data;
				if(!FunctionData->IsCompleted())
				{
					FunctionData->init(*FunctionData->GetClassObject());
					FunctionData->SetCompleted();
				}
			}
			pFunction->GetFunctionValue()->assign(*result, pFunction, true);
			return 2;
		}
	}
	
}

int fuzzy_driver::GetItemCount(const NODE *tree)
{
	int count = 0;
	for (const NODE *t = tree; t != NULL; t = t->right)
		count++;
	return count;	
}

bool fuzzy_driver::MatchParams(Object *pFunction, const FuzArray<NODE *> &ParamNodeArray)
{
	PARAM_ARRAY *pParamArray = pFunction->GetParamArray();
	if (pParamArray->GetCount() != ParamNodeArray.GetCount())
		return false;
	if (pParamArray->GetCount() == 0)
		return true;
	for (int i = 0; i < pParamArray->GetCount(); i++)
		if ((*pParamArray)[i]->GetClassId() != ParamNodeArray[i]->data->GetClassId())
			return false;
		else if ((*pParamArray)[i]->GetType() != ParamNodeArray[i]->data->GetType())
			return false;
	
	return true;	
}

Object *fuzzy_driver::FindFunction(STRUCT *parentStruct, const string &name,
					const FuzArray<NODE *> &ParamNodeArray, int &code_out)
{
	STRUCT *parent = parentStruct;
	while (parent)
	{
		POSITION pos = parent->VarMap.FindFirstWithKey(name);
		while (pos)
		{
			Object *pFunction = parent->VarMap.GetNextValueWithKey(pos, name);
			if (!(pFunction->GetType() & Type_function))
			{
				code_out = ERROR_VAR_USE_AS_FUNCTION;
				return NULL;
			}
			if (MatchParams(pFunction, ParamNodeArray))
				return pFunction;
		}
		parent = parent->GetParent();
	}
	parent = parentStruct;
	while (parent)
	{
		POSITION pos = parent->VarMap.FindFirstWithKey(name);
		while (pos)
		{
			Object *pFunction = parent->VarMap.GetNextValueWithKey(pos, name);
			if ((pFunction->GetParamArray()->GetCount() == ParamNodeArray.GetCount()))
				return pFunction;
		}
		parent = parent->GetParent();
	}
	parent = parentStruct;
	while (parent)
	{
		POSITION pos = parent->VarMap.FindFirstWithKey(name);
		while (pos)
		{
			Object *pFunction = parent->VarMap.GetNextValueWithKey(pos, name);
			if ((ParamNodeArray.GetCount() > pFunction->GetParamArray()->GetCount()))
				code_out = ERROR_TOO_MANY_PARAMS;
			else
				code_out = ERROR_TOO_FEW_PARAMS;
			return pFunction;
		}
		parent = parent->GetParent();
	}
	code_out = ERROR_OBJECT_NOT_FOUND_AT_ROOT;
	return NULL;
}

inline STRUCT *get_this(STRUCT *parent) {
    
    STRUCT *start = parent;
    while (start->GetType() != Type_function)
        start = start->GetParent();
    return start->GetParent();
    
    /*
    if (parent->GetClassObject())
        return parent;
    STRUCT *start = parent;
    while (! start->GetType() & Type_function)
        start = start->GetParent();
    return get_this(start->GetParent());
    */
}

Object *fuzzy_driver::do_namespace(NODE *tree, STRUCT *parentStruct)
{
	NODE *t;
	int error_code = ERROR_OBJECT_OK;
	POSITION pos;
	
	Object *pObject = NULL;
	STRUCT *parent = parentStruct; 
	string name;
	
	GetItemName(tree, name);
    
    if (name == "this") {
        check_this_keyword_in_class(tree, parent);
        return get_this(parent);
    }
	
	if(tree->left->type == Node_function)
	{
		// do params
		FuzList<NODE *> nodelist;
		FuzArray<NODE *> ParamNodeArray;
		
		do_params(tree, parentStruct, nodelist, ParamNodeArray);
		
		pObject = FindFunction(parentStruct, name, ParamNodeArray, error_code);
		if(error_code != ERROR_OBJECT_OK)
		{
			Object *pObject_buildin;
			pObject_buildin = do_buildin_functions(tree, ParamNodeArray, 1, pObject, name);
			if(pObject_buildin)
				return pObject_buildin;
			
			pObject_buildin = do_buildin_functions(tree, ParamNodeArray, 2, pObject, name);
			if(pObject_buildin)
				return pObject_buildin;
			
            if (name == "Defuzz") {
                FUNC_PAIR2 *p2 = functions_buildin2.Lookup(name);
                if(ParamNodeArray.GetCount() == 2)
					return p2->m_value(ParamNodeArray[0]->data,
						ParamNodeArray[1]->data, tree->loc);
                else if(ParamNodeArray.GetCount() == 1)
					return p2->m_value(ParamNodeArray[0]->data, NULL, tree->loc);
				else if(ParamNodeArray.GetCount() > 2 && !pObject)	
				{
					string msg = "too many arguments to this function";
					error(tree->loc, msg.data());
					exit(EXIT_FAILURE);
				}
				else if(ParamNodeArray.GetCount() == 0 && !pObject)
				{
					string msg = "too few arguments to this function";
					error(tree->loc, msg.data());
					exit(EXIT_FAILURE);
				}
            }
            
			FUNC_PAIR2 *p2 = functions_buildin2.Lookup(name);
            FUNC_PAIR5 *p5 = functions_buildin5.Lookup(name);
            if ( p2 && p5 ) {
                if(ParamNodeArray.GetCount() == 2)
					return p2->m_value(ParamNodeArray[0]->data,
						ParamNodeArray[1]->data, tree->loc);
                else if(ParamNodeArray.GetCount() == 5)
					return p5->m_value(ParamNodeArray[0]->data,
                        ParamNodeArray[1]->data,
                        ParamNodeArray[2]->data,
                        ParamNodeArray[3]->data,
						ParamNodeArray[4]->data, tree->loc);
				else if( !pObject )	
				{
					string msg = "must be 2 or 5 arguments for this named function";
					error(tree->loc, msg.data());
					exit(EXIT_FAILURE);
				}
            }
			else if(p2)
			{
				if(ParamNodeArray.GetCount() == 2)
					return p2->m_value(ParamNodeArray[0]->data,
						ParamNodeArray[1]->data, tree->loc);
				else if(ParamNodeArray.GetCount() > 2 && !pObject)	
				{
					string msg = "too many arguments to this function";
					error(tree->loc, msg.data());
					exit(EXIT_FAILURE);
				}
				else if(ParamNodeArray.GetCount() < 2 && !pObject)
				{
					string msg = "too few arguments to this function";
					error(tree->loc, msg.data());
					exit(EXIT_FAILURE);
				}
			}
			else if(p5)
			{
				if(ParamNodeArray.GetCount() == 5)
					return p5->m_value(ParamNodeArray[0]->data,
                        ParamNodeArray[1]->data,
                        ParamNodeArray[2]->data,
                        ParamNodeArray[3]->data,
						ParamNodeArray[4]->data, tree->loc);
				else if(ParamNodeArray.GetCount() > 5 && !pObject)	
				{
					string msg = "too many arguments to this function";
					error(tree->loc, msg.data());
					exit(EXIT_FAILURE);
				}
				else if(ParamNodeArray.GetCount() < 5 && !pObject)
				{
					string msg = "too few arguments to this function";
					error(tree->loc, msg.data());
					exit(EXIT_FAILURE);
				}
			}
			
			FUNC_PAIR1 *p1 = functions_buildin1.Lookup(name);
			if(p1)
			{
				if(ParamNodeArray.GetCount() == 1)
					return p1->m_value(ParamNodeArray[0]->data, tree->loc);
				else if(ParamNodeArray.GetCount() > 1 && !pObject)	
				{
					string msg = "too many arguments to this function";
					error(tree->loc, msg.data());
					exit(EXIT_FAILURE);
				}
				else if(ParamNodeArray.GetCount() < 1 && !pObject)
				{
					string msg = "too few arguments to this function";
					error(tree->loc, msg.data());
					exit(EXIT_FAILURE);
				}
			}
					
			goto ERROR;
		}
		
		assign_params(pObject, nodelist, ParamNodeArray);
		
		if(tree->right != NULL)
			pObject = call_function(pObject, tree->loc)->data;
	}
	else
	{
		while (parent)
		{
			if(lookup_params(tree, parent, parentStruct, pObject, name, error_code))
				goto INTERNAL_LOOKUP;
			if(error_code != ERROR_OBJECT_OK)
				goto ERROR;
		
			POSITION pos = parent->VarMap.FindFirstWithKey(name);
			if (pos)
			{
				pObject = parent->VarMap.GetValueAt(pos);
				switch(tree->left->type)
				{
					case Node_array:
					{
						if(pObject->GetType() & Type_array)
						{
							NODE temp(Type_interger, tree->left->right->loc);
							temp.assign(*tree_eval(tree->left->right,
										parentStruct));
							INTERGER *pIndex = static_cast<INTERGER *>(temp.data);
							if(pIndex->GetInterger() < 0)
							{
								error_code = ERROR_INVALID_INDEX;
								goto ERROR;
							}
							Object *pTemp = pObject->GetArrayElement(*pIndex);
							if(pTemp == NULL)
							{
								error_code = ERROR_INDEX_EXCEED_SIZE;
								goto ERROR;
							}
							else
								pObject = pTemp;
						}
						else if(pObject->GetType() & Type_function)
						{
							error_code = ERROR_FUNCTION_USE_AS_ARRAY;
							goto ERROR;
						}
						else
						{
							error_code = ERROR_VAR_USE_AS_ARRAY;
							goto ERROR;
						}
						
						break;
					}
					case Node_name:
					{
						if(pObject->GetType() & Type_function)
						{
							error_code = ERROR_FUNCTION_USE_AS_VAR;
							goto ERROR;
						}
						
						break;
					}
				}
				
				goto INTERNAL_LOOKUP;
			}
			
			parent = parent->GetParent();	
		}
		
		error_code = ERROR_OBJECT_NOT_FOUND_AT_ROOT;
		goto ERROR;
	}

INTERNAL_LOOKUP:

	for(t = tree->right; t != NULL; t = t->right)
	{
		if (pObject->GetType() != Type_struct)
		{
			if(pObject->GetType() & Type_array)
				error_code = ERROR_ARRAY_USE_AS_STRUCT;
			else
				error_code = ERROR_BASICTYPE_CALL_MEMBER;
			goto ERROR;
		}
		
		GetItemName(t, name);
		
		STRUCT *pStruct = static_cast<STRUCT *>(pObject);
		POSITION pos = pStruct->VarMap.FindFirstWithKey(name);
		if (pos)
		{
			pObject = pStruct->VarMap.GetValueAt(pos);
			
			switch(t->left->type)
			{
				case Node_name:
				{
					if(pObject->GetType() & Type_function)
					{
						error_code = ERROR_FUNCTION_USE_AS_VAR;
						goto ERROR;
					}
					break;
				}
				case Node_array:
				{
					if(pObject->GetType() & Type_array)
					{
						NODE temp(Type_interger, t->left->right->loc);
						temp.assign(*tree_eval(t->left->right,
									parentStruct));
						INTERGER *pIndex = static_cast<INTERGER *>(temp.data);
						if(pIndex->GetInterger() < 0)
						{
							error_code = ERROR_INVALID_INDEX;
							goto ERROR;
						}
						Object *pTemp = pObject->GetArrayElement(*pIndex);
						if(pTemp == NULL)
						{
							error_code = ERROR_INDEX_EXCEED_SIZE;
							goto ERROR;
						}
						else
							pObject = pTemp;
					}
					else if(pObject->GetType() & Type_function)
					{
						error_code = ERROR_FUNCTION_USE_AS_ARRAY;
						goto ERROR;
					}
					else
					{
						error_code = ERROR_VAR_USE_AS_ARRAY;
						goto ERROR;
					}
					break;
				}
				case Node_function:
				{
					if(pObject->GetType() & Type_array)
					{
						error_code = ERROR_ARRAY_USE_AS_FUNCTION;
						goto ERROR;	
					}
					else if(!(pObject->GetType() & Type_function))
					{
						error_code = ERROR_VAR_USE_AS_FUNCTION;
						goto ERROR;
					}
					
					// do params
					
					POSITION posOrigin = pos;
					
					FuzList<NODE *> nodelist;
					FuzArray<NODE *> ParamNodeArray;
					
					do_params(t, parentStruct, nodelist, ParamNodeArray);
					
					pos = posOrigin;
					while (pos)
					{
						pObject = pStruct->VarMap.GetNextValueWithKey(pos, name);
						
						if (MatchParams(pObject, ParamNodeArray))
						{
							goto SUCCESS;
						}
					}
					
					pos = posOrigin;
					while (pos)
					{
						pObject = pStruct->VarMap.GetNextValueWithKey(pos, name);
						if ((pObject->GetParamArray()->GetCount() == 
									ParamNodeArray.GetCount()))
						{
							goto SUCCESS;
						}
					}
					
					pos = posOrigin;
					while (pos)
					{
						pObject = pStruct->VarMap.GetNextValueWithKey(pos, name);
						if ((ParamNodeArray.GetCount() > pObject->
									GetParamArray()->GetCount()))
							error_code = ERROR_TOO_MANY_PARAMS;
						else
							error_code = ERROR_TOO_FEW_PARAMS;
						goto ERROR;	
					}
				SUCCESS:	
					assign_params(pObject, nodelist, ParamNodeArray);
					
					if(t->right != NULL)
						pObject = call_function(pObject, tree->loc)->data;
					break;
				}
			}
		}
		else
		{
			error_code = ERROR_OBJECT_NOT_FOUND;
			goto ERROR;
		}
		
	}
	
ERROR:
	string namespace_name;
	if (error_code != ERROR_OBJECT_OK)
	{
		GetNamespaceText(tree, parentStruct, namespace_name);
	}
	
	switch (error_code)
	{
	
	case ERROR_ARRAY_USE_AS_STRUCT:
	{
		string msg = "array type has no memeber but elements: `";
		msg += GetArrayFullName(pObject) + "'";
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}
	case ERROR_INVALID_INDEX:
	{
		string msg = "invalid array index for `";
		msg += GetArrayFullName(pObject) + "'";
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}	
	case ERROR_INDEX_EXCEED_SIZE:
	{
		string msg = "index exceeds array size for `";
		msg += GetArrayFullName(pObject) + "'";
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}
	case ERROR_OBJECT_NOT_FOUND_AT_ROOT:
	{
		string msg = "`" + name;
		msg += "' was not declared in this scope";
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}
	case ERROR_OBJECT_NOT_FOUND:
	{
		string msg = "type `" + pObject->GetTypename();
		msg += "' has no memeber named `" + name + "'";
		msg += "\n\t" + namespace_name;
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}
	case ERROR_TOO_FEW_PARAMS:
	{	
		string msg = "too few arguments to function `";
		GetFunctionName(pObject, msg);
		msg += "'";
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}
	case ERROR_TOO_MANY_PARAMS:
	{	
		string msg = "too many arguments to function `";
		GetFunctionName(pObject, msg);
		msg += "'";
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}
	case ERROR_VAR_USE_AS_FUNCTION:
	{
		string msg = "`" + name;
		msg += "' cannot be used as a function";
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}
	case ERROR_VAR_USE_AS_ARRAY:
	{
		string msg = "`" + name;
		msg += "' cannot be used as a array";
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}
	case ERROR_ARRAY_USE_AS_FUNCTION:
	{
		string msg = "`" + name;
		msg += "' cannot be used as a function";
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}
	case ERROR_FUNCTION_USE_AS_VAR:
	{
		string msg = "`" + name;
		msg += "' cannot be used as a variable";
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}
	case ERROR_FUNCTION_USE_AS_ARRAY:
	{
		string msg = "`" + name;
		msg += "' cannot be used as a array";
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}
	case ERROR_BASICTYPE_CALL_MEMBER:
	{
		string msg = "variable `" + name + "' ";
		msg += "is of basic type `" + pObject->GetTypename();
		msg += "', which has no memeber to request";
		error(tree->loc, msg.data());
		exit(EXIT_FAILURE);
		break;
	}
	
	}
	
	return pObject;
}

void fuzzy_driver::GetNamespaceText(NODE *tree, STRUCT *parentStruct, string &text)
{
	for (NODE *t = tree; t != NULL; t = t->right)
	{
		switch(t->left->type)
		{
			case Node_name:
				text += t->left->data->GetString();
				break;
			case Node_array:
			{
				text += t->left->left->data->GetString();
				char text_index[32];
				NODE temp(Type_interger, t->left->right->loc);
				temp.assign(*tree_eval(t->left->right, parentStruct));
				INTERGER *pIndex = static_cast<INTERGER *>(temp.data);
				
				sprintf(text_index, "%d", pIndex->GetInterger());
				text += "[";
				text += text_index;
				text += "]";
				break;
			}
			case Node_function:
			{
				text += t->left->left->data->GetString() + "(";
				for (NODE *u = t->left->right; u != NULL; u = u->right)
				{
					Object *param = tree_eval(u->left, parentStruct)->data;
					text += param->GetName();
					if(u->right != NULL)
						text += ", ";
				}
				text += ")";
				break;
			}
		}
		if(t->right != NULL)
			text += ".";
	}
}


