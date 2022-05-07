grammar templ;

file
	: (evaluation | text)*
	;


// non terminals
evaluation
	: loop
	| variable
	| cond_variable
	;

variable
	: START_BLOCK ID END_BLOCK
	;
// a conditiona variable consists of: 
// [% ID (asd | dsa) %]
// and will limit you to either use asd or dsa
cond_variable
	: START_BLOCK ID '(' cond ')' END_BLOCK
	;

cond
	: text ( '|' text )*
	;
// a loop consists of:
// [% loop %]
// ...
// [% endloop %]
loop
	: START_BLOCK 'loop' END_BLOCK text+ START_BLOCK 'endloop' END_BLOCK
	;
// must not be terminal to be able to be generated fully
text
	: ~(BLOCK_DATA)+
	;

BLOCK_DATA
	: START_BLOCK
	| END_BLOCK
	;

// terminals
ID
	: [a-zA-Z_][a-zA-Z0-9_]*
	;

START_BLOCK
	: '[% '
	;

END_BLOCK
	: ' %]'
	;

WHITE_SPACES: 
	( ' ' | '\t' | '\n' | '\r' ) -> skip
    ;