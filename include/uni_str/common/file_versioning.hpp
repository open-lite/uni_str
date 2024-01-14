#pragma once

// These macros are used in the below template
#define OCT_STR(x) #x


#define OCT_OUTDATED_WARN(header_name, old_major, old_minor, new_major, new_minor, ...) \
"You are using an outdated verison (" OCT_STR(old_major) "." OCT_STR(old_minor) ") "    \
"of the common OCT " OCT_STR(header_name) " header! "                                   \
__VA_ARGS__																			    \
																					    \
"You have version " OCT_STR(new_major) "." OCT_STR(new_minor) " available. "            \
																					    \
"Update your other OCT libaries OR "													\
"set " #old_major "=" OCT_STR(new_major) " and " #old_minor "=" OCT_STR(new_minor) " "  \
"in your project to use version " OCT_STR(new_major) "." OCT_STR(new_minor)


#define OCT_VERSION_STR(major, minor) OCT_STR(major) "." OCT_STR(minor)



/// Template for versioning a file/header within a library
/// Meant for compatibility within headers that could be re-used (and thus have duplicate code) in other libraries

/// NOTE: 
/// Only use when you forsee that said header could have changes (that actually affect end-user code) in the future. 
/// If you do use this template, list why in the file you're using it in.
/// If you do not forsee such changes, then just use a common include guard instead of this template

// REPLACE: <INCLUDES>, <EXPLANATION>, <HEADER>, <LIBRARY>, <OPTIONAL_CONSEQUENCE_EXPLANATION>, <VERSION_MAJOR>, <VERSION_MINOR>

/***********************************************
<INCLUDES>



// <EXPLANATION>
#define OCT_<HEADER>_MAJOR_<LIBRARY> <VERSION_MAJOR>
#define OCT_<HEADER>_MINOR_<LIBRARY> <VERSION_MINOR>


#if  OCT_<HEADER>_MAJOR  < OCT_<HEADER>_MAJOR_<LIBRARY> || \
	(OCT_<HEADER>_MAJOR == OCT_<HEADER>_MAJOR_<LIBRARY> && OCT_<HEADER>_MINOR <= OCT_<HEADER>_MINOR_<LIBRARY>)
#define OCT_<HEADER>_<LIBRARY>_IS_NEWER true
#endif



#if  !defined(OCT_<HEADER>_MAJOR) || \
	(!defined(OCT_<HEADER>_DECLARED) && defined(OCT_<HEADER>_<LIBRARY>_IS_NEWER))


<CODE>



#undef OCT_<HEADER>
#undef OCT_<HEADER>_MAJOR
#undef OCT_<HEADER>_MINOR

#define OCT_<HEADER>          OCT_VERSION_STR(OCT_<HEADER>_MAJOR_<LIBRARY>, OCT_<HEADER>_MINOR_<LIBRARY>)
#define OCT_<HEADER>_MAJOR    OCT_<HEADER>_MAJOR_<LIBRARY>
#define OCT_<HEADER>_MINOR	  OCT_<HEADER>_MINOR_<LIBRARY>
#define OCT_<HEADER>_DECLARED true

#elif defined(OCT_<HEADER>_<LIBRARY>_IS_NEWER)
#pragma message(OCT_OUTDATED_WARN(endian, OCT_<HEADER>_MAJOR, OCT_<HEADER>_MINOR, OCT_<HEADER>_MAJOR_<LIBRARY>, OCT_<HEADER>_MINOR_<LIBRARY>, "<OPTIONAL_CONSEQUENCE_EXPLANATION>"))
#endif
**********************************************/