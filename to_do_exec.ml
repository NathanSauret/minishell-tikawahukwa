[X] - Replace my struct by the data variables for less memory leaks potential.
[X] - Handle infiles and outfiles in exec.
[X] - When there is a problem with a file, make exec->in==-1 and exec->out==-1 to skip the command.
[ ] - >> redirection.
[ ] - "< Makefile cat | cat | cat | cat | cat > outfile1 > outfile2 > outfile3 | ls > outfile2" should work properly.
[ ] - << redirection .
[ ] - Use builtins when possible.
[ ] - Add sleep function.
[ ] - "< Makefile cat | grep A > outfile1 > outfile2 > outfile3 | ls -l" sould work properly.