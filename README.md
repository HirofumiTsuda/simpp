[![GoogleTest](https://github.com/HirofumiTsuda/simpp/actions/workflows/googletest.yaml/badge.svg)](https://github.com/HirofumiTsuda/simpp/actions/workflows/googletest.yaml)

# simpp

Sim++ (sim-plus-plus) is a library for discrete simulation which aims to be a C++ version of the great
library, [SimPy](https://simpy.readthedocs.io/en/latest/). Since C++ does not have a gabage collection,
it is expected that simulation can be done at higher speed.

Note that only core functions are implemented now. Future works are written below.
- "Resource" package (Store/Resource etc... see [original package](https://gitlab.com/team-simpy/simpy/-/tree/master/src/simpy/resources))
- The function "succeed" takes an argument `value` whose type is `Any` in `SimPy`.
- and so on...

# Notation
- In this library, [coroutine2](https://www.boost.org/doc/libs/1_72_0/libs/coroutine2/doc/html/index.html)
library in [Boost](https://www.boost.org/). Please check the version of your Boost beforehand. For Ubuntu, please
type as follows to install Boost:
```sh
$ sudo apt install libboost-all-dev
```
- C++11 is required.

In the `simpp` directory, CMakeLists.txt is prepared. With this file, `libsimpp.a` is generated.

# Examples
Some examples will be added to enrich this library in the future.

