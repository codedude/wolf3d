#! /bin/bash

function print_files()
{
	files=$(find $1 -regex ".*/.*\.[c|h]")
	echo "Number of $1 files : "$(echo "$files" | wc -l)
}

print_files "libft"
print_files "libtpool"
print_files "srcs"
print_files "includes"
print_files "map_generator"

echo "Some stats about the project :"
cloc .

exit
