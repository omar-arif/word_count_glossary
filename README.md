# Glossaire Program

This C++ program processes a text file, counts the occurrences of each word, and outputs the word frequency into a new file. The input file is read, filtered for valid words, and the word count is stored in an unordered map. The output file contains each word and its frequency, sorted by occurrence.

## Features

- Reads an input file containing text data.
- Counts the occurrences of each word, filtering based on specific criteria (e.g., valid characters, length).
- Outputs a sorted glossary of words and their frequencies into a new file.
- Uses efficient data structures like unordered maps for fast lookup and insertion.

## Usage

1. **Compile the Program**:
   ```bash
   g++ -o glossary glossary.cpp
   ```
2. Run the Program:
   Pass the input text file as a command-line argument:
   ```bash
   ./glossary <input_file_path>
   ```
