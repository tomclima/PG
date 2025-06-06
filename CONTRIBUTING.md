# Contribution Guide

Thank you for your interest in contributing! To keep the project organized, consistent, and easy to maintain, we ask that you please follow the guidelines below.

## Development Workflow

1. **Setup Environment**: Ensure your environment is configured as described in the "Development Environment Setup" section.
2. **Create a Branch**: Follow our "Branching Strategy" to create a new branch for your feature or fix.
3. **Code**: Make your changes, following the guidelines in "Code Style" and "Adding New Classes".
4. **Test**: Ensure all tests pass by running `ctest --preset test` from the project root. Add new tests to cover your changes.
5. **Commit**: Use our "Commit Message Style" to write a clear and descriptive commit message.
6. **Open a Pull Request**: Follow the "Pull Request Process" to submit your changes for review.

---

## Adding New Classes to the `Prism` Library

All new public classes added to the `Prism` library must follow a specific header file structure. This ensures consistency and proper functionality with our shared library setup, which requires symbols to be correctly exported.

### Required Header Pattern

```cpp
#ifndef PRISM_YOURCLASS_HPP_
#define PRISM_YOURCLASS_HPP_

#include "Prism_export.h"

namespace Prism {

    class Prism_EXPORT YourClass {
        // Class implementation here
    };

}  // namespace Prism

#endif  // PRISM_YOURCLASS_HPP_
```

**Rules:**

- **Include Guard**: Use the format `PRISM_<CLASSNAME_IN_UPPERCASE>_HPP_`.
- **Export Header**: Always include `"Prism_export.h"`.
- **Namespace**: All code must be wrapped within the `namespace Prism`.
- **Export Macro**: The class declaration must be `class Prism_EXPORT YourClass`.

---

## Code Style and Formatting

To ensure a uniform code style across the project, we use **Clang-Format**. A configuration file (`.clang-format`) should be present at the root of the repository to define the style rules.

- **Before committing**, please format your code files.
- If you use VS Code with the C/C++ extension, you can configure it to format automatically on save.

---

## Commit Message Style

We follow the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/) specification. This helps us maintain a clean history and generate changelogs automatically.

- **`feat:`**: For new features. Ex: `feat(parser): Add support for quad faces`.
- **`fix:`**: For bug fixes. Ex: `fix(core): Correct vector normalization for zero-length vectors`.
- **`docs:`**: For documentation changes. Ex: `docs: Update installation instructions in README`.
- Other types: `style:`, `refactor:`, `test:`, `build:`.

---

## Branching Strategy

Please use the following prefixes when creating a new branch:

- **New Features**: `feat/<short-description>` (e.g., `feat/texture-mapping`)
- **Bug Fixes**: `fix/<bug-description>` (e.g., `fix/off-by-one-in-parser`)

---

## Development Environment Setup

For the best development experience, we recommend using **Visual Studio Code** with the following extensions:

- `ms-vscode.cpptools-extension-pack`: Essential pack for C++ development.
- `ms-vscode.cmake-tools`: Integrates with our CMake build system and CTest.
- `xaver.clang-format`: For automatic code formatting.

---

## Pull Request (PR) Process

When opening a Pull Request, please fill out the description to help us understand your changes. Ensure your PR meets the following checklist:

- [ ] My code compiles without errors or new warnings.
- [ ] All existing tests pass with my changes.
- [ ] I have added new tests that prove my fix is effective or that my feature works.
- [ ] My code follows the style guidelines and has been formatted with Clang-Format.
- [ ] My commit messages and PR title follow the Conventional Commits standard.
