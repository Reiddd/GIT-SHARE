#!/bin/bash
# usage of shift

while [ $# -gt 0 ]; do
    echo "the first argument is $1, the number of arguments is $#"
    shift 1
done
