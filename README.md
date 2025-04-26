# Quiz Game Application (C++ Project)

This is a simple command-line **Quiz Game** built using C++.  
The program allows users to answer multiple-choice questions from different categories and difficulty levels, track their scores, and save results to various file formats (text, CSV, and binary).

---

## Features

- Welcome screen and player name input
- Choose among multiple categories:
  - History
  - Geography
  - Computer Science
  - Science
- Difficulty levels:
  - Easy
  - Medium
  - Hard
- Score tracking during the quiz
- Display individual scores and overall leaderboard
- Save scores into:
  - Plain text files
  - CSV files
  - Binary files

---

## Files

| File | Description |
|:-----|:------------|
| `test 2.cpp` | Main source file containing all classes, functions, and the game flow logic. |

---

## Technologies Used

- C++ Standard Libraries (`iostream`, `fstream`, `string`, `conio.h`)
- Object-Oriented Programming (Classes: `Question`, `SubCategories`, `ScoreCollector`)
- File handling:
  - Text file operations
  - CSV file operations
  - Binary file operations

---

## How to Run

1. Make sure you have a C++ compiler installed (e.g., GCC, Visual Studio).
2. Compile the program:
   ```
   g++ "test 2.cpp" -o quiz_game
   ```
3. Run the executable:
   ```
   ./quiz_game
   ```

---

## Notes

- The program uses `WELCOME.txt` file to display a welcome screen. Ensure it is present in the same directory.
- Leaderboards and individual score files are created automatically during the game.
- This project was built as my term project for "Object Oriented Programming" course.
