# AGENTS.md

## Cursor Cloud specific instructions

**CxOOP** is a single-header C macro library (~85 lines) providing OOP features (classes, inheritance, polymorphism, encapsulation) for plain C with zero runtime overhead.

### Project structure

- `CxOOP_lib/CxOOP.h` — the library (single header)
- `example/` — Shape → Circle → Sphere demo (builds to `./bin/example`)
- `test/` — 8 unit test programs

### Build, test, run

All commands run from the repository root. See `README.md` for full details.

- **Build:** `make` (produces `./bin/example`)
- **Run example:** `./bin/example`
- **Run tests:** `make test` (compiles and runs all 8 test suites)
- **Clean:** `make clean`

### Notes

- The only system dependencies are `gcc` (C99) and `make` — no package managers, containers, or external services.
- Compiler warnings about "address will always evaluate as true" in `DCAST` macro usage are expected and benign; they come from using `DCAST` on stack variables whose address is never NULL.
- There is no linter configured; compilation with `-Wall` serves as the lint step.
- No `.devcontainer`, Docker, or CI/CD configuration exists in this repo.
