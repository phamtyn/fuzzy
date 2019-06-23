// A Bison parser, made by GNU Bison 3.2.2.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "fuzzy_parser.hh"


// Unqualified %code blocks.
#line 61 "fuzzy_parser.yy" // lalr1.cc:438

# include "fuzzy_driver.hh"
# include <stdio.h>  /* For printf, etc. */


#line 51 "fuzzy_parser.cc" // lalr1.cc:438


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

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
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
#line 146 "fuzzy_parser.cc" // lalr1.cc:513

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
    , location ()
  {}

  template <typename Base>
  fuzzy_parser::basic_symbol<Base>::basic_symbol (YY_RVREF (basic_symbol) other)
    : Base (YY_MOVE (other))
    , value (YY_MOVE (other.value))
    , location (YY_MOVE (other.location))
  {
  }


  /// Constructor for valueless symbols.
  template <typename Base>
  fuzzy_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  fuzzy_parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
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
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
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

  fuzzy_parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  fuzzy_parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  fuzzy_parser::stack_symbol_type&
  fuzzy_parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

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
            case 59: // BOOLEN

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.bval); }
#line 403 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 60: // "Number type"

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.dval); }
#line 410 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 61: // "int type"

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.lval); }
#line 417 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 62: // STRING

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.sval); }
#line 424 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 63: // NAME

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.sval); }
#line 431 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 64: // "String"

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.sval); }
#line 438 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 65: // "Number"

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.sval); }
#line 445 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 66: // "bool"

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.sval); }
#line 452 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 67: // "fuzzy"

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.sval); }
#line 459 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 68: // "int"

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.sval); }
#line 466 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 69: // "operator"

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.sval); }
#line 473 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 70: // "ASSIGN OPERATOR"

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_type); }
#line 480 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 71: // RELOP

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_type); }
#line 487 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 72: // REDIRECT_OP

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_type); }
#line 494 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 75: // statements

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 501 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 76: // statement

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 508 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 77: // case_statements

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 515 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 78: // case_statement

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 522 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 79: // for_init_stmt

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 529 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 80: // simple_stmt

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 536 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 83: // redirection

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 543 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 84: // opt_simple_stmt

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 550 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 85: // declares

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 557 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 86: // function_decl

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 564 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 87: // function_define

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 571 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 88: // function_call

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 578 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 89: // opt_param_list

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 585 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 90: // param_list

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 592 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 91: // datatype

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 599 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 92: // action

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 606 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 93: // declare_var

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 613 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 94: // fuzzy_params

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 620 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 95: // fuzzy_input

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 627 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 96: // declare

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 634 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 97: // if_statement

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 641 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 98: // expression_list

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 648 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 99: // opt_expression_list

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 655 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 100: // namescope

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 662 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 101: // variable_decl

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 669 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 102: // name

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 676 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 103: // variable_decl_list

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 683 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 104: // name_general

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 690 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 105: // namespace

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 697 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 106: // opt_exp

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 704 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 107: // conditional

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 711 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 108: // exp_fuzzy

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 718 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 109: // fuzzy_rule

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 725 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 110: // namespaces

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 732 "fuzzy_parser.cc" // lalr1.cc:672
        break;

      case 111: // exp

#line 149 "fuzzy_parser.yy" // lalr1.cc:672
        { yyoutput << (yysym.value.Node_ptr); }
#line 739 "fuzzy_parser.cc" // lalr1.cc:672
        break;


      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  fuzzy_parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  fuzzy_parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  fuzzy_parser::yypop_ (int n)
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
  fuzzy_parser::operator() ()
  {
    return parse ();
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 54 "fuzzy_parser.yy" // lalr1.cc:784
{
  // Initialize the initial location.
  yyla.location.begin.filename = yyla.location.end.filename = &driver->file;
}

#line 865 "fuzzy_parser.cc" // lalr1.cc:784

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

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
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, driver));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
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
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
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
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 187 "fuzzy_parser.yy" // lalr1.cc:907
    {
		  driver->root = (yystack_[0].value.Node_ptr);
		}
#line 983 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 3:
#line 192 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = NULL; }
#line 989 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 4:
#line 195 "fuzzy_parser.yy" // lalr1.cc:907
    {
			if((yystack_[1].value.Node_ptr) == NULL)
				(yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_statements,(NODE *) NULL, yylhs.location);
			else	
				(yylhs.value.Node_ptr) = append_right((yystack_[1].value.Node_ptr), node((yystack_[0].value.Node_ptr), Node_statements,(NODE *) NULL, yystack_[0].location));
		}
#line 1000 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 5:
#line 204 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr); }
#line 1006 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 6:
#line 205 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_statement,(NODE *) NULL, yylhs.location);}
#line 1012 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 7:
#line 207 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_K_while, (yystack_[0].value.Node_ptr), yylhs.location); }
#line 1018 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 8:
#line 209 "fuzzy_parser.yy" // lalr1.cc:907
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
#line 1034 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 9:
#line 221 "fuzzy_parser.yy" // lalr1.cc:907
    { 
			(yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_switch, (yystack_[4].value.Node_ptr), yylhs.location);
		}
#line 1042 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 10:
#line 225 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((NODE *)NULL, Node_K_break, (NODE *)NULL, yylhs.location); }
#line 1048 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 11:
#line 227 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((NODE *)NULL, Node_K_continue, (NODE *)NULL, yylhs.location); }
#line 1054 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 12:
#line 229 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_K_exit, (NODE *)NULL, yylhs.location); }
#line 1060 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 13:
#line 230 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1066 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 14:
#line 233 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1072 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 15:
#line 235 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr); }
#line 1078 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 16:
#line 237 "fuzzy_parser.yy" // lalr1.cc:907
    {
		    (yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_return, NULL, yylhs.location);
		}
#line 1086 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 17:
#line 241 "fuzzy_parser.yy" // lalr1.cc:907
    {
		    (yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_system, NULL, yylhs.location);
		}
#line 1094 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 18:
#line 244 "fuzzy_parser.yy" // lalr1.cc:907
    {}
#line 1100 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 19:
#line 247 "fuzzy_parser.yy" // lalr1.cc:907
    {	
			include_data data = driver->list.RemoveTail();
			yyla.location = data.loc;
			yy_delete_buffer_();
			yy_switch_to_buffer_(data.buffer);
		}
#line 1111 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 20:
#line 253 "fuzzy_parser.yy" // lalr1.cc:907
    {	
			string &newname = driver->filenames.GetTail();
			yyla.location.initialize(&newname);
			yy_switch_to_buffer_(yy_create_buffer_());
		}
#line 1121 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 21:
#line 259 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr); }
#line 1127 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 22:
#line 260 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr); }
#line 1133 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 23:
#line 264 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = NULL;	}
#line 1139 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 24:
#line 266 "fuzzy_parser.yy" // lalr1.cc:907
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
#line 1154 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 25:
#line 280 "fuzzy_parser.yy" // lalr1.cc:907
    {
			(yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_case, (yystack_[0].value.Node_ptr), yylhs.location);
		}
#line 1162 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 26:
#line 284 "fuzzy_parser.yy" // lalr1.cc:907
    { 
			(yylhs.value.Node_ptr) = node (NULL, Node_default, (yystack_[0].value.Node_ptr), yylhs.location); 	
		}
#line 1170 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 27:
#line 290 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr);	}
#line 1176 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 28:
#line 291 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); 	}
#line 1182 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 29:
#line 295 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), (yystack_[1].value.Node_type), (yystack_[0].value.Node_ptr), yylhs.location);	}
#line 1188 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 30:
#line 297 "fuzzy_parser.yy" // lalr1.cc:907
    { driver->want_redirect = true; }
#line 1194 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 31:
#line 299 "fuzzy_parser.yy" // lalr1.cc:907
    {
			driver->want_redirect = false;
			(yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_K_print, (yystack_[0].value.Node_ptr), yylhs.location); 	
		}
#line 1203 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 32:
#line 304 "fuzzy_parser.yy" // lalr1.cc:907
    { driver->want_redirect = true; }
#line 1209 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 33:
#line 306 "fuzzy_parser.yy" // lalr1.cc:907
    {
			driver->want_redirect = false;
			(yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_print_set, (yystack_[0].value.Node_ptr), yylhs.location); 	
		}
#line 1218 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 34:
#line 311 "fuzzy_parser.yy" // lalr1.cc:907
    { 
			NODE *one = node ((long)1, yystack_[0].location);
			(yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_assign_plus, one, yylhs.location);
		}
#line 1227 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 35:
#line 316 "fuzzy_parser.yy" // lalr1.cc:907
    { 
			NODE *one = node ((long)1, yystack_[0].location);
			(yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_assign_minus, one, yylhs.location);
		}
#line 1236 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 36:
#line 323 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = NULL;	}
#line 1242 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 37:
#line 325 "fuzzy_parser.yy" // lalr1.cc:907
    {
			NODE *filename = node ((yystack_[0].value.sval), yystack_[0].location);
			(yylhs.value.Node_ptr) = node (filename, (yystack_[1].value.Node_type), NULL, yylhs.location); 	
		}
#line 1251 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 38:
#line 332 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = NULL;	}
#line 1257 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 39:
#line 333 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); 	}
#line 1263 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 40:
#line 337 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = NULL;	}
#line 1269 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 41:
#line 339 "fuzzy_parser.yy" // lalr1.cc:907
    {
			if((yystack_[1].value.Node_ptr) == NULL)
				(yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_illegal, (NODE *) NULL, yylhs.location);
			else	
				(yylhs.value.Node_ptr) = append_right((yystack_[1].value.Node_ptr), node((yystack_[0].value.Node_ptr), Node_illegal,(NODE *) NULL, yystack_[0].location));
		}
#line 1280 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 42:
#line 349 "fuzzy_parser.yy" // lalr1.cc:907
    {
		NODE *func_name = node((yystack_[3].value.sval), yystack_[3].location);
		NODE *type = node(NULL, Node_type_void, NULL, yystack_[4].location);
		NODE *type_name = node(type, type->type, func_name, yystack_[4].location + yystack_[3].location);
		NODE *params = (yystack_[1].value.Node_ptr);
		(yylhs.value.Node_ptr) = node(type_name, Node_function_decl, params, yylhs.location);
	  }
#line 1292 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 43:
#line 357 "fuzzy_parser.yy" // lalr1.cc:907
    {
		NODE *func_name = node((yystack_[3].value.sval), yystack_[3].location);
		NODE *type_name = node((yystack_[4].value.Node_ptr), (yystack_[4].value.Node_ptr)->type, func_name, yystack_[4].location + yystack_[3].location);
		NODE *params = (yystack_[1].value.Node_ptr);
		(yylhs.value.Node_ptr) = node(type_name, Node_function_decl, params, yylhs.location);
	  }
#line 1303 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 44:
#line 364 "fuzzy_parser.yy" // lalr1.cc:907
    {
		NODE *func_name = node((yystack_[5].value.sval), yystack_[5].location);
		NODE *type_name = node((yystack_[6].value.Node_ptr), (yystack_[6].value.Node_ptr)->type, func_name, yystack_[6].location + yystack_[5].location);
		NODE *param = node((yystack_[2].value.Node_ptr), (yystack_[2].value.Node_ptr)->type, (yystack_[1].value.Node_ptr), yystack_[2].location + yystack_[1].location);
		param = node(param, Node_argument, NULL, yystack_[2].location + yystack_[1].location);
		(yylhs.value.Node_ptr) = node(type_name, (yystack_[4].value.Node_type), param, yylhs.location);
	  }
#line 1315 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 45:
#line 372 "fuzzy_parser.yy" // lalr1.cc:907
    {
		NODE *func_name = node((yystack_[5].value.sval), yystack_[5].location);
		NODE *type = node(NULL, Node_type_void, NULL, yystack_[6].location);
		NODE *type_name = node(type, type->type, func_name, yystack_[6].location + yystack_[5].location);
		NODE *param = node((yystack_[2].value.Node_ptr), (yystack_[2].value.Node_ptr)->type, (yystack_[1].value.Node_ptr), yystack_[2].location + yystack_[1].location);
		param = node(param, Node_argument, NULL, yystack_[2].location + yystack_[1].location);
		(yylhs.value.Node_ptr) = node(type_name, (yystack_[4].value.Node_type), param, yylhs.location);
	  }
#line 1328 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 46:
#line 381 "fuzzy_parser.yy" // lalr1.cc:907
    {
		NODE *func_name = node((yystack_[3].value.sval), yystack_[3].location);
		NODE *type_name = node((yystack_[4].value.Node_ptr), (yystack_[4].value.Node_ptr)->type, func_name, yystack_[4].location + yystack_[3].location);
		NODE *param = NULL;
		(yylhs.value.Node_ptr) = node(type_name, Node_unary_minus, param, yylhs.location);
	  }
#line 1339 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 47:
#line 391 "fuzzy_parser.yy" // lalr1.cc:907
    {
		(yylhs.value.Node_ptr) = node((yystack_[1].value.Node_ptr), Node_function_define, (yystack_[0].value.Node_ptr), yylhs.location);
	  }
#line 1347 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 48:
#line 398 "fuzzy_parser.yy" // lalr1.cc:907
    {
		NODE *namenode = node ((yystack_[3].value.sval), yystack_[3].location);
		//namenode = node (namenode, Node_illegal, NULL, @1);
		//NODE *namespace_node = namenode;
		NODE *exp_node = (yystack_[1].value.Node_ptr);
		(yylhs.value.Node_ptr) = node( namenode, Node_function, exp_node, yylhs.location);
	  }
#line 1359 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 49:
#line 408 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = NULL; }
#line 1365 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 50:
#line 409 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1371 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 51:
#line 414 "fuzzy_parser.yy" // lalr1.cc:907
    { 
		    (yylhs.value.Node_ptr) = node (node((yystack_[1].value.Node_ptr), (yystack_[1].value.Node_ptr)->type, (yystack_[0].value.Node_ptr), yylhs.location), Node_argument, NULL, yylhs.location);
		}
#line 1379 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 52:
#line 418 "fuzzy_parser.yy" // lalr1.cc:907
    {
		    (yylhs.value.Node_ptr) = append_right((yystack_[3].value.Node_ptr), node(node((yystack_[1].value.Node_ptr), (yystack_[1].value.Node_ptr)->type, (yystack_[0].value.Node_ptr), yystack_[1].location + yystack_[0].location),
				Node_argument, NULL, yylhs.location));
		}
#line 1388 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 53:
#line 425 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1394 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 54:
#line 427 "fuzzy_parser.yy" // lalr1.cc:907
    {
		    (yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_number, NULL, yylhs.location);
		}
#line 1402 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 55:
#line 431 "fuzzy_parser.yy" // lalr1.cc:907
    {
		    (yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_interger, NULL, yylhs.location);
		}
#line 1410 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 56:
#line 435 "fuzzy_parser.yy" // lalr1.cc:907
    {
		    (yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_string, NULL, yylhs.location);
		}
#line 1418 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 57:
#line 439 "fuzzy_parser.yy" // lalr1.cc:907
    {
		    (yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_bool, NULL, yylhs.location);
		}
#line 1426 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 58:
#line 443 "fuzzy_parser.yy" // lalr1.cc:907
    {
		    (yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_fuzzy, NULL, yylhs.location);
		}
#line 1434 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 59:
#line 450 "fuzzy_parser.yy" // lalr1.cc:907
    { 
			(yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr);
			if((yylhs.value.Node_ptr) != NULL)
			{
				(yylhs.value.Node_ptr)->loc = yylhs.location; (yylhs.value.Node_ptr)->type = Node_command_block;
			}
		}
#line 1446 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 60:
#line 461 "fuzzy_parser.yy" // lalr1.cc:907
    {   
		    (yylhs.value.Node_ptr) = node ((yystack_[1].value.Node_ptr), Node_var_decl, (yystack_[0].value.Node_ptr), yylhs.location);
		}
#line 1454 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 61:
#line 468 "fuzzy_parser.yy" // lalr1.cc:907
    {
			NODE *param = node ((yystack_[2].value.Node_ptr), Node_illegal, (yystack_[0].value.Node_ptr), yylhs.location);
			(yylhs.value.Node_ptr) = node (param, Node_illegal, NULL, yylhs.location);
		}
#line 1463 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 62:
#line 473 "fuzzy_parser.yy" // lalr1.cc:907
    {
			NODE *param = node ((yystack_[2].value.Node_ptr), Node_illegal, (yystack_[0].value.Node_ptr), yystack_[2].location + yystack_[0].location);
			(yylhs.value.Node_ptr) = append_right((yystack_[4].value.Node_ptr), node (param, Node_illegal, NULL, yystack_[2].location + yystack_[0].location));
			(yylhs.value.Node_ptr)->loc = yylhs.location;
		}
#line 1473 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 63:
#line 482 "fuzzy_parser.yy" // lalr1.cc:907
    {
			(yylhs.value.Node_ptr) = node ((yystack_[4].value.Node_ptr), Node_fuzzy_input, (yystack_[1].value.Node_ptr), yylhs.location);
		}
#line 1481 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 64:
#line 489 "fuzzy_parser.yy" // lalr1.cc:907
    {   
		    (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr);
		}
#line 1489 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 65:
#line 493 "fuzzy_parser.yy" // lalr1.cc:907
    {
		    NODE *name = node ((yystack_[4].value.sval), yystack_[4].location);
		    (yylhs.value.Node_ptr) = node (name, Node_var_decl_fuzzy_discrete, (yystack_[2].value.Node_ptr), yylhs.location);
		}
#line 1498 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 66:
#line 498 "fuzzy_parser.yy" // lalr1.cc:907
    {
		    (yylhs.value.Node_ptr) = node (node ((yystack_[4].value.sval), yystack_[4].location), Node_type_struct_declare, (yystack_[2].value.Node_ptr), yylhs.location);
		}
#line 1506 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 67:
#line 502 "fuzzy_parser.yy" // lalr1.cc:907
    {
		    NODE *name = node ((yystack_[11].value.sval), yystack_[11].location);
		    NODE *min_max = node ((yystack_[9].value.Node_ptr), Node_illegal, (yystack_[7].value.Node_ptr), yystack_[9].location + yystack_[7].location);
		    NODE *size = node ((yystack_[5].value.lval), yystack_[5].location);
		    NODE *params = node (min_max, Node_illegal, size, yystack_[9].location + yystack_[5].location);
		    NODE *header = node (name, Node_illegal, params, yystack_[11].location + yystack_[4].location);
		    NODE *body = (yystack_[2].value.Node_ptr);
		    (yylhs.value.Node_ptr) = node (header, Node_type_struct_declare_fuzzy, body, yylhs.location);
		}
#line 1520 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 68:
#line 512 "fuzzy_parser.yy" // lalr1.cc:907
    {
		    NODE *name = node ((yystack_[7].value.sval), yystack_[7].location);
		    NODE *size = node ((yystack_[5].value.lval), yystack_[5].location);
		    NODE *header = node (name, Node_illegal, size, yystack_[7].location + yystack_[4].location);
		    NODE *body = (yystack_[2].value.Node_ptr);
		    (yylhs.value.Node_ptr) = node (header, Node_type_struct_declare_fuzzy_discrete, body, yylhs.location);
		}
#line 1532 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 69:
#line 520 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1538 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 70:
#line 525 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_K_if,
				node ((yystack_[0].value.Node_ptr), Node_if_branches, (NODE *)NULL, yystack_[0].location), yylhs.location); 
		}
#line 1546 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 71:
#line 529 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[4].value.Node_ptr), Node_K_if,
				node ((yystack_[2].value.Node_ptr), Node_if_branches, (yystack_[0].value.Node_ptr), yystack_[1].location + yystack_[0].location), yylhs.location); 
		}
#line 1554 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 72:
#line 535 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_expression_list, (NODE *)NULL, yylhs.location); }
#line 1560 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 73:
#line 537 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = append_right((yystack_[2].value.Node_ptr), node( (yystack_[0].value.Node_ptr), Node_expression_list, (NODE *)NULL, yystack_[0].location)); }
#line 1566 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 74:
#line 539 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = append_right((yystack_[3].value.Node_ptr), node( (yystack_[1].value.Node_ptr), Node_expression_list, (NODE *)NULL, yystack_[1].location)); }
#line 1572 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 75:
#line 543 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = NULL; }
#line 1578 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 76:
#line 544 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1584 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 77:
#line 548 "fuzzy_parser.yy" // lalr1.cc:907
    { 	(yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_var, (NODE *)NULL, yylhs.location);	}
#line 1590 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 78:
#line 550 "fuzzy_parser.yy" // lalr1.cc:907
    { 	
			(yylhs.value.Node_ptr) = node (node ((yystack_[0].value.sval), yystack_[0].location), Node_type_var_rootpath,
			(NODE *)NULL, yylhs.location);	
		  }
#line 1599 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 79:
#line 555 "fuzzy_parser.yy" // lalr1.cc:907
    {
			(yylhs.value.Node_ptr) = append_right((yystack_[2].value.Node_ptr), node( node ((yystack_[0].value.sval), yystack_[0].location),
				Node_illegal, (NODE *)NULL, yystack_[0].location));
		  }
#line 1608 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 80:
#line 562 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node (node ((yystack_[2].value.sval), yystack_[2].location), Node_assign, (yystack_[0].value.Node_ptr), yylhs.location);	}
#line 1614 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 81:
#line 563 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1620 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 82:
#line 567 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.sval), yylhs.location);	(yylhs.value.Node_ptr)->type = Node_name; }
#line 1626 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 83:
#line 568 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node (node ((yystack_[3].value.sval), yystack_[3].location), Node_array, (yystack_[1].value.Node_ptr), yylhs.location);	}
#line 1632 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 84:
#line 572 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_illegal, NULL, yylhs.location);	}
#line 1638 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 85:
#line 574 "fuzzy_parser.yy" // lalr1.cc:907
    {
			(yylhs.value.Node_ptr) = append_right((yystack_[2].value.Node_ptr), node ((yystack_[0].value.Node_ptr), Node_illegal, NULL, yystack_[0].location));
			(yylhs.value.Node_ptr)->loc = yylhs.location;
		  }
#line 1647 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 86:
#line 581 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1653 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 87:
#line 582 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1659 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 88:
#line 586 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_namespace, NULL, yylhs.location);	}
#line 1665 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 89:
#line 588 "fuzzy_parser.yy" // lalr1.cc:907
    {
			(yylhs.value.Node_ptr) = append_right((yystack_[2].value.Node_ptr), node ((yystack_[0].value.Node_ptr), Node_namespace, NULL, yystack_[0].location));
			(yylhs.value.Node_ptr)->loc = yylhs.location;
		  }
#line 1674 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 90:
#line 596 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = NULL; }
#line 1680 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 91:
#line 598 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr); }
#line 1686 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 92:
#line 602 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_not, NULL, yylhs.location);	}
#line 1692 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 93:
#line 605 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), (yystack_[1].value.Node_type), (yystack_[0].value.Node_ptr), yylhs.location);		}
#line 1698 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 94:
#line 607 "fuzzy_parser.yy" // lalr1.cc:907
    {
			(yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_and, (yystack_[0].value.Node_ptr), yylhs.location);	
		}
#line 1706 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 95:
#line 611 "fuzzy_parser.yy" // lalr1.cc:907
    {
			(yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_or, (yystack_[0].value.Node_ptr), yylhs.location);	
		}
#line 1714 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 96:
#line 617 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr);					}
#line 1720 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 97:
#line 618 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_or, (yystack_[0].value.Node_ptr), yylhs.location); 		}
#line 1726 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 98:
#line 619 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_and, (yystack_[0].value.Node_ptr), yylhs.location); 		}
#line 1732 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 99:
#line 620 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_really, NULL, yylhs.location);	}
#line 1738 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 100:
#line 621 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_little, NULL, yylhs.location);	}
#line 1744 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 101:
#line 622 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_very, NULL, yylhs.location);		}
#line 1750 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 102:
#line 623 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_extremely, NULL, yylhs.location);		}
#line 1756 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 103:
#line 624 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_seemed, NULL, yylhs.location);		}
#line 1762 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 104:
#line 625 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_bit, NULL, yylhs.location);		}
#line 1768 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 105:
#line 626 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_not, NULL, yylhs.location);		}
#line 1774 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 106:
#line 627 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr); (yylhs.value.Node_ptr)->loc = yylhs.location;			}
#line 1780 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 107:
#line 632 "fuzzy_parser.yy" // lalr1.cc:907
    {
			{ (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_fuzzy_rule, (yystack_[0].value.Node_ptr), yylhs.location); 	}
		}
#line 1788 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 108:
#line 638 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), (yystack_[1].value.Node_type), (yystack_[0].value.Node_ptr), yylhs.location);	}
#line 1794 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 109:
#line 639 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr);			}
#line 1800 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 110:
#line 643 "fuzzy_parser.yy" // lalr1.cc:907
    { 
		  if((yystack_[0].value.dval) == HUGE_VALF)
		  {
		    error(yystack_[0].location,"compilation terminated.");
		    YYABORT;
		  }
		  (yylhs.value.Node_ptr) = node ((yystack_[0].value.dval), yylhs.location);
		}
#line 1813 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 111:
#line 651 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.lval), yylhs.location);		}
#line 1819 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 112:
#line 652 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.sval), yylhs.location);		}
#line 1825 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 113:
#line 653 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.bval), yylhs.location);		}
#line 1831 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 114:
#line 654 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr);			}
#line 1837 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 115:
#line 655 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[0].value.Node_ptr);			}
#line 1843 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 116:
#line 656 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_plus, (yystack_[0].value.Node_ptr), yylhs.location); 			}
#line 1849 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 117:
#line 657 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_minus, (yystack_[0].value.Node_ptr), yylhs.location); 			}
#line 1855 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 118:
#line 658 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_multive, (yystack_[0].value.Node_ptr), yylhs.location); 		}
#line 1861 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 119:
#line 659 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_quotient, (yystack_[0].value.Node_ptr), yylhs.location); 		}
#line 1867 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 120:
#line 660 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[2].value.Node_ptr), Node_mod, (yystack_[0].value.Node_ptr), yylhs.location); 		}
#line 1873 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 121:
#line 661 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = node ((yystack_[0].value.Node_ptr), Node_unary_minus, (NODE *)NULL, yylhs.location); 	}
#line 1879 "fuzzy_parser.cc" // lalr1.cc:907
    break;

  case 122:
#line 662 "fuzzy_parser.yy" // lalr1.cc:907
    { (yylhs.value.Node_ptr) = (yystack_[1].value.Node_ptr); (yylhs.value.Node_ptr)->loc = yylhs.location;                     		   	}
#line 1885 "fuzzy_parser.cc" // lalr1.cc:907
    break;


#line 1889 "fuzzy_parser.cc" // lalr1.cc:907
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
      yypush_ ("Shifting", YY_MOVE (error_token));
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
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
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


  const short fuzzy_parser::yypact_ninf_ = -218;

  const signed char fuzzy_parser::yytable_ninf_ = -78;

  const short
  fuzzy_parser::yypact_[] =
  {
    -218,    10,   447,  -218,  -218,    -6,     7,    24,    71,  -218,
      37,    45,  -218,    53,   326,  -218,  -218,   -51,   110,   127,
     128,   326,    80,  -218,   389,   120,  -218,  -218,  -218,   131,
    -218,  -218,   165,   175,  -218,  -218,    42,  -218,   172,   174,
    -218,  -218,   178,  -218,  -218,   263,   176,   333,   326,   326,
    -218,  -218,   391,   181,   190,  -218,   326,   326,   326,  -218,
    -218,  -218,  -218,    83,    17,   182,  -218,  -218,   302,   196,
     152,   326,   437,   326,    79,    31,   333,   389,   389,   389,
     389,   389,   389,   389,   389,   123,  -218,   333,   326,   161,
    -218,  -218,    11,     6,  -218,  -218,   213,  -218,  -218,   163,
    -218,    80,  -218,  -218,   326,  -218,   333,     5,   302,   135,
     156,  -218,  -218,   340,  -218,   173,  -218,   326,  -218,   326,
     326,   326,   326,   326,   326,   326,   326,   481,   220,   207,
    -218,   215,  -218,  -218,   183,  -218,   232,   214,  -218,   228,
       5,     2,  -218,  -218,  -218,  -218,  -218,  -218,  -218,    80,
     389,   389,   225,   230,   227,   237,   481,   326,   239,   240,
     183,  -218,  -218,   302,   241,   173,   326,   189,  -218,   447,
     447,   496,   245,    39,  -218,   302,   179,   179,  -218,  -218,
    -218,    27,    32,   346,  -218,   249,   256,   198,   481,   246,
     326,    60,   257,   326,  -218,  -218,   260,  -218,   244,  -218,
    -218,   326,   290,   302,   291,   481,  -218,   326,   302,  -218,
     280,  -218,   278,  -218,   299,   326,  -218,   481,   281,  -218,
     198,  -218,   296,  -218,   125,   310,   139,  -218,  -218,   198,
     268,   447,  -218,  -218,   276,   198,   311,   118,    52,  -218,
     326,   326,   307,   322,  -218,  -218,   503,   271,  -218,  -218,
     331,  -218,   326,   293,  -218,   320,   143,  -218,  -218,   319,
     335,   447,   286,  -218,   326,  -218,   341,  -218,  -218,   447,
     144,  -218,   447,   510,   336,  -218
  };

  const unsigned char
  fuzzy_parser::yydefact_[] =
  {
       3,     0,     2,     1,    30,     0,     0,     0,     0,     3,
       0,     0,    18,     0,    90,    19,    20,     0,     0,     0,
       0,     0,     0,    32,     0,    82,    56,    54,    57,    58,
      55,     4,     0,     0,    69,    86,     0,    13,     0,     0,
      14,     6,    53,    87,    88,     0,     0,     0,     0,     0,
      10,    11,     0,     0,     0,    78,     0,     0,     0,   113,
     110,   111,   112,    82,   109,     0,   114,   115,    91,     0,
       0,     0,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    96,    75,     0,     0,
       5,    47,    82,     0,    84,    81,    60,    64,    22,     0,
      15,     0,    34,    35,     0,    21,     0,    36,    72,     0,
       0,    59,    40,     0,   121,     0,    92,     0,    16,     0,
       0,     0,     0,     0,     0,     0,     0,    49,     0,     0,
      58,     0,    39,    28,     0,    27,     0,     0,    17,     0,
      36,     0,   105,   101,   102,   103,   104,   100,    99,     0,
       0,     0,    76,     0,     0,     0,    49,     0,     0,     0,
       0,    79,    89,    29,     0,    72,     0,     0,    31,     0,
       0,     0,   111,     0,   122,   108,   117,   116,   118,   119,
     120,    94,    95,    93,    77,     0,    50,     0,     0,     0,
      90,    82,     0,     0,    33,   106,   107,    98,    97,    48,
      83,     0,     0,    80,     0,     0,    85,     0,    73,    37,
      70,     7,     0,    41,     0,     0,    42,     0,    82,    51,
       0,    12,     0,    23,     0,     0,     0,    43,    46,     0,
      73,     0,    66,    40,     0,     0,     0,    38,     0,    63,
       0,     0,     0,     0,    74,    71,     0,     0,    52,    45,
       0,     9,     0,     0,    24,     0,   119,    65,    44,     0,
       0,     0,     0,     3,     0,    68,     0,     8,     3,    26,
     119,    40,    25,     0,     0,    67
  };

  const short
  fuzzy_parser::yypgoto_[] =
  {
    -218,  -218,    -8,  -162,  -218,  -218,  -218,   -68,  -218,  -218,
     221,   117,  -217,  -218,  -218,  -218,   206,  -218,   -59,   330,
     292,   166,  -218,  -166,  -218,     3,  -218,  -218,   208,   -33,
    -218,   265,    -2,   180,  -218,   -55,  -218,   -18,     0
  };

  const short
  fuzzy_parser::yydefgoto_[] =
  {
      -1,     1,     2,    31,   238,   254,   131,    32,    47,    76,
     168,   133,   171,    33,    34,    35,   185,   186,    36,    37,
      38,   224,    39,    40,    41,   107,   153,    42,    94,    43,
      96,    44,    64,    65,    66,    85,    46,    67,   108
  };

  const short
  fuzzy_parser::yytable_[] =
  {
      45,    52,    48,    95,   132,   213,    86,   210,   211,   158,
       3,   195,    69,   134,    68,    49,   246,   166,    70,   156,
      75,    74,   141,   142,   143,   144,   145,   146,   147,   148,
     119,   120,   121,   122,   123,   119,   120,   121,   122,   123,
      88,   101,   119,   120,   121,   122,   123,    50,   109,   110,
      45,   215,   150,   151,   273,   101,   114,   115,   116,    86,
      86,    86,    86,    86,    86,    86,    86,   124,   187,   245,
     136,   129,   251,   137,   124,   125,   159,   167,   139,   140,
     213,   157,   119,   120,   121,   122,   123,   117,   154,    88,
     152,    87,   252,   253,    51,   197,   198,   187,   126,   267,
      53,    95,   138,   126,   163,    92,   165,   213,    54,   164,
     126,    93,    88,   173,   124,   125,    55,   175,    71,   176,
     177,   178,   179,   180,   181,   182,   183,    95,    87,   220,
     157,     4,    86,    86,   239,    72,    73,   240,   119,   120,
     121,   122,   123,    63,   169,   -77,   229,   196,   242,    88,
     126,   240,   -61,   -62,   219,   -61,   -62,   203,   235,   119,
     120,   121,   122,   123,    23,   170,   208,    45,    45,   132,
     124,   125,   149,   150,   151,    89,   119,   120,   121,   122,
     123,    63,   174,   -77,   121,   122,   123,   236,    90,   -77,
      68,   124,   125,   225,     9,    97,   243,    98,   113,   105,
     112,   225,   248,    99,   127,   118,   126,   230,   124,   125,
     119,   120,   121,   122,   123,   234,   189,   119,   120,   121,
     122,   123,   128,   192,   155,   160,   161,   126,   188,    45,
     119,   120,   121,   122,   123,   136,   193,   166,   190,   199,
     255,   256,   124,   125,   126,   201,   191,   204,   205,   124,
     125,   209,   262,   207,   214,   269,   101,   200,   216,    45,
     272,   218,   124,   125,   270,   102,   103,    45,   217,   221,
      45,   119,   120,   121,   122,   123,   223,   244,   126,   119,
     120,   121,   122,   123,   101,   126,   100,   101,   247,   119,
     120,   121,   122,   123,   150,   231,   102,   103,   126,   227,
     228,   232,   104,   124,   125,   119,   120,   121,   122,   123,
      88,   124,   125,   119,   120,   121,   241,   123,   233,   237,
     249,   124,   125,   119,   120,   121,   264,   123,   268,    56,
     257,   258,   260,   104,    57,   263,    56,   124,   125,   126,
     261,   106,   265,    56,   266,   124,   125,   126,    57,   119,
     120,   121,   122,   123,   250,   124,   125,   126,    58,   275,
     271,   194,   202,    91,   135,    58,   162,   226,   206,     0,
     222,     0,    58,   126,     0,     0,     0,     0,     0,     0,
       0,   126,     0,     0,     0,    59,    60,    61,    62,    63,
       0,   126,    59,    60,    61,    62,    63,    77,     0,    59,
      60,   172,    62,    63,     4,     5,     0,     6,     7,     8,
       9,   111,    10,    11,    12,     0,    13,    14,    15,    16,
       0,     0,    17,     0,     0,     0,     0,     0,    18,    19,
      20,     0,     0,     0,    21,     0,    22,    23,     0,    24,
       0,    78,    79,    80,    81,    82,    83,    84,     0,     0,
       4,     0,    63,     0,    25,    26,    27,    28,    29,    30,
       4,     5,    13,     6,     7,     8,     9,     0,    10,    11,
      12,     0,    13,    14,    15,    16,     0,     0,    17,     0,
       0,     0,     0,    23,    18,    19,    20,     0,     0,     0,
      21,     0,    22,    23,     0,    24,     0,     0,     0,     0,
      25,    26,    27,    28,   130,    30,    13,     0,     0,     0,
      25,    26,    27,    28,    29,    30,   212,    10,    11,     0,
       0,    13,     0,   259,    10,    11,     0,    17,    13,     0,
     274,    10,    11,     0,    17,    13,     0,     0,     0,     0,
       0,    17,     0,     0,   184,    26,    27,    28,   130,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   184,
      26,    27,    28,    29,    30,     0,   184,    26,    27,    28,
      29,    30,     0,   184,    26,    27,    28,    29,    30
  };

  const short
  fuzzy_parser::yycheck_[] =
  {
       2,     9,     8,    36,    72,   171,    24,   169,   170,     3,
       0,     9,    63,    72,    14,     8,   233,    12,    69,     8,
      22,    21,    77,    78,    79,    80,    81,    82,    83,    84,
       3,     4,     5,     6,     7,     3,     4,     5,     6,     7,
      29,    24,     3,     4,     5,     6,     7,    23,    48,    49,
      52,    12,    50,    51,   271,    24,    56,    57,    58,    77,
      78,    79,    80,    81,    82,    83,    84,    35,   127,   231,
      72,    71,    20,    73,    35,    36,    70,    72,    47,    76,
     246,    70,     3,     4,     5,     6,     7,    70,    88,    29,
      87,     8,    40,    41,    23,   150,   151,   156,    71,   261,
      63,   134,    23,    71,   104,    63,   106,   273,    63,   106,
      71,    69,    29,   113,    35,    36,    63,   117,     8,   119,
     120,   121,   122,   123,   124,   125,   126,   160,     8,   188,
      70,    13,   150,   151,     9,     8,     8,    12,     3,     4,
       5,     6,     7,    63,     9,    25,   205,   149,     9,    29,
      71,    12,     9,     9,   187,    12,    12,   157,   217,     3,
       4,     5,     6,     7,    46,     9,   166,   169,   170,   237,
      35,    36,    49,    50,    51,    44,     3,     4,     5,     6,
       7,    63,     9,    63,     5,     6,     7,   220,    23,    69,
     190,    35,    36,   193,    19,    23,   229,    23,     8,    23,
      19,   201,   235,    25,     8,    23,    71,   207,    35,    36,
       3,     4,     5,     6,     7,   215,     9,     3,     4,     5,
       6,     7,    70,     9,    63,    12,    63,    71,     8,   231,
       3,     4,     5,     6,     7,   237,     8,    12,    23,     9,
     240,   241,    35,    36,    71,     8,    63,     8,     8,    35,
      36,    62,   252,    12,     9,   263,    24,    30,     9,   261,
     268,    63,    35,    36,   264,    33,    34,   269,    12,    23,
     272,     3,     4,     5,     6,     7,    19,     9,    71,     3,
       4,     5,     6,     7,    24,    71,    23,    24,    12,     3,
       4,     5,     6,     7,    50,    15,    33,    34,    71,     9,
       9,    23,    70,    35,    36,     3,     4,     5,     6,     7,
      29,    35,    36,     3,     4,     5,     6,     7,    19,    23,
       9,    35,    36,     3,     4,     5,     6,     7,    42,     3,
      23,     9,    61,    70,     8,    42,     3,    35,    36,    71,
       9,     8,    23,     3,     9,    35,    36,    71,     8,     3,
       4,     5,     6,     7,   237,    35,    36,    71,    32,    23,
      19,   140,   156,    33,    72,    32,   101,   201,   160,    -1,
     190,    -1,    32,    71,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      -1,    71,    59,    60,    61,    62,    63,     8,    -1,    59,
      60,    61,    62,    63,    13,    14,    -1,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    25,    26,    27,    28,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    37,    38,
      39,    -1,    -1,    -1,    43,    -1,    45,    46,    -1,    48,
      -1,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      13,    -1,    63,    -1,    63,    64,    65,    66,    67,    68,
      13,    14,    25,    16,    17,    18,    19,    -1,    21,    22,
      23,    -1,    25,    26,    27,    28,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    46,    37,    38,    39,    -1,    -1,    -1,
      43,    -1,    45,    46,    -1,    48,    -1,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    68,    25,    -1,    -1,    -1,
      63,    64,    65,    66,    67,    68,    20,    21,    22,    -1,
      -1,    25,    -1,    20,    21,    22,    -1,    31,    25,    -1,
      20,    21,    22,    -1,    31,    25,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    63,    64,    65,    66,    67,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    68,    -1,    63,    64,    65,    66,
      67,    68,    -1,    63,    64,    65,    66,    67,    68
  };

  const unsigned char
  fuzzy_parser::yystos_[] =
  {
       0,    74,    75,     0,    13,    14,    16,    17,    18,    19,
      21,    22,    23,    25,    26,    27,    28,    31,    37,    38,
      39,    43,    45,    46,    48,    63,    64,    65,    66,    67,
      68,    76,    80,    86,    87,    88,    91,    92,    93,    95,
      96,    97,   100,   102,   104,   105,   109,    81,     8,     8,
      23,    23,    75,    63,    63,    63,     3,     8,    32,    59,
      60,    61,    62,    63,   105,   106,   107,   110,   111,    63,
      69,     8,     8,     8,   111,   105,    82,     8,    52,    53,
      54,    55,    56,    57,    58,   108,   110,     8,    29,    44,
      23,    92,    63,    69,   101,   102,   103,    23,    23,    25,
      23,    24,    33,    34,    70,    23,     8,    98,   111,   111,
     111,    20,    19,     8,   111,   111,   111,    70,    23,     3,
       4,     5,     6,     7,    35,    36,    71,     8,    70,   111,
      67,    79,    80,    84,    91,    93,   105,   111,    23,    47,
      98,   108,   108,   108,   108,   108,   108,   108,   108,    49,
      50,    51,    98,    99,   111,    63,     8,    70,     3,    70,
      12,    63,   104,   111,    98,   111,    12,    72,    83,     9,
       9,    85,    61,   111,     9,   111,   111,   111,   111,   111,
     111,   111,   111,   111,    63,    89,    90,    91,     8,     9,
      23,    63,     9,     8,    83,     9,   105,   108,   108,     9,
      30,     8,    89,   111,     8,     8,   101,    12,   111,    62,
      76,    76,    20,    96,     9,    12,     9,    12,    63,   102,
      91,    23,   106,    19,    94,   111,    94,     9,     9,    91,
     111,    15,    23,    19,   111,    91,   102,    23,    77,     9,
      12,     6,     9,   102,     9,    76,    85,    12,   102,     9,
      84,    20,    40,    41,    78,   111,   111,    23,     9,    20,
      61,     9,   111,    42,     6,    23,     9,    76,    42,    75,
     111,    19,    75,    85,    20,    23
  };

  const unsigned char
  fuzzy_parser::yyr1_[] =
  {
       0,    73,    74,    75,    75,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    77,    77,    78,    78,    79,    79,    80,
      81,    80,    82,    80,    80,    80,    83,    83,    84,    84,
      85,    85,    86,    86,    86,    86,    86,    87,    88,    89,
      89,    90,    90,    91,    91,    91,    91,    91,    91,    92,
      93,    94,    94,    95,    96,    96,    96,    96,    96,    96,
      97,    97,    98,    98,    98,    99,    99,   100,   100,   100,
     101,   101,   102,   102,   103,   103,   104,   104,   105,   105,
     106,   106,   107,   107,   107,   107,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   109,   110,   110,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111
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
       2,     3,     5,     6,     2,     7,     6,    13,     9,     1,
       5,     7,     1,     3,     5,     0,     1,     1,     2,     3,
       3,     1,     1,     4,     1,     3,     1,     1,     1,     3,
       0,     1,     2,     3,     3,     3,     1,     3,     3,     2,
       2,     2,     2,     2,     2,     2,     3,     4,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     2,     3
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
  "\"AND\"", "\"OR\"", "\"NOT\"", "\"VERY\"", "\"EXTREMELY\"",
  "\"SEEMED\"", "\"BIT\"", "\"LITTLE\"", "\"REALLY\"", "BOOLEN",
  "\"Number type\"", "\"int type\"", "STRING", "NAME", "\"String\"",
  "\"Number\"", "\"bool\"", "\"fuzzy\"", "\"int\"", "\"operator\"",
  "\"ASSIGN OPERATOR\"", "RELOP", "REDIRECT_OP", "$accept", "unit",
  "statements", "statement", "case_statements", "case_statement",
  "for_init_stmt", "simple_stmt", "$@1", "$@2", "redirection",
  "opt_simple_stmt", "declares", "function_decl", "function_define",
  "function_call", "opt_param_list", "param_list", "datatype", "action",
  "declare_var", "fuzzy_params", "fuzzy_input", "declare", "if_statement",
  "expression_list", "opt_expression_list", "namescope", "variable_decl",
  "name", "variable_decl_list", "name_general", "namespace", "opt_exp",
  "conditional", "exp_fuzzy", "fuzzy_rule", "namespaces", "exp", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short
  fuzzy_parser::yyrline_[] =
  {
       0,   186,   186,   192,   194,   204,   205,   206,   208,   220,
     224,   226,   228,   230,   232,   234,   236,   240,   244,   246,
     253,   259,   260,   264,   265,   279,   283,   290,   291,   295,
     297,   296,   304,   303,   310,   315,   323,   324,   332,   333,
     337,   338,   348,   356,   363,   371,   380,   390,   397,   408,
     409,   413,   417,   425,   426,   430,   434,   438,   442,   449,
     460,   467,   472,   481,   488,   492,   497,   501,   511,   519,
     524,   528,   535,   536,   538,   543,   544,   548,   549,   554,
     562,   563,   567,   568,   572,   573,   581,   582,   586,   587,
     595,   597,   602,   605,   606,   610,   617,   618,   619,   620,
     621,   622,   623,   624,   625,   626,   627,   631,   638,   639,
     643,   651,   652,   653,   654,   655,   656,   657,   658,   659,
     660,   661,   662
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
      65,    66,    67,    68,    69,    70,    71,    72
    };
    const unsigned user_token_number_max_ = 327;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 2564 "fuzzy_parser.cc" // lalr1.cc:1218
#line 667 "fuzzy_parser.yy" // lalr1.cc:1219

void
yy::fuzzy_parser::error (const location_type& l,
                          const std::string& m)
{
  driver->error (l, m);
}
