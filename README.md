timeout
=======
Run a program with a timeout

Usage
-----
**timeout** [**-q**] [**-s** *signal*] *timeout* *program* [*argument* ...]

Starts *program*. If it does not terminate within the given timeout, the
program is killed with *signal* (`SIGHUP` by default) and a message is
printed to standard error. The message can be surpressed with **-q**.

The *timeout* can be a bare number of seconds, or suffixed with 's' for
seconds, 'm' for minutes, or 'h' for hours. The *signal*, if given, must
be numeric.

Exit status
-----------
Passes through the exit status of program.

Exits 64 (`EX_USAGE`) on missing or invalid argument, 127 if *program*
cannot be started, or 1 on any other error.

Example
-------
Run a configure script with a 10 minute timeout:

    $ timeout 10m ./configure
    ...
    timeout: ./configure exceeded 10m

Installation
------------
Should work on any modern Unix, including macOS and Linux:

    make
    [sudo] make install
    [sudo] make uninstall

Author
------
Sijmen J. Mulder (<ik@sjmulder.nl>)
