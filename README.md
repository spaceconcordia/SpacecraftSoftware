# Spacecraft Software

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
- [Github repository](https://github.com/spaceconcordia/SpacecraftSoftware)
- [Project management](https://tree.taiga.io/project/slijs-spacecraft-software/)
- [Dev environment](https://github.com/spaceconcordia/vagrant)
- [Documentation](https://github.com/Slijs/SpacecraftSoftware/wiki)


## Slack (Space Concordia)
- spacecraft_software (conversation)
- spacecraft_software_a (auto updates)

### Useful tools
- [Lucidchart](https://www.lucidchart.com/) for diagrams
