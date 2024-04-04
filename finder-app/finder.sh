#!/bin/bash

# Ensure parameters specified; else exit 1
if [ "$#" -ne 2 ]; then
    echo "ERROR: Invalid Number of Arguments"
    echo "Total number of arguments should be 2"
    echo "    1)File directory path"
    echo "    2)String to be searched in the specified directory path"
    exit 1
fi

DIRECTORY_PATH=$1
TEXT_SEARCH_STRING=$2

# Ensure directory; else exit 1
if [ -d "$DIRECTORY_PATH" ]; then
    echo "$DIRECTORY_PATH found"
else
    echo "$DIRECTORY_PATH not found"
    exit 1
fi

# Output "The number of files are X and the number of matching lines are Y"
files=$(grep -rl "$TEXT_SEARCH_STRING" "$DIRECTORY_PATH"/*)
file_count=$($files | wc -l)
# echo "$files"
# echo "$file_count"

total_files=0
total_lines=0
while IFS= read -r file; do
    ((total_files++))

    lines=$(grep -c "$TEXT_SEARCH_STRING" "$file")
    ((total_lines += lines))
done <<< "$files"
echo "The number of files are $total_files and the number of matching lines are $total_lines"

if [ "$?" -eq 0 ]; then
    echo "success"
    exit 0
else
    echo "failed: expected ${} in ${} but instead"
    exit 1
fi
