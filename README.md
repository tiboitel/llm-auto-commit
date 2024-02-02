# llm-auto-commit

[![License](https://img.shields.io/github/license/tiboitel/llm-auto-commit)](LICENSE) ![GitHub Repo stars](https://img.shields.io/github/stars/tiboitel/llm-auto-commit) ![GitHub forks](https://img.shields.io/github/forks/tiboitel/llm-auto-commit)

## Description

Automate your commit messages effortlessly with llm-auto-commit. This project utilizes the LLM API to generate commit messages, streamlining the development workflow. Enhance productivity and maintain clarity in your version control history. Easy integration, minimal setup.

## Features

⚡️ Minimal setup \
⚡️ LLM API integration \

# Exemple

Example of use:

```bash
./llm-auto-commit "documentation lolf my chat popup ok"
git commit -m "docs(chat): update chat popup documentation"
```


---

## Getting Started 🚀

Instructions to set up and run a copy of the project on a local machine for development and testing purposes. Detailed notes on deployment can be found below.

### Prerequisites 📋

You need to have [curl](https://curl.haxx.se/), [json-c](https://github.com/json-c/json-c), [gcc](https://gcc.gnu.org/) installed on your computer.

```bash
curl@latest_version
json-c@latest_version
gcc@latest_version
```

To install dependencies on Ubuntu:

```bash
sudo apt-get update && sudo apt-get install -y curl libjson-c-dev gcc
```

To install dependencies on Arch:

```bash
sudo pacman -Syu --noconfirm && sudo pacman -S --noconfirm curl json-c gcc
```

In case you are using Windows, well, I can only advice you to reconsider your lifestyle. I use Arch btw.

### How To Use 🔧

Clone the repository and navigate to it in the terminal:

```bash
# Clone the repository
$ git clone https://github.com/tiboitel/llm-auto-commit/

# Move into the repository
$ cd llm-auto-commit
```

Build the project:

```bash
# Build llm-auto-commit
$ make
```

Run llm-auto-commit:

```bash
# Usage
$ ./llm-auto-commit [MESSAGE]
# Transforms MESSAGE into a formatted commit message.
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Author 

tiboitel - [GitHub Profile](https://github.com/tiboitel)


