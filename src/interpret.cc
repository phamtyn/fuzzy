/*
  fuzzy - The implementation of the FUZZY programming language

  File: interpret.cc

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
#include <fstream>

int fuzzy_driver::interpret (NODE *tree, STRUCT *parentStruct)
{
	register NODE *t, *v, *r;		/* temporary */
	volatile jmp_buf loop_tag_stack;	/* shallow binding stack for loop_tag */
	
	if(tree == NULL)
		return 1;
	switch (tree->type) {
	
	case Node_statements:
		for (t = tree; t != NULL; t = t->right) {
			(void)interpret (t->left, parentStruct);
		}
		break;
	
	case Node_type_struct_declare:
	{
		if(!parentStruct->CheckName_type_decl(tree->left->data->GetString()))
		{
			string text = "redefinition of struct `";
			text += tree->left->data->GetString();
			text += "'";
			error(tree->left->loc, text);
			exit(EXIT_FAILURE);
		}
		STRUCT *thisType = new STRUCT(tree->left->data->GetString(), parentStruct);
		parentStruct->Add_type(thisType, tree->left->data->GetString());
		for (t = tree->right; t != NULL; t = t->right) {
			(void)interpret (t->left, thisType);
		}
		thisType->SetCompleted();
	}
	break;
	
	case Node_type_struct_declare_fuzzy:
	{
		string &name = tree->left->left->data->GetString();
        long size = tree->left->right->right->data->GetInterger();
        
        if(size < 2)
		{
			string text = "The size of a fuzzy term must be 2 or more";
			error(tree->left->left->loc, text);
			exit(EXIT_FAILURE);
		}
		
		NODE *eval_min = tree_eval(tree->left->right->left->left, parentStruct);
		NODE *eval_max = tree_eval(tree->left->right->left->right, parentStruct);
		NODE *node_min = new NODE(Type_number, tree->left->right->left->left->loc);
		NODE *node_max = new NODE(Type_number, tree->left->right->left->right->loc);
		node_min->assign(*eval_min);
		node_max->assign(*eval_max);
		
		double _min = node_min->data->GetNumber();
		double _max = node_max->data->GetNumber();
		delete node_min;
		delete node_max;
		
		if(!parentStruct->CheckName_type_decl(name))
		{
			string text = "redefinition of struct `";
			text += name;
			text += "'";
			error(tree->left->left->loc, text);
			exit(EXIT_FAILURE);
		}
		STRUCT *thisType = new STRUCT(name, parentStruct);
		parentStruct->Add_type(thisType, name);
		thisType->SetFuzzy(_min, _max, size);
        
        Object *fuzzy_size = new INTERGER(size);
        thisType->Add_var(fuzzy_size, "size");
		
        for (t = tree->right; t != NULL; t = t->right) {
			(void)interpret (t->left, thisType);
		}
		thisType->SetCompleted();
	}
	break;
	
	case Node_type_struct_declare_fuzzy_discrete:
	{
		string &name = tree->left->left->data->GetString();
		long size = tree->left->right->data->GetInterger();
		
        if(size < 2)
		{
			string text = "The size of a fuzzy term must be 2 or more";
			error(tree->left->left->loc, text);
			exit(EXIT_FAILURE);
		}
		if(!parentStruct->CheckName_type_decl(name))
		{
			string text = "redefinition of struct `";
			text += name;
			text += "'";
			error(tree->left->left->loc, text);
			exit(EXIT_FAILURE);
		}
		STRUCT *thisType = new STRUCT(name, parentStruct);
		parentStruct->Add_type(thisType, name);
		
		thisType->SetFuzzy(size);
        
        Object *fuzzy_size = new INTERGER(size);
        thisType->Add_var(fuzzy_size, "size");
		
		for (t = tree->right; t != NULL; t = t->right) {
			(void)interpret (t->left, thisType);
		}
		thisType->SetCompleted();
	}
	break;
	
	case Node_command_block:
	{
		STRUCT *&child = parentStruct->GetChild();
		if(child != NULL)
			delete child;
		child = new STRUCT(parentStruct);
			
		for (t = tree; t != NULL; t = t->right) {
			(void)interpret (t->left, child);
		}
	}
	break;
	
	case Node_var_decl_fuzzy_discrete:
	{
		if(parentStruct->IsFuzzy() != 2)
		{
			string msg = "discrete fuzzy set must be inside a discrete fuzzy term";
			error(tree->loc, msg);
			exit(EXIT_FAILURE);
		}
		
		if(!Check_var(parentStruct, tree->left))
			exit(EXIT_FAILURE);
		Object *thisType = new FUZZY(parentStruct);
		
		thisType->SetName(tree->left->data->GetString());
		parentStruct->Add_var(thisType, tree->left->data->GetString());
		
		int i = 0;
		for (t = tree->right; t != NULL; t = t->right)
			i++;
		if(i != parentStruct->GetFuzzySize())
		{
			string msg = "no match element count, expecting ";
			char text_index[32];
			sprintf(text_index, "%d", parentStruct->GetFuzzySize());
			msg += text_index;
			msg += " elements";
			error(tree->loc, msg);
			exit(EXIT_FAILURE);
		}
		
		i = 0;
		for (t = tree->right; t != NULL; t = t->right) {
			NODE *param = t->left;
			
			NODE *eval_belong = tree_eval(param->left, parentStruct);
			NODE *eval_value = tree_eval(param->right, parentStruct);
			NODE *node_belong = new NODE(Type_number, param->left->loc);
			NODE *node_value = new NODE(Type_number, param->right->loc);
			node_belong->assign(*eval_belong);
			node_value->assign(*eval_value);
			
			double belong = node_belong->data->GetNumber();
			double value = node_value->data->GetNumber();
			delete node_belong;
			delete node_value;
			
			thisType->GetBelong()[i].m_grade = belong;
			thisType->GetBelong()[i].m_value = value;
			i++;
		}
		
	}
	break;
	
	case Node_fuzzy_input:
	{
		t = tree_eval(tree->left, parentStruct);
		
		if(!CheckFuzzyObject_discrete(t->data, tree->loc, "put statement"))
			exit(EXIT_FAILURE);
		
		Object *fuzzy_set;
		
		if(t->data->GetType() == Type_fuzzy)
			fuzzy_set = t->data;
		else
			fuzzy_set = t->data->GetFuzzy();
		
		int i = 0;
		for (t = tree->right; t != NULL; t = t->right)
			i++;
		if(i != fuzzy_set->GetParent()->GetFuzzySize())
		{
			string msg = "no match element count, expecting ";
			char text_index[32];
			sprintf(text_index, "%d", fuzzy_set->GetParent()->GetFuzzySize());
			msg += text_index;
			msg += " elements";
			error(tree->loc, msg);
			exit(EXIT_FAILURE);
		}
		
		i = 0;
		for (t = tree->right; t != NULL; t = t->right) {
			NODE *param = t->left;
			
			NODE *eval_belong = tree_eval(param->left, parentStruct);
			NODE *eval_value = tree_eval(param->right, parentStruct);
			NODE *node_belong = new NODE(Type_number, param->left->loc);
			NODE *node_value = new NODE(Type_number, param->right->loc);
			node_belong->assign(*eval_belong);
			node_value->assign(*eval_value);
			
			double belong = node_belong->data->GetNumber();
			double value = node_value->data->GetNumber();
			delete node_belong;
			delete node_value;
			
			fuzzy_set->GetBelong()[i].m_grade = belong;
			fuzzy_set->GetBelong()[i].m_value = value;
			i++;
		}
		
	}
	break;
	
	case Node_var_decl:
	{
		for(t = tree->right; t != NULL; t = t->right)
		{
			switch(t->left->type)
			{
				case Node_name:
				{
					if(!Check_var(parentStruct, t->left))
						exit(EXIT_FAILURE);
					Object *thisType;
					switch(tree->left->type)
					{
						case Node_type_number:
							thisType = new Number;	
							break;
						case Node_type_interger:
							thisType = new INTERGER;	
							break;	
						case Node_type_string:
							thisType = new String;	
							break;
						case Node_type_bool:
							thisType = new TBOOL;	
							break;	
						case Node_type_fuzzy:
							thisType = new FUZZY(parentStruct);	
							break;		
						case Node_type_var:
						case Node_type_var_rootpath:  
						{	
							STRUCT *ClassObject = Check_type(parentStruct, tree->left, true);
							if(!ClassObject)
								exit(EXIT_FAILURE);
							
							thisType = new STRUCT(*ClassObject);
							thisType->SetParent(parentStruct);
							
							break;
						}
					}
					thisType->SetName(t->left->data->GetString());
					parentStruct->Add_var(thisType, t->left->data->GetString());
					break;
				}
				case Node_array:
				{
					if(!Check_var(parentStruct, t->left->left))
						exit(EXIT_FAILURE);
					ARRAY *thisType;
					NODE temp(0.0, t->left->right->loc);
					temp.assign(*tree_eval(t->left->right, parentStruct));
					Number *pIndex = static_cast<Number *>(temp.data);
					switch (tree->left->type)
					{
						case Node_type_number:
						case Node_type_interger:	
						case Node_type_string:
						case Node_type_bool:	
						case Node_type_fuzzy:		
						{
							thisType = new ARRAY(tree->left->type, *pIndex);
							break;
						}
						case Node_type_var:
						case Node_type_var_rootpath:  
						{	
							STRUCT *ClassObject = Check_type(parentStruct, tree->left, true);
							if(!ClassObject)
								exit(EXIT_FAILURE);
							
							thisType = new ARRAY(parentStruct, ClassObject, *pIndex);
							break;
						}
					
					}
					thisType->SetName(t->left->left->data->GetString());
					parentStruct->Add_var(thisType, t->left->left->data->GetString());
					break;
				}
				case Node_assign:
				{
					if(!Check_var(parentStruct, t->left->left))
						exit(EXIT_FAILURE);
					Object *thisType;
					switch(tree->left->type)
					{
						case Node_type_number:
							thisType = new Number;	
							break;
						case Node_type_interger:
							thisType = new INTERGER;	
							break;		
						case Node_type_string:
							thisType = new String;	
							break;
						case Node_type_bool:
							thisType = new TBOOL;	
							break;	
						case Node_type_fuzzy:
							thisType = new FUZZY(parentStruct);
							break;		
						case Node_type_var:
						case Node_type_var_rootpath:  
						{	
							STRUCT *ClassObject = Check_type(parentStruct, tree->left, true);
							if(!ClassObject)
								exit(EXIT_FAILURE);
							
							thisType = new STRUCT(*ClassObject);
							thisType->SetParent(parentStruct);
							
							break;
						}
					}
					thisType->SetName(t->left->left->data->GetString());
					parentStruct->Add_var(thisType, t->left->left->data->GetString());
					
					NODE *eval = tree_eval(t->left->right, parentStruct);
					if(thisType == eval->data)
						break;
					t->left->attach(thisType);
					t->left->assign(*eval);
					
					break;
				}
			}
		}
	}
	break;

	case Node_assign:
	{
		Object *pvar = do_namespace(tree->left, parentStruct);
		NODE *eval = tree_eval(tree->right, parentStruct);
		if(pvar == eval->data)
			break;
		tree->left->attach(pvar);
		tree->left->assign(*eval);
	}
	break; 
	
	case Node_assign_plus:
	{
		Object *pvar = do_namespace(tree->left, parentStruct);
		tree->left->attach(pvar);
		t = new NODE(*tree->left);
		NODE *eval = tree_eval(tree->right, parentStruct);
		r = *t + *eval;
		tree->left->attach(pvar);
		tree->left->assign(*r);
		delete r;
		delete t;
	}
	break;
	
	case Node_assign_minus:
	{
		Object *pvar = do_namespace(tree->left, parentStruct);
		tree->left->attach(pvar);
		t = new NODE(*tree->left);
		NODE *eval = tree_eval(tree->right, parentStruct);
		r = *t - *eval;
		tree->left->attach(pvar);
		tree->left->assign(*r);
		delete r;
		delete t;
	}
	break;
	
	case Node_assign_multive:
	{
		Object *pvar = do_namespace(tree->left, parentStruct);
		tree->left->attach(pvar);
		t = new NODE(*tree->left);
		NODE *eval = tree_eval(tree->right, parentStruct);
		r = *t * *eval;
		tree->left->attach(pvar);
		tree->left->assign(*r);
		delete r;
		delete t;
	}
	break;
	
	case Node_assign_quotient:
	{
		Object *pvar = do_namespace(tree->left, parentStruct);
		tree->left->attach(pvar);
		t = new NODE(*tree->left);
		NODE *eval = tree_eval(tree->right, parentStruct);
		r = *t / *eval;
		tree->left->attach(pvar);
		tree->left->assign(*r);
		delete r;
		delete t;
	}
	break;
	
	case Node_assign_mod:
	{
		Object *pvar = do_namespace(tree->left, parentStruct);
		tree->left->attach(pvar);
		t = new NODE(*tree->left);
		NODE *eval = tree_eval(tree->right, parentStruct);
		r = *t % *eval;
		tree->left->attach(pvar);
		tree->left->assign(*r);
		delete r;
		delete t;
	}
	break;
	
	case Node_namespace:  
	{
		Object *pObject = do_namespace(tree, parentStruct);
		if(pObject->GetType() & Type_function)
			call_proc(pObject);
	}
	
	break;
	
	case Node_function_define:  
	{
	 
	string typename_out;
	UINT classid;
	NODE *pFunctionValue = NULL;
	switch (tree->left->left->left->type) {
	case Node_type_void:
		typename_out = "Void";
		classid = CLASS_ID_VOID;
		break;
	case Node_type_number:
		typename_out = "Number";
		classid = CLASS_ID_NUMBER;
		pFunctionValue = new NODE(Type_number, tree->loc);
		break;
	case Node_type_interger:
		typename_out = "int";
		classid = CLASS_ID_INTERGER;
		pFunctionValue = new NODE(Type_interger, tree->loc);
		break;	
	case Node_type_string:
		typename_out = "String";
		classid = CLASS_ID_STRING;
		pFunctionValue = new NODE(Type_string, tree->loc);
		break;
	case Node_type_bool:
		typename_out = "bool";
		classid = CLASS_ID_BOOL;
		pFunctionValue = new NODE(Type_bool, tree->loc);
		break;	
	case Node_type_fuzzy:
		typename_out = "fuzzy";
		classid = CLASS_ID_FUZZY;
		pFunctionValue = new NODE(Type_fuzzy, tree->loc);
		break;		
	default:
	{
		STRUCT *ClassObject = Check_type(parentStruct, tree->left->left->left, false, &typename_out);
		if (!ClassObject)
			exit(EXIT_FAILURE);
		classid = ClassObject->GetClassId();
		Object *FunctionData = new STRUCT(parentStruct);
		FunctionData->SetClassObject(ClassObject);
		pFunctionValue = new NODE(tree->loc);
		pFunctionValue->attach(FunctionData);
		break;	
	}
	}
	
	DATATYPE datatype = Type_function | Type_classobject;
	string functionname = tree->left->left->right->data->GetString();
	switch (tree->left->type) {
		
		case Node_assign:
			datatype |= Type_operator_assign;
			functionname += "=";
			break;
		case Node_unary_minus:
			datatype |= Type_operator_neg;
			functionname += "-";
			break;
	}
		
	if(!Check_function(parentStruct, tree, functionname))
		exit(EXIT_FAILURE);		
	
	STRUCT *thisType = new STRUCT(parentStruct, datatype);
	
	thisType->SetTypename(typename_out);
	
	thisType->SetName(functionname);
	
	thisType->SetClassId(classid);
	
	parentStruct->Add_var(thisType, functionname);
	
	thisType->ParamArray.SetCount(0, 10);
	
	thisType->SetFunctionBody(tree->right);
	
	thisType->SetFunctionValue(pFunctionValue);
	
	t = tree->left->right;
	while (t)
	{
		if (!Check_params(thisType, t->left))
			exit(EXIT_FAILURE);
		
		Object *param;
		if(t->left->right->left == NULL)
		{
			switch (t->left->type)
			{
				case Node_type_number:
					param = new Number;
					break;
				case Node_type_interger:
					param = new INTERGER;
					break;	
				case Node_type_string:
					param = new String;
					break;
				case Node_type_bool:
					param = new TBOOL;
					break;	
				case Node_type_fuzzy:
					param = new FUZZY;
					break;		
				default:
				{	
					STRUCT *ClassObject = Check_type(thisType, t->left->left, false);
					if(!ClassObject)
						exit(EXIT_FAILURE);
					param = new STRUCT(thisType);
					param->SetClassObject(ClassObject);
					
					break;
				}			
			}
			param->SetName(t->left->right->data->GetString());
		}
		else
		{
			NODE temp(0.0, t->left->right->right->loc);
			temp.assign(*tree_eval(t->left->right->right, parentStruct));
			Number *pIndex = static_cast<Number *>(temp.data);
			switch (t->left->type)
			{
				case Node_type_number:
				case Node_type_interger:	
				case Node_type_string:
				case Node_type_bool:
				case Node_type_fuzzy:	
				{
					param = new ARRAY(t->left->type, *pIndex);
					break;
				}
				case Node_type_var:
				case Node_type_var_rootpath:  
				{	
					STRUCT *ClassObject = Check_type(thisType, t->left->left, false);
					if(!ClassObject)
						exit(EXIT_FAILURE);
					
					param = new ARRAY(parentStruct, ClassObject, *pIndex, false);
					break;
				}
			
			}
			param->SetName(t->left->right->left->data->GetString());
		}
		
		thisType->ParamArray.Add(param);
		
		t = t->right;
	}
	}
	break; 

	case Node_K_if:
		if (eval_condition(tree->left, parentStruct)) {
			(void)interpret (tree->right->left, parentStruct);
		} else {
			(void)interpret (tree->right->right, parentStruct);
		}
		break;
		
	case Node_K_while:
	{
		PUSH_BINDING (loop_tag_stack, loop_tag);

		while (eval_condition (tree->left, parentStruct)) 
		{
			STRUCT *&child = parentStruct->GetChild();
			if(child != NULL)
				delete child;
			child = new STRUCT(parentStruct);
			
			switch (_setjmp (loop_tag)) 
			{
				case 0:
				{	
					(void)interpret (tree->right, child);
					break;
				}
				case TAG_CONTINUE:	/* continue statement */
					break;
				case TAG_BREAK:		/* break statement */
				{
					RESTORE_BINDING (loop_tag_stack, loop_tag);
					return 1;
				}
				case TAG_RETURN:		/* break statement */
		
				RESTORE_BINDING (loop_tag_stack, loop_tag);
				if(loop_tag_valid > 0)
					_longjmp (loop_tag, TAG_RETURN);
				if(result->type == Node_return_null)
					delete result;
				return 1;
			}
		}
		RESTORE_BINDING (loop_tag_stack, loop_tag);
		break;  
	}
	
	case Node_K_for:
	{
		PUSH_BINDING (loop_tag_stack, loop_tag);
		
		NODE *head = tree->left;
		NODE *body = tree->right;
		NODE *init = head->left;
		NODE *expr = head->right->left;
		NODE *incr = head->right->right->left;
		
		STRUCT *&for_scope = parentStruct->GetChild();
		if(for_scope != NULL)
			delete for_scope;
		for_scope = new STRUCT(parentStruct);
		
		interpret(init, for_scope);

		while (eval_condition (expr, for_scope)) 
		{
			STRUCT *&child = for_scope->GetChild();
			if(child != NULL)
				delete child;
			child = new STRUCT(for_scope);
			
			switch (_setjmp (loop_tag)) 
			{
				case 0:
				{	
					(void)interpret (body, child);
					(void)interpret (incr, for_scope);
					break;
				}
				case TAG_CONTINUE:	/* continue statement */
					(void)interpret (incr, for_scope);
					break;
				case TAG_BREAK:		/* break statement */
				{
					RESTORE_BINDING (loop_tag_stack, loop_tag);
					return 1;
				}
				case TAG_RETURN:		/* break statement */
		
				RESTORE_BINDING (loop_tag_stack, loop_tag);
				if(loop_tag_valid > 0)
					_longjmp (loop_tag, TAG_RETURN);
				if(result->type == Node_return_null)
					delete result;
				return 1;
			}
		}
		RESTORE_BINDING (loop_tag_stack, loop_tag);
		break;  
	}
	
	case Node_switch:
	{
		PUSH_BINDING (loop_tag_stack, loop_tag);
		
		NODE *case_statements = tree->left;
		if(case_statements == NULL)
			break;
		NODE *expr = tree_eval(tree->right, parentStruct);
		
		STRUCT *&switch_scope = parentStruct->GetChild();
		if(switch_scope != NULL)
			delete switch_scope;
		switch_scope = new STRUCT(parentStruct);
		
		switch (_setjmp (loop_tag)) 
		{
			case 0:
			{
				bool bFound = false;
				switch(expr->data->GetType())
				{
					case Type_number:
					case Type_interger:	
					{
						FuzList<NODE> list;
						for(t = case_statements; t != NULL; t = t->right)
						{
							NODE *case_stmt = t->left;
							NODE *case_value = tree_eval(
								case_stmt->left, switch_scope);
							if(case_value == NULL)
								continue;
							switch(case_value->data->GetType())
							{
								case Type_number:
								case Type_interger:	
									break;
								default:
								{
									string msg = "case label does not match type of switch(`";
									msg += expr->data->GetTypename() + "' and `";
									msg += case_value->data->GetTypename() + "')";
									error(case_value->loc, msg);
									exit(EXIT_FAILURE);
								
								}
							}
							
							if(list.Find(*case_value))
							{
								error(case_value->loc, "duplicate case value");
								exit(EXIT_FAILURE);
							}
							list.AddTail(*case_value);
						}
						break;
					}
					case Type_string:
					{
						FuzList<NODE> list;
						for(t = case_statements; t != NULL; t = t->right)
						{
							NODE *case_stmt = t->left;
							NODE *case_value = tree_eval(
								case_stmt->left, switch_scope);
							if(case_value == NULL)
								continue;
							if(case_value->data->GetType() != 
								expr->data->GetType())
							{
								string msg = "case label does not match type of switch(`";
								msg += expr->data->GetTypename() + "' and `";
								msg += case_value->data->GetTypename() + "')";
								error(case_value->loc, msg);
								exit(EXIT_FAILURE);
								
							}
							if(list.Find(*case_value))
							{
								error(case_value->loc, "duplicate case value");
								exit(EXIT_FAILURE);
							}
							list.AddTail(*case_value);
						}
						break;
					}
					
					default:
					{
						error(tree->right->loc, "invalid type of switch");
						exit(EXIT_FAILURE);
					}
				}
				for(t = case_statements; t != NULL; t = t->right)
				{
					NODE *case_stmt = t->left;
					NODE *case_value = tree_eval(case_stmt->left, switch_scope);
					if(case_value != NULL && *case_value == *expr)
					{
						v = t;
						bFound = true;
						break;
					}
				}
				if(!bFound)
				{
					for(t = case_statements; t != NULL; t = t->right)
					{
						NODE *case_stmt = t->left;
						NODE *case_value = tree_eval(case_stmt->left, switch_scope);
						if(case_value == NULL)
						{
							v = t;
							bFound = true;
							break;
						}
					}
				}
				if(!bFound)
					break;
				for(t = v; t != NULL; t = t->right)
				{
					NODE *statements = t->left->right;
					for(NODE *t = statements; t != NULL; t = t->right)
						interpret(t->left, switch_scope);
				}
				break;
			}
			case TAG_CONTINUE:	/* continue statement */
				break;
			case TAG_BREAK:		/* break statement */
			{
				RESTORE_BINDING (loop_tag_stack, loop_tag);
				return 1;
			}
			case TAG_RETURN:		/* break statement */
		
				RESTORE_BINDING (loop_tag_stack, loop_tag);
				if(loop_tag_valid > 0)
					_longjmp (loop_tag, TAG_RETURN);
				if(result->type == Node_return_null)
					delete result;
				return 1;
		}
		
		RESTORE_BINDING (loop_tag_stack, loop_tag);
		break;  
	}
	
	case Node_return:
	if (loop_tag_valid == 0)
	{
		error(tree->loc, "unexpected return");
		exit(EXIT_FAILURE);
	}/* jfw */
	if (tree->left != NULL)
		result = tree_eval(tree->left, parentStruct);
	else
		result = new_node (NULL, Node_return_null, NULL, tree->loc);
	_longjmp (loop_tag, TAG_RETURN);
	
	break;  
	
	case Node_K_break:
		if (loop_tag_valid == 0)
		{
			error(tree->loc, "unexpected break");
			exit(EXIT_FAILURE);
		}
		_longjmp (loop_tag, TAG_BREAK);
		break;  
	
	case Node_K_continue:
		if (loop_tag_valid == 0)
		{
			error(tree->loc, "unexpected continue");
			exit(EXIT_FAILURE);
		}
		_longjmp (loop_tag, TAG_CONTINUE);
		break;
	
	case Node_K_exit:
	{
        long exit_code;
        NODE *eval = tree_eval(tree->left, parentStruct);
        switch (eval->data->GetType()) {
            case Type_interger:
                exit_code = eval->data->GetInterger();
                break;
            case Type_number:
                exit_code = (long)eval->data->GetNumber();
                break;
            default:
                error(tree->loc, "Exit code must be a number");
                exit(EXIT_FAILURE);
        }
        exit(exit_code);
	}
	
	case Node_K_print:
	{
		std::ios::openmode mode;
		std::ofstream foutput;
		std::ostream *poutput;
		NODE *redirect = tree->right;
		if(redirect != NULL)
		{
			poutput = &foutput;
			switch(redirect->type)
			{
				case Node_redirect_output:
					mode = std::ios::out;
					break;
				case Node_redirect_append:
					mode = std::ios::app;
					break;	
			}
			NODE *filename = redirect->left;
			foutput.open(filename->data->GetString().data(), mode);
		}
		else 
			poutput = &cout;
		
		t = tree->left;
		while(t != NULL)
		{
			v = tree_eval(t->left, parentStruct);
			*poutput << *v;
			t = t->right;
		}
		*poutput << std::endl;
		break;  
	}
	
	case Node_print_set:
	{
		std::ios::openmode mode;
		std::ofstream foutput;
		std::ostream *poutput;
		NODE *redirect = tree->right;
		if(redirect != NULL)
		{
			poutput = &foutput;
			switch(redirect->type)
			{
				case Node_redirect_output:
					mode = std::ios::out;
					break;
				case Node_redirect_append:
					mode = std::ios::app;
					break;	
			}
			NODE *filename = redirect->left;
			foutput.open(filename->data->GetString().data(), mode);
		}
		else 
			poutput = &cout;
		
		t = tree->left;
		while(t != NULL)
		{
			v = tree_eval(t->left, parentStruct);
			if(!CheckFuzzyObject_all(v->data, t->left->loc, "prints statement"))
				exit(EXIT_FAILURE);
			Object *fuzzy_set;
		
			if(v->data->GetType() == Type_fuzzy)
				fuzzy_set = v->data;
			else
				fuzzy_set = v->data->GetFuzzy();
			
			for(int i = 0; i < fuzzy_set->GetSize(); i++)
			{
				double belong = fuzzy_set->GetBelong()[i].m_grade;
				double value = fuzzy_set->GetBelong()[i].m_value;
				*poutput << belong << "/" << value;
				if(i < fuzzy_set->GetSize() -1)
					*poutput << ", ";
			}
			*poutput << endl;
			t = t->right;
		}
		
		break;  
	}
	
	case Node_system:
	{
		NODE *command_origin = tree_eval(tree->left, parentStruct);
		NODE *command_convert = new NODE(Type_string, tree->left->loc);
		command_convert->assign(*command_origin);
		system(command_convert->data->GetString().data());
		delete command_convert;
		break;
	}
	
	case Node_fuzzy_rule:
	{
		NODE *eval = tree_eval(tree->right, parentStruct);
		Object *pObject = eval->data;
		if(!CheckFuzzyObject(pObject, tree->right->loc))
			exit(EXIT_FAILURE);
		FUZZY *dest = static_cast<FUZZY *>(pObject);
		
		FUZZY *rule = eval_fuzzy_rule(tree->left, dest, parentStruct);
		
		STRUCT *parent_dest = dest->GetParent();
		for(int i=0; i < dest->GetSize(); i++)
			parent_dest->GetFuzzy()->GetBelong()[i].m_value = dest->GetBelong()[i].m_value;
			
		parent_dest->GetFuzzy()->Union(*rule);
		
		//parent_dest->MakeFuzzyClear();
		delete rule;
		
		break;
	}

	default:
        /* Appears to be an expression statement.  Throw away the value. */
        //(void)tree_eval (tree,  parentStruct);
        
        (void)interpret (tree->left, parentStruct);
        (void)interpret (tree->right, parentStruct);
        
        break;
	}
	return 1;
}

inline FUZZY *inference (FUZZY *from, const FUZZY *dest) {
    
    register FUZZY *r;
    r = new FUZZY(*dest);
    r->MakeMatrix(*from);
    FUZZY *from_input = from->GetParent()->GetFuzzy();
    
    r->MakeBelong(*from_input);
    
    return r;
}

FUZZY *fuzzy_driver::eval_rule_left(NODE *tree, FUZZY *dest, STRUCT *parentStruct) {
    
    register FUZZY *left, *right, *r, *left_dest, *right_dest;
    register NODE *t;
    
    switch (tree->type) {
        case Node_and:
            left = eval_rule_left(tree->left, dest, parentStruct);
			right = eval_rule_left(tree->right, dest, parentStruct);
            if (left->GetParent() != dest->GetParent() && left->GetParent() == right->GetParent()) {
                r = new FUZZY(*left);
                r->Intersect(*left, *right);
                delete left;
                delete right;
                return r;
            }
            if (left->GetParent() != dest->GetParent()) {
                left_dest = inference(left, dest);
                delete left;
                left = left_dest;
            }
            if (right->GetParent() != dest->GetParent()) {
                right_dest = inference(right, dest);
                delete right;
                right = right_dest;
            }
            r = new FUZZY(*dest);
            r->Intersect(*left, *right);
            delete left;
            delete right;
            return r;
            
        case Node_or:
            left = eval_rule_left(tree->left, dest, parentStruct);
			right = eval_rule_left(tree->right, dest, parentStruct);
            if (left->GetParent() != dest->GetParent() && left->GetParent() == right->GetParent()) {
                r = new FUZZY(*left);
                r->Union(*left, *right);
                delete left;
                delete right;
                return r;
            }
            if (left->GetParent() != dest->GetParent()) {
                left_dest = inference(left, dest);
                delete left;
                left = left_dest;
            }
            if (right->GetParent() != dest->GetParent()) {
                right_dest = inference(right, dest);
                delete right;
                right = right_dest;
            }
            r = new FUZZY(*dest);
            r->Union(*left, *right);
            delete left;
            delete right;
            return r;
            
        case Node_very:
            left = eval_rule_left(tree->left, dest, parentStruct);
            r = new FUZZY(left->Very());
            delete left;
            return r;
            
        case Node_extremely:
            left = eval_rule_left(tree->left, dest, parentStruct);
            r = new FUZZY(left->Extremely());
            delete left;
            return r;
            
        case Node_seemed:
            left = eval_rule_left(tree->left, dest, parentStruct);
            r = new FUZZY(left->Seemed());
            delete left;
            return r;
            
        case Node_bit:
            left = eval_rule_left(tree->left, dest, parentStruct);
            r = new FUZZY(left->Bit());
            delete left;
            return r;
            
        case Node_little:
            left = eval_rule_left(tree->left, dest, parentStruct);
            r = new FUZZY(left->Little());
            delete left;
            return r;
            
        case Node_really:
            left = eval_rule_left(tree->left, dest, parentStruct);
            r = new FUZZY(left->Really());
            delete left;
            return r;
            
        case Node_not:
            left = eval_rule_left(tree->left, dest, parentStruct);
            r = new FUZZY(left->Not());
            delete left;
            return r;
    }
    
    t = tree_eval (tree, parentStruct);
    Object *pObject = t->data;
    if(!CheckFuzzyObject(pObject, tree->loc))
        exit(EXIT_FAILURE);
    FUZZY *from = static_cast<FUZZY *>(pObject);
    return new FUZZY(*from);
}

FUZZY *fuzzy_driver::eval_fuzzy_rule(NODE *tree, FUZZY *dest, STRUCT *parentStruct)
{
	register FUZZY *left, *right, *r, *from, *left_dest, *right_dest;
	register NODE *t;
	
	switch (tree->type)
	{
		case Node_and:
		{
			left = eval_rule_left(tree->left, dest, parentStruct);
			right = eval_rule_left(tree->right, dest, parentStruct);
            
            if (left->GetParent() != dest->GetParent() && left->GetParent() == right->GetParent()) {
                from = new FUZZY(*left);
                from->Intersect(*left, *right);
                delete left;
                delete right;
            
                r = inference (from, dest);
                
                delete from;
            
                return r;
            }
            if (left->GetParent() != dest->GetParent()) {
                left_dest = inference(left, dest);
                delete left;
                left = left_dest;
            }
            if (right->GetParent() != dest->GetParent()) {
                right_dest = inference(right, dest);
                delete right;
                right = right_dest;
            }
            r = new FUZZY(*dest);
            r->Intersect(*left, *right);
            delete left;
            delete right;
            return r;
		}
		case Node_or:
		{
            left = eval_rule_left(tree->left, dest, parentStruct);
			right = eval_rule_left(tree->right, dest, parentStruct);
            
            if (left->GetParent() != dest->GetParent() && left->GetParent() == right->GetParent()) {
                from = new FUZZY(*left);
                from->Union(*left, *right);
                delete left;
                delete right;
            
                r = inference (from, dest);
                
                delete from;
            
                return r;
            }
            if (left->GetParent() != dest->GetParent()) {
                left_dest = inference(left, dest);
                delete left;
                left = left_dest;
            }
            if (right->GetParent() != dest->GetParent()) {
                right_dest = inference(right, dest);
                delete right;
                right = right_dest;
            }
            r = new FUZZY(*dest);
            r->Union(*left, *right);
            delete left;
            delete right;
            return r;
		}
		case Node_not:
		{
            left = eval_rule_left(tree->left, dest, parentStruct);
			from = new FUZZY(left->Not());
            delete left;
            if (from->GetParent() == dest->GetParent())
                return from;
            
			r = inference (from, dest);
			
            delete from;
            
			return r;
		}
		case Node_very:
		{
            left = eval_rule_left(tree->left, dest, parentStruct);
			from = new FUZZY(left->Very());
            delete left;
            if (from->GetParent() == dest->GetParent())
                return from;
            
			r = inference (from, dest);
			
            delete from;
            
			return r;
		}
		case Node_extremely:
		{
            left = eval_rule_left(tree->left, dest, parentStruct);
			from = new FUZZY(left->Extremely());
            delete left;
            if (from->GetParent() == dest->GetParent())
                return from;
            
			r = inference (from, dest);
			
            delete from;
            
			return r;
		}
		case Node_little:
		{
			left = eval_rule_left(tree->left, dest, parentStruct);
			from = new FUZZY(left->Little());
            delete left;
            if (from->GetParent() == dest->GetParent())
                return from;
            
			r = inference (from, dest);
			
            delete from;
            
			return r;
		}
		case Node_seemed:
		{
            left = eval_rule_left(tree->left, dest, parentStruct);
			from = new FUZZY(left->Seemed());
            delete left;
            if (from->GetParent() == dest->GetParent())
                return from;
            
			r = inference (from, dest);
			
            delete from;
            
			return r;
		}
		case Node_bit:
		{
            left = eval_rule_left(tree->left, dest, parentStruct);
			from = new FUZZY(left->Bit());
            delete left;
            if (from->GetParent() == dest->GetParent())
                return from;
            
			r = inference (from, dest);
			
            delete from;
            
			return r;
		}
		case Node_really:
		{
            left = eval_rule_left(tree->left, dest, parentStruct);
			from = new FUZZY(left->Really());
            delete left;
            if (from->GetParent() == dest->GetParent())
                return from;
            
			r = inference (from, dest);
			
            delete from;
            
			return r;
		}
		
		default:
		{
			t = tree_eval (tree, parentStruct);
			Object *pObject = t->data;
			if(!CheckFuzzyObject(pObject, tree->loc))
				exit(EXIT_FAILURE);
			from = static_cast<FUZZY *>(pObject);
			
			r = inference (from, dest);
			
			return r;
		}
	}
	
	return NULL;
}

/* evaluate a subtree, allocating strings on a temporary stack. */
/* This used to return a whole NODE, instead of a ptr to one, but that
   led to lots of obnoxious copying.  I got rid of it (JF) */
NODE *fuzzy_driver::tree_eval (NODE *tree, STRUCT *parentStruct)
{
	register NODE *r, *t1, *t2, *t;		/* return value and temporary subtrees */
	register NODE **lhs;
	volatile jmp_buf loop_tag_stack;	/* shallow binding stack for loop_tag */

	if(tree == NULL) {
		return 0;
	}
	switch (tree->type)
	{	/* trivial data */
		case Node_constant_bool:
		case Node_constant_string:
		case Node_constant_number:
		case Node_constant_interger:	
			return tree;
		
		case Node_namespace:  
		{
			Object *pObject = do_namespace(tree, parentStruct);
			if(pObject->GetType() & Type_function)
				return call_function(pObject, tree->loc);
			else
			{	
				if(pObject->GetNode() && 
					(
						pObject->GetNode()->type == Node_function_1 ||
						pObject->GetNode()->type == Node_function_2	
					)
				)
					return pObject->GetNode();
				tree->attach(pObject);
				return tree;
			}
			break;
		}
		
		case Node_unary_minus:
		{
			r = tree_eval(tree->left, parentStruct);
			tree->free_data();
			switch(r->data->GetType())
			{
				case Type_number:
				{	
					tree->attach(new Number);
					break;
				}
				case Type_interger:
				{	
					tree->attach(new INTERGER);
					break;
				}
				case Type_struct:
				{
					tree->attach(new STRUCT);
					tree->data->init(*r->data->GetClassObject());
					break;
				}
			}
			tree->assign(-*r);
			return tree;
		}
		case Node_assign:
		{
			Object *pvar = do_namespace(tree->left, parentStruct);
			NODE *eval = tree_eval(tree->right, parentStruct);
			tree->left->attach(pvar);
			return &tree->left->assign(*eval);
		}
		
		case Node_and:
		case Node_or:
		case Node_not:
		case Node_match:
		case Node_nomatch:
		case Node_equal:
		case Node_notequal:
		case Node_less:
		case Node_greater:
		case Node_le:
		case Node_ge:
			tree->free_data();
			tree->attach(new TBOOL((bool)eval_condition(tree, parentStruct)));
			return tree; 
	
	}
	/* Note that if TREE is invalid, gAWK will probably bomb in one of these
	tree_evals here.  */
	/* evaluate subtrees in order to do binary operation, then keep going */
	t1 = tree_eval (tree->left, parentStruct);
	
	Object *pObject = t1->data;
	
	t2 = tree_eval (tree->right, parentStruct);
	
	bool bSameObject = false;
	if(t2->data == pObject)
	{
		t1 = new NODE(*t2);
		bSameObject = true;
	}
	
	switch (tree->type) {

	case Node_multive:
		r = *t1 * *t2;
		break;

	case Node_quotient:
		r = *t1 / *t2;
		break;

	case Node_plus:
		r = *t1 + *t2;
		break;

	case Node_minus:
		r = *t1 - *t2;
		break;
	
	case Node_mod:
		r = *t1 % *t2;
		break;	
		
	}
	
	tree->free_data();
	tree->attach(r->data);
	delete r;
	if(bSameObject)
		delete t1;
	
	return tree;
}

/* Is TREE true or false?  Returns 0==false, non-zero==true */
int fuzzy_driver::eval_condition (NODE *tree, STRUCT *parentStruct)
{
	register NODE	*t1,*t2;

	if(tree==NULL)	/* Null trees are the easiest kinds */
		return 1;
	switch (tree->type) {

	case Node_and:
		return eval_condition (tree->left, parentStruct)
		&& eval_condition (tree->right, parentStruct);

	case Node_or:
		return eval_condition (tree->left, parentStruct)
		|| eval_condition (tree->right, parentStruct);
	
	case Node_not:
		return !eval_condition (tree->left, parentStruct);

	/* Node_line_range is kind of like Node_match, EXCEPT:
	* the left field (more properly, the condpair field) is a node of
	* a Node_cond_pair; whether we evaluate the left of that node or the
	* right depends on the triggered word.  More precisely:  if we are not
	* yet triggered, we tree_eval the left; if that returns true, we set
	* the triggered word.  If we are triggered (not ELSE IF, note), we
	* tree_eval the right, clear triggered if it succeeds, and perform our
	* action (regardless of success or failure).  We want to be able to
	* begin and end on a single input record, so this isn't an ELSE IF, as
	* noted above.
	* This feature was implemented by John Woods, jfw@eddie.mit.edu, during
	* a rainy weekend.
	*/
	
	}

	/* Could just be J.random expression.
	in which case, null and 0 are false,
	anything else is true */

	switch(tree->type) {
	case Node_match:
	case Node_nomatch:
	case Node_equal:
	case Node_notequal:
	case Node_less:
	case Node_greater:
	case Node_le:
	case Node_ge:
		break;

	default:
	
		t1 = tree_eval(tree, parentStruct);
		return t1->GetBoolen();
	}

	t1 = tree_eval (tree->left, parentStruct);

	t2 = tree_eval (tree->right, parentStruct);

	switch (tree->type) {
	
	case Node_equal:
		return *t1 == *t2;
	
	case Node_notequal:
		return *t1 != *t2;
		
	case Node_less:
		return *t1 < *t2;
		
	case Node_greater:
		return *t1 > *t2;
	
	case Node_le:
		return *t1 <= *t2;
		
	case Node_ge:
		return *t1 >= *t2;
		
	/*
	case Node_leq:
	return di <= 0;
	case Node_geq:
	return di >= 0;
	*/
	}
	
	return 0;
}



 
int STRUCT::CheckName_var_decl(const string &varname, const NODE *tree, Object *&pFunction_out)
{	
	POSITION pos = VarMap.FindFirstWithKey(varname);
	if (pos)
	{
		Object *pvar = VarMap.GetValueAt(pos);
		if (!(pvar->m_type & Type_function))
		{
			pFunction_out = pvar;
			return 2;
		}
		while(pos)
		{
			Object *pObject = VarMap.GetNextValueWithKey(pos, varname);
			STRUCT *pFunction = static_cast<STRUCT *>(pObject);
			if (pFunction->ParamArray.GetCount() != NODE::driver->GetItemCount(tree))
				continue;
			if (pFunction->ParamArray.GetCount() == 0)
			{
				pFunction_out = pFunction;
				return 0;
			}
			int i = 0, k = 0;
			for (const NODE *t = tree; t != NULL; t = t->right)
			{
				DATATYPE type;
				switch (t->left->type)
				{
				case Node_type_number:
				case Node_type_interger:
				case Node_type_string:
				case Node_type_bool:
				case Node_type_fuzzy:
					type = t->left->type;
					if(t->left->right->left != NULL)
						type |= Type_array;
					if (pFunction->ParamArray[k]->m_type == type)
						i++;
					break;		
				default:
				{	
					Object *ClassObject = NODE::driver->Check_type(this, t->left->left, false);
					if(!ClassObject)
						exit(EXIT_FAILURE);
					type = ClassObject->m_type;
					if (type & Type_classobject)
						type &= ~Type_classobject;
					if(t->left->right->left != NULL)
						type |= Type_array;
					if ((ClassObject->m_classid == pFunction->ParamArray[k]->m_classid)
						&& (type == pFunction->ParamArray[k]->m_type))
						i++;
					break;
				}			
				}
				k++;
				if (i < k)
					break;
			}
			if (i == pFunction->ParamArray.GetCount())
			{
				pFunction_out = pFunction;
				return 0;
			}
		}	
	}
	/*
	for (int i = 0; i < ParamArray.GetCount(); i++)
	{
	  if (ParamArray[i]->m_name == varname)
	    return 2;
	}
	*/
	return 1;
} 

 
