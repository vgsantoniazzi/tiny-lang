## Welcome to Tiny lang

This project is an open-source interpreter based on C++. The proposal of this repository is understand interpreters and build a new one based on my own syntax.

## Getting Started

Clone the project:

```
git clone git@github.com:vgsantoniazzi/tiny-lang.git
```

[Install Google test](https://code.google.com/p/googletest/)

## Usage

##### Compile

```
make
```

##### Run

```
make run
```

##### Docs

Generate doxygen docs

```
make docs
```

### Run in other language

Create tokens file (based on `tokens/` dir files and run your examples based on `examples/` dir)

```
make run FILE=examples/portugues.tl TOKENS=tokens/portugues.yml
```

##### Format code

```
make format
```

##### Install

```
make install
```

##### Clean

```
make clean
```

To run manually, open bin/run

## Contributing

I :heart: Open source!

Before sending a pull request: Please, format the source code

```
bin/format
```

[Follow github guides for forking a project](https://guides.github.com/activities/forking/)

[Follow github guides for contributing open source](https://guides.github.com/activities/contributing-to-open-source/#contributing)

[Squash pull request into a single commit](http://eli.thegreenplace.net/2014/02/19/squashing-github-pull-requests-into-a-single-commit/)

## Code status

[![Build Status](https://travis-ci.org/vgsantoniazzi/tiny-lang.svg?branch=master)](https://travis-ci.org/vgsantoniazzi/tiny-lang)

## License

Tiny lang is released under the [MIT license](http://opensource.org/licenses/MIT).
