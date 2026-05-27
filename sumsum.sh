#!/bin/bash

sum() {
    local result=0
    for arg in "$@"; do
        local new_result
        new_result=$(expr "$result" + "$arg" 2>/dev/null)
        if [ $? -eq 2 ]; then
            echo 0
            return
        fi
        result="$new_result"
    done
    echo "$result"
}

read line1
read line2

sum1=$(sum $line1)
sum2=$(sum $line2)

if [ "$sum1" -eq "$sum2" ]; then
    echo "Equal"
else
    echo "Not equal"
fi
