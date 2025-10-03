# Terminal-Based Text Editor

A lightweight, terminal-based text editor written in **C++** using the **ncurses** library.  
Inspired by editors like **Vim** and **Nano**, this editor supports essential text-editing features along with efficient handling of larger files while maintaining a minimal memory footprint.

---
## Inspiration:
Somehow low level techy things exite me in a different way. well, c & cpp more than anything. (also, since it was my first language and I have more practice in it.) After starting this, feels almost as if I can build anything in c/cpp.. 

## Features

- **Navigation & Editing**
  - Smooth cursor navigation (arrow keys, word-wise movement)
  - Text insertion and deletion
  - Real-time word-wrap for readability
- **Advanced Functionalities**
  - Search and replace within files
  - Dynamic window resizing with instant layout adjustment
  - Scrolling support for larger files
- **Performance Optimizations**
  - Advanced buffering mechanisms for efficient editing
  - Minimal memory usage with dynamic data structures
  - Responsive user interaction with low input-to-display latency

---

## Technologies Used

- **C++** – Core programming language
- **ncurses** – Terminal handling and UI rendering
- **Data Structures** – Efficient buffer management for editing large files


---

## Installation & Usage

### Prerequisites

- Linux / macOS terminal with **ncurses** installed
- C++17 or later compiler (`g++`, `clang++`, etc.)

### Build Instructions

```bash
# Clone the repository
git clone https://github.com/p7729/Text-Editor-in-cpp.git
cd terminal-text-editor

# Build the project
make
```

### Run the Editor

```bash
./build/editor filename.txt
```

---

## Future Improvements

- Syntax highlighting for popular programming languages
- Undo/Redo functionality
- Configurable keybindings
- Multi-tab / buffer support

---

## Learning Outcomes

- Low-level terminal handling with **ncurses**
- Efficient buffer and memory management in **C++**
- Designing responsive CLI applications with real-time updates

---

## 🤝 Contributing

Contributions are welcome!  
Feel free to fork this repo, submit issues, and create pull requests.

---