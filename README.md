[![Build Status](https://travis-ci.org/spaceconcordia/SpacecraftSoftware.svg?branch=master)](https://travis-ci.org/spaceconcordia/SpacecraftSoftware) [![Coverage Status](https://coveralls.io/repos/github/spaceconcordia/SpacecraftSoftware/badge.svg)](https://coveralls.io/github/spaceconcordia/SpacecraftSoftware)

# Spacecraft Software

## Development Guide
This section will provide a tour of the project's structure and the development
workflow you can expect to follow.

The `common` directory contains Makefiles and other configuration files that are
used by all of the project's packages.

The `ext-tree` directory contains the project-specific configurations for
Buildroot, the tool used to compile an embedded Linux system for the Arietta. It
It contains, among other things, the project executables which will be placed in
the root filesystem if not building locally.

The `googletest` directory is a submodule which contains Google's unit testing
library. It will be compiled along with any unit tests.

The remaining directories contain the project "packages" i.e. the source code to
compile the project's libraries and executables. `hello` is an example package
to help you understand the development environment. If you enter the `hello`
directory, you will see that each package is a self-contained project, with its
own README, Makefile, .gitignore, unit tests, etc.

To build the packages, run the command `make target=<target> mode=<mode>`, where
presently the only supported value of target is`arietta` and mode can be either
`debug` or `release`. **If the target is not specified, the packages are built
for the local machine**; consequently, the Linux OS need not be built. In this
case, package executables will be found in their associated project directory.

To build and unit tests, run the command `make mode=<mode> test`. Unit tests can
only be built when targeting the local machine. (This might change in the
future.) Individual the unit test executable will be found in the packages'
project directory.

To build the packages for testing in the arietta, it is **first** necessary to
build the Linux OS. To do this, `make target=<target> build`. (If you get an
error about an ARM compiler not being found, it's probably because you forgot to
run this command.) This step requires that the target be specified. Furthermore,
**note that it will take approximately one hour to build the OS.** Subsequent
invokations of `make` will not need to rebuild the entire OS and so will take
much less time. Further note that the build output will be in your home
directory. This is because most developers will be compiling this project in a
shared folder inside our Vagrant environment, and the Linux kernel cannot be
built in a shared folder.

After building the Linux kernel, it is possible to build the rest of the
packages for arietta. Run the command `make target=<target> mode=<mode>`,
where target can be either `arietta` and mode can be either `debug` or
`release`. To build the unit tests, run the command `make target=<target>
mode=<mode> test`. (Presently this does not work as the unit testing framework
has yet to be integrated with the toolchain.) In this case, project executables
will be found in the `ext-tree` directory.

## Git Workflow
### Basic Guidelines
- Master should always:
  - Compile
  - Pass all tests
  - Be merged into only after code review process is completed
- All development will take place in branches
  - There will be 2 choices, depending on the size of the task
    1. Upon starting a new small development task, create a topic branch off of master, named `topic-DESCRIPTIVE_NAME`. Do all development, and merge back into master.
    2. Upon starting a new large development task, create a feature branch off of master, named `feature-DESCRIPTIVE_NAME`. Create topic branches from this new branch.
- Can link commit messages to taiga, see [these instructions](https://tree.taiga.io/support/integrations/changing-elements-status-via-commit-message/).

### Further Reading
[Branching workflow](https://git-scm.com/book/en/v2/Git-Branching-Branching-Workflows)

## Project Links
### Organization
- [GitHub repository](https://github.com/spaceconcordia/SpacecraftSoftware)
- [Project management](https://tree.taiga.io/project/slijs-spacecraft-software/)
- [Dev environment](https://github.com/spaceconcordia/vagrant)
- [Documentation](https://github.com/Slijs/SpacecraftSoftware/wiki)


## Slack (Space Concordia)
- spacecraft_software (conversation)
- spacecraft_software_a (auto updates)

### Useful tools
- [Lucidchart](https://www.lucidchart.com/) for diagrams
