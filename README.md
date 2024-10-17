<h1 align="center"> 💾Minishell</h1>

<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C"/>
  <img src="https://img.shields.io/badge/Shell-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white" alt="Shell"/>
  <img src="https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white" alt="42"/>
</p>

<p align="center">
  A minimalistic shell implementation inspired by Bash, developed as part of the 42 curriculum.
</p>

## 📋 Overview

Minishell is a custom shell implementation that replicates core Bash functionalities. This project focuses on understanding the fundamentals of shell programming, process management, and inter-process communication in Unix-like systems.

## ✨ Features

### Built-in Commands
- `env`: Display environment variables
- `echo`: Print text to standard output
- `cd`: Change current directory
- `unset`: Remove environment variables
- `export`: Set environment variables
- `exit`: Exit the shell

### Command Handling
- Input/Output redirections (`>`, `<`, `>>`)
- Pipes (`|`) for command chaining
- Here-documents (`<<`) for custom input
- Environment variable expansion
- Wildcard pattern matching

### Process Management
- Fork and execute child processes
- Pipeline implementation
- Signal handling
- Error management

## 🚀 Getting Started

### Prerequisites
- GCC compiler
- Make
- Unix-like operating system

### Installation
```bash
# Clone the repository
git clone https://github.com/lciullo/Minishell
cd minishell

# Compile the project
make
```

### Usage
```bash
# Run the shell
./minishell
```
## 🎯 Project Objectives

- Implement essential shell functionalities
- Handle command line parsing and execution
- Manage process creation and communication
- Implement environment variable management
- Handle various types of redirections and pipes
- Ensure proper error handling and memory management

## 🤝 Contributors

- **Lisa Ciullo** - [@lciullo](https://github.com/YOUR_USERNAME)
- **Clémence Llovio** - [@clemllovio](https://github.com/clemllovio)

## 🧠 Learning Outcomes

This project provided valuable experience in:
- Low-level system programming
- Process management and IPC
- Shell behavior and command interpretation
- Collaborative development and code organization
- Advanced error handling and memory management
- Git workflow and team collaboration

## 📝 License

This project is part of the 42 school curriculum. 
