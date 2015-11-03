# Proto [![Build Status](https://travis-ci.org/earaujoassis/proto.svg)](https://travis-ci.org/earaujoassis/proto)

> A Prototype-Based Programming library for the C language

## Build & Install

You must install Autotools before attempting to build & install it.

```sh
$ autoreconf -i
$ ./configure
$ make
$ make install
```

## Tests

```sh
$ make tests
$ tests/scripts/valgrind.py
$ tests/scripts/run.py
```

## License

[MIT License](http://earaujoassis.mit-license.org/) &copy; Ewerton Assis
