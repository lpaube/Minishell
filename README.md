# minishell
A smaller shell

## Summary
Replicates the basic features of bash like execution and pipes

## Features
- Working history
- Tab autocompletion
- Launch programs (absolute or relative path using PATH)
- echo with option -n
- cd with only a relative or absolute path
- pwd with no options
- export with no options
- unset with no options
- env with no options or arguments
- exit with no options
- Quotes inhibit all interpretation of a sequence of characters
- Double quotes inhibit all interpretation of a sequence of characters except for $
- 4 redirections (> >> < <<)
- Unix like pipes
- Environment variables interpolation (sequence starting with $)
- $? for last exit status
- Ctrl+C, Ctrl+\ and Ctrl+D works like in bash
