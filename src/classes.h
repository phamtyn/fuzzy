/*
  fuzzy - The implementation of the FUZZY programming language

  File: classes.h

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

#ifndef __CALC__
#define __CALC__

//# define _DEBUG

# define VERSION "Fuzzy 1.3.1"
# define error_prefix 		"Fuzzy: "
# define BASETYPE_ID_LIMIT 	100
# define CLASS_ID_FUZZY_PAIR 	BASETYPE_ID_LIMIT
# define MATRIX_SIZE 		11
# define K_GAUSS 		25.0

# include <string>
# include <iostream>
# include <cmath>
# include "location.hh"

# include "tcoll.h"

void usage(int code);

typedef UINT DATATYPE;

# define	Type_number		UINT(1)
# define	Type_interger		(Type_number		<< 	1)
# define	Type_string		(Type_interger		<< 	1)
# define	Type_bool		(Type_string		<< 	1)
# define	Type_fuzzy		(Type_bool		<< 	1)
# define	Type_struct		(Type_fuzzy		<< 	1)
# define	Type_class		(Type_struct		<< 	1)
# define	Type_classobject	(Type_class		<< 	1)
# define	Type_function		(Type_classobject	<< 	1)
# define	Type_command_block	(Type_function		<< 	1)
# define	Type_operator_assign	(Type_command_block	<< 	1)
# define	Type_array		(Type_operator_assign	<< 	1)
# define	Type_void		(Type_array		<< 	1)
# define	Type_operator_neg	(Type_void		<< 	1)

# define	CLASS_ID_VOID		0
# define	CLASS_ID_NUMBER		1
# define	CLASS_ID_INTERGER	2
# define	CLASS_ID_STRING		3
# define	CLASS_ID_BOOL		4
# define	CLASS_ID_FUZZY		5


typedef enum {
  
  Node_type_number 	= Type_number,
  Node_type_interger 	= Type_interger,
  Node_type_string 	= Type_string,
  Node_type_bool   	= Type_bool, 
  Node_type_fuzzy   	= Type_fuzzy, 
  
  Node_constant_number,
  Node_constant_string,
  Node_constant_bool, 
  Node_constant_interger, 
  
  Node_illegal,

  /* binary operators  lnode and rnode are the expressions to work on */
  Node_multive,		/* 1 */
  Node_quotient,	/* 2 */
  Node_mod,		/* 3 */
  Node_plus,		/* 4 */
  Node_minus,		/* 5 */
  Node_cond_pair,	/* 6: conditional pair (see Node_line_range) jfw */
  Node_subscript,	/* 7 */
  Node_concat,		/* 8 */

  Node_unary_minus,	/* 13 */
  Node_field_spec,	/* 14 */

  /* assignments   lnode is the var to assign to, rnode is the exp */
  Node_assign,		/* 15 */
  Node_assign_multive,	/* 16 */
  Node_assign_quotient,	/* 17 */
  Node_assign_mod,	/* 18 */
  Node_assign_plus,	/* 19 */
  Node_assign_minus,	/* 20 */

  /* boolean binaries   lnode and rnode are expressions */
  Node_and,		/* 21 */
  Node_or,		/* 22 */

  /* binary relationals   compares lnode and rnode */
  Node_equal,		/* 23 */
  Node_notequal,	/* 24 */
  Node_less,		/* 25 */
  Node_greater,		/* 26 */
  Node_le,		/* 27 */
  Node_ge,		/* 28 */

  /* unary relationals   works on subnode */
  Node_not,		/* 29 */

  /* match ops (binary)   work on lnode and rnode ??? */
  Node_match,		/* 30 */
  Node_nomatch,		/* 31 */

  /* program structures */ 
  Node_rule_list,	/* 35 lnode is a rule, rnode is rest of list */
  Node_rule_node,	/* 36 lnode is an conditional, rnode is statement */
  Node_statement_list,	/* 37 lnode is a statement, rnode is more list */
  Node_if_branches,	/* 38 lnode is to run on true, rnode on false */
  Node_expression_list,	/* 39 lnode is an exp, rnode is more list */

  /* keywords */ 
  Node_K_BEGIN,		/* 40 no stuff */
  Node_K_END,		/* 41 ditto */
  Node_K_if,		/* 42 lnode is conditonal, rnode is if_branches */
  Node_K_while,		/* 43 lnode is condtional, rnode is stuff to run */
  Node_K_for,		/* 44 lnode is for_struct, rnode is stuff to run */
  Node_K_arrayfor,	/* 45 lnode is for_struct, rnode is stuff to run */
  Node_K_break,		/* 46 no subs */
  Node_K_continue,	/* 47 no stuff */
  Node_K_print,		/* 48 lnode is exp_list, rnode is redirect */
  Node_K_printf,	/* 49 lnode is exp_list, rnode is redirect */
  Node_K_next,		/* 59 no subs */
  Node_K_exit,		/* 51 subnode is return value, or NULL */

  /* I/O redirection for print statements */
  Node_redirect_output,	/* 52 subnode is where to redirect */
  Node_redirect_append,	/* 53 subnode is where to redirect */
  Node_redirect_pipe,	/* 54 subnode is where to redirect */

  /* Builtins   subnode is explist to work on, proc is func to call */
  Node_function_1,		/* 57 */
  Node_function_2,
  
  Node_statements,
  Node_statement,
  Node_argument,
  Node_namespace,
  
  Node_type_var,
  Node_type_var_rootpath,
  
  Node_type_struct_declare,
  Node_type_struct_declare_fuzzy,
  Node_type_struct_declare_fuzzy_discrete,
  
  Node_command_block, 
  Node_function_define, 
  Node_function_decl, 
  Node_function_proc, 
  Node_function_call, 
  Node_return, 
  Node_array, 
  Node_type_void, 
  Node_return_null, 
  Node_var_decl, 
  Node_name, 
  Node_function, 
  Node_case, 
  Node_default, 
  Node_switch, 
  Node_system, 
  Node_fuzzy_rule, 
  Node_very, 
  Node_little, 
  Node_really, 
  Node_var_decl_fuzzy_discrete, 
  Node_fuzzy_input, 
  Node_print_set, 
  Node_function_buildin, 
  
} NODETYPE;

struct FUZZY_PAIR {
	double m_grade;
	double m_value;
};

// data classes

class fuzzy_driver;

class NODE;
class Object;
class STRUCT;
class FUZZY;

typedef double (*FNCT1) (double);
typedef double (*FNCT2) (double, double);
typedef Object * (*FNCT_BUILDIN2) (Object *, Object *, const yy::location &);
typedef Object * (*FNCT_BUILDIN1) (Object *, const yy::location &);

using std::string;
using std::cout;
using std::endl;

double min(double a, double b);
double max(double a, double b);
Object * FuzzyToArray (Object *, Object *, const yy::location &);
Object * Defuzz (Object *, const yy::location &);
Object * ZeroFuzz (Object *, const yy::location &);

typedef FuzMap< string, STRUCT * > TYPE_MAP;
typedef FuzMultiMap< string, Object * > VAR_MAP;
typedef FuzArray< Object * > PARAM_ARRAY;
typedef FuzArray< Object * > OBJECT_ARRAY;

typedef FuzMap< string, FNCT_BUILDIN2 >::FuzPair FUNC_PAIR2;
typedef FuzMap< string, FNCT_BUILDIN1 >::FuzPair FUNC_PAIR1;

class Object {

protected:
	DATATYPE m_type;
	string m_typename;
	UINT m_classid;
	string m_name;
	NODE *m_node;
	
public:
	Object() {}
	Object(DATATYPE type, const string &typename_) : m_type(type), m_typename(typename_), m_node(NULL){}
	Object(DATATYPE type, const string &typename_, UINT classid) :
		m_type(type), m_typename(typename_), m_classid(classid), m_node(NULL) {}
	Object(DATATYPE type) : m_type(type), m_node(NULL) {}
	Object(NODE *node_) : m_node(node_) {}
	
	void SetName(const string &name) { m_name = name; }
	void SetTypename(const string &name) { m_typename = name; }
	DATATYPE GetType() { return m_type; }
	//void SetType(DATATYPE type) { m_type = type; }
	string &GetName() { return m_name; }
	string &GetTypename() { return m_typename; }
	UINT GetClassId() { return m_classid; }
	void SetClassId(UINT classid) { m_classid = classid; }
	bool IsBaseType() { return m_classid < BASETYPE_ID_LIMIT; }
	void attach(NODE *new_node);
	NODE *GetNode()	{ return m_node; };
	
	friend class STRUCT;
	friend class ARRAY;
	friend class NODE;
	
	static UINT CurrentId;
	
	virtual Object &operator=(const Object &t) {}
	
	virtual string &GetString() {}
	virtual double &GetNumber() {}
	virtual long &GetInterger() {}
	virtual double &GetValue() {}
	virtual TYPE_MAP *GetTypeMap() {}
	virtual VAR_MAP *GetVarMap() {}
	virtual PARAM_ARRAY *GetParamArray() {}
	virtual NODE *GetFunctionBody() {}
	virtual void init(const STRUCT &t) {}
	virtual void init(const Object &t) {}
	virtual void init() {}
	
	virtual Object *GetArrayElement(int i) {}
	virtual int GetArrayCount() {}
	virtual NODE *GetFunctionValue() {}
	virtual STRUCT *GetClassObject() {}
	virtual void SetClassObject(STRUCT *ClassObject) {}
	virtual bool IsCompleted() { return true; }
	virtual void SetCompleted() {}
	virtual bool &GetFlag()		{}
	virtual void SetFlag(bool flag)	{}
	virtual void SetParent(STRUCT *parent) {}
	virtual STRUCT *GetParent() {}
	virtual void InitBelong() {}
	virtual void ZeroBelong() {}
	virtual FUZZY_PAIR *&GetBelong() {}
	virtual int IsFuzzy() {}
	virtual FUZZY *GetFuzzy() {}
	virtual int &GetSize() {}
	virtual double MakeFuzzyClear() {}
	
	virtual ~Object() {}
	
};

class Number : public Object {

	double m_number;
public:
	Number() : Object(Type_number, "Number", CLASS_ID_NUMBER) {}
	Number(double number) : Object(Type_number, "Number", CLASS_ID_NUMBER), m_number(number) {}
	Number(const Number &t) : Object(Type_number, "Number", CLASS_ID_NUMBER), m_number(t.m_number) {}
	
	Number operator+(const Number &t) { return Number(m_number + t.m_number); }
	Number &operator += (const Number &t) { m_number += t.m_number; return *this; }
	Number &operator -= (const Number &t) { m_number -= t.m_number; return *this; }
	Number &operator *= (const Number &t) { m_number *= t.m_number; return *this; }
	Number &operator /= (const Number &t) { m_number /= t.m_number; return *this; }
	Number operator-(const Number &t) { return Number(m_number - t.m_number); }
	Number operator*(const Number &t) { return Number(m_number * t.m_number); }
	Number operator/(const Number &t) { return Number(m_number / t.m_number); }

	Number operator-() { return Number(-m_number); }
	
	bool operator>(const Number &t) {
	  return m_number > t.m_number ? true : false;
	}
	bool operator<(const Number &t) {
	  return m_number < t.m_number ? true : false;
	}
	bool operator >= (const Number &t) {
	  return m_number >= t.m_number ? true : false;
	}
	bool operator <= (const Number &t) {
	  return m_number <= t.m_number ? true : false;
	}
	bool operator != (const Number &t) { return m_number != t.m_number; }
	bool operator == (const Number &t) { return m_number == t.m_number; }
	
	
	operator double() { return m_number; }
	//operator int() { return (int)m_number; }
	
	Number &operator=(const Object &t) {
		if (this == &t)
			return *this;
		const Number *pt = static_cast<const Number *>(&t);
		m_number = pt->m_number;
		return *this;
	}
	
	double &GetNumber() { return m_number; }
	
	friend std::ostream & operator<<(std::ostream &os, const Number &t);
	
	~Number();
};

class INTERGER : public Object {

	long m_interger;
public:
	INTERGER() : Object(Type_interger, "int", CLASS_ID_INTERGER) {}
	INTERGER(long number) : Object(Type_interger, "int", CLASS_ID_INTERGER), m_interger(number) {}
	INTERGER(const INTERGER &t) : Object(Type_interger, "int", CLASS_ID_INTERGER), 
								m_interger(t.m_interger) {}
	
	INTERGER operator+(const INTERGER &t) { return INTERGER(m_interger + t.m_interger); }
	INTERGER &operator += (const INTERGER &t) { m_interger += t.m_interger; return *this; }
	INTERGER &operator -= (const INTERGER &t) { m_interger -= t.m_interger; return *this; }
	INTERGER &operator *= (const INTERGER &t) { m_interger *= t.m_interger; return *this; }
	INTERGER &operator /= (const INTERGER &t) { m_interger /= t.m_interger; return *this; }
	INTERGER operator-(const INTERGER &t) { return INTERGER(m_interger - t.m_interger); }
	INTERGER operator*(const INTERGER &t) { return INTERGER(m_interger * t.m_interger); }
	INTERGER operator/(const INTERGER &t) { return INTERGER(m_interger / t.m_interger); }

	INTERGER operator-() { return INTERGER(-m_interger); }
	
	bool operator>(const INTERGER &t) {
	  return m_interger > t.m_interger ? true : false;
	}
	bool operator<(const INTERGER &t) {
	  return m_interger < t.m_interger ? true : false;
	}
	bool operator >= (const INTERGER &t) {
	  return m_interger >= t.m_interger ? true : false;
	}
	bool operator <= (const INTERGER &t) {
	  return m_interger <= t.m_interger ? true : false;
	}
	bool operator != (const INTERGER &t) { return m_interger != t.m_interger; }
	bool operator == (const INTERGER &t) { return m_interger == t.m_interger; }
	
	
	operator long() { return m_interger; }
	//operator int() { return (int)m_interger; }
	
	INTERGER &operator=(const Object &t) {
		if (this == &t)
			return *this;
		const INTERGER *pt = static_cast<const INTERGER *>(&t);
		m_interger = pt->m_interger;
		return *this;
	}
	
	long &GetInterger() { return m_interger; }
	
	friend std::ostream & operator<<(std::ostream &os, const INTERGER &t);
	
	~INTERGER();
};

class String : public Object {

	string m_string;
public:
	String() : Object(Type_string, "String", CLASS_ID_STRING) {}
	String(const string &sval) : Object(Type_string, "String", CLASS_ID_STRING), m_string(sval) {}
	String(const String &t) : Object(Type_string, "String", CLASS_ID_STRING), m_string(t.m_string) {}
	
	String operator+(const String &t) { return String(m_string + t.m_string); }
	String &operator += (const String &t) { m_string += t.m_string; return *this; }
	
	bool operator>(const String &t) {
	  return m_string > t.m_string ? true : false;
	}
	bool operator<(const String &t) {
	  return m_string < t.m_string ? true : false;
	}
	bool operator >= (const String &t) {
	  return m_string >= t.m_string ? true : false;
	}
	bool operator <= (const String &t) {
	  return m_string <= t.m_string ? true : false;
	}
	
	bool operator != (const String &t) { return m_string != t.m_string; }
	bool operator == (const String &t) { return m_string == t.m_string; }
	
	operator string() { return m_string; }
	
	friend std::ostream & operator<<(std::ostream &os, const String &t);
	string &GetString() { return m_string; }
	
	String &operator=(const Object &t) {
		if (this == &t)
			return *this;
		const String *pt = static_cast<const String *>(&t);
		m_string = pt->m_string;
		return *this;
	}
	
	~String();
};

    
typedef FuzMap< string, Object * >::FuzPair Pair;
typedef FuzMap< string, STRUCT * >::FuzPair SPair;
typedef FuzMultiMap< string, Object * >::FuzPair TPair;

typedef FuzMap< string, NODE >::FuzPair NPair;

class STRUCT : public Object {

	bool m_bComplete;
	STRUCT * m_parent;
	STRUCT * m_child;
	NODE *m_pFunctionBody;
	NODE * m_pFunctionValue;
	STRUCT *m_ClassObject;
	FUZZY *m_fuzzy;
	int m_bFuzzy;
	double m_min, m_max;
	int m_fuzzy_size;
public:
	
	STRUCT() : Object((NODE *)NULL), m_bComplete(false), m_parent(NULL), m_fuzzy(NULL), 
					m_child(NULL), m_pFunctionValue(NULL), m_bFuzzy(0) {
						m_type = Type_struct;
					}
	STRUCT(const string &_typename, STRUCT *parent, DATATYPE type = Type_struct | Type_classobject);
	STRUCT(STRUCT *parent, DATATYPE type = Type_struct);
	STRUCT(const STRUCT &t);
	
	TYPE_MAP TypeMap;
	VAR_MAP VarMap;
	PARAM_ARRAY ParamArray;
	
	bool CheckName_type_decl(const string &typename_);
	int CheckName_var_decl(const string &varname, const NODE *tree, Object *&pFunction_out);
	int CheckName_var_decl(const string &varname);
	bool IsBaseType(const string &name);
	void Add_type(STRUCT *child, const string &name);
	void Add_var(Object *child, const string &name);
	STRUCT *FindClass(const string &name);
	STRUCT *FindClass(const FuzList<string> &list, NODETYPE type);
	bool IsCompleted() { return m_bComplete; }
	void SetCompleted() { m_bComplete = true; }
	void SetFunctionBody(NODE *pnode) { m_pFunctionBody = pnode; }
	NODE *GetFunctionBody() { return m_pFunctionBody; }
	STRUCT *GetParent() { return m_parent; }
	void SetParent(STRUCT *parent) { m_parent = parent; }
	
	STRUCT *&GetChild() { return m_child; }
	void SetChild(STRUCT *child) { m_child = child; }
	
	NODE *GetFunctionValue() { return m_pFunctionValue; }
	void SetFunctionValue(NODE *pFunctionValue) { m_pFunctionValue = pFunctionValue; }
	
	STRUCT *GetClassObject() { return m_ClassObject; }
	void SetClassObject(STRUCT *ClassObject) { 
		m_ClassObject = ClassObject; 
		m_classid = ClassObject->m_classid; 
		m_typename = ClassObject->m_typename; 
	}
	
	static STRUCT *root;
	
	TYPE_MAP *GetTypeMap() 		{ return &TypeMap; }
	VAR_MAP *GetVarMap() 		{ return &VarMap; }
	PARAM_ARRAY *GetParamArray() 	{ return &ParamArray; }
	
	STRUCT &operator=(const STRUCT &t);
	STRUCT &operator=(const Object &t);
	
	void init(const STRUCT &t);
	void init(const Object &t);
	
	FUZZY *GetFuzzy() { return m_fuzzy; }
	
	void SetFuzzy(double _min, double _max) { m_min = _min; m_max = _max; m_bFuzzy = 1; }
	void SetFuzzy(int fuzzy_size) { m_fuzzy_size = fuzzy_size; m_bFuzzy = 2; }
	int IsFuzzy() { return m_bFuzzy; }
	double MakeFuzzyClear();
	void ZeroBelong();
	
	double GetMin() { return m_min; }
	double GetMax() { return m_max; }
	int GetFuzzySize() { return m_fuzzy_size; }
	
	friend class FUZZY;
	friend class ARRAY;
	
	~STRUCT();
	
};

class ARRAY : public Object
{
	OBJECT_ARRAY data;
	bool m_bComplete;
	STRUCT *m_ClassObject;
public:
	ARRAY() : Object(Type_array), m_bComplete(false), m_ClassObject(NULL){}
	ARRAY(DATATYPE type, int size);
	ARRAY(STRUCT *parent, STRUCT *ClassObject, int size, bool bInit = true);
	ARRAY(const ARRAY &t);
	
	int GetArrayCount() { return data.GetCount(); }
	Object *GetArrayElement(int i);
	STRUCT *GetClassObject() { return m_ClassObject; }
	
	void init();
	
	bool IsCompleted() { return m_bComplete; }
	void SetCompleted() { m_bComplete = true; }
	
	friend class STRUCT;
	friend class NODE;
	
	~ARRAY();
};

class TBOOL : public Object
{
	bool m_flag;
public:
	TBOOL() : Object(Type_bool, "bool", CLASS_ID_BOOL) {}
	TBOOL(bool flag) : Object(Type_bool, "bool", CLASS_ID_BOOL), m_flag(flag) {}
	TBOOL(const TBOOL &t) : Object(Type_bool, "bool", CLASS_ID_BOOL), m_flag(t.m_flag) {}
	
	bool &GetFlag()		{ return m_flag; }
	void SetFlag(bool flag)	{ m_flag = flag; }
	
	TBOOL &operator=(const Object &t) {
		if (this == &t)
			return *this;
		const TBOOL *pt = static_cast<const TBOOL *>(&t);
		m_flag = pt->m_flag;
		return *this;
	}
	
	friend class STRUCT;
	friend class NODE;
	
	~TBOOL();
};

class FUZZY : public Object {

	STRUCT * m_parent;
	double **m_matrix;
	FUZZY_PAIR *m_belong;
	double m_value;
	int m_size;
public:
	
	FUZZY() : Object(Type_fuzzy, "fuzzy", CLASS_ID_FUZZY), m_parent(NULL), m_matrix(NULL) {
		
		m_size = MATRIX_SIZE;
		m_belong = new FUZZY_PAIR[m_size];	
		ZeroBelong();
	}
	FUZZY(double value) : Object(Type_fuzzy, "fuzzy", CLASS_ID_FUZZY),
		m_value(value), m_parent(NULL), m_matrix(NULL) {
	  
		m_size = MATRIX_SIZE;
		m_belong = new FUZZY_PAIR[m_size];	
		InitBelong();
	}
	FUZZY(STRUCT *parent) : Object(Type_fuzzy, "fuzzy", CLASS_ID_FUZZY), m_value(0), 
		m_parent(parent), m_matrix(NULL) { 
	  
		m_size = MATRIX_SIZE;
		
		if (m_parent->IsFuzzy() == 2)
			m_size = m_parent->m_fuzzy_size;
			
		m_belong = new FUZZY_PAIR[m_size];	
		ZeroBelong();
	}
	FUZZY(const FUZZY &t);
	
	STRUCT *GetParent() { return m_parent; }
	void SetParent(STRUCT *parent) { m_parent = parent; }
	
	double &GetValue() { return m_value; }
	int &GetSize() { return m_size; }
	
	FUZZY &operator=(const Object &t);
	
	FUZZY &operator=(const FUZZY &t);
	
	double **GetMatrix() { return m_matrix; }
	FUZZY_PAIR *&GetBelong() { return m_belong; }
	
	void InitBelong();
	void ZeroBelong() { memset(m_belong, 0, sizeof(FUZZY_PAIR) * m_size); }
	void Intersect(const FUZZY &t1, const FUZZY &t2);
	void Union(const FUZZY &t1, const FUZZY &t2);
	void Not(const FUZZY &t);
	FUZZY Very();
	FUZZY Little();
	FUZZY Really();
	
	void MakeMatrix(const FUZZY &from);
	void MakeBelong(const FUZZY &from_input);
	void Union(const FUZZY &from_rule);
	double MakeFuzzyClear();
	
	friend class STRUCT;
	friend class NODE;
	
	friend std::ostream & operator<<(std::ostream &os, const FUZZY &t);
	
	~FUZZY();
	
};

inline FUZZY::FUZZY(const FUZZY &t) : Object(Type_fuzzy, "fuzzy", CLASS_ID_FUZZY), m_matrix(NULL),
					m_value(t.m_value), m_size(t.m_size), m_parent(t.m_parent) 
{	
	m_belong = new FUZZY_PAIR[m_size];
	for (int i = 0; i < m_size; i++)
		m_belong[i] = t.m_belong[i];		
}

inline FUZZY &FUZZY::operator=(const Object &t) {
	if (this == &t)
		return *this;
	const FUZZY *pt = static_cast<const FUZZY *>(&t);
	
	m_value = pt->m_value;
	for (int i = 0; i < m_size; i++)
		m_belong[i] = pt->m_belong[i];
	return *this;
}

inline FUZZY &FUZZY::operator=(const FUZZY &t) {
	if (this == &t)
		return *this;
	m_value = t.m_value;
	for (int i = 0; i < m_size; i++)
		m_belong[i] = t.m_belong[i];
	return *this;
}

inline void FUZZY::InitBelong()
{
	if (m_parent->IsFuzzy() == 2)
		return;
	double _min = m_parent->m_min, _max = m_parent->m_max;
	for (int i = 0; i < m_size; i++)
	{
		double xi = _min + (_max - _min) / (m_size - 1) * i;
		m_belong[i].m_grade = exp(-pow((m_value - xi) / (_max - _min), 2) * K_GAUSS);
		//m_belong[i].m_value = xi;
	}
}

inline void FUZZY::Intersect(const FUZZY &t1, const FUZZY &t2)
{
	for (int i = 0; i < m_size; i++)
		m_belong[i].m_grade = min(t1.m_belong[i].m_grade, t2.m_belong[i].m_grade);
}

inline void FUZZY::Union(const FUZZY &t1, const FUZZY &t2)
{
	for (int i = 0; i < m_size; i++)
		m_belong[i].m_grade = max(t1.m_belong[i].m_grade, t2.m_belong[i].m_grade);
}

inline void FUZZY::Not(const FUZZY &t)
{
	for (int i = 0; i < m_size; i++)
		m_belong[i].m_grade = 1.0 - t.m_belong[i].m_grade;
}

inline FUZZY FUZZY::Very()
{
	FUZZY t;
	for (int i = 0; i < m_size; i++)
		t.m_belong[i].m_grade = pow(m_belong[i].m_grade, 2);
	return t;	
}

inline FUZZY FUZZY::Little()
{
	FUZZY t;
	for (int i = 0; i < m_size; i++)
		t.m_belong[i].m_grade = pow(m_belong[i].m_grade, 0.5);
	return t;	
}

inline FUZZY FUZZY::Really()
{
	FUZZY t;
	for (int i = 0; i < m_size; i++)
	{
		if (m_belong[i].m_grade <= 0.5)
			t.m_belong[i].m_grade = 2 * pow(m_belong[i].m_grade, 2);
		else
			t.m_belong[i].m_grade = 1 - 2 * pow(1- m_belong[i].m_grade, 2);
	}
	return t;	
}

inline void FUZZY::MakeMatrix(const FUZZY &from)
{
	m_matrix = new double *[m_size];
	for (int i = 0; i < m_size; i++)
		m_matrix[i] = new double[from.m_size];
	
	for(int j=0; j< from.m_size; j++)
		for(int i=0; i < m_size; i++)
			m_matrix[i][j] = from.m_belong[j].m_grade * m_belong[i].m_grade;
			//(*m_matrix)[i][j] = min(from.m_belong[i], m_belong[j]);
}

inline void FUZZY::MakeBelong(const FUZZY &from_input)
{
	for(int j = 0; j < m_size; j++)
	{
		double _max = 0;
		for(int i = 0; i < from_input.m_size; i++)
		{
			double _min = min(from_input.m_belong[i].m_grade, m_matrix[j][i]);
			if(_max < _min)
				_max = _min; 
		}
		m_belong[j].m_grade = _max;	
	}
}

inline void FUZZY::Union(const FUZZY &from_rule)
{
	for (int i = 0; i < m_size; i++)
		m_belong[i].m_grade = max(m_belong[i].m_grade, from_rule.m_belong[i].m_grade);
}

inline double FUZZY::MakeFuzzyClear()
{
	double _min = m_parent->m_min, _max = m_parent->m_max;
	
	if (m_parent->IsFuzzy() == 1)
	{
		for (int i = 0; i < m_size; i++)
			m_belong[i].m_value = _min + (_max - _min) / (m_size - 1) * i;
	}
	
	double total_a = 0;
	double total_b = 0;
	
	for (int i = 0; i < m_size - 1; i++)
	{
		double x1 = m_belong[i].m_value;
		double x2 = m_belong[i + 1].m_value;
		double y1 = m_belong[i].m_grade;
		double y2 = m_belong[i + 1].m_grade;
		double dx = x2 - x1;
		double dy = y2 - y1;
		if (dx == 0)
			return m_value = 0;
		double Fax1 = 1.0/2 * pow(x1, 2) * dy / dx + x1 * (y1 - x1 * dy / dx);	
		double Fax2 = 1.0/2 * pow(x2, 2) * dy / dx + x2 * (y1 - x1 * dy / dx);
		double a = Fax2 - Fax1;
		
		double Fbx1 = 1.0/3 * pow(x1, 3) * dy / dx + 1.0/2 * pow(x1, 2) * (y1 - x1 * dy / dx);	
		double Fbx2 = 1.0/3 * pow(x2, 3) * dy / dx + 1.0/2 * pow(x2, 2) * (y1 - x1 * dy / dx);
		double b = Fbx2 - Fbx1;
		
		total_a += a;
		total_b += b;
	}
	
	if (total_a == 0)
		return m_value = 0;
	
	return m_value = total_b / total_a;
}

inline ARRAY::ARRAY(const ARRAY &t) : Object((NODE *)NULL)
{
	m_type = t.m_type;
	m_classid = t.m_classid;
	m_typename = t.m_typename;
	DATATYPE type = m_type;
	type &= ~Type_array;
	data.SetCount(t.data.GetCount());
	switch (type)
	{
		case Type_number:
		{
			for (int i = 0; i < data.GetCount(); i++)
			{
				Number * pElement = static_cast<Number *>(t.data[i]);
				data[i] = new Number(*pElement);
			}
			break;	
		}
		case Type_string:
		{
			for (int i = 0; i < data.GetCount(); i++)
			{
				String * pElement = static_cast<String *>(t.data[i]);
				data[i] = new String(*pElement);
			}
			break;	
		}
		case Type_bool:
		{
			for (int i = 0; i < data.GetCount(); i++)
			{
				TBOOL * pElement = static_cast<TBOOL *>(t.data[i]);
				data[i] = new TBOOL(*pElement);
			}
			break;	
		}
		case Type_fuzzy:
		{
			for (int i = 0; i < data.GetCount(); i++)
			{
				FUZZY * pElement = static_cast<FUZZY *>(t.data[i]);
				data[i] = new FUZZY(*pElement);
			}
			break;	
		}
		case Type_struct:
		{
			for (int i = 0; i < data.GetCount(); i++)
			{
				STRUCT * pElement = static_cast<STRUCT *>(t.data[i]);
				data[i] = new STRUCT(*pElement);
				data[i]->SetParent(pElement->m_parent);
			}
			break;	
		}
	}
}

inline void ARRAY::init()
{
	for (int i = 0; i < data.GetCount(); i++)
	{
		data[i]->init(*m_ClassObject);
		*data[i] = *m_ClassObject;
	}
}

inline Object *ARRAY::GetArrayElement(int i)
{
	if (i >= data.GetCount())
		return NULL;
	return data[i];	
}

inline ARRAY::ARRAY(DATATYPE type, int size) : Object(Type_array), m_ClassObject(NULL)
{
	m_type |= type;
	data.SetCount(size);
	switch (type)
	{
		case Type_number:
		{
			for (int i = 0; i < data.GetCount(); i++)
				data[i] = new Number;
			m_classid = CLASS_ID_NUMBER;
			m_typename = "Number";	
			break;	
		}
		case Type_interger:
		{
			for (int i = 0; i < data.GetCount(); i++)
				data[i] = new INTERGER;
			m_classid = CLASS_ID_INTERGER;
			m_typename = "int";	
			break;	
		}
		case Type_string:
		{
			for (int i = 0; i < data.GetCount(); i++)
				data[i] = new String;
			m_classid = CLASS_ID_STRING;
			m_typename = "String";	
			break;	
		}
		case Type_bool:
		{
			for (int i = 0; i < data.GetCount(); i++)
				data[i] = new TBOOL;
			m_classid = CLASS_ID_BOOL;
			m_typename = "bool";	
			break;	
		}
		case Type_fuzzy:
		{
			for (int i = 0; i < data.GetCount(); i++)
				data[i] = new FUZZY;
			m_classid = CLASS_ID_FUZZY;
			m_typename = "fuzzy";	
			break;	
		}
	}
}
inline ARRAY::ARRAY(STRUCT *parent, STRUCT *ClassObject, int size, bool bInit) : Object(Type_array),
				m_bComplete(false), m_ClassObject(ClassObject)
{
	m_type |= ClassObject->m_type;
	if (m_type & Type_classobject)
		m_type &= ~Type_classobject;
	m_classid = ClassObject->m_classid;
	data.SetCount(size);
	for (int i = 0; i < data.GetCount(); i++)
	{
		data[i] = new STRUCT(parent);
		if (bInit)
		{
			data[i]->init(*ClassObject);
			*data[i] = *ClassObject;
		}
	}
	
	m_typename = ClassObject->m_typename;
}

inline STRUCT::STRUCT(const string &_typename, STRUCT *parent, DATATYPE type) : 
	m_parent(parent), m_child(NULL), Object(type, _typename), 
	m_bComplete(false), m_pFunctionValue(NULL), m_fuzzy(NULL), m_bFuzzy(0)
{
	m_classid = CurrentId++;
	m_ClassObject = this;
}

inline STRUCT::STRUCT(STRUCT *parent, DATATYPE type) :  
		m_parent(parent), m_child(NULL), Object(type), 
		m_bComplete(false), m_pFunctionValue(NULL), m_fuzzy(NULL), m_bFuzzy(0)
{
}

class NODE
{

public:
	NODE() : data(NULL), left(NULL), right(NULL) {}
	//NODE(double number) : type(Node_type_number), data(new Number(number)) {}
	NODE(double number, const yy::location &__loc) :
		type(Node_constant_number), loc(__loc), data(new Number(number)), left(NULL), right(NULL) {
			data->m_node = this;
		}
		
	NODE(long number, const yy::location &__loc) :
		type(Node_constant_interger), loc(__loc), data(new INTERGER(number)), left(NULL), right(NULL) {
			data->m_node = this;
		}	
	
	NODE(const std::string &string, const yy::location &__loc) :
		type(Node_constant_string), loc(__loc), data(new String(string)), left(NULL), right(NULL) {
			data->m_node = this;
		}
		
	NODE(bool flag, const yy::location &__loc) :
		type(Node_constant_bool), loc(__loc), data(new TBOOL(flag)), left(NULL), right(NULL) {
			data->m_node = this;
		}
	
	NODE(FNCT1 fnct1, const yy::location &__loc) :
		type(Node_function_1), loc(__loc), data(NULL), left(NULL), right(NULL)
	{
		value.fnct1 = fnct1;
	}
	NODE(FNCT2 fnct2, const yy::location &__loc) :
		type(Node_function_2), loc(__loc), data(NULL), left(NULL), right(NULL)
	{
		value.fnct2 = fnct2;
	}	
	
	NODE(NODETYPE t, const yy::location &__loc) : type(t), loc(__loc), 
						data(NULL), left(NULL), right(NULL){}
	
	NODE(DATATYPE data_type, const yy::location &__loc);
	
	//NODE(NODETYPE t, DATATYPE data_type, const yy::location &__loc);
	
	NODE(const yy::location &__loc) : loc(__loc), data(NULL), left(NULL), right(NULL){}
	
	~NODE();
	
	NODETYPE type;
	yy::location loc;
	Object *data;
	
	struct {
		FNCT1 fnct1;
		FNCT2 fnct2;	
	} value;
	
	NODE *left;
	NODE *right;
	
	static fuzzy_driver *driver;
	friend std::ostream & operator<<(std::ostream &os, const NODE &t);
	
	NODE &assign(const NODE &t, Object *pFunction = NULL, bool bFunctionConvert = false);
	NODE operator-();
	
	bool GetBoolen();
	NODE(const NODE &t);
	
	void attach(Object *new_data);
	//void detach() { if (data) { data->m_node = NULL; data = NULL; } }	
	void free_data();
};

inline void Object::attach(NODE *new_node) { 
	if (new_node == m_node)
		return;
	if (m_node) m_node->data = NULL; m_node = new_node; }

inline void NODE::attach(Object *new_data) { 
	if (new_data == data)
		return;
	if (data) data->m_node = NULL; new_data->attach(this); data = new_data; }

inline NODE::NODE(const NODE &t) : left(NULL), right(NULL), data(NULL)
{
	type = t.type;
	loc = t.loc;
	value = t.value;
	if (t.data !=  NULL)
	{
		DATATYPE datatype = t.data->m_type;
		if (datatype & Type_array)
			datatype = Type_array;
		switch (datatype)
		{
			case Type_number:
			{
				Number * pElement = static_cast<Number *>(t.data);
				attach(new Number(*pElement));
				break;	
			}
			case Type_interger:
			{
				INTERGER * pElement = static_cast<INTERGER *>(t.data);
				attach(new INTERGER(*pElement));
				break;	
			}
			case Type_string:
			{
				String * pElement = static_cast<String *>(t.data);
				attach(new String(*pElement));
				break;
			}
			case Type_bool:
			{
				TBOOL * pElement = static_cast<TBOOL *>(t.data);
				attach(new TBOOL(*pElement));
				break;
			}
			case Type_fuzzy:
			{
				FUZZY * pElement = static_cast<FUZZY *>(t.data);
				attach(new FUZZY(*pElement));
				break;
			}
			case Type_struct:
			{
				STRUCT * pElement = static_cast<STRUCT *>(t.data);
				attach(new STRUCT(*pElement));
				break;
			}
			case Type_array:
			{
				ARRAY * pElement = static_cast<ARRAY *>(t.data);
				attach(new ARRAY(*pElement));
				break;
			}
		}
	}
	
	
	if (t.left != NULL)
		left = new NODE (*t.left);
	if (t.right != NULL)
		right = new NODE (*t.right);
}


inline Number::~Number() { m_name.clear(); m_typename.clear(); if (m_node) m_node->data = NULL; }
inline INTERGER::~INTERGER() { m_name.clear(); m_typename.clear(); if (m_node) m_node->data = NULL; }
inline String::~String() { m_name.clear(); m_typename.clear(); m_string.clear();
								if (m_node) m_node->data = NULL; }
inline TBOOL::~TBOOL() { m_name.clear(); m_typename.clear(); if (m_node) m_node->data = NULL; }	
inline FUZZY::~FUZZY() { 
	if (m_matrix)
	{
		for (int i = 0; i < m_size; i++)
			delete m_matrix[i];
		delete m_matrix; 
	}
	delete m_belong;
	if (m_node) m_node->data = NULL; 
}
inline ARRAY::~ARRAY()
{
	for (int i = 0; i < data.GetCount(); i++)
		delete data[i];
	data.RemoveAll();
	
	m_name.clear(); m_typename.clear();
	if (m_node) m_node->data = NULL;
}

inline STRUCT::~STRUCT()
{
	POSITION pos;
	pos = TypeMap.GetStartPosition();
	while (pos)
	{
		Object *pObject = TypeMap.GetNextValue(pos);
		delete pObject;
	}
	TypeMap.RemoveAll();
	
	pos = VarMap.GetHeadPosition();
	while (pos)
	{
		Object *pObject = VarMap.GetNextValue(pos);
		delete pObject;
	}
	VarMap.RemoveAll();
	
	if (m_type & Type_function)
	{
		if (m_type & Type_classobject)
		{
			for (int i = 0; i < ParamArray.GetCount(); i++)
				delete ParamArray[i];
			
			assert(m_classid == CLASS_ID_VOID || m_pFunctionValue->data != NULL);
			
			delete m_pFunctionValue;	
		}	
		ParamArray.RemoveAll();	
	}
	
	if (m_child)
	{
		delete m_child;
		m_child = NULL;
	}
	if (m_fuzzy)
		delete m_fuzzy;
	
	m_name.clear(); m_typename.clear();	
	if (m_node) m_node->data = NULL;
}

inline void NODE::free_data()
{
	if (data)
	{
		data->m_node = NULL;
		delete data;	
		data = NULL;
	}
}

inline NODE::~NODE()
{
	if (left)
	{
		delete left;
		left = NULL;
	}
	if (right)
	{
		delete right;
		right = NULL;
	}
	
	free_data();
}

inline NODE::NODE(DATATYPE data_type, const yy::location &__loc) : loc(__loc),
					left(NULL), right(NULL), data(NULL)
{
	switch (data_type)
	{
		case Type_number:
			attach(new Number);
			break;
		case Type_interger:
			attach(new INTERGER);
			break;
		case Type_string:
			attach(new String);
			break;
		case Type_bool:
			attach(new TBOOL);
			break;
		case Type_fuzzy:
			attach(new FUZZY);
			break;
	}
}

inline STRUCT &STRUCT::operator=(const STRUCT &t)
{
	if(this == &t)
		return *this;	

	POSITION pos = VarMap.GetHeadPosition();
	POSITION pos_t = t.VarMap.GetHeadPosition();
	while(pos)
	{
		Object *p = VarMap.GetNextValue(pos);
		const Object *p_t = t.VarMap.GetNextValue(pos_t);
		switch (p->m_type)
		{
			case Type_number:
			{
				Number *pNumber = static_cast<Number *>(p);
				const Number *pNumber_t = static_cast<const Number *>(p_t);
				*pNumber = *pNumber_t;
				
				break;
			}
			case Type_interger:
			{
				INTERGER *pInterger = static_cast<INTERGER *>(p);
				const INTERGER *pInterger_t = static_cast<const INTERGER *>(p_t);
				*pInterger = *pInterger_t;
				
				break;
			}
			case Type_string:
			{
				String *pString = static_cast<String *>(p);
				const String *pString_t = static_cast<const String *>(p_t);
				*pString = *pString_t;
				
				break;
			}
			case Type_bool:
			{
				TBOOL *pBool = static_cast<TBOOL *>(p);
				const TBOOL *pBool_t = static_cast<const TBOOL *>(p_t);
				*pBool = *pBool_t;
				
				break;
			}
			case Type_fuzzy:
			{
				FUZZY *pFuzzy = static_cast<FUZZY *>(p);
				const FUZZY *pFuzzy_t = static_cast<const FUZZY *>(p_t);
				*pFuzzy = *pFuzzy_t;
				
				break;
			}
			case Type_struct:
			{
				STRUCT *pStruct = static_cast<STRUCT *>(p);
				const STRUCT *pStruct_t = static_cast<const STRUCT *>(p_t);
				*pStruct = *pStruct_t;
				
				break;
			}
		}
		if (p->m_type & Type_array)
		{
			int count = p->GetArrayCount();
			
			for (int i = 0; i < count; i++)
			{
				ARRAY *pArray = static_cast<ARRAY *>(p);
				const ARRAY *pArray_t = static_cast<const ARRAY *>(p_t);
				*pArray->data[i] = *pArray_t->data[i];
				
			}	
		}
	}
	
	return *this;
}

inline STRUCT &STRUCT::operator=(const Object &t)
{
	if(this == &t)
		return *this;	

	const STRUCT *pt = static_cast<const STRUCT *>(&t);
	*this = *pt;
	
	return *this;
}

inline void STRUCT::init(const Object &t)
{
	const STRUCT *pt = static_cast<const STRUCT *>(&t);
	init(*pt);
}

inline STRUCT::STRUCT(const STRUCT &t) : m_child(NULL), Object((NODE *)NULL), m_fuzzy(NULL), m_bFuzzy(0)
{
	init(*t.m_ClassObject);
	*this = t;
}

inline void STRUCT::init(const STRUCT &t)
{
	m_type = t.m_type;
	if (m_type & Type_classobject)
		m_type &= ~Type_classobject;
	m_typename = t.m_typename;
	m_classid = t.m_classid;
	m_ClassObject = t.m_ClassObject;
	if (m_name.empty())
		m_name = t.m_name;
	m_bFuzzy = t.m_bFuzzy;
	if (m_bFuzzy)
	{
		if (m_bFuzzy == 1)
		{
			m_min = t.m_min;
			m_max = t.m_max;
		}
		else
			m_fuzzy_size = t.m_fuzzy_size;
		m_fuzzy = new FUZZY(this);
	}
	
	if (t.m_type & Type_function)
	{
		m_pFunctionBody = t.m_pFunctionBody;
		m_pFunctionValue = t.m_pFunctionValue;
		ParamArray.SetCount(t.ParamArray.GetCount());
		for (int i = 0; i < t.ParamArray.GetCount(); i++)
			ParamArray[i] = t.ParamArray[i];
	}
	
	POSITION pos = t.VarMap.GetHeadPosition();
	while(pos)
	{
		const TPair *p = t.VarMap.GetNext(pos);
		switch (p->m_value->m_type)
		{
			case Type_number:
			{
				Number *pElement = new Number;
				VarMap.Insert(p->m_key, pElement);
				break;
			}
			case Type_interger:
			{
				INTERGER *pElement = new INTERGER;
				VarMap.Insert(p->m_key, pElement);
				break;
			}
			case Type_string:
			{
				String *pElement = new String;
				VarMap.Insert(p->m_key, pElement);
				break;
			}
			case Type_bool:
			{
				TBOOL *pElement = new TBOOL;
				VarMap.Insert(p->m_key, pElement);
				break;
			}
			case Type_fuzzy:
			{
				FUZZY *pElement = new FUZZY(this);
				VarMap.Insert(p->m_key, pElement);
				break;
			}
			default:
			{	if (p->m_value->m_type & Type_array)
					break;
				STRUCT *pElement = new STRUCT;
				STRUCT *pStruct = static_cast<STRUCT *>(p->m_value);
				pElement->init(*pStruct);
				VarMap.Insert(p->m_key, pElement);
				pElement->m_parent = this;
				break;
			}
		}
		if (p->m_value->m_type & Type_array)
		{
			int count = p->m_value->GetArrayCount();
			DATATYPE type = p->m_value->m_type;
			type &= ~Type_array;
			if (type < Type_struct)
				VarMap.Insert(p->m_key, new ARRAY(type, count));
			else
			{
				VarMap.Insert(p->m_key, new ARRAY(this, p->m_value->GetClassObject(), count));
			}
		}
	}
}

inline void STRUCT::Add_type(STRUCT *child, const string &name)
{
	TypeMap[name] = child;
}

inline void STRUCT::Add_var(Object *child, const string &name)
{
	VarMap.Insert(name, child);
}

inline bool STRUCT::IsBaseType(const string &name) 
{
	return name == "Number" || name == "String" || name == "bool" || name == "fuzzy" || name == "int";
}

inline bool STRUCT::CheckName_type_decl(const string &typename_)
{
	if (IsBaseType(typename_))
		return false;
	STRUCT *parent = this; 
	while (parent)
	{
		if (parent->TypeMap.Lookup(typename_))
			return false;
		parent = parent->m_parent;	
	}

	return true;
}    

inline int STRUCT::CheckName_var_decl(const string &varname)
{	
	POSITION pos = VarMap.FindFirstWithKey(varname);
	if (pos)
		return 0;
	
	for (int i = 0; i < ParamArray.GetCount(); i++)
	{
	  if (ParamArray[i]->m_name == varname)
	    return 2;
	}
	return 1;
} 
 
NODE *operator+(const NODE &t1, const NODE &t2);
NODE *operator-(const NODE &t1, const NODE &t2);
NODE *operator*(const NODE &t1, const NODE &t2);
NODE *operator/(const NODE &t1, const NODE &t2);
NODE *operator % (const NODE &t1, const NODE &t2);
bool operator>(const NODE &t1, const NODE &t2);
bool operator<(const NODE &t1, const NODE &t2);
bool operator != (const NODE &t1, const NODE &t2);
bool operator == (const NODE &t1, const NODE &t2);
bool operator >= (const NODE &t1, const NODE &t2);
bool operator <= (const NODE &t1, const NODE &t2);

inline STRUCT *STRUCT::FindClass(const string &name)
{
	STRUCT *parent = this; 
	while (parent)
	{
		SPair *p = parent->TypeMap.Lookup(name);
		if (p)
			return p->m_value;
		parent = parent->m_parent;	
	}
	
	return NULL;
}

inline STRUCT *STRUCT::FindClass(const FuzList<string> &list, NODETYPE type) 
{
	POSITION pos = list.GetHeadPosition();
	STRUCT *pclass;
	if (type == Node_type_var_rootpath)
		pclass = root;
	else
	{
		const string &classname = list.GetNext(pos);
		pclass = FindClass(classname);
		if (!pclass)
			return NULL;
	}
	  
	while (pos)
	{
		const string &name = list.GetNext(pos);
		SPair *p = pclass->TypeMap.Lookup(name);
		if (p)
			pclass = p->m_value;
		else
			return NULL;
	}
	return pclass;
}

inline double min(double a, double b)
{
	if (a < b)
		return a;
	return b;	
}

inline double max(double a, double b)
{
	if (a > b)
		return a;
	return b;	
}

inline double STRUCT::MakeFuzzyClear()
{	
	return m_fuzzy->MakeFuzzyClear();
}

inline void STRUCT::ZeroBelong() { m_fuzzy->ZeroBelong(); }


#endif	//end __CALC__
