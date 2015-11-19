## Welcome to Tiny lang

This project is an open-source interpreter based on C++. The proposal of this repository is understand interpreters and build a new one based on my own syntax.

## Getting Started

Clone the project:

```
git clone git@github.com:vgsantoniazzi/tiny-lang.git
```

[Install Google test](https://code.google.com/p/googletest/)

## Usage

Run first time:

```
bin/run
```

Execute the tests

```
bin/test
```

Compiling manually:

```
g++  src/**/*.cpp src/*.cpp  -o tiny
cp tiny /usr/local/bin/
tiny examples/full.tl
```

## Contributing

I :heart: Open source!

[Follow github guides for forking a project](https://guides.github.com/activities/forking/)

[Follow github guides for contributing open source](https://guides.github.com/activities/contributing-to-open-source/#contributing)

## Code status

[![Build Status](https://travis-ci.org/vgsantoniazzi/tiny-lang.svg?branch=master)](https://travis-ci.org/vgsantoniazzi/tiny-lang)

## License

Tiny lang is released under the [MIT license](http://opensource.org/licenses/MIT).
