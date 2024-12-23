# `xls` Linux Program 

This repository contains an implementation of the `ls` command, replicating the functionality of the GNU `ls` command in Bash. The program provides detailed information about files and directories, including attributes and metadata. It also features intuitive color coding to distinguish between different file types.

## Credits
This project was part of STMicroelectronics Internship program "Linux System Programming".
Under supervision of Eng. Reda Maher.

---

## Features

- **Inode Number**: Displays the inode number of each file.
- **Hard Link Count**: Shows the number of hard links associated with each file.
- **File Size**: Displays the size of each file in bytes.
- **File Permissions**: Displays file permissions, including special permissions (setuid, setgid, sticky bit).
- **File Type**: Identifies file types such as:
  - Regular files
  - Directories
  - Block device files
  - Character device files
  - Symbolic links
  - FIFOs
  - Sockets
- **Modification Timestamp**: Shows the last modification time of each file.
- **Intuitive Colors**: Distinguishes between file types using intuitive colors for improved readability.

These are obtained by passing the right option to the "ls" command

---

## How to Build

1. Clone the repository:
   ```bash
   git clone https://github.com/AhmedDesoky14/myls
   cd myls
   ```
2. Compile the program:
   ```bash
   make xls
   make install
   ```

---

## Usage

Run the program in the terminal

```bash
xls
```

---

## Features Highlight

### File Types with Color Coding and Permissions Display

Same as GNU "ls" command

---

## Contact 

For questions or suggestions, please contact me, Ahmed Desoky at "ahmed0201150@gmail.com".
