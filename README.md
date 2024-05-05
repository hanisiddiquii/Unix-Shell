# Unix Shell Project

Welcome to the Unix Shell project repository! This project aims to create a simple Unix shell with various features and functionalities. The shell is developed in C programming language and provides a command-line interface for users to interact with the operating system.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Documentation](#documentation)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Command Execution**: Execute various system commands and utilities.
- **Built-in Commands**: Includes built-in commands like `ls`, `cd`, `echo`, `pwd`, `pinfo`, and more.
- **Redirection**: Redirect input and output of commands using `<`, `>`, and `>>`.
- **Piping**: Execute commands with pipes (`|`).
- **Background Processes**: Run processes in the background using `&`.
- **Signal Handling**: Handle signals such as `SIGINT`, `SIGTSTP`, and `SIGCHLD`.
- **History**: Maintain command history and support for repeating commands.
- **Job Control**: Manage background jobs with `fg` and `bg` commands.
- **Help**: Provides help information about available commands.
- **Find**: Search for files and directories.

## Installation

To install and run the Unix Shell project, follow these steps:

1. Clone the repository to your local machine:

   ```bash
   git clone https://github.com/hanisiddiquii/Unix-Shell
   ```

2. Navigate to the project directory:

   ```bash
   cd unix-shell
   ```

3. Compile the source code using the provided Makefile:

   ```bash
   make
   ```

4. Run the shell executable:

   ```bash
   ./shell
   ```

## Usage

Once the shell is running, you can interact with it using various commands and utilities. Here are some examples:

- Execute system commands:

  ```bash
  ls -l
  ```

- Use built-in commands:

  ```bash
  cd directory_name
  ```

- Redirect input and output:

  ```bash
  cat input_file > output_file
  ```

- Execute commands with pipes:

  ```bash
  ls | grep keyword
  ```

- Run processes in the background:

  ```bash
  sleep 10 &
  ```

- View command history:

  ```bash
  history
  ```

For more detailed usage instructions, refer to the documentation section below.

## Documentation

Detailed documentation of the Unix Shell project can be found [here](/docs/Unix-Shell-Project-Report.docx). It includes descriptions of various features, usage examples, and code documentation.

## Contributing

Contributions to the Unix Shell project are welcome! If you'd like to contribute, please follow these guidelines:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature`)
3. Make your changes.
4. Commit your changes (`git commit -am 'Add new feature'`)
5. Push to the branch (`git push origin feature`)
6. Create a new Pull Request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

