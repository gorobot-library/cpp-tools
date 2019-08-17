# CPP-TOOLS

An opinionated collection of tools for C++ development.

- [clap](#clap)
- [manifesto](#manifesto)
- [scaffold](#scaffold)
- [tpl](#tpl)

## Why?

Javascript, Python, and Node.js have set the standard for command-line tools
that help set up a new project. It's time C++ had the same.

## How do I use this?

### Installation

Install the tools using CMake.
```
> git clone https://github.com/gorobot-library/cpp-tools.git
> cd cpp-tools
> mkdir build
> (cd build && cmake .. && make && make install)
> manifesto -v
```
_Or..._ use the Docker image to avoid clutter on
your system (__Recommended__).
```
> git clone https://github.com/gorobot-library/cpp-tools.git
> cd cpp-tools
> docker build -t cpp-tools .
> docker run --rm -it -v "$PWD:/data" cpp-tools sh
> # cd data
> # manifesto -v
```

### The `.manifest.yaml` Configuration File

All of your project's configuration is stored in a `.manifest.yaml`
config file. Run `manifesto init` in your project directory to generate a new
config file with a step-by-step command-line walkthrough.

> The config file supports a stripped-down version of YAML. Some features, such
> as literal blocks, folded blocks, and the abbreviated form of dictionaries and
> lists are unavailable. These will produce unnexpected results and should be
> avoided.

Once you have a config file,  run `scaffold` in the project directory to
generate a minimal project skeleton.

Sample `.manifest.yaml` file:
```yaml
project: TestProject
version: 0.1.0
author: Jeffrey "The Dude" Lebowski

build: cmake
ci: travis

structure: gnu
```

#### Config File Structure

Configure the name of the project.
```yaml
project: TestProject
```

The project version.
```yaml
version: 0.1.0
```

Add the author (singular) and the contributors (plural) to the config file.
```yaml
author: Jeffrey "The Dude" Lebowski
contributors:
  - Walter Sobchak
  - Theodore Donald "Donny" Kerabatsos
```

Basic project info, such as the project description, the project keywords, and
the license info.
```yaml
description: "The most super cool project ever."
keywords:
  - awesome
  - super cool
license: MIT
```

The build system used by the project.
```yaml
build: cmake
```

The directory structure of the project. `gnu` denotes the standard directory
structure, i.e. `lib`, `src`, `include`, etc, while `minimal` lumps all source
and header files into one directory.
```yaml
# Can be one of: gnu, minimal
structure: gnu
```

## CLAP

A modern, minimal Command Line Argument Parser.

## Manifesto

A manifest generator/parser/emitter.

## Scaffold

Set up your next project with ease.

## TPL

Miniature string templating library.
