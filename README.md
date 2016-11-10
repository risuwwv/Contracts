# Contracts
A basic pre-condition/post-condition checks implementation while waiting for C++17 contracts...

I had the idea to try to implement this while reading "Imperfect C++: Practical Solutions for Real-Life Programming".
The implementation uses RAII and macros. The checks are off by default, see command below for enabling them.

	PRE_CONDITION(test) checks that its parameter is true at the point of call, aborts on failure
	POST_CONDITION(test) checks that its parameter is true at the end of the scope containing the call, aborts on failure
	VALIDITY_CHECK(obj) checks obj.is_valid() at the point of call, aborts on failure
	INVARIANT_CHECK(obj) checks obj.is_valid() at the point of call and at the end of the scope containing the call, aborts on failure

See src/test.cpp for an example or src/contracts.h for the implementation.

Built on windows 10, with clang 3.7.0 and gcc 5.1.0.

Default compiler is clang and default compilation mode is release.

Example of command: 'make mode=release compiler=gcc checks=true'
Run 'make help' for details. 
