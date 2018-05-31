#!/bin/bash
# background-loop

for i in 1 2 3 4 5 6 7 8 9 10; do
    echo -n "$i "
    sleep 1
done &

echo 

for i in 11 12 13 14 15 16 17 18 19 20; do
    echo -n "$i "
    sleep 1
done

echo