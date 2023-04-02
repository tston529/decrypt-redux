#!/usr/bin/python3

import sys

#################################
# copy your cipher here, if a value exists here it will override the default
user_cipher = ['i', 'r', 'e', 'a', 'l', 'y', 'd', 'o', 'n', 't', 'c', 'w', 'h', 'v', 'b', 'f', 'g', 'j', 'k', 'm', 'p', 'q', 's', 'u', 'x', 'z']
#################################

# generated with my create_cipher script with the keyphrase "george frank and estelle costanza"
default_cipher = ['g', 'e', 'o', 'r', 'f', 'a', 'n', 'k', 'd', 's', 't', 'l', 'c', 'z', 'b', 'h', 'i', 'j', 'm', 'p', 'q', 'u', 'v', 'w', 'x', 'y']
alphabet       = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

if len(sys.argv) < 2:
	print("need a phrase to encode")

phrase = ' '.join(sys.argv[1:])

output = ''

if user_cipher is not None:
	cipher = {alphabet[i] : user_cipher[i] for i in range(0, len(alphabet))}
else:
	cipher = {alphabet[i] : default_cipher[i] for i in range(0, len(alphabet))}

for char in phrase:
	char = char.lower()
	if char in cipher:
		output += cipher[char]
	else:
		output += char

print(output.upper())

