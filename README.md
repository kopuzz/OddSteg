# OddSteg
- Steganography via odd and or even numbers

For Linux and MAC

This uses SFML so make sure to link that.

This is a basic steganography tool, embed a two tone binary image within another image with minimal pixel data loss.
This is currently set up to work on the RED channel, i have enums setup if you wish to change that.
Technically you could hide 4 images "same size as the host" within the host, one image for each channel ARGB. 

Uasge:
./oddSteg host-img.png secret-img.png output-img.png

ESC  - Quit
E    - Encode
D    - Decode

You can also use it to check for any hidden messaes might come in usefull for a CTF.
