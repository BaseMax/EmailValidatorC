# Email List Filtering Program

The Email List Filtering Program is a C language program designed to validate and filter a list of email addresses. It ensures that each email address in the provided text file is valid and exists. The program helps to identify and remove fake or incorrect email addresses from the list, ensuring that the remaining email addresses are valid and reachable.

## Features

- Validates email addresses to check their format and structure.
- Verifies if an email address exists by checking its domain and server connectivity.
- Filters out invalid or fake email addresses, producing a clean and accurate list.

## Requirements

To run the Email List Filtering Program, you need a C compiler installed on your system.

## Usage

- Place your email list in a text file (e.g., email_list.txt), with one email address per line.
- Ensure that the text file is in the same directory as the C source file (email_filter.c).
- Open a terminal or command prompt and navigate to the directory containing the C source file.
- Compile the source code by executing the following command:

```bash
gcc email_filter.c -o email_filter
```

Run the compiled program by executing the following command:

```bash
./email_filter email_list.txt
```

Make sure to replace email_list.txt with the actual name of your text file.

The program will process the email addresses, validate their format, and check their existence.

After completion, the program will generate two text files:

- `valid_emails.txt`: Contains the list of valid and reachable email addresses.
- `invalid_emails.txt`: Contains the list of invalid or fake email addresses.

## Note

The program uses simple heuristics to validate email addresses and check their existence. However, keep in mind that not all email servers allow external validation, so the program might not be able to determine the existence of all email addresses.

It's recommended to review the results manually as well, as the program's validation is based on certain assumptions and heuristics.

Ensure that you have the necessary permissions to access and modify files in the directory where the program and email list are located.

## License

This program is released under the GPL-3.0 License. Feel free to modify and distribute it according to your needs.

## Disclaimer

The Email List Filtering Program aims to improve the accuracy of email lists by validating and filtering email addresses. However, it cannot guarantee 100% accuracy, as email address validation depends on various factors beyond the program's control. Use the program at your own risk.

If you encounter any issues or have suggestions for improvement, please feel free to contribute or open an issue on the project's GitHub repository.

Copyright 2023, Max Base
