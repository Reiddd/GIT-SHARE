#!/bin/bash
# usage of getopts


NO_ARGS    = 0
E_OPTERROR = 85

if [ $# -eq "$NO_ARGS" ]; then
    echo "Usage: `basename $0` options (-mnopqrs)"
    exit $E_OPTERROR
fi

# getopts ":mnopq:rs" option, then the option is one of (m n o p q r s)
# ':' means this option has argument, which can be accessed with $OPTARG
while getopts ":mnopq:rs" option; do
    case $option in
        m)
            echo "#1 : option -m- [OPTIND = ${OPTIND}]"
            ;;
        n|0)
            echo "#2 : option -$option- [OPTIND = ${OPTIND}]"
            ;;
        p)
            echo "#3 : option -p- [OPTIND = ${OPTIND}]"
            ;;
        q)
            echo "#4 : option -q- with argument \"$OPTARG\" [OPTIND = ${OPTIND}]"
            ;;
        r|s)
            echo "#5 : option -$option- "
            ;;
        *)
            echo "Unimplemented option chosen."
            ;;
    esac
done

exit $?