#!/bin/bash
# usage of awk


_FILE = '/etc/passwd'
echo "the file we will use is "$_FILE", it's content is:"
nl ${_FILE-"/etc/passwd"}

echo -e "\n+------------------+\n"

# devide fields
# -F : specify the seperator
# $1 : the first field, notice that $0 alway represents the program itself
echo -e '1. devide fields with -F: \n\tawk -F ":" "{ print $1 }" $_FILE'
awk -F ':' '{ print $1 }' ${_FILE-"/etc/passwd"}

echo -e "\n+------------------+\n"

# arithmetic compare
# == != < <= => > ?: && ||
echo -e '2. arithmetic compare with == != < <= => > ?: && ||: \n\tawk -F ":" "{ print "$1" " --> " "$3" } $_FILE"'
awk -F ':' '$3 <= 100 && $3 >=5 { print $1 " --> " $3 }' ${_FILE-"/etc/passwd"}

echo -e "\n+------------------+\n"

# pattern match
echo -e '3. pattern match: \n\tawk -F ":" "/root|redis|mysql|sshd/ { print }" $_FILE'
awk -F ':' '/root|redis|mysql|sshd/ { print $1 }' ${_FILE-"/etc/passwd"}

echo -e "\n+------------------+\n"

# specify line number
echo -e '4. specify line number: '

echo -e '\n\tawk "NR == 1 { print }" $_FILE'
awk 'NR == 1 { print }' ${_FILE-"/etc/passwd"}

echo -e '\n\tawk "BEGIN { print }" $_FILE'
awk 'BEGIN { print }' ${_FILE-"/etc/passwd"}

echo -e '\n\tawk "END { print }" $_FILE'
awk 'END { print }' ${_FILE-"/etc/passwd"}

echo -e "\n+------------------+\n"