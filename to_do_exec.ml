[X] - Replace my struct by the data variables for less memory leaks potential.
[X] - Handle infiles and outfiles in exec.
[X] - When there is a problem with a file, make exec->in==-1 and exec->out==-1 to skip the command.
[X] - >> redirection.
[X] - "< Makefile cat | cat | cat | cat | cat > outfile1 > outfile2 > outfile3 | ls > outfile2" should work properly.
[X] - "< Makefile cat | grep A > outfile1 > outfile2 > outfile3 | ls -l" sould work properly.
[X] - Use builtins when possible.
[X] - Get the result of execve when exiting child function.
[X] - Fix leaks when exit cmd.
[X] - Fix leaks when builtin in pipe.
[X] - Fix builtins redirections.
[X] - << redirection.
[X] - cd, export and unset must be executed in parent.
[ ] - Add sleep function.
[ ] - Here_doc without a file.
[ ] - Fix "> outfile".
[ ] - Fix "<< EOF"
[ ] - Fix "cat Makefile | ls > /dev/stdin".
[ ] - Fix  open fds at exit.
