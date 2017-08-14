# Gettext_translator [![Travis Build Status](https://travis-ci.org/Krandelbord/gettext_translator.svg?branch=master)](https://travis-ci.org/Krandelbord/gettext_translator)

Simple lightweight translator for gettext *.po files

## Screenshot
![gettext_translator screenshot](https://user-images.githubusercontent.com/8105637/29140303-5a19518a-7d4a-11e7-8d78-3fb2c291afa2.png "Gettext translator screen")


## Compilation

# For debian/ubuntu
Check if you have all dependencies by running
$ dpkg-checkbuilddeps
Build package by running:
$ dpkg-buildpackage -b -uc

# Other systems
to compile this program you need
GNU Make
gtkmm 2.4 
gtkspell-2.0
libgettextpo.so

To check if all needed libraries are detected you can use ./check.sh script
If everything is fine type make to compile program, and make install to
install it to /usr/share/

If you want to change destination directory you have to edit prefix line in
'makefile' and enter here desired destination path
