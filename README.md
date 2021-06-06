# simpleRecognizingDFA
A simple DFA that recognize words and comments.

## Table of contents:
- [General info](General-info)
- [File Descriptions](File-descriptions)
- [Set up](Set-up)
- [Usage](Usage)
- [Credits](Credits)

## General info
This DFA is the first part in the creation of a Lexer.
A *lexer* should take an input string and split it in his base elements: *tokens*.
This DFA job is to recognize specifics tokens.

### Classes of the DFA
In this little project we have 3 classes:
- **AbstractDFA**: this class represent an arbitrary DFA with states and transitions;
- **WordDFA**: instantiated with a string, this DFA recognize the word specified;
- **CommentDFA**: DFA that recognise inline comments and multilines comments.

## File descriptions
- Makefile: self explanatory, the file for the make command;
- automata.h: header file, with the declaration of the 3 classes.
- automata.cpp: file with classes initializations
- main.cpp: self explanatory.

## Set up
You need to download **ANTLR v4** from the [official page](https://www.antlr.org/download.html) and the **c++ runtime dev** [libantlr4-runtime-dev](https://packages.debian.org/sid/libantlr4-runtime-dev).

## Usage
You'll find some simple examples in the **test** directory. There is a ***Makefile*** to help you with compiling, using ```make``` (use ```make clean``` to reverse).
After compiling, with the test folder you can use:
```
./main test/test1.txt
```
### Type of comments acceppted
- *//comment*
- *(&ast;comment&ast;)*
- *{comment}*

## Credits
This project is a test I made for my university ([Universita' degli Studi di Padova](https://www.unipd.it/)) in the Automata and Formal Language course, so the "skeleton" of the project is made by them.
