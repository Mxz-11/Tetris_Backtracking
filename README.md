# Betris (Backtracking Tetris)

This repository contains the implementation of Betris, a variant of Tetris to test where the piece must be placed to optimize the available space.

<h1 align="center">
  <img src="https://media.tenor.com/SLT4ZkqLg7IAAAAC/twow-tr.gif" alt="Ten Words of Wisdom" />
</h1>

## Betris follows these features:

- Rectangular Board: The board dimensions (number of rows and columns) are provided as command-line arguments.

- Non-Rotating Pieces: Pieces cannot be rotated. Each piece is placed vertically on the board using a backtracking search strategy to assign columns so that rows are completely filled.

- Objective: The game ends when the specified number of complete rows is achieved or when it is determined that reaching this objective is impossible.

- Program Input: The parameters are provided via the command line in the following format:
  
  **nfils ncols objective delay N1 N2 N3 ... -1**

  **Where**:

    - nfils: Number of rows on the board.

    - ncols: Number of columns on the board.

    - objective: The target number of rows to be completed.

    - delay: Time in milliseconds to pause between board updates.

    - N1, N2, N3, ... -1: Sequence of piece identifiers. The sequence ends with -1. If the first piece identifier is negative, a random sequence of pieces is generated.
 
## Project Structure

    mainB.cpp: Main file that reads the input parameters and controls the execution of the game.

    betris.cpp: Implementation of the game functions as defined in the header file.

    betris.hpp: Header file defining constants, data types, and function prototypes required by the project.

    Makefile: Script for compiling the project.

    enunciado_trabajo_Prog2_betris.pdf: Project requirements document containing detailed specifications.

# Compilation and Execution

## Compilation

Ensure you have a C++ compiler (such as g++) installed. To compile the project, run:

```bash
make
```

This command will generate the executable mainB.

### Execution Example

For a basic example with 4 pieces, run:

```bash
./mainB 6 5 4 100 1 2 3 4 -1
```

Where:

- 6 is the number of rows on the board.

- 5 is the number of columns.

- 4 is the objective (target number of complete rows).

- 100 is the delay in milliseconds between updates.

- 1 2 3 4 are the piece identifiers.

- -1 marks the end of the piece sequence.

# Authors

  Javier Perez

  Máximo Valenciano
