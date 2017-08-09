# Gettext_translator

  Simple lightweight translator for gettext *.po files

## Screenshot
![gettext_translator screenshot](https://user-images.githubusercontent.com/8105637/29140303-5a19518a-7d4a-11e7-8d78-3fb2c291afa2.png "Gettext translator screen")

## Compilation
to compile this program you need
GNU Make
gtkmm 2.4 
gtkspell-2.0
libgettextpo.so

To chceck if all needed libraries are detected you can use ./check.sh script
If everything is fine type make to compile program, and make install to
install it to /usr/share/

If you want to change destination directory you have to edit prefix line in
'makefile' and enter here desired destination path
