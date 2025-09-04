# Namehack

This was written to de-uglify the output of `ls -l` if you need to use an account
with a very long username.

Directions: Build using the supplied Makefile. Install `libnamehack.so` somewhere
and create an alias `ls='LD_PRELOAD=<somewhere>/libnamehack.so ls'`.

Set the `NAMEHACK_TERMINATOR` environment variable to a character to terminate
the user and group name strings. The default terminator is `@`.


### Output example
```shell
$ ls -l
total 28
-rw-rw-r-- 1 firstname.lastname@example.com firstname.lastname@example.com   109 Sep  2 15:32 Makefile
-rw-rw-r-- 1 firstname.lastname@example.com firstname.lastname@example.com   417 Sep  3 10:50 README.md
-rwxrwxr-x 1 firstname.lastname@example.com firstname.lastname@example.com 15960 Sep  3 16:00 libnamehack.so
-rw-rw-r-- 1 firstname.lastname@example.com firstname.lastname@example.com  2887 Sep  2 18:19 namehack.c

$ LD_PRELOAD=./libnamehack.so ls -l
total 28
-rw-rw-r-- 1 firstname.lastname firstname.lastname   109 Sep  2 15:32 Makefile
-rw-rw-r-- 1 firstname.lastname firstname.lastname   417 Sep  3 10:50 README.md
-rwxrwxr-x 1 firstname.lastname firstname.lastname 15960 Sep  3 16:00 libnamehack.so
-rw-rw-r-- 1 firstname.lastname firstname.lastname  2887 Sep  2 18:19 namehack.c

$ NAMEHACK_TERMINATOR=. LD_PRELOAD=./libnamehack.so ls -l
total 28
-rw-rw-r-- 1 firstname firstname   109 Sep  2 15:32 Makefile
-rw-rw-r-- 1 firstname firstname   417 Sep  3 10:50 README.md
-rwxrwxr-x 1 firstname firstname 15960 Sep  3 16:00 libnamehack.so
-rw-rw-r-- 1 firstname firstname  2887 Sep  2 18:19 namehack.c
```
