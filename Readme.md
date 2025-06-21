# DevDeck

**DevDeck** is a lightweight, multi-language code scratchpad built with **Qt** and **C++**. It offers a clean, focused environment for writing, building, and running small snippets of code in various programming languages—all from a single desktop GUI.

---

## ✨ Features **TODO**

- 🧠 **Multi-language support** (Python, C++, JavaScript, etc.)
- 🧰 **Custom build & run commands** per language
- ✍️ **Syntax-highlighted code editor**
- 📥 **Console output display** for stdout/stderr
- 📂 **Language templates via JSON** in `lang/` folder
- 🎨 **Dark/light theme support** via QSS stylesheets
- 🧩 Built using **Qt Widgets**, **CMake**, and clean modular C++

---

## 🖥️ Screenshot

> Coming soon — stay tuned!

---

## 🔧 Building DevDeck

### Requirements

- Qt 6.x
- CMake 3.16+
- C++17 or later compiler

### Build Instructions

```bash
# Clone and build
git clone https://github.com/yourname/devdeck.git
cd devdeck
mkdir build && cd build
cmake ..
make
./DevDeck
```

---

## 📁 Project Structure

```
DevDeck/
├── CMakeLists.txt             # CMake build script
├── main.cpp                   # Entry point
├── mainwindow.{cpp,h,ui}      # Main UI logic
├── lang/                      # Language templates (JSON)
├── icons/                     # Icons for sidebar/UI
├── styles/                    # QSS stylesheets (dark.qss, etc.)
├── resources.qrc              # Embedded resource config
└── output/                    # Optional: output logs (runtime)
```

---

## 📜 License

This project is licensed under the **MIT License**.

```
MIT License

Copyright (c) 2025 Brad Northern

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction...
```

Full license text is available in the LICENSE file.

---

## 📫 Contributing / Feedback

- Open issues for bugs, feature requests, or ideas
- Pull requests welcome!

> DevDeck is a solo-built open-source tool for quick coding experiments — contributions are appreciated!

---

Made with ❤️ in Qt Creator.

