#!/bin/bash

cd minishell_tester
./tester
./tester builtins
./tester extras
./tester os_specific
./tester pipes
./tester redirects
cd ..