#!/bin/bash
# reading lines from specified file

_DEFAULT_FILE = /etc/ssh/sshd_config
E_WRONGARGS   = 85

if [ -f $1 ]; then
    file = $1
elif [ -z $1 ]; then
    file = $_DEFAULT_FILE
else
    echo "this is a example of codeblock IO redirection, please privide a file path argument."
    exit $E_WRONGARGS
fi

{
    read line1
    read line2
} < $file

echo -e "the first line of $file is: "
echo    "$line1"
echo -e "the second line of $file is: "
echo    "$line2"