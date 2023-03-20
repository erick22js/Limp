# Instructions

Create a src file called "main.asm" and put in the same directory as the assembler executable.

Run the executable, if has no any error, a file called "output.o" will be created with success, load it in the limp memory to execute.

# Syntax

The basic of any a assembly language:

* For instructions, follow the templates defineds in docs.json in folder util
* Each instruction has its own format, and specific descriptors for behavior changing, all this descripted in docs.xlsx
* All instructions can only be defined one for line
* Labels are defined in its classic way, your label name folowed by a colon. The assembler also allow you to stack labels definition in the same line, and followed by a instruction for easying syntax
* You can use binary arithmetic in literals, the available operators are: + - * / (Basic operators), % (Module), & | ^ (Bitwise operators), == != (Equality comparators), > < >= <= (Comparators), >> << (Shift operators), && || (Logical operators)
* The symbol @ is available as current program address reference, you may use in its literal way (ie, lonely or in binary arithmetic), or accomplish it with a literal value or address identifier (ex: @addr1, @50), this way, you can get relative jump offset

Also, the syntax have preprocessors:

* include => Includes a file from a relative source path
* predef => Defines the symbol before binary compilation phase
* const => Defines a constant in binary compilation phase

# Behaviors

The assembly has two phases:

* phase I => evaluates all the label address, and predef processors
* phase II => in this phase, the assembling is started, all other symbols are defined, the instructions are evaluated and compiled
