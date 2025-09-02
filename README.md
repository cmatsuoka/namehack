# Namehack

This was written to de-uglify the output of `ls -l` if you need to use an account
with a very long username.

Directions: Build using the supplied Makefile. Install `libnamehack.so` somewhere
and create an alias `ls='LD_PRELOAD <somewhere>/libnamehack.so ls'`.

Set the `NAMEHACK_TERMINATOR` environment variable to a character to terminate
the user and group name strings. The default terminator is `.`.
