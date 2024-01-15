#pragma once

// These macros are used in the below template
#define OL_STR(x) #x


#define OL_OUTDATED_WARN(header_name, old_major, old_minor, new_major, new_minor, ...) \
"You are using an outdated verison (" OL_STR(old_major) "." OL_STR(old_minor) ") "    \
"of the common OL " OL_STR(header_name) " header! "                                   \
__VA_ARGS__																			    \
																					    \
"You have version " OL_STR(new_major) "." OL_STR(new_minor) " available. "            \
																					    \
"Update your other OL libaries OR "													\
"set " #old_major "=" OL_STR(new_major) " and " #old_minor "=" OL_STR(new_minor) " "  \
"in your project to use version " OL_STR(new_major) "." OL_STR(new_minor)


#define OL_VERSION_STR(major, minor) OL_STR(major) "." OL_STR(minor)



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
#define OL_<HEADER>_MAJOR_<LIBRARY> <VERSION_MAJOR>
#define OL_<HEADER>_MINOR_<LIBRARY> <VERSION_MINOR>


#if  OL_<HEADER>_MAJOR  < OL_<HEADER>_MAJOR_<LIBRARY> || \
	(OL_<HEADER>_MAJOR == OL_<HEADER>_MAJOR_<LIBRARY> && OL_<HEADER>_MINOR <= OL_<HEADER>_MINOR_<LIBRARY>)
#define OL_<HEADER>_<LIBRARY>_IS_NEWER true
#endif



#if  !defined(OL_<HEADER>_MAJOR) || \
	(!defined(OL_<HEADER>_DECLARED) && defined(OL_<HEADER>_<LIBRARY>_IS_NEWER))


<CODE>



#undef OL_<HEADER>
#undef OL_<HEADER>_MAJOR
#undef OL_<HEADER>_MINOR

#define OL_<HEADER>          OL_VERSION_STR(OL_<HEADER>_MAJOR_<LIBRARY>, OL_<HEADER>_MINOR_<LIBRARY>)
#define OL_<HEADER>_MAJOR    OL_<HEADER>_MAJOR_<LIBRARY>
#define OL_<HEADER>_MINOR	  OL_<HEADER>_MINOR_<LIBRARY>
#define OL_<HEADER>_DECLARED true

#elif defined(OL_<HEADER>_<LIBRARY>_IS_NEWER)
#pragma message(OL_OUTDATED_WARN(endian, OL_<HEADER>_MAJOR, OL_<HEADER>_MINOR, OL_<HEADER>_MAJOR_<LIBRARY>, OL_<HEADER>_MINOR_<LIBRARY>, "<OPTIONAL_CONSEQUENCE_EXPLANATION>"))
#endif
**********************************************/