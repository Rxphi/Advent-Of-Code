%{
open Printf
open Result


let parse_error s = (* Called by the parser function on error *)
  print_endline s;
  flush stdout

%}

%token <int> INT
%token  MUL COMMA LPAREN RPAREN 
%token NEWLINE

%start input
%type <result> input

%%

input:    /* empty */		{  [] }
        | input line		{  $2 :: $1 }
;

line: 
        | NEWLINE		{ Error "empty line" }
        | MUL LPAREN INT COMMA INT RPAREN { MUL ($3, $5) }
        | error { Error "Invalid syntax" }
;

%%
