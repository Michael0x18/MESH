MESH: The Mathematical Evaluation SHell
=======================================

MESH is a frontend for the accompanying mathematical expression parser.
It is designed with platform compatibility in mind, and will eventually allow BOS to be used as a calculator, in addition to as a more complex environment. The project is in the alpha stage, and I take no responsibility for any bugs that may occur.
In other words, DO NOT USE MESH IN ITS CURRENT STATE AS YOUR SOLE CALCULATION ASSISTANT. Again: DO NOT USE MESH IN ITS CURRENT STATE AS YOUR SOLE CALCULATION ASSISTANT. Threre is a high probability that some undiscovered bug with expression parsing, construction, and evaluation.

TODO:
 - [ ] Polish up frontend, including allowing scrolling of up to 30 entries
 - [ ] Integrate copy and paste with a system clipboard
 - [ ] Add ability to pretty-print expressions, including correct justification of exponents.
 - [ ] Refactor code

Bigger TODOs:
 - [ ] Rewrite evaluation engine to use real numbers instead of floats.
 - [ ] Rewrite evaluation engine to handle the usage of variables.
 - [ ] Add basic flow control structures and change evaluation engine into a simple interpreter.
 - [ ] Add basic computer algebra system capability, possibly by porting an existing (and likely well known) CAS.
