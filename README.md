# cedilla40

*cedilla* is a decent recursive parser implementation and an AST macro engine, it comes with C supersets examples

## TODO

- [x] rename and or split macros.h
- [x] create a separate module for objects for AST ctx
- [x] implement define / in-source preprocessor definition / includes ?
- parse all C syntax
	- [x] check the best option between a module per C syntaxes or built in within compiler ?
		-> Need for correct type analysis to perform parsing ?
	- [ ] create a module for having a type list, having a list of types and names per scope is needed
	- [ ] for object, create a wrapper around to get correct types ? (see object.h commentary)
- [x] choose between a single pass and ast macro in reverse order, or a parsing pass and a second preprocessor pass => 2nd pass
- [ ] maybe add an escape / unescape function to add/remove \" etc (todo : check where it may be usefull).
- [x] restructre project
- [x] add klist to void*, free, type? as parser context objets for IE #define etc... + add a clone function
- [x] klist : add an exists function, and allow non pointers type
- [x] determine logic, way to parse and compile at same time for single file pass ?
- [x] ast_node, remove useless alloc
- [ ] name consitency, BRACKET => OPEN_BRACKET ?, also, is the ast tree root cell required (not if ast ptr ptr instead of ast ptr in prototypes, but more error prone)

*PARSER*

- [x] reccursive engine
- [x] C brackets, parethesis, braces
- [x] unknow syntax detection
- [x] closing pair parent check
- [x] detect file end with opened pair
- [x] stop return check (should be done withun upperway anyway, just for safety)
- [x] assert parsers length
- [x] C double quotes
- [x] C simple quotes
- [x] C comments
- [x] C operators
- [x] C identifiers
- [x] check memory issue
- [x]  fix overlapping issues check
- [x] better debug with line / col pos
- [x] function to parse a file directly
- [x] free function
- [x] dump ast function
- [x] string begin / end ptr check ?? function to access more easily the parents / childs while checking error
- [x] remove weird stuffs around ast primitves for debuggin g -> remove ctx, add a debug for ctx and an other for __FILE__
- [x] overlapping etc.. also specify macro name ? ORR maro that om ast syntax exec would populate ctx
- [x] create a list wrapper for named items (use klist from previous cedilla versions)

*MACROS*
- [x] ast macro engine
- [ ] emit #line for gcc

*COMPILER*
- [ ] implement compiler function

*SYNTAX*
- [ ] in-source syntax extensiohs

*DEMO*
- [ ] lambda
- [ ] async await with io uring backend
- [ ] defer keyword
- [ ] class


===

preprocessing :


=======


2nd pass :


Reverse order :

cedilla_load

cedilla_load ./modules/c99/c99
// (if (ast_type == id and prev == load do ...))

unsigned(ID) <--- TYPE
unsigned(TYPE) long(ID) <--- TYPE
unsigned long(TYPE) long(ID) <--- TYPE
unsigned long long(TYPE) 	f(ID) <--- VAR
unsigned long long(TYPE) 	f(ID) \( (Parenthesis)  <--- PROTOTYPE
unsigned long long 	f(int
unsigned long long 	f(int x
unsigned long long 	f(int x )
unsigned long long 	f(int x ) (PROTOTYPE) { (Braces) <--- named func decl
unsigned long long 	f(int x ) { instr
unsigned long long 	f(int x ) { instr }

===> This logic would be same in both 2 pass or reverse order ?
y e s

===> Is there is a risk for misinterpretation ?


shall syntax error checking be done in compile time or preprocessing time ? both ?
BOTH
