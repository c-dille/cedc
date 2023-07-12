# cedilla40

## TODO

- [x] restructre project
- [x] add klist to void*, free, type? as parser context objets for IE #define etc... + add a clone function
- [x] klist : add an exists function, and allow non pointers type
- [x] determine logic, way to parse and compile at same time for single file pass ?

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
- [ ] dump ast function
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
