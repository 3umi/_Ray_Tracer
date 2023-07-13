#!/bin/bash

for file in *.c; do
    if [ -f "$file" ]; then
        new_name="${file%.c}_bonus.c"
        mv "$file" "$new_name"
    fi
done

