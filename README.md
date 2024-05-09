## Pipex

Pipex is a 42 project where you create a program that simulates the behavior of the shell pipe operator ('|') in UNIX systems. The goal is to execute two commands provided as arguments to your program, with the output of the first command piped as input to the second command. This project helps reinforce your understanding of process management, file descriptors, and inter-process communication.

*For more information, please refer to the subject in the git.*

## Installation

To install Pipex, clone the project from the Git repository:

```bash
git clone git@github.com:fZpHr/pipex_42.git
cd pipex_42
```

Then compile the executable using the provided Makefile:

```bash
make
```

## Usage

To run Pipex, execute the following command:

```bash
./pipex file1 cmd1 cmd2 file2
```

Where:
- `file1` is the input file whose contents will be piped to `cmd1`.
- `cmd1` is the first command to execute, whose output will be piped to `cmd2`.
- `cmd2` is the second command to execute, which will receive the output of `cmd1` as input.
- `file2` is the output file where the final result will be written.

## Example

Here is an example of how to use Pipex:

```bash
./pipex infile "ls -l" "wc -l" outfile
```

## Description

The program will execute the two provided commands (`cmd1` and `cmd2`) sequentially, with the output of `cmd1` piped as input to `cmd2`. The final result will be written to `file2`.

## Bonus

For bonus functionality, additional features such as handling multiple pipes or heredoc.

## Usage with Bonus Features

To compile Pipex with bonus features, use the following command:

```bash
make bonus
```

Then you can use Pipex with additional features, such as handling multiple pipes:

```bash
./pipex file1 "grep keyword" "sort -r" "head -n 10" file2
./pipex here_doc LIMITER "ls -l" "wc -l" outfile
```

In this example, the output of `grep` is piped to `sort`, and then the output of `sort` is piped to `head`, with the final result written to `file2`.

