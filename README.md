# Sloth

Sloth is a custom compiler designed to transform high-level source code into
machine-readable instructions. This project was intended for me to gain a deeper understanding of compilers, software development, and strengthen my
knowledge of the language C. 

# Features

- Lexical Analysis: Tokenizes the input source code into meaningful tokens
- Syntax Parsing: Analyzes the token stream to ensure adherence to the language
grammar
- Semantic Analysis: Checks for meaningfulness and correctness of the source code
- Intermediate Code Representation (IR): Transforms source code into an intermediate format for easier optimization and code generation.
- Code generation: Outputs assembly or bytecode instructions

# Directory Structure
|--- src/              # Source code files
|    |--- lexer.c       # Lexical analysis implementation
|    |--- parser.c      # Syntax parsing implementation
|    |--- semantic.c    # Semantic analysis implementation
|    |--- codegen.c     # Code generation implementation
|    |___ main.c        # Main entry point of the compiler
|--- include/          # Header files
|    |--- lexer.h       # Lexer header file
|    |--- parser.h      # Parser header file
|    |--- common.h      # Common definitions
|--- tests/            # Test cases for various modules
|--- docs/             # Documentation files
|--- build/            # Build artifacts (ignored in version control)

# Getting Started

Prerequisites
 - C Compiler: GCC or Clang
 - Build tools: Make or an equivalent build system
 - Git: Version control system

# Installation
    1. Clone the repository
        git clone  https://github.com/your-username/Sloth.git
        cd Sloth
    2. Build the compiler:
        make
    3. Run tests
        make test

# Usage
Compile a source file:
    ./sloth source.sloth

# Contributing
Contributions are welcome! To contribute:
    1. Fork the repository
    2. Create a new branch:
        git checkout -b feature-name
    3. Make your changes and commit them:
        git commit -m "Add commit message"
    4. Push the branch:
        git push origin feature-name
    5. Open a Pull Request

# License
This project is licensed under the MIT License. See the LICENSE file for details.

# Acknowledgements
    - Inspired by classic compilers like GCC and LLVM
    - Resources: "Compilers: Principles, Techniques, and Tools" (Dragon Book)
    - Open-source contributions and community support