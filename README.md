# simpleRecognizingDFA
A simple DFA that recognize words and comments.
This DFA is the first part in the creation of a Lexer.
A *lexer* should take an input string and split it in his base elements: *tokens*.
This DFA job is to recognize specifics tokens.

## Classes of the DFA
In this little project we have 3 classes:
- **AbstractDFA**: this class represent an arbitrary DFA with states and transitions;
- **WordDFA**: instantiated with a string, this DFA recognize the word specified;
- **CommentDFA**: DFA that recognise inline comments and multilines comments.

You'll find some simple examples in the **test** directory. There is a Makefile to help you with compiling.
After compiling, with the test folder you can use:
```
./main test/test1.txt
```
### Type of comments acceppted
*//comment*
*(&ast;comment&ast;)*
*{comment}*


This project is a work I made for my university (Universita' degli Studi di Padova) in the Automata and Formal Language course, so the "skeleton" of the project is made by them, just to be precise.
