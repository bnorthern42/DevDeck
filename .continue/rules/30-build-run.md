---
name: DevDeck - Build/run expectations
---

Build/Run pipeline requirements:

- Build and run must be driven by the selected language JSON in lang/
- Support variable substitution (at minimum): ${SRC}, ${WORKDIR}, ${OUT}
- Run build then run (or just run where applicable)
- Capture stdout + stderr + exit code and render in output panel
- Never freeze the UI: run external commands async (Qt process / threads)
