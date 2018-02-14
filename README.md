# oblig1-OPSYS
Code has been quality assured by using cppcheck and linter-gcc 0.7.1.

to quality assure the same way I did, you need to get cppcheck through apt-get in linux commandline, and run the command "cppcheck . 2> err.txt", which checks the current folder and writes all errors to a err.txt file. Linter-gcc can be installed through Atom's package system and comes with a "lint on the fly" feature, which lints the application as you go. This together with the gcc compiler error messages, is how I did it.
