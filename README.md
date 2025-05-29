# Pong project for "UADE::Introducción a la programación"

## Requirements

This project works with **Conan** + **CMake** to simplify dependency installation, building and debugging.

Before even running anything, we need to make sure we have the tools installed in our computer:

### Conan

We need to have `python` installed in our pc so we can install it using the official command:

```sh
pip install conan
```

Using the pip installer is important to have autocomplete on the conanfile.py file.

### CMake

CMake, cl.exe and all the tooling is installed with the MSVC from Visual Studio. Should be installed the "Desktop development with C++" in Visual Studio Installer.

## Common commands

> If we're running commands from the CLI, we need to open the "Developer Command Prompt for VS 2022".

### (First command) To install dependencies and configure conan:

```sh
conan install . --build=missing
```

> Install the requirements specified in a recipe (conanfile.py or conanfile.txt).
> If any requirement is not found in the local cache, it will iterate the remotes looking for it. When the full dependency graph is computed, and all dependencies recipes have been found, it will look for binary packages matching the current settings.
>
> If no binary package is found for some or several dependencies, it will error, unless the '--build' argument is used to build it from source.
>
> After installation of packages, the generators and deployers will be called.
>
> Documentation from the `conan install --help` command.

### To configure the Debug setting:

```sh
conan install . -s build_type=Debug
```

### Building using cmake

First, required:

```sh
cmake --preset conan-default
```

For debugging:

```sh
cmake --build --preset conan-debug
```

For release:

```sh
cmake --build --preset conan-release
```

These two last commands will create the executable files inside the `build/Debug` or `build/Release` folders.

## Common configuration with VSCode

- Required extensions are declared as recommendations.
- Run the common comands for conan and cmake to generate the build presets at least one time.
- The task to regenerate the debug version is already configured.
- Launch is setted to execute the debug version.
