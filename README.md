# fuzzy
Fuzzy is the implementation of the FUZZY programming language. Fuzzy is designed to process linguistic variables and fuzzy sets with vague concepts such as HIGH, LOW, MEDIUM, VERY HIGH, NOT VERY LOW.

Full documentation at: <https://omarine.org/fuzzy>.

Version: 1.4.1

Homepage: https://omarine.org

## Configuring and Building Fuzzy

In order to compile Fuzzy you need following software packages:
- GCC compiler
- flex
- bison

Basic configuring and building:
```sh
./configure --prefix=/usr
make
```
Now as the root user:
```sh
make install
```

Please see the INSTALL file for additional options.

**Tip:** For a portable binary version you compile as below at the src directory:
```sh
g++ -Wno-return-type -o fuzzy *.cc
```
