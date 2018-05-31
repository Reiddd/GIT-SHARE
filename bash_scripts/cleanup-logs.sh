#!/bin/bash
# clean up log files

_LOG_DIR    = "/var/log"
_ROOT_UID   = 0
_LINES      = 50            # lines saved after purge
E_XCD       = 86            # exit code, can't cd the directory
E_NOTROOT   = 87            # exit code, run by not-root user
E_WRONGARGS = 85            # exit code, wrong arguments


# check for root authority
if [ "$UID" -ne "$_ROOT_UID" ]; then
    echo "this script must be run by root user."
    exit $E_NOTROOT
fi


# check whether the command-line argument presents
case "$1" in
    "")
        lines = 50
        ;;
    *[!0-9]*)
        echo "Usage: `basename $0` lines-to-cleanup"
        exit $E_WRONGARGS
        ;;
    *)
        lines = $1
        ;;
esac


# double check before manipulating the file
cd $_LOG_DIR || { echo "can't cd $_LOG_DIR"; exit $E_XCD; }


cat /dev/null > wtmp


echo "Log file cleaned up."


exit 0