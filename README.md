# Spacecraft Software

## Development Guide
This section will provide a tour of the project's structure and the development
workflow you can expect to follow.

The `buildroot` directory contains source code to compile an embedded Linux OS.
This directory should remain unchanged and you do not need to concern yourself
with it. The `ext-tree` directory contains the project-specific configurations
for Buildroot. It contains, among other things, the project executables which
will be placed in the root filesystem. `qemu.sh` launches the Qemu emulator.

The remaining directories contain the project "packages" i.e. the source code to
compile the project's libraries and executables. `hello` is an example package
to help you understand the development environment. If you enter the `hello`
directory, you will see that each package is a self-contained project, with its
own README, Makefile, .gitignore, and unit tests.

To build the packages, run the command `make target=<target> mode=<mode>`, where
target can be either `qemu` or `arietta` and mode can be either `debug` or
`release`. If the target is not specified, the packages are built for the local
machine; consequently, the Linux OS need not be built nor should the emulator
be run. In this case, package executables will be found in their associated
project directory.

To build unit tests, run the command `make mode=<mode> test`. Unit tests can
only be built when targeting the local machine. (This might change in the
future.) The unit test executable will be found in the packages' project
directory.

Finally, to build the Linux OS, run the command `make target=<target> build`.
This step requires that the target be specified. **Note that you should run
this command before building any packages if you are not compiling for the
local machine.** (This is a bug that should be fixed soon.) Furthermore,
**note that it will take approximately one hour to build the OS.** Subsequent
invokations of `make` will not need to rebuild the entire OS and so will take
much less time. Further note that the build output will be in your home
directory. This is because most developers will be compiling this project in a
shared folder inside our Vagrant environment, and the Linux kernel cannot be
built in a shared folder.

To run the emulator, simply execute the `qemu.sh` script with `./qemu.sh`. After
some generic boot messages, you will be prompter for login information. The
login name is `root` with no password. The project packages, such as `hello`,
can be found in various locations of the OS e.g. `hello` will be in `/usr/bin`.

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

##Project Links
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
