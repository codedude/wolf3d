#!/bin/sh

# get_norm_result r "includes"
# pass ref to function, and set new result in
# function get_norm_result()
# {
# 	local ref="$1"
# 	t="$(norminette $(find $2 -regex ".*/.*\.[c|h]") | grep "Error:")"
# 	eval ${ref}='$t'
# }

function norm_print()
{
	files="$(find $1 -regex ".*/.*\.[c|h]")"
	out=$(norminette $files)
	out=$(echo $out | sed -E 's/(Norme|Error)/\'$'\n&/g')
	IFS=$'\n' read -rd '' -a array <<<"$out"
	last=0
	printed=0
	for i in "${!array[@]}"
	do
		echo $array[$i]
	done
	#echo "Check "$1":\n"$t
}

function norm_print_all()
{
	norm_print "libft"
	norm_print "libtpool"
	norm_print "includes"
	norm_print "srcs"
}

if [ "$#" -ge "1" ]; then
	norm_print $1
else
	norm_print_all
fi

exit
