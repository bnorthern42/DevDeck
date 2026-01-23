---
name: DevDeck - Coding standards
---

C++:
- Prefer modern C++ (C++17/20 depending on project settings)
- Use RAII, smart pointers where ownership is non-trivial
- Keep functions small and readable

Qt:
- Use signals/slots idiomatically
- Keep UI wiring in MainWindow/UI layer; keep process/run logic in a separable component if it grows

Always update README when completing major MVP milestones.
