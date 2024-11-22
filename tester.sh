#!/bin/bash

echo patapon > infile

VALGRIND="valgrind --trace-children=yes --suppressions=supp.supp --quiet ./minishell"



#builtins
echo
echo "\t\t~ BUILTINS ~"
echo

echo "cd .. -> pwd :"
eval $VALGRIND "'cd ..'"
eval $VALGRIND "'pwd'"
echo

echo "echo test :"
eval $VALGRIND "'echo test'"
echo



#one cmd
echo
echo "\t\t~ ONE CMD ~"
echo

echo "pwd :"
eval $VALGRIND "'pwd'"
echo

echo "cat infile :"
eval $VALGRIND "'cat infile'"
echo

echo "ls :"
eval $VALGRIND "'ls'"
echo



#builtins with pipes
echo
echo "\t  ~ BUILTINS WITH PIPES ~"
echo

echo "echo test | cat :"
eval $VALGRIND "'echo test | cat'"
echo

echo "echo test | cat | cat | cat | cat :"
eval $VALGRIND "'echo test | cat | cat | cat | cat'"
echo



#cmds with pipes
echo
echo "\t   ~ CMDS WITH PIPES ~"
echo

echo "cat infile | cat"
eval $VALGRIND "'cat infile | cat'"
echo

echo "cat infile | cat | cat | cat | cat :"
eval $VALGRIND "'cat infile | cat | cat | cat | cat'"
echo



#infile redirection
echo
echo "\t  ~ INFILE REDIRECTION ~"
echo

echo "< infile cat"
eval $VALGRIND "'< infile cat'"
echo

echo "< infile cat | grep -o pon"
eval $VALGRIND "'< infile cat | grep -o pon'"
echo



#outfile trunc redirection
echo
echo "\t~ OUTFILE TRUNC REDIRECTION ~"
echo

echo "cat infile > outfile | cat outfile"
eval $VALGRIND "'cat infile > outfile | cat outfile'"
echo

echo "cat infile | grep -o pon > outfile | cat outfile"
eval $VALGRIND "'cat infile | grep -o pon > outfile | cat outfile'"
echo



#outfile append redirection
echo
echo "\t ~ OUTFILE APPEND REDIRECTION ~"
echo

echo "echo start > outfile | cat infile >> outfile | cat outfile"
eval $VALGRIND "'echo start > outfile | cat infile >> outfile | cat outfile'"
echo

echo "echo start > outfile | cat infile | grep -o pon > outfile | cat outfile"
eval $VALGRIND "'echo start > outfile | cat infile | grep -o pon >> outfile | cat outfile'"
echo



rm infile
