#!/bin/bash

cd minishell_tester
./tester
./tester builtins
./tester extras
./tester os_specific
./tester pipes
./tester redirects
cd ..

# echo "[M]"
# echo "exit" | ./minishell
# echo $?
# echo "[B]"
# echo "exit" | bash
# echo $?
# echo

# echo "[M]"
# echo "exit 42" | ./minishell
# echo $?
# echo "[B]"
# echo "exit 42" | bash
# echo $?
# echo

# echo "[M]"
# echo "exit pata" | ./minishell
# echo $?
# echo "[B]"
# echo "exit pata" | bash
# echo $?
# echo

# echo "[M]"
# echo "exit 42 42
# exit" | ./minishell
# echo $?
# echo "[B]"
# echo "exit 42 42
# exit" | bash
# echo $?
# echo

# echo "[M]"
# echo "exit pata 42" | ./minishell
# echo $?
# echo "[B]"
# echo "exit pata 42" | bash
# echo $?
# echo
