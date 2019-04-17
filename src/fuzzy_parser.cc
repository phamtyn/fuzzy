// A Bison parser, made by GNU Bison 3.0.5.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "fuzzy_parser.cc" // lalr1.cc:406

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "fuzzy_parser.hh"

// User implementation prologue.

#line 51 "fuzzy_parser.cc" // lalr1.cc:414
// Unqualified %code blocks.
#line 61 "fuzzy_parser.yy" // lalr1.cc:415

# include "fuzzy_driver.hh"
# include <stdio.h>  /* For printf, etc. */


#line 59 "fuzzy_parser.cc" // lalr1.cc:415


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 145 "fuzzy_parser.cc" // lalr1.cc:481

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  fuzzy_parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  fuzzy_parser::fuzzy_parser (fuzzy_driver *driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  fuzzy_parser::~fuzzy_parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  fuzzy_parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  fuzzy_parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  fuzzy_parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }

  template <typename Base>
  fuzzy_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  fuzzy_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  fuzzy_parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  void
  fuzzy_parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  bool
  fuzzy_parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  fuzzy_parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  fuzzy_parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  fuzzy_parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  fuzzy_parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  fuzzy_parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  fuzzy_parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  fuzzy_parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  fuzzy_parser::by_state::by_state ()
    : state (empty_state)
  {}

  fuzzy_parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  fuzzy_parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  fuzzy_parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  fuzzy_parser::by_state::by_state (state_type s)
    : state (s)
  {}

  fuzzy_parser::symbol_number_type
  fuzzy_parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  fuzzy_parser::stack_symbol_type::stack_symbol_type ()
  {}

  fuzzy_parser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state, that.location)
  {
    value = that.value;
  }

  fuzzy_parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  fuzzy_parser::stack_symbol_type&
  fuzzy_parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  void
  fuzzy_parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  fuzzy_parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
            case 56: // BOOLEN

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.bval); }
#line 396 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 57: // "Number type"

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.dval); }
#line 403 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 58: // "int type"

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.lval); }
#line 410 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 59: // STRING

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.sval); }
#line 417 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 60: // NAME

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.sval); }
#line 424 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 61: // "String"

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.sval); }
#line 431 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 62: // "Number"

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.sval); }
#line 438 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 63: // "bool"

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.sval); }
#line 445 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 64: // "fuzzy"

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.sval); }
#line 452 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 65: // "int"

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.sval); }
#line 459 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 66: // "operator"

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.sval); }
#line 466 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 67: // "ASSIGN OPERATOR"

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_type); }
#line 473 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 68: // RELOP

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_type); }
#line 480 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 69: // REDIRECT_OP

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_type); }
#line 487 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 72: // statements

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 494 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 73: // statement

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 501 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 74: // case_statements

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 508 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 75: // case_statement

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 515 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 76: // for_init_stmt

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 522 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 77: // simple_stmt

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 529 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 80: // redirection

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 536 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 81: // opt_simple_stmt

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 543 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 82: // declares

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 550 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 83: // function_decl

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 557 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 84: // function_define

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 564 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 85: // function_call

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 571 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 86: // opt_param_list

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 578 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 87: // param_list

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 585 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 88: // datatype

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 592 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 89: // action

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 599 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 90: // declare_var

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 606 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 91: // fuzzy_params

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 613 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 92: // fuzzy_input

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 620 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 93: // declare

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 627 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 94: // if_statement

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 634 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 95: // expression_list

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 641 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 96: // opt_expression_list

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 648 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 97: // namescope

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 655 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 98: // variable_decl

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 662 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 99: // name

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 669 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 100: // variable_decl_list

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 676 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 101: // name_general

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 683 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 102: // namespace

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 690 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 103: // opt_exp

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 697 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 104: // conditional

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 704 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 105: // exp_fuzzy

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 711 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 106: // fuzzy_rule

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 718 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 107: // namespaces

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 725 "fuzzy_parser.cc" // lalr1.cc:635
        break;

      case 108: // exp

#line 146 "fuzzy_parser.yy" // lalr1.cc:635
        { yyoutput << (yysym.value.Node_ptr); }
#line 732 "fuzzy_parser.cc" // lalr1.cc:635
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  fuzzy_parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  fuzzy_parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  fuzzy_parser::yypop_ (unsigned n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  fuzzy_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  fuzzy_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  fuzzy_parser::debug_level_type
  fuzzy_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  fuzzy_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  fuzzy_parser::state_type
  fuzzy_parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  fuzzy_parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  fuzzy_parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  fuzzy_parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
    #line 54 "/home/tuyen/projects/fuzzy-1.3/src/fuzzy_parser.yy" // lalr1.cc:737
{
  // Initialize the initial location.
  yyla.location.begin.filename = yyla.location.end.filename = &driver->file;
}

#line 848 "fuzzy_parser.cc" // lalr1.cc:737

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 181 "fuzzy_parser.yy" // lalr1.cc:856
    {
		  driver->root = (yystack_[0].value.Node_ptr);
		}
#line 961 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 3:
#line 186 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = NULL; }
#line 967 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 4:
#line 189 "fuzzy_parser.yy" // lalr1.cc:856
    {
			if((yystack_[1].value.Node_ptr) == NULL)
				(yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_statements,(NODE *) NULL, yylhs.location);
			else	
				(yylhs.value.Node_ptr) = append_right((yystack_[1].value.Node_ptr), node((yystack_[0].value.Node_ptr), Node_statements,(NODE *) NULL, yystack_[0].location));
		}
#line 978 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 5:
#line 198 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr); }
#line 984 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 6:
#line 199 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_statement,(NODE *) NULL, yylhs.location);}
#line 990 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 7:
#line 201 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_K_while, (yystack_[0].value.Node_ptr), yylhs.location); }
#line 996 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 8:
#line 203 "fuzzy_parser.yy" // lalr1.cc:856
    { 
			NODE *init = (yystack_[6].value.Node_ptr);
			NODE *expr = (yystack_[4].value.Node_ptr);
			NODE *incr = (yystack_[2].value.Node_ptr);
			NODE *body = (yystack_[0].value.Node_ptr);
			NODE *head = node (init, Node_illegal, NULL, yystack_[7].location + yystack_[1].location);
			head = append_right(head, node(expr, Node_illegal, NULL, yystack_[4].location + yystack_[2].location));
			head = append_right(head, node(incr, Node_illegal, NULL, yystack_[2].location));
			(yylhs.value.Node_ptr) = node (head, Node_K_for, body, yylhs.location);
			
		}
#line 1012 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 9:
#line 215 "fuzzy_parser.yy" // lalr1.cc:856
    { 
			(yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_switch, (yystack_[4].value.Node_ptr), yylhs.location);
		}
#line 1020 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 10:
#line 219 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((NODE *)NULL, Node_K_break, (NODE *)NULL, yylhs.location); }
#line 1026 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 11:
#line 221 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((NODE *)NULL, Node_K_continue, (NODE *)NULL, yylhs.location); }
#line 1032 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 12:
#line 223 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node (node ((yystack_[2].value.lval), yystack_[2].location), Node_K_exit, (NODE *)NULL, yylhs.location); }
#line 1038 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 13:
#line 224 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1044 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 14:
#line 227 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1050 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 15:
#line 229 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr); }
#line 1056 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 16:
#line 231 "fuzzy_parser.yy" // lalr1.cc:856
    {
		    (yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_return, NULL, yylhs.location);
		}
#line 1064 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 17:
#line 235 "fuzzy_parser.yy" // lalr1.cc:856
    {
		    (yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_system, NULL, yylhs.location);
		}
#line 1072 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 18:
#line 238 "fuzzy_parser.yy" // lalr1.cc:856
    {}
#line 1078 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 19:
#line 241 "fuzzy_parser.yy" // lalr1.cc:856
    {	
			include_data data = driver->list.RemoveTail();
			yyla.location = data.loc;
			yy_delete_buffer_();
			yy_switch_to_buffer_(data.buffer);
		}
#line 1089 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 20:
#line 247 "fuzzy_parser.yy" // lalr1.cc:856
    {	
			string &newname = driver->filenames.GetTail();
			yyla.location.initialize(&newname);
			yy_switch_to_buffer_(yy_create_buffer_());
		}
#line 1099 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 21:
#line 253 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr); }
#line 1105 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 22:
#line 254 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr); }
#line 1111 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 23:
#line 258 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = NULL;	}
#line 1117 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 24:
#line 260 "fuzzy_parser.yy" // lalr1.cc:856
    { 
			if((yystack_[1].value.Node_ptr) == NULL)
			{
				(yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_illegal, NULL, yylhs.location);
			}
			else
			{
				(yylhs.value.Node_ptr) = append_right((yystack_[1].value.Node_ptr), node((yystack_[0].value.Node_ptr), Node_illegal, NULL, yylhs.location));
			}
		}
#line 1132 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 25:
#line 274 "fuzzy_parser.yy" // lalr1.cc:856
    {
			(yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_case, (yystack_[0].value.Node_ptr), yylhs.location);
		}
#line 1140 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 26:
#line 278 "fuzzy_parser.yy" // lalr1.cc:856
    { 
			(yylhs.value.Node_ptr) = node (NULL, Node_default, (yystack_[0].value.Node_ptr), yylhs.location); 	
		}
#line 1148 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 27:
#line 284 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr);	}
#line 1154 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 28:
#line 285 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); 	}
#line 1160 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 29:
#line 289 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), (yystack_[1].value.Node_type), (yystack_[0].value.Node_ptr), yylhs.location);	}
#line 1166 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 30:
#line 291 "fuzzy_parser.yy" // lalr1.cc:856
    { driver->want_redirect = true; }
#line 1172 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 31:
#line 293 "fuzzy_parser.yy" // lalr1.cc:856
    {
			driver->want_redirect = false;
			(yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_K_print, (yystack_[0].value.Node_ptr), yylhs.location); 	
		}
#line 1181 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 32:
#line 298 "fuzzy_parser.yy" // lalr1.cc:856
    { driver->want_redirect = true; }
#line 1187 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 33:
#line 300 "fuzzy_parser.yy" // lalr1.cc:856
    {
			driver->want_redirect = false;
			(yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_print_set, (yystack_[0].value.Node_ptr), yylhs.location); 	
		}
#line 1196 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 34:
#line 305 "fuzzy_parser.yy" // lalr1.cc:856
    { 
			NODE *one = node ((long)1, yystack_[0].location);
			(yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_assign_plus, one, yylhs.location);
		}
#line 1205 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 35:
#line 310 "fuzzy_parser.yy" // lalr1.cc:856
    { 
			NODE *one = node ((long)1, yystack_[0].location);
			(yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_assign_minus, one, yylhs.location);
		}
#line 1214 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 36:
#line 317 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = NULL;	}
#line 1220 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 37:
#line 319 "fuzzy_parser.yy" // lalr1.cc:856
    {
			NODE *filename = node ((yystack_[0].value.sval), yystack_[0].location);
			(yylhs.value.Node_ptr) = node (filename, (yystack_[1].value.Node_type), NULL, yylhs.location); 	
		}
#line 1229 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 38:
#line 326 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = NULL;	}
#line 1235 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 39:
#line 327 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); 	}
#line 1241 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 40:
#line 331 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = NULL;	}
#line 1247 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 41:
#line 333 "fuzzy_parser.yy" // lalr1.cc:856
    {
			if((yystack_[1].value.Node_ptr) == NULL)
				(yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_illegal, (NODE *) NULL, yylhs.location);
			else	
				(yylhs.value.Node_ptr) = append_right((yystack_[1].value.Node_ptr), node((yystack_[0].value.Node_ptr), Node_illegal,(NODE *) NULL, yystack_[0].location));
		}
#line 1258 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 42:
#line 343 "fuzzy_parser.yy" // lalr1.cc:856
    {
		NODE *func_name = node((yystack_[3].value.sval), yystack_[3].location);
		NODE *type = node(NULL, Node_type_void, NULL, yystack_[4].location);
		NODE *type_name = node(type, type->type, func_name, yystack_[4].location + yystack_[3].location);
		NODE *params = (yystack_[1].value.Node_ptr);
		(yylhs.value.Node_ptr) = node(type_name, Node_function_decl, params, yylhs.location);
	  }
#line 1270 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 43:
#line 351 "fuzzy_parser.yy" // lalr1.cc:856
    {
		NODE *func_name = node((yystack_[3].value.sval), yystack_[3].location);
		NODE *type_name = node((yystack_[4].value.Node_ptr), (yystack_[4].value.Node_ptr)->type, func_name, yystack_[4].location + yystack_[3].location);
		NODE *params = (yystack_[1].value.Node_ptr);
		(yylhs.value.Node_ptr) = node(type_name, Node_function_decl, params, yylhs.location);
	  }
#line 1281 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 44:
#line 358 "fuzzy_parser.yy" // lalr1.cc:856
    {
		NODE *func_name = node((yystack_[5].value.sval), yystack_[5].location);
		NODE *type_name = node((yystack_[6].value.Node_ptr), (yystack_[6].value.Node_ptr)->type, func_name, yystack_[6].location + yystack_[5].location);
		NODE *param = node((yystack_[2].value.Node_ptr), (yystack_[2].value.Node_ptr)->type, (yystack_[1].value.Node_ptr), yystack_[2].location + yystack_[1].location);
		param = node(param, Node_argument, NULL, yystack_[2].location + yystack_[1].location);
		(yylhs.value.Node_ptr) = node(type_name, (yystack_[4].value.Node_type), param, yylhs.location);
	  }
#line 1293 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 45:
#line 366 "fuzzy_parser.yy" // lalr1.cc:856
    {
		NODE *func_name = node((yystack_[5].value.sval), yystack_[5].location);
		NODE *type = node(NULL, Node_type_void, NULL, yystack_[6].location);
		NODE *type_name = node(type, type->type, func_name, yystack_[6].location + yystack_[5].location);
		NODE *param = node((yystack_[2].value.Node_ptr), (yystack_[2].value.Node_ptr)->type, (yystack_[1].value.Node_ptr), yystack_[2].location + yystack_[1].location);
		param = node(param, Node_argument, NULL, yystack_[2].location + yystack_[1].location);
		(yylhs.value.Node_ptr) = node(type_name, (yystack_[4].value.Node_type), param, yylhs.location);
	  }
#line 1306 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 46:
#line 375 "fuzzy_parser.yy" // lalr1.cc:856
    {
		NODE *func_name = node((yystack_[3].value.sval), yystack_[3].location);
		NODE *type_name = node((yystack_[4].value.Node_ptr), (yystack_[4].value.Node_ptr)->type, func_name, yystack_[4].location + yystack_[3].location);
		NODE *param = NULL;
		(yylhs.value.Node_ptr) = node(type_name, Node_unary_minus, param, yylhs.location);
	  }
#line 1317 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 47:
#line 385 "fuzzy_parser.yy" // lalr1.cc:856
    {
		(yylhs.value.Node_ptr) = node((yystack_[1].value.Node_ptr), Node_function_define, (yystack_[0].value.Node_ptr), yylhs.location);
	  }
#line 1325 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 48:
#line 392 "fuzzy_parser.yy" // lalr1.cc:856
    {
		NODE *namenode = node ((yystack_[3].value.sval), yystack_[3].location);
		//namenode = node (namenode, Node_illegal, NULL, @1);
		//NODE *namespace_node = namenode;
		NODE *exp_node = (yystack_[1].value.Node_ptr);
		(yylhs.value.Node_ptr) = node( namenode, Node_function, exp_node, yylhs.location);
	  }
#line 1337 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 49:
#line 402 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = NULL; }
#line 1343 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 50:
#line 403 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1349 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 51:
#line 408 "fuzzy_parser.yy" // lalr1.cc:856
    { 
		    (yylhs.value.Node_ptr) = node (node((yystack_[1].value.Node_ptr), (yystack_[1].value.Node_ptr)->type, (yystack_[0].value.Node_ptr), yylhs.location), Node_argument, NULL, yylhs.location);
		}
#line 1357 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 52:
#line 412 "fuzzy_parser.yy" // lalr1.cc:856
    {
		    (yylhs.value.Node_ptr) = append_right((yystack_[3].value.Node_ptr), node(node((yystack_[1].value.Node_ptr), (yystack_[1].value.Node_ptr)->type, (yystack_[0].value.Node_ptr), yystack_[1].location + yystack_[0].location),
				Node_argument, NULL, yylhs.location));
		}
#line 1366 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 53:
#line 419 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1372 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 54:
#line 421 "fuzzy_parser.yy" // lalr1.cc:856
    {
		    (yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_number, NULL, yylhs.location);
		}
#line 1380 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 55:
#line 425 "fuzzy_parser.yy" // lalr1.cc:856
    {
		    (yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_interger, NULL, yylhs.location);
		}
#line 1388 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 56:
#line 429 "fuzzy_parser.yy" // lalr1.cc:856
    {
		    (yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_string, NULL, yylhs.location);
		}
#line 1396 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 57:
#line 433 "fuzzy_parser.yy" // lalr1.cc:856
    {
		    (yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_bool, NULL, yylhs.location);
		}
#line 1404 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 58:
#line 437 "fuzzy_parser.yy" // lalr1.cc:856
    {
		    (yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_fuzzy, NULL, yylhs.location);
		}
#line 1412 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 59:
#line 444 "fuzzy_parser.yy" // lalr1.cc:856
    { 
			(yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr);
			if((yylhs.value.Node_ptr) != NULL)
			{
				(yylhs.value.Node_ptr)->loc = yylhs.location; (yylhs.value.Node_ptr)->type = Node_command_block;
			}
		}
#line 1424 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 60:
#line 455 "fuzzy_parser.yy" // lalr1.cc:856
    {   
		    (yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_var_decl, (yystack_[0].value.Node_ptr), yylhs.location);
		}
#line 1432 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 61:
#line 462 "fuzzy_parser.yy" // lalr1.cc:856
    {
			NODE *param = node ((yystack_[2].value.Node_ptr), Node_illegal, (yystack_[0].value.Node_ptr), yylhs.location);
			(yylhs.value.Node_ptr) = node (param, Node_illegal, NULL, yylhs.location);
		}
#line 1441 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 62:
#line 467 "fuzzy_parser.yy" // lalr1.cc:856
    {
			NODE *param = node ((yystack_[2].value.Node_ptr), Node_illegal, (yystack_[0].value.Node_ptr), yystack_[2].location + yystack_[0].location);
			(yylhs.value.Node_ptr) = append_right((yystack_[4].value.Node_ptr), node (param, Node_illegal, NULL, yystack_[2].location + yystack_[0].location));
			(yylhs.value.Node_ptr)->loc = yylhs.location;
		}
#line 1451 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 63:
#line 476 "fuzzy_parser.yy" // lalr1.cc:856
    {
			(yylhs.value.Node_ptr) = node ((yystack_[4].value.Node_ptr), Node_fuzzy_input, (yystack_[1].value.Node_ptr), yylhs.location);
		}
#line 1459 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 64:
#line 483 "fuzzy_parser.yy" // lalr1.cc:856
    {   
		    (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr);
		}
#line 1467 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 65:
#line 487 "fuzzy_parser.yy" // lalr1.cc:856
    {
		    NODE *name = node ((yystack_[4].value.sval), yystack_[4].location);
		    (yylhs.value.Node_ptr) = node (name, Node_var_decl_fuzzy_discrete, (yystack_[2].value.Node_ptr), yylhs.location);
		}
#line 1476 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 66:
#line 492 "fuzzy_parser.yy" // lalr1.cc:856
    {
		    (yylhs.value.Node_ptr) = node (node ((yystack_[4].value.sval), yystack_[4].location), Node_type_struct_declare, (yystack_[2].value.Node_ptr), yylhs.location);
		}
#line 1484 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 67:
#line 496 "fuzzy_parser.yy" // lalr1.cc:856
    {
		    NODE *name = node ((yystack_[9].value.sval), yystack_[9].location);
		    NODE *min_max = node ((yystack_[7].value.Node_ptr), Node_illegal, (yystack_[5].value.Node_ptr), yystack_[7].location + yystack_[5].location);
		    NODE *header = node (name, Node_illegal, min_max, yystack_[9].location + yystack_[4].location);
		    NODE *body = (yystack_[2].value.Node_ptr);
		    (yylhs.value.Node_ptr) = node (header, Node_type_struct_declare_fuzzy, body, yylhs.location);
		}
#line 1496 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 68:
#line 504 "fuzzy_parser.yy" // lalr1.cc:856
    {
		    NODE *name = node ((yystack_[7].value.sval), yystack_[7].location);
		    NODE *size = node ((yystack_[5].value.lval), yystack_[5].location);
		    NODE *header = node (name, Node_illegal, size, yystack_[7].location + yystack_[4].location);
		    NODE *body = (yystack_[2].value.Node_ptr);
		    (yylhs.value.Node_ptr) = node (header, Node_type_struct_declare_fuzzy_discrete, body, yylhs.location);
		}
#line 1508 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 69:
#line 512 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1514 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 70:
#line 517 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_K_if,
				node ((yystack_[0].value.Node_ptr), Node_if_branches, (NODE *)NULL, yystack_[0].location), yylhs.location); 
		}
#line 1522 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 71:
#line 521 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[4].value.Node_ptr), Node_K_if,
				node ((yystack_[2].value.Node_ptr), Node_if_branches, (yystack_[0].value.Node_ptr), yystack_[1].location + yystack_[0].location), yylhs.location); 
		}
#line 1530 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 72:
#line 527 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_expression_list, (NODE *)NULL, yylhs.location); }
#line 1536 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 73:
#line 529 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = append_right((yystack_[2].value.Node_ptr), node( (yystack_[0].value.Node_ptr), Node_expression_list, (NODE *)NULL, yystack_[0].location)); }
#line 1542 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 74:
#line 531 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = append_right((yystack_[3].value.Node_ptr), node( (yystack_[1].value.Node_ptr), Node_expression_list, (NODE *)NULL, yystack_[1].location)); }
#line 1548 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 75:
#line 535 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = NULL; }
#line 1554 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 76:
#line 536 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1560 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 77:
#line 540 "fuzzy_parser.yy" // lalr1.cc:856
    { 	(yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_var, (NODE *)NULL, yylhs.location);	}
#line 1566 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 78:
#line 542 "fuzzy_parser.yy" // lalr1.cc:856
    { 	
			(yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_var_rootpath,
			(NODE *)NULL, yylhs.location);	
		  }
#line 1575 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 79:
#line 547 "fuzzy_parser.yy" // lalr1.cc:856
    {
			(yylhs.value.Node_ptr) = append_right((yystack_[2].value.Node_ptr), node( node ((yystack_[0].value.sval), yystack_[0].location),
				Node_illegal, (NODE *)NULL, yystack_[0].location));
		  }
#line 1584 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 80:
#line 554 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node (node ((yystack_[2].value.sval), yystack_[2].location), Node_assign, (yystack_[0].value.Node_ptr), yylhs.location);	}
#line 1590 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 81:
#line 555 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1596 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 82:
#line 559 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.sval), yylhs.location);	(yylhs.value.Node_ptr)->type = Node_name; }
#line 1602 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 83:
#line 560 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node (node ((yystack_[3].value.sval), yystack_[3].location), Node_array, (yystack_[1].value.Node_ptr), yylhs.location);	}
#line 1608 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 84:
#line 564 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_illegal, NULL, yylhs.location);	}
#line 1614 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 85:
#line 566 "fuzzy_parser.yy" // lalr1.cc:856
    {
			(yylhs.value.Node_ptr) = append_right((yystack_[2].value.Node_ptr), node ((yystack_[0].value.Node_ptr), Node_illegal, NULL, yystack_[0].location));
			(yylhs.value.Node_ptr)->loc = yylhs.location;
		  }
#line 1623 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 86:
#line 573 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1629 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 87:
#line 574 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1635 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 88:
#line 578 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_namespace, NULL, yylhs.location);	}
#line 1641 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 89:
#line 580 "fuzzy_parser.yy" // lalr1.cc:856
    {
			(yylhs.value.Node_ptr) = append_right((yystack_[2].value.Node_ptr), node ((yystack_[0].value.Node_ptr), Node_namespace, NULL, yystack_[0].location));
			(yylhs.value.Node_ptr)->loc = yylhs.location;
		  }
#line 1650 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 90:
#line 588 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = NULL; }
#line 1656 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 91:
#line 590 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1662 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 92:
#line 594 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_not, NULL, yylhs.location);	}
#line 1668 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 93:
#line 597 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), (yystack_[1].value.Node_type), (yystack_[0].value.Node_ptr), yylhs.location);		}
#line 1674 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 94:
#line 599 "fuzzy_parser.yy" // lalr1.cc:856
    {
			(yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_and, (yystack_[0].value.Node_ptr), yylhs.location);	
		}
#line 1682 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 95:
#line 603 "fuzzy_parser.yy" // lalr1.cc:856
    {
			(yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_or, (yystack_[0].value.Node_ptr), yylhs.location);	
		}
#line 1690 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 96:
#line 609 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr);					}
#line 1696 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 97:
#line 610 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_or, (yystack_[0].value.Node_ptr), yylhs.location); 		}
#line 1702 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 98:
#line 611 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_and, (yystack_[0].value.Node_ptr), yylhs.location); 		}
#line 1708 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 99:
#line 612 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_really, NULL, yylhs.location);	}
#line 1714 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 100:
#line 613 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_little, NULL, yylhs.location);	}
#line 1720 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 101:
#line 614 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_very, NULL, yylhs.location);		}
#line 1726 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 102:
#line 615 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_not, NULL, yylhs.location);		}
#line 1732 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 103:
#line 616 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr); (yylhs.value.Node_ptr)->loc = yylhs.location;			}
#line 1738 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 104:
#line 621 "fuzzy_parser.yy" // lalr1.cc:856
    {
			{ (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_fuzzy_rule, (yystack_[0].value.Node_ptr), yylhs.location); 	}
		}
#line 1746 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 105:
#line 627 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), (yystack_[1].value.Node_type), (yystack_[0].value.Node_ptr), yylhs.location);	}
#line 1752 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 106:
#line 628 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr);			}
#line 1758 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 107:
#line 632 "fuzzy_parser.yy" // lalr1.cc:856
    { 
		  if((yystack_[0].value.dval) == HUGE_VALF)
		  {
		    error(yystack_[0].location,"compilation terminated.");
		    YYABORT;
		  }
		  (yylhs.value.Node_ptr) = node ((yystack_[0].value.dval), yylhs.location);
		}
#line 1771 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 108:
#line 640 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.lval), yylhs.location);		}
#line 1777 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 109:
#line 641 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.sval), yylhs.location);		}
#line 1783 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 110:
#line 642 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.bval), yylhs.location);		}
#line 1789 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 111:
#line 643 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr);			}
#line 1795 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 112:
#line 644 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr);			}
#line 1801 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 113:
#line 645 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_plus, (yystack_[0].value.Node_ptr), yylhs.location); 			}
#line 1807 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 114:
#line 646 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_minus, (yystack_[0].value.Node_ptr), yylhs.location); 			}
#line 1813 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 115:
#line 647 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_multive, (yystack_[0].value.Node_ptr), yylhs.location); 		}
#line 1819 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 116:
#line 648 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_quotient, (yystack_[0].value.Node_ptr), yylhs.location); 		}
#line 1825 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 117:
#line 649 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_mod, (yystack_[0].value.Node_ptr), yylhs.location); 		}
#line 1831 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 118:
#line 650 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_unary_minus, (NODE *)NULL, yylhs.location); 	}
#line 1837 "fuzzy_parser.cc" // lalr1.cc:856
    break;

  case 119:
#line 651 "fuzzy_parser.yy" // lalr1.cc:856
    { (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr); (yylhs.value.Node_ptr)->loc = yylhs.location;                     		   	}
#line 1843 "fuzzy_parser.cc" // lalr1.cc:856
    break;


#line 1847 "fuzzy_parser.cc" // lalr1.cc:856
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  fuzzy_parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  fuzzy_parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int fuzzy_parser::yypact_ninf_ = -188;

  const signed char fuzzy_parser::yytable_ninf_ = -78;

  const short int
  fuzzy_parser::yypact_[] =
  {
    -188,    10,   413,  -188,  -188,     1,    63,    55,    61,  -188,
      26,    79,  -188,    88,   121,  -188,  -188,   -21,    87,   104,
     146,   121,    98,  -188,    36,   178,  -188,  -188,  -188,   115,
    -188,  -188,   149,   155,  -188,  -188,   -14,  -188,   159,   160,
    -188,  -188,   192,  -188,  -188,   239,   208,   132,   121,   121,
    -188,  -188,   360,   196,   224,  -188,   121,   121,   121,  -188,
    -188,  -188,  -188,    35,   -16,   218,  -188,  -188,   289,   240,
     180,   194,   403,   121,    30,   126,   132,    36,    36,    36,
      36,    36,    83,  -188,   132,   121,   195,  -188,  -188,    64,
       2,  -188,  -188,   247,  -188,  -188,   200,  -188,    98,  -188,
    -188,   121,  -188,   132,    -1,   289,   102,   140,  -188,  -188,
     312,  -188,   162,  -188,   121,  -188,   121,   121,   121,   121,
     121,   121,   121,   121,   445,   266,   261,  -188,   258,  -188,
    -188,   230,  -188,     8,   207,  -188,   283,    -1,   106,  -188,
    -188,  -188,  -188,    98,    36,    36,   292,   298,   215,   297,
     445,   121,   310,   311,   230,  -188,  -188,   289,   309,   162,
     121,   263,  -188,   413,   413,   459,   317,   221,  -188,   289,
     199,   199,  -188,  -188,  -188,    24,    19,   330,  -188,   318,
     316,   269,   445,   315,   121,     9,   320,   121,  -188,  -188,
     321,  -188,   290,  -188,  -188,   121,   337,   289,   338,   445,
    -188,   121,   289,  -188,   333,  -188,   327,  -188,   332,   121,
    -188,   445,   323,  -188,   269,  -188,   331,  -188,   184,   296,
     190,  -188,  -188,   269,   262,   413,  -188,  -188,   273,   269,
     344,    34,    59,  -188,   121,   121,   335,   346,  -188,  -188,
     466,   340,  -188,  -188,   347,  -188,   121,   319,  -188,   307,
     227,  -188,  -188,   339,  -188,   413,   281,  -188,   121,  -188,
     473,  -188,  -188,   413,   228,   342,   413,  -188
  };

  const unsigned char
  fuzzy_parser::yydefact_[] =
  {
       3,     0,     2,     1,    30,     0,     0,     0,     0,     3,
       0,     0,    18,     0,    90,    19,    20,     0,     0,     0,
       0,     0,     0,    32,     0,    82,    56,    54,    57,    58,
      55,     4,     0,     0,    69,    86,     0,    13,     0,     0,
      14,     6,    53,    87,    88,     0,     0,     0,     0,     0,
      10,    11,     0,     0,     0,    78,     0,     0,     0,   110,
     107,   108,   109,    82,   106,     0,   111,   112,    91,     0,
       0,     0,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,    75,     0,     0,     5,    47,    82,
       0,    84,    81,    60,    64,    22,     0,    15,     0,    34,
      35,     0,    21,     0,    36,    72,     0,     0,    59,    40,
       0,   118,     0,    92,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,    49,     0,     0,    58,     0,    39,
      28,     0,    27,     0,     0,    17,     0,    36,     0,   102,
     101,   100,    99,     0,     0,     0,    76,     0,     0,     0,
      49,     0,     0,     0,     0,    79,    89,    29,     0,    72,
       0,     0,    31,     0,     0,     0,   108,     0,   119,   105,
     114,   113,   115,   116,   117,    94,    95,    93,    77,     0,
      50,     0,     0,     0,    90,    82,     0,     0,    33,   103,
     104,    98,    97,    48,    83,     0,     0,    80,     0,     0,
      85,     0,    73,    37,    70,     7,     0,    41,     0,     0,
      42,     0,    82,    51,     0,    12,     0,    23,     0,     0,
       0,    43,    46,     0,    73,     0,    66,    40,     0,     0,
       0,    38,     0,    63,     0,     0,     0,     0,    74,    71,
       0,     0,    52,    45,     0,     9,     0,     0,    24,     0,
     116,    65,    44,     0,    40,     0,     0,     3,     0,    68,
       0,     8,     3,    26,   116,     0,    25,    67
  };

  const short int
  fuzzy_parser::yypgoto_[] =
  {
    -188,  -188,    -8,  -151,  -188,  -188,  -188,   -68,  -188,  -188,
     223,   135,  -187,  -188,  -188,  -188,   213,  -188,   -69,   334,
     322,   189,  -188,  -163,  -188,    52,  -188,  -188,   235,   -29,
    -188,   294,    -2,   206,  -188,   -62,  -188,   -18,     0
  };

  const short int
  fuzzy_parser::yydefgoto_[] =
  {
      -1,     1,     2,    31,   232,   248,   128,    32,    47,    76,
     162,   130,   165,    33,    34,    35,   179,   180,    36,    37,
      38,   218,    39,    40,    41,   104,   147,    42,    91,    43,
      93,    44,    64,    65,    66,    82,    46,    67,   105
  };

  const short int
  fuzzy_parser::yytable_[] =
  {
      45,    52,   207,   131,   129,   152,    83,    92,    98,    48,
       3,   160,   204,   205,    68,   138,   139,   140,   141,   142,
      75,    74,   116,   117,   118,   119,   120,   116,   117,   118,
     119,   120,    98,   116,   117,   118,   119,   120,    85,    69,
     240,    99,   100,    84,    77,    70,    89,     4,   106,   107,
      45,   114,    90,   135,   121,   181,   111,   112,   113,    83,
      83,    83,    83,    83,    85,   121,   122,   260,   161,   153,
     133,    49,   150,   134,   239,   101,   151,   207,    50,   245,
      23,   181,   191,   192,    51,   148,    53,   123,    78,    79,
      80,    81,   123,    85,    63,    71,    63,   207,   123,   246,
     247,   157,    92,   159,   261,   116,   117,   118,   119,   120,
     167,   163,    72,   214,   169,   189,   170,   171,   172,   173,
     174,   175,   176,   177,    56,    92,    83,    83,   137,    57,
     223,   151,   143,   144,   145,    56,   146,   121,   122,    54,
     103,   190,   229,   116,   117,   118,   119,   120,    55,   164,
      98,   197,   213,    58,    73,   158,   144,   145,    63,    86,
     202,    45,    45,   129,    58,   116,   117,   118,   119,   120,
     123,   168,    87,   136,     9,   121,   122,    59,    60,    61,
      62,    63,    94,    95,    68,   230,    84,   219,    59,    60,
      61,    62,    63,   233,   237,   219,   234,   121,   122,   236,
     242,   224,   234,   -77,   118,   119,   120,    85,   123,   228,
     116,   117,   118,   119,   120,   109,   186,    96,   116,   117,
     118,   119,   120,    45,   116,   117,   118,   119,   120,   133,
     123,   102,   110,   209,   249,   250,   -61,   -62,   -77,   -61,
     -62,   115,   121,   122,   -77,   194,   256,   125,   124,   263,
     121,   122,   126,    45,   266,   149,   121,   122,   264,   154,
     155,    45,    97,    98,    45,   116,   117,   118,   119,   120,
     183,   238,    99,   100,   182,   123,   116,   117,   118,   119,
     120,   184,   241,   123,   116,   117,   118,   119,   120,   123,
     185,   187,   116,   117,   118,   119,   120,   121,   122,   116,
     117,   118,   235,   120,   160,   195,   101,   193,   121,   122,
     116,   117,   118,   258,   120,    56,   121,   122,   198,   199,
      57,   201,   203,   262,   121,   122,   208,   210,   211,   212,
     123,   121,   122,   116,   117,   118,   119,   120,   215,   217,
     144,   123,   121,   122,    58,    98,   221,   222,   225,   123,
     226,   227,    85,   243,   231,   252,   255,   123,   251,   254,
     188,   257,   259,   196,   123,   267,   244,    88,    59,    60,
     166,    62,    63,     4,     5,   123,     6,     7,     8,     9,
     108,    10,    11,    12,   220,    13,    14,    15,    16,   200,
     216,    17,   156,     0,   132,     0,     0,    18,    19,    20,
       0,     0,     0,    21,     0,    22,    23,     0,    24,     0,
       0,     0,     0,     0,     0,     0,     4,     0,     0,     0,
      25,    26,    27,    28,    29,    30,     4,     5,    13,     6,
       7,     8,     9,     0,    10,    11,    12,     0,    13,    14,
      15,    16,     0,     0,    17,     0,     0,     0,     0,    23,
      18,    19,    20,     0,     0,     0,    21,     0,    22,    23,
       0,    24,     0,    25,    26,    27,    28,   127,    30,     0,
      13,     0,     0,    25,    26,    27,    28,    29,    30,   206,
      10,    11,     0,     0,    13,     0,   253,    10,    11,     0,
      17,    13,     0,   265,    10,    11,     0,    17,    13,     0,
       0,     0,     0,     0,    17,   178,    26,    27,    28,   127,
      30,     0,     0,     0,     0,     0,     0,     0,     0,   178,
      26,    27,    28,    29,    30,     0,   178,    26,    27,    28,
      29,    30,     0,   178,    26,    27,    28,    29,    30
  };

  const short int
  fuzzy_parser::yycheck_[] =
  {
       2,     9,   165,    72,    72,     3,    24,    36,    24,     8,
       0,    12,   163,   164,    14,    77,    78,    79,    80,    81,
      22,    21,     3,     4,     5,     6,     7,     3,     4,     5,
       6,     7,    24,     3,     4,     5,     6,     7,    29,    60,
     227,    33,    34,     8,     8,    66,    60,    13,    48,    49,
      52,    67,    66,    23,    35,   124,    56,    57,    58,    77,
      78,    79,    80,    81,    29,    35,    36,   254,    69,    67,
      72,     8,     8,    73,   225,    67,    67,   240,    23,    20,
      46,   150,   144,   145,    23,    85,    60,    68,    52,    53,
      54,    55,    68,    29,    60,     8,    60,   260,    68,    40,
      41,   101,   131,   103,   255,     3,     4,     5,     6,     7,
     110,     9,     8,   182,   114,     9,   116,   117,   118,   119,
     120,   121,   122,   123,     3,   154,   144,   145,    76,     8,
     199,    67,    49,    50,    51,     3,    84,    35,    36,    60,
       8,   143,   211,     3,     4,     5,     6,     7,    60,     9,
      24,   151,   181,    32,     8,   103,    50,    51,    60,    44,
     160,   163,   164,   231,    32,     3,     4,     5,     6,     7,
      68,     9,    23,    47,    19,    35,    36,    56,    57,    58,
      59,    60,    23,    23,   184,   214,     8,   187,    56,    57,
      58,    59,    60,     9,   223,   195,    12,    35,    36,     9,
     229,   201,    12,    25,     5,     6,     7,    29,    68,   209,
       3,     4,     5,     6,     7,    19,     9,    25,     3,     4,
       5,     6,     7,   225,     3,     4,     5,     6,     7,   231,
      68,    23,     8,    12,   234,   235,     9,     9,    60,    12,
      12,    23,    35,    36,    66,    30,   246,    67,     8,   257,
      35,    36,    58,   255,   262,    60,    35,    36,   258,    12,
      60,   263,    23,    24,   266,     3,     4,     5,     6,     7,
       9,     9,    33,    34,     8,    68,     3,     4,     5,     6,
       7,    23,     9,    68,     3,     4,     5,     6,     7,    68,
      60,     8,     3,     4,     5,     6,     7,    35,    36,     3,
       4,     5,     6,     7,    12,     8,    67,     9,    35,    36,
       3,     4,     5,     6,     7,     3,    35,    36,     8,     8,
       8,    12,    59,    42,    35,    36,     9,     9,    12,    60,
      68,    35,    36,     3,     4,     5,     6,     7,    23,    19,
      50,    68,    35,    36,    32,    24,     9,     9,    15,    68,
      23,    19,    29,     9,    23,     9,     9,    68,    23,    19,
     137,    42,    23,   150,    68,    23,   231,    33,    56,    57,
      58,    59,    60,    13,    14,    68,    16,    17,    18,    19,
      20,    21,    22,    23,   195,    25,    26,    27,    28,   154,
     184,    31,    98,    -1,    72,    -1,    -1,    37,    38,    39,
      -1,    -1,    -1,    43,    -1,    45,    46,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    13,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    13,    14,    25,    16,
      17,    18,    19,    -1,    21,    22,    23,    -1,    25,    26,
      27,    28,    -1,    -1,    31,    -1,    -1,    -1,    -1,    46,
      37,    38,    39,    -1,    -1,    -1,    43,    -1,    45,    46,
      -1,    48,    -1,    60,    61,    62,    63,    64,    65,    -1,
      25,    -1,    -1,    60,    61,    62,    63,    64,    65,    20,
      21,    22,    -1,    -1,    25,    -1,    20,    21,    22,    -1,
      31,    25,    -1,    20,    21,    22,    -1,    31,    25,    -1,
      -1,    -1,    -1,    -1,    31,    60,    61,    62,    63,    64,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    62,    63,    64,    65,    -1,    60,    61,    62,    63,
      64,    65,    -1,    60,    61,    62,    63,    64,    65
  };

  const unsigned char
  fuzzy_parser::yystos_[] =
  {
       0,    71,    72,     0,    13,    14,    16,    17,    18,    19,
      21,    22,    23,    25,    26,    27,    28,    31,    37,    38,
      39,    43,    45,    46,    48,    60,    61,    62,    63,    64,
      65,    73,    77,    83,    84,    85,    88,    89,    90,    92,
      93,    94,    97,    99,   101,   102,   106,    78,     8,     8,
      23,    23,    72,    60,    60,    60,     3,     8,    32,    56,
      57,    58,    59,    60,   102,   103,   104,   107,   108,    60,
      66,     8,     8,     8,   108,   102,    79,     8,    52,    53,
      54,    55,   105,   107,     8,    29,    44,    23,    89,    60,
      66,    98,    99,   100,    23,    23,    25,    23,    24,    33,
      34,    67,    23,     8,    95,   108,   108,   108,    20,    19,
       8,   108,   108,   108,    67,    23,     3,     4,     5,     6,
       7,    35,    36,    68,     8,    67,    58,    64,    76,    77,
      81,    88,    90,   102,   108,    23,    47,    95,   105,   105,
     105,   105,   105,    49,    50,    51,    95,    96,   108,    60,
       8,    67,     3,    67,    12,    60,   101,   108,    95,   108,
      12,    69,    80,     9,     9,    82,    58,   108,     9,   108,
     108,   108,   108,   108,   108,   108,   108,   108,    60,    86,
      87,    88,     8,     9,    23,    60,     9,     8,    80,     9,
     102,   105,   105,     9,    30,     8,    86,   108,     8,     8,
      98,    12,   108,    59,    73,    73,    20,    93,     9,    12,
       9,    12,    60,    99,    88,    23,   103,    19,    91,   108,
      91,     9,     9,    88,   108,    15,    23,    19,   108,    88,
      99,    23,    74,     9,    12,     6,     9,    99,     9,    73,
      82,     9,    99,     9,    81,    20,    40,    41,    75,   108,
     108,    23,     9,    20,    19,     9,   108,    42,     6,    23,
      82,    73,    42,    72,   108,    20,    72,    23
  };

  const unsigned char
  fuzzy_parser::yyr1_[] =
  {
       0,    70,    71,    72,    72,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    74,    74,    75,    75,    76,    76,    77,
      78,    77,    79,    77,    77,    77,    80,    80,    81,    81,
      82,    82,    83,    83,    83,    83,    83,    84,    85,    86,
      86,    87,    87,    88,    88,    88,    88,    88,    88,    89,
      90,    91,    91,    92,    93,    93,    93,    93,    93,    93,
      94,    94,    95,    95,    95,    96,    96,    97,    97,    97,
      98,    98,    99,    99,   100,   100,   101,   101,   102,   102,
     103,   103,   104,   104,   104,   104,   105,   105,   105,   105,
     105,   105,   105,   105,   106,   107,   107,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108
  };

  const unsigned char
  fuzzy_parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     2,     1,     5,     9,     7,
       2,     2,     5,     1,     1,     2,     3,     3,     1,     1,
       1,     2,     2,     0,     2,     4,     3,     1,     1,     3,
       0,     4,     0,     4,     2,     2,     0,     2,     0,     1,
       0,     2,     5,     5,     7,     7,     5,     2,     4,     0,
       1,     2,     4,     1,     1,     1,     1,     1,     1,     3,
       2,     3,     5,     6,     2,     7,     6,    11,     9,     1,
       5,     7,     1,     3,     5,     0,     1,     1,     2,     3,
       3,     1,     1,     4,     1,     3,     1,     1,     1,     3,
       0,     1,     2,     3,     3,     3,     1,     3,     3,     2,
       2,     2,     2,     3,     4,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     2,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const fuzzy_parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"-\"", "\"+\"", "\"*\"",
  "\"/\"", "\"%\"", "\"(\"", "\")\"", "\"^\"", "\"NEG\"", "\",\"",
  "\"print\"", "\"if\"", "\"else\"", "\"while\"", "\"break\"",
  "\"continue\"", "\"{\"", "\"}\"", "\"struct\"", "\"term\"", "\";\"",
  "\".\"", "\"::\"", "\"return\"", "\"end of include file\"",
  "\"switch to include file\"", "\"[\"", "\"]\"", "\"void\"", "\"!\"",
  "\"++\"", "\"--\"", "\"&&\"", "\"||\"", "\"exit\"", "\"for\"",
  "\"switch\"", "\"case\"", "\"default\"", "\":\"", "\"system\"",
  "\"discrete\"", "\"put\"", "\"prints\"", "\":=\"", "\"rule\"", "\"=>\"",
  "\"AND\"", "\"OR\"", "\"NOT\"", "\"VERY\"", "\"LITTLE\"", "\"REALLY\"",
  "BOOLEN", "\"Number type\"", "\"int type\"", "STRING", "NAME",
  "\"String\"", "\"Number\"", "\"bool\"", "\"fuzzy\"", "\"int\"",
  "\"operator\"", "\"ASSIGN OPERATOR\"", "RELOP", "REDIRECT_OP", "$accept",
  "unit", "statements", "statement", "case_statements", "case_statement",
  "for_init_stmt", "simple_stmt", "$@1", "$@2", "redirection",
  "opt_simple_stmt", "declares", "function_decl", "function_define",
  "function_call", "opt_param_list", "param_list", "datatype", "action",
  "declare_var", "fuzzy_params", "fuzzy_input", "declare", "if_statement",
  "expression_list", "opt_expression_list", "namescope", "variable_decl",
  "name", "variable_decl_list", "name_general", "namespace", "opt_exp",
  "conditional", "exp_fuzzy", "fuzzy_rule", "namespaces", "exp", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  fuzzy_parser::yyrline_[] =
  {
       0,   180,   180,   186,   188,   198,   199,   200,   202,   214,
     218,   220,   222,   224,   226,   228,   230,   234,   238,   240,
     247,   253,   254,   258,   259,   273,   277,   284,   285,   289,
     291,   290,   298,   297,   304,   309,   317,   318,   326,   327,
     331,   332,   342,   350,   357,   365,   374,   384,   391,   402,
     403,   407,   411,   419,   420,   424,   428,   432,   436,   443,
     454,   461,   466,   475,   482,   486,   491,   495,   503,   511,
     516,   520,   527,   528,   530,   535,   536,   540,   541,   546,
     554,   555,   559,   560,   564,   565,   573,   574,   578,   579,
     587,   589,   594,   597,   598,   602,   609,   610,   611,   612,
     613,   614,   615,   616,   620,   627,   628,   632,   640,   641,
     642,   643,   644,   645,   646,   647,   648,   649,   650,   651
  };

  // Print the state stack on the debug stream.
  void
  fuzzy_parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  fuzzy_parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  fuzzy_parser::token_number_type
  fuzzy_parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
    };
    const unsigned user_token_number_max_ = 324;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 2503 "fuzzy_parser.cc" // lalr1.cc:1163
#line 656 "fuzzy_parser.yy" // lalr1.cc:1164

void
yy::fuzzy_parser::error (const location_type& l,
                          const std::string& m)
{
  driver->error (l, m);
}
