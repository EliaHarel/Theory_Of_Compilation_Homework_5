%{ /* regex patterns, start conditions, debug mode */
    /* Declarations Section */
#include <stdio.h>
#include "attributes.hpp"
#include "hw3_output.hpp"
#include "parser.tab.hpp"
%}

%option yylineno
%option noyywrap

%%
    /* Rules Section */

void                                return VOID;
int                                 return INT;
byte                                return BYTE;
b                                   return B;
bool                                return BOOL;
set                                 return SET;
and                                 return AND;
or                                  return OR;
not                                 return NOT;
true                                return TRUE;
false                               return FALSE;
return                              return RETURN;
if                                  return IF;
else                                return ELSE;
while                               return WHILE;
break                               {yylval = new utype(std::string(yytext));
													return BREAK;}
continue                            {yylval = new utype(std::string(yytext));
													return CONTINUE;}
													
;                                   return SC;
,                                   return COMMA;
\(                                  return LPAREN;
\)                                  return RPAREN;
\{                                  return LBRACE;
\}                                  return RBRACE;
\[                                  return LBRACKET;
\]                                  return RBRACKET;
=                                   return ASSIGN;
\<|\>|\<=|\>= 		    					{yylval = new utype(std::string(yytext));
													return RELOP_GT_1N;}
in                                  return RELOP_IN;
==|!=                               {yylval = new utype(std::string(yytext));
													return RELOP_EQ_2L;}
\*|\/                               {yylval = new utype(std::string(yytext));
													return BINOP_MUL_L1;}
												
\+|\-                               {yylval = new utype(std::string(yytext));
													return BINOP_ADD_L2;}

\.\.                                return DOTS;
[a-zA-Z][a-zA-Z0-9]*                {yylval = new utype(std::string(yytext));
												 	return ID;}
0|[1-9][0-9]*                       {yylval = new utype(atoi(yytext));
													return NUM;}
\"([^\n\r\"\\]|\\[rnt"\\])+\"       {std::string temp (yytext);
													temp = temp.substr(1, temp.size()-2);
													yylval = new utype(temp);
												 	return STRING;}
\n												{
//													CodeBuffer::instance().code_line_debugging_only();
													}
\/\/[^\r\n]*[\r|\n|\r\n]?           ;
[ \t\n\r]+                          ;
.                                   {output::errorLex(yylineno); exit(1);};

%%

