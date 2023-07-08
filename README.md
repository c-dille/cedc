# cedilla40

## TODO

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
- [ ] function to parse a file directly
- [ ] free function
- [ ] dump ast function
- [x] string begin / end ptr check ?? function to access more easily the parents / childs while checking error
- [x] remove weird stuffs around ast primitves for debuggin g -> remove ctx, add a debug for ctx and an other for __FILE__
- [x] overlapping etc.. also specify macro name ? ORR maro that om ast syntax exec would populate ctx

*COMPILER*
- [ ] ast macro engine
- [ ] emit #line for gcc

*SYNTAX*
- [ ] in-source syntax extensiohs

*DEMO*
- [ ] lambda
- [ ] async await with io uring backend
- [ ] defer keyword
- [ ] class
