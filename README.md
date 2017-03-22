# Translators Project
## CS480 - Translators
### Oregon State University - Winter 2017
### By Helena Bales

#### Overview
This project is made up of three main parts, the scanner, the parser, and the checker. These parts are
 called from the translator. They work together to create a Symbol Table and Parse Tree of a file 
given as a command line argument. The translator checks that the file is syntatically valid by first 
scanning it, then parsing it, then checking it. This assignment is for the CS480 course at Oregon 
Stat University in Winter term of 2017.

#### Files
- `Makefile` - a script to compile the project (see Compiling)

- `translator.cpp` - the translator, contains the main function for the project

- `scanner.h` - header file for the scanner

- `scanner.cpp` - the scanner, called by the parser, responsible for scanning and tokenizing the file.

- `parser.h` - header file for the parser

- `parser.cpp` - the parser, called by the translator, responsible for parsing tokens from the scanner.

- `checker.h` - header file for the checker

- `checker.cpp` - the checker, called by the translator, responsible for checking the parse tree from 
the parser

- `treenode.h` - header file for the treenode

- `treenode.cpp` - the TreeNode constructor

- `token.h` - the Token struct used by the scanner and parser

- `enum.h` - contains all the possible token values and enumerates them for use throughout translator.

- `test.cm` - program to provide as test input for the translator

- `test2.cm` - a second program to provide as test input for the tranlator

#### Compiling
From the directory containing the files listed above, type `make`. This will compile the whole 
translator. The Makefile contains more possible targets that can be specified by typing 
`make <target>`.

#### Running
Use the following commands to run the translator with the provided tests files while in the directory 
containing the files listed in the Files section of this document.

`./translator ./test.cm`

`./translator ./test2.cm`

Use the following command to run the translator on any other text file.

`./translator <file>`

#### Acknowledgements
I would like to Acknowledge Josh Bowen for his help with this assignment. We worked together on 
the scanner and parser, both of which he helped to explain to me. He also wrote the test files.

