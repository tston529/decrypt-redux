# Alphabet Cipher Decryption (redux)

After grad school + nearly 4 years as a professional developer, this is my attempt at (restarting from the ground up and) finishing what I started in college: an alphabet cipher breaker.  
  
[Original project's repo](https://github.com/tston529/decrypt)
  
The old code is almost completely unreadable and "works" only if it can find a string in the cipher with a single possible decrypted word, and stops after that. I got stuck, admittedly, and the lack of organization in the code didn't do me any favors.

## Getting Started
At the moment the file names of the dictionary used and the encoded text are baked into the code, so it'll need to be rebuilt if you want to use different files.  
  
I created a few scripts for the sake of coming up with new ciphers and using those ciphers to encode phrases, found under the `utils` directory.
- `create_cipher.py` accepts any string(s) you throw at it, and it will create an alphabet cipher based on the unique letters in the arg(s) you provide it, then pad the remainder with the unused portion of the alphabet.
- `encode.py` takes a phrase and runs it through the cipher. Modify the cipher in the script with the output of create_cipher.py to use your own.

## Do The Thing
#### Requires
- g++/libstdc++ >= 11 (uses features from C++ 20)
- GNU Make
#### Compile/Run
- `make` : builds the main program and the test suite, then runs the test suite
- `make run` : builds and runs the main program only
- `make test` : builds and runs the test suite only
- `make clean` : cleans up the build directory.

## Limitations
- This presently works only if it can find confident guesses for all of the words in the provided dictionary, so it helps to have a phrase with at least one long-ish word. However, unlike the original project, this makes an honest effort to decrypt the entire phrase.
- If the string that the program had saved for last to decrypt has multiple possible values, it will pick the first option it has available to it and call it a day. In the default dictionary + ciphered text combo, this yields "zen" instead of "men."