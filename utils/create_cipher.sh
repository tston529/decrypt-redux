#!/bin/bash

cipherkey="$@"
cipherkey="${cipherkey// /}"
alphabet="a b c d e f g h i j k l m n o p q r s t u v w x y z"
used_letters=()

function remove_char_from_string {
	str=( $1 )
	doomed_char=$2
	retval=()
	for char in "${str[@]}"; do
		if [[ "${char}" != "${doomed_char}" ]]; then
			retval+="${char} "
		fi
	done

	echo "${retval[@]}"
}

function add_to_set {
	char=$1
	for c in ${used_letters[@]}; do
		if [[ "${c}" == "${char}" ]]; then
			return 0
		fi
	done
	used_letters+=("${char}")
}

for (( i = 0; i < ${#cipherkey}; i++ )); do
	if (( ${#used_letters[@]} == 26 )); then
		break
	fi
	char="${cipherkey:${i}:1}"
	add_to_set "${char}"
	alphabet="$(remove_char_from_string "${alphabet}" "${char}")"
done

echo "${used_letters[@]} ${alphabet}"
