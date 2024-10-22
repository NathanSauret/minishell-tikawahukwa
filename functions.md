# Functions list
This is the list of the important functions used in minishell.
All the functions are listed in the subject.

---

## Syntax:
#### type name_of_the_function(parameters)
description of the function.

> Note: The desciption of the function always comes from the man.

---

## Functions

#### char *readline (const char *prompt)
readline will read a line from the terminal and return it, using prompt as a prompt. If prompt is NULL or the empty string, no prompt is issued.The line returned is allocated with malloc(3); the caller must free it when finished. The line returned has the final  newline removed, so only the text of the line remains.
</br>

#### void rl_clear_history (void)
Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. This differs from clear_history because it frees private data Readline saves in the history list.
</br>

#### int rl_on_new_line (void)
Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
</br>

#### void rl_replace_line (const char *text, int clear_undo)
Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
</br>

#### void rl_redisplay (void)
Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.
</br>

#### void add_history (const char *string)
Place string at the end of the history list. The associated data field (if any) is set to NULL. If the maximum number of history entries has been set using stifle_history(), and the new number of history entries would exceed that maximum, the oldest history entry is removed.
</br>

#### int printf(const char *format, ...)
The functions printf() write output to stdout, the standard output stream
</br>

#### void *malloc(size_t size)
The malloc() function allocates size bytes and returns a pointer to the allocated  memory. The memory is not initialized. If size is 0, then malloc() returns either NULL, or a unique pointer value that can  later be successfully passed to free().
</br>

#### void free(void *ptr)
The free() function frees the memory space pointed to by ptr, which must have been returned by a previous call to malloc(), calloc(), or realloc(). Otherwise, or if free(ptr) has already been called before, undefined behavior occurs. If ptr is NULL, no operation is performed.
</br>

#### ssize_t write(int fd, const void *buf, size_t count)
write() writes up to count bytes from the buffer starting at buf to the file referred to by the file descriptor fd.
</br>

#### int access(const char *pathname, int mode)
access() checks whether the calling process can access the file pathname.  If pathname is a symbolic link, it is dereferenced.
The mode specifies the accessibility check(s) to be performed, and is either the value **F_OK**, or a mask consisting of the bitwise OR of one or more of **R_OK**, **W_OK**, and **X_OK**. **F_OK** tests for the existence of the file. **R_OK**, **W_OK**, and **X_OK** test whether the file exists and grants read, write, and execute permissions, respectively.
</br>

#### int open(const char *pathname, int flags)
The open() system call opens the file specified by pathname.  If the specified file does not exist, it may (if **O_CREAT** is specified in flags) be created open().
</br>

#### ssize_t read(int fd, void *buf, size_t count)
read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.
</br>

#### int close(int fd)
close() closes a  file descriptor, so that it no longer refers to any file and may be reused. Any record locks (see fcntl(2)) held on  the file it was associated with, and owned by the process, are removed (regardless of the file descriptor that was used to obtain the lock).
</br>

#### pid_t fork(void)
fork() creates a new process by duplicating the calling process. The new process is referred to as the child process. The calling process is referred to as the parent process.
</br>

#### pid_t wait(int *wstatus)
The wait() system call suspends execution of the calling  thread until one  of its children terminates. The call wait(&wstatus) is equivalent to:
```C
waitpid(-1, &wstatus, 0);
```
</br>

#### pid_t waitpid(pid_t pid, int *wstatus, int options)
The waitpid() system call suspends execution of the calling thread until a child specified by pid argument has changed state. By default, waitpid() waits only for terminated children, but this behavior is modifiable via the options argument, as described below.
The value of pid can be:
- \< -1 meaning wait  for  any  child process whose process group ID is equal to the absolute value of pid.
- -1 meaning wait for any child process.
- 0 meaning wait for any child process whose  process  group ID is equal to that of the calling process at the time of the call to waitpid().
- \> 0 meaning wait for the child whose process ID is equal to the value of pid.
</br>

#### pid_t wait3(int *wstatus, int options, struct rusage *rusage)
#### / pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage)
The wait3() and wait4() system calls are similar to waitpid(2), but additionally return resource usage information about the child in the structure pointed to by rusage.
In other words, wait3() waits of any child, while wait4() can be used to select a specific child, or children, on which to wait. See wait(2) for further details.
</br>

#### sighandler_t signal(int signum, sighandler_t handler)
The behavior of signal() varies across UNIX versions, and has also varied historically across different versions of Linux. Avoid its use: use sigaction(2) instead. See Portability below.
Signal() sets the disposition of the signal signum to handler, which is either **SIG_IGN**, **SIG_DFL**, or the address of a programmer-defined function (a "signal handler").
</br>

#### int sigaddset(sigset_t *set, int signum)
sigaddset() and sigdelset() add and delete respectively signal signum from set.
</br>

#### int kill(pid_t pid, int sig)
The kill() system call can be used to send any signal to any process group or process.
- If pid is positive, then signal sig is sent to the process with the ID specified by pid.
- If pid equals 0, then sig is sent to every process in the process group of the calling process.
- If pid equals -1, then sig is sent to every process for which the calling process has permission to send signals, except for process 1 (init), but see below.
- If pid is less than -1, then sig is sent to every process in the process group whose ID is -pid.
- If sig is 0, then no signal is sent, but existence and permission checks are still performed; this can be used to check for the existence of a process ID or process group ID that the caller is permitted to signal.
</br>

#### void exit(int status)
The exit() function causes normal process termination and the least significant byte of status (i.e., status & 0xFF) is returned to the parent (see wait(2)).
</br>

#### char *getcwd(char *buf, size_t size)
The getcwd() function copies an absolute pathname of the current working directory to the array pointed to by buf, which is of length size.
</br>

#### int chdir(const char *path)
chdir() changes the current working directory of the calling process to the directory specified in path.
</br>

#### int stat(const char *restrict pathname, struct stat *restrict statbuf);
#### / int fstat(int fd, struct stat *statbuf);
#### / int lstat(const char *restrict pathname, struct stat *restrict statbuf);
These functions return information about a file, in the buffer pointed to by statbuf. No permissions are required on the file itself, but—in the case of stat(), fstatat(), and lstat()—execute (search) permission is required on all of the directories in pathname that lead to the file.
stat() and fstatat() retrieve information about the file pointed to by pathname; the differences for fstatat() are described below.
lstat() is identical to stat(), except that if pathname is a symbolic link, then it returns information about the link itself, not the file that the link refers to.
fstat() is identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor fd.
</br>

#### int unlink(const char *pathname)
unlink() deletes a name from the filesystem. If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.
If the name was the last link to a file but any processes still have the file open, the file will remain in existence until the last file descriptor referring to it is closed.
If the name referred to a symbolic link, the link is removed.
If the name referred to a socket, FIFO, or device, the name for it is removed but processes which have the object open may continue to use it.
</br>

#### int execve(const char *pathname, char *const _Nullable argv[], char *const _Nullable envp[])
execve() executes the program referred to by pathname. This causes the program that is currently being run by the calling process to be replaced with a new program, with newly initialized stack, heap, and (initialized and uninitialized) data segments.
</br>

#### int dup(int oldfd)
The dup() system call creates a copy of the file descriptor oldfd, using the lowest-numbered unused file descriptor for the new descriptor
</br>

#### int dup2(int oldfd, int newfd)
The dup2() system call performs the same task as dup(), but instead of using  the lowest-numbered unused file descriptor, it uses the file descriptor number specified in newfd. If the file descriptor newfd was previously open, it is silently closed before being reused
</br>

#### int pipe(int pipefd[2])
pipe() creates a pipe, a unidirectional data channel that can be used for interprocess communication. The array pipefd is used to return two file  descriptors referring to the ends of the pipe. pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe. Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe. For further details, see pipe(7)
</br>

#### DIR *opendir(const char *name)
The opendir() function opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream. The stream is positioned at the first entry in the directory.
</br>

#### struct dirent *readdir(DIR *dirp);
The readdir() function returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp. It returns NULL on reaching the end of the directory stream or if an error occurred.
</br>

#### int closedir(DIR *dirp)
The closedir() function closes the directory stream associated with dirp. A successful call to closedir() also closes the underlying file descriptor associated with dirp. The directory stream descriptor dirp is not available after this call.
</br>

#### char *strerror(int errnum)
The strerror() function returns a pointer to a string that describes the error code passed in the argument errnum, possibly using the LC_MESSAGES part of the current locale to select the appropriate language. (For example, if errnum is EINVAL, the returned description will be "Invalid argument".) This string must not be modified by the application, and the returned pointer will be invalidated on a subsequent call to strerror() or strerror_l(), or if the thread that obtained the string exits. No other library function, including perror(3), will modify this string.
</br>

#### void perror(const char *s)
The  perror() function produces a message on standard error describing the last error encountered during a call to a system or library function.
</br>

#### int isatty(int fd)
The isatty() function tests whether fd is an open file descriptor referring to a terminal.
</br>

#### char *ttyname(int fd)
The function ttyname() returns a pointer to the null-terminated pathname of the terminal device that is open on the file descriptor fd, or NULL on error (for example, if fd is not connected to a terminal). The return value may point to static data, possibly overwritten by the next call.
</br>

#### int ttyslot(void)
The legacy function ttyslot() returns the index of the current user's entry in some file.
</br>

#### int ioctl(int fd, unsigned long op, ...)
The ioctl() system call manipulates the underlying device parameters of special files. In particular, many operating characteristics of character special files (e.g., terminals) maybe controlled with ioctl() operations. The argument fd must be an open file descriptor.
The second argument is a device-dependent operation code. The third argument is an untyped pointer to memory. It's traditionally char *argp (from the days before void * was valid C), and will be so named for this discussion.
</br>

#### char *getenv(const char *name)
The getenv() function searches the environment list to find the environment variable name, and returns a pointer to the corresponding value string.
</br>

#### int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p)
The tcsetattr() function shall set the parameters associated with the terminal referred to by the open file descriptor fildes (an open file descriptor associated with a terminal) from the termios structure referenced by termios_p as follows:
- If optional_actions is **TCSANOW**, the change shall occur immediately.
- If optional_actions is **TCSADRAIN**, the change shall occur after all output written to fildes is transmitted. This function should be used when changing parameters that affect output.
- If optional_actions is **TCSAFLUSH**, the change shall occur after all output written to fildes is transmitted, and all input so far received but not read shall be discarded before the change is made.
</br>

#### int tcgetattr(int fildes, struct termios *termios_p)
The tcgetattr() function shall get the parameters associated with the terminal referred to by fildes and store them in the termios structure referenced by termios_p. The fildes argument is an open file descriptor associated with a terminal.
</br>

#### int tgetent(char *bp, const char *name)
The tgetent routine loads the entry for name. It returns:
- 1  on success,
- 0  if there is no such entry (or that it is a generic  type,  having too little information for curses applications to run),
- -1 if the terminfo database could not be found.
</br>

#### int tgetflag(const char *id)
The tgetflag routine gets the boolean entry for id, or zero if it is not available.
</br>

#### int tgetnum(const char *id)
The tgetnum routine gets the numeric entry for id, or -1 if it is not available.
</br>

#### char *tgetstr(const char *id, char **area)
The tgetstr routine returns the string entry for id, or zero if it  is not available.
</br>

#### char *tgoto(const char *cap, int col, int row)
The tgoto routine expands the given capability using the parameters.
</br>

#### int tputs(const char *str, int affcnt, int (*putc)(int))
Use tputs to output the returned string.  The area parameter is used as follows:
- It is assumed to be the address of a pointer to a buffer managed by the calling application.
- However, ncurses checks to ensure that area is not NULL, and al‐ so that the resulting buffer pointer is not NULL. If either check fails, the area parameter is ignored.
- If the checks succeed, ncurses also copies the return value to the buffer pointed to by area, and the area value will be updated to point past the null ending this value.
- The return value itself is an address in the terminal description which is loaded into memory.
