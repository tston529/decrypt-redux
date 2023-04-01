#!/usr/bin/python3

import sys

keyphrase = ''
if len(sys.argv) > 1:
	keyphrase = ''.join(sys.argv[1:]).lower()

alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

used_letters = []
for letter in keyphrase:
	if letter not in used_letters:
		used_letters += letter

alphabet = [letter for letter in alphabet if letter not in used_letters]

cipher  = used_letters + alphabet

print(cipher)