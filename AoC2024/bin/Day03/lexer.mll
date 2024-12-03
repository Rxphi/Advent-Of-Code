{
  open Parser 
}
let digit = ['0'-'9']
let validInt = digit | digit digit | digit digit digit

rule token = parse
  | "mul"              { MUL }
  | ','                { COMMA }
  | '('                { LPAREN }
  | ')'                { RPAREN }
  | validInt as i      { INT (int_of_string i) }
  | '\n'	{ NEWLINE }
  | eof		{ raise End_of_file }
  | _		{ token lexbuf }

