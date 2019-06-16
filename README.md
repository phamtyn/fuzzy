# fuzzy
Fuzzy is the implementation of the FUZZY programming language. Fuzzy is designed to process linguistic variables and fuzzy sets with vague concepts such as HIGH, LOW, MEDIUM, VERY HIGH, NOT VERY LOW.

Full documentation at: <https://omarine.org/fuzzy>.

Version: 1.5.1

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

**Tip:** Remove debugging symbols from the fuzzy binary then gzip it to get it running as portable such as running on a virtual machine on a cloud::
```sh
strip -d fuzzy
gzip fuzzy
```
