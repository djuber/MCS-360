#!/bin/sh
echo "updating Doxyfile"
# append options to end of Doxyfile, this
# overrides the defaults.
# this is called from the main directory make, and 
# inherits cwd from the environment (no ../ needed)
cat >> Doxyfile <<EOF


PROJECT_NAME           = "Integer Dictionary Program"
PROJECT_BRIEF          = "MCS 360 Project 4"
TAB_SIZE               = 4
BUILTIN_STL_SUPPORT    = YES
SOURCE_BROWSER         = YES
INLINE_SOURCES         = YES
EXTRACT_PRIVATE        = YES
REFERENCES_RELATION    = YES
HTML_DYNAMIC_SECTIONS  = YES
PAPER_TYPE             = letter
LATEX_SOURCE_CODE      = YES
HAVE_DOT               = YES
HIDE_UNDOC_RELATIONS   = YES
UML_LOOK               = YES
CALL_GRAPH             = YES
CALLER_GRAPH           = YES

EOF

echo "Done"