                                                            /* -*- C++ -*- */
%option c++
%option nounput
%option debug
%option batch

%{

#include <cerrno>
#include <climits>
#include <regex>
#include <string>

#include <boost/lexical_cast.hpp>

#include <misc/contract.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << '\n';
  //
  // reports about `\n' instead of an actual new-line character.
#include <misc/escape.hh>
#include <misc/symbol.hh>
#include <parse/parsetiger.hh>
#include <parse/tiger-parser.hh>


  /*FIXME: Some code was deleted here. Convenient shortcuts. -> DONE */


#define YY_USER_ACTION                          \
    tp.location_.columns(yyleng);

#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, tp.location_)

#define TOKEN(Type)                             \
  parser::make_ ## Type(tp.location_)


// Flex uses `0' for end of file.  0 is not a token_type.
#define yyterminate() return TOKEN(EOF)

# define CHECK_EXTENSION()                              \
  do {                                                  \
    if (!tp.enable_extensions_p_)                       \
      tp.error_ << misc::error::error_type::scan        \
                << tp.location_                         \
                << ": invalid identifier: `"            \
                << misc::escape(yytext) << "'\n";       \
  } while (false)

YY_FLEX_NAMESPACE_BEGIN
%}

%x SC_COMMENT SC_STRING

/* Abbreviations.  */
int             [0-9]+

        /* FIXME: Some code was deleted here. -> DONE */

INT             [0-9]+
id [A-Za-z][_A-Za-z0-9]*
SPACE           [ \t]+

%%
%{
  /* FIXME: Some code was deleted here (Local variables). -> DONE*/

    std::string grown_string;
    int cpt_comment = 0;

  // Each time yylex is called.
  tp.location_.step();
%}

 /* The rules.  */

{int}         {
                int val = 0;

  /* FIXME: Some code was deleted here (Decode, and check the value).
                check if the value is valid -> DONE */

                try
                {
                    val = std::stoi(yytext, nullptr,10);
                }
                catch (std::invalid_argument& e)
                {
                    tp.error_ << misc::error::error_type::scan
                            << tp.location_
                            << ": invalid identifier: `"
                            << misc::escape(yytext) << "'\n";
                }
                return TOKEN_VAL(INT, val);
              }

 /* FIXME: Some code was deleted here. DONE*/

"+"             { return TOKEN(PLUS);}
"-"             { return TOKEN(MINUS);}
"*"             { return TOKEN(TIMES);}
"/"             { return TOKEN(DIVIDE);}
"="             { return TOKEN(EQ);}
":="            { return TOKEN(ASSIGN);}
"<"             { return TOKEN(LT);}
">"             { return TOKEN(GT);}
"|"             { return TOKEN(OR);}
"&"             { return TOKEN(AND);}
"<>"            { return TOKEN(NE);}
">="            { return TOKEN(GE);}
"<="            { return TOKEN(LE);}
"("             { return TOKEN(LPAREN);}
")"             { return TOKEN(RPAREN);}
"["             { return TOKEN(LBRACK);}
"]"             { return TOKEN(RBRACK);}
"{"             { return TOKEN(LBRACE);}
"}"             { return TOKEN(RBRACE);}
";"             { return TOKEN(SEMI);}
","             { return TOKEN(COMMA);}
"."             { return TOKEN(DOT);}
":"             { return TOKEN(COLON);}
[ \t]+          {tp.location_.step();}
\n+             {tp.location_.lines(yyleng); tp.location_.step();}


"if"            { return TOKEN(IF);}
"else"          { return TOKEN(ELSE);}
"for"           { return TOKEN(FOR);}
"while"         { return TOKEN(WHILE);}
"do"            { return TOKEN(DO);}
"end"           { return TOKEN(END);}
"break"         { return TOKEN(BREAK);}
"_cast"         { return TOKEN(CAST);}
"class"         { return TOKEN(CLASS);}
"array"         { return TOKEN(ARRAY);}
"function"      { return TOKEN(FUNCTION);}
"extends"       { return TOKEN(EXTENDS);}
"import"        { return TOKEN(IMPORT);}
"in"            { return TOKEN(IN);}
"let"           { return TOKEN(LET);}
"method"        { return TOKEN(METHOD);}
"new"           { return TOKEN(NEW);}
"nil"           { return TOKEN(NIL);}
"of"            { return TOKEN(OF);}
"primitive"     { return TOKEN(PRIMITIVE);}
"then"          { return TOKEN(THEN);}
"to"            { return TOKEN(TO);}
"type"          { return TOKEN(TYPE);}
"var"           { return TOKEN(VAR);}
{id}            { return TOKEN_VAL(ID, yytext);}
"_main"         { return TOKEN_VAL(ID, yytext);}
"_chunks"       { return TOKEN(CHUNKS);}
"_exp"          { return TOKEN(EXP);}
"_lvalue"       { return TOKEN(LVALUE);}
"_namety"       { return TOKEN(NAMETY);}

  /* String in quotes" */

"\""        grown_string.clear(); BEGIN SC_STRING;

<SC_STRING>{ /* Handling of the strings.  Initial " is eaten. */
  "\"" {
    BEGIN INITIAL;
    return TOKEN_VAL(STRING, grown_string);
  }


  \\x[0-9a-fA-F]{2}  {
    grown_string.append(1, strtol(yytext + 2, 0, 16));
  }

  \\a                           {
    grown_string += '\a';
  }

  \\b                           {
    grown_string += '\b';
  }

  \\f                           {
   grown_string += '\f';
  }

  \\n                           {
   grown_string += '\n';
  }

  \\r                           {
   grown_string += '\r';
  }

  \\t                           {
   grown_string += '\t';
  }

  \\v                           {
   grown_string += '\v';
  }

  \\[0-3][0-7]{2}               {
   grown_string.append(1, strtol(yytext + 3, 0, 8));
  }


  \\\\                          {
   grown_string += '\\';
  }

  "\\\""                        {
   grown_string += '\"';
  }

  \\.                           {
   tp.error_ << misc::error::error_type::scan
             << tp.location_
             << ": invalid identifier: `"
             << misc::escape(yytext) << "'\n";
  }

  <<EOF>>                       {
   tp.error_ << misc::error::error_type::scan
             << tp.location_
             << ": invalid identifier: `"
             << misc::escape(yytext) << "'\n"; BEGIN INITIAL;
  }

   .                            {
   grown_string += yytext;
  }

}

"/*"        BEGIN SC_COMMENT; cpt_comment++;

<SC_COMMENT>{ /* Handling of the strings.  Initial " is eaten. */
  "*/" {
            cpt_comment--;
            if (cpt_comment == 0)
                BEGIN INITIAL;
  }

    <<EOF>>                       {
     tp.error_ << misc::error::error_type::scan
               << tp.location_
               << ": unexpected end of file in a comment"
               << misc::escape(yytext) << "\n"; BEGIN INITIAL;
    }

    "/*"   cpt_comment++;

    .                             {
    grown_string.append(yytext);
  }

}

.    {

      tp.error_ << misc::error::error_type::scan
        << tp.location_
        << ": invalid identifier: `"
        << misc::escape(yytext) << "'\n";
}





%%

// Do not use %option noyywrap, because then flex generates the same
// definition of yywrap, but outside the namespaces, so it defines it
// for ::yyFlexLexer instead of ::parse::yyFlexLexer.
int yyFlexLexer::yywrap() { return 1; }

void
yyFlexLexer::scan_open_(std::istream& f)
{
  yypush_buffer_state(YY_CURRENT_BUFFER);
  yy_switch_to_buffer(yy_create_buffer(&f, YY_BUF_SIZE));
}

void
yyFlexLexer::scan_close_()
{
  yypop_buffer_state();
}

YY_FLEX_NAMESPACE_END
