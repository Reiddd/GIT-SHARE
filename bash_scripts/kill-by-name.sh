#!/bin/bash
# kill processes by name

E_BADARGS = 66

if [ -z "$1" ]; then
    echo "Usage: `basename $0` Processes to kill."
    exit $E_BADARGS
fi

_PROCESS_NAME = "$1"
ps ax | egrep "$_PROCESS_NAME" | awk `{ print $1 }` | xargs -i kill {} 2&>/dev/null

exit $?