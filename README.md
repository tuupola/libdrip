# [WIP] libdrip

[Drone Remote Identification Protocol (DRIP)](https://www.rfc-editor.org/info/rfc9575) message encoding and decoding library written in C programming language.

## Build

```
$ cmake -B build -DDRIP_BUILD_EXAMPLES=ON
$ cmake --build build
```

## Test

```
$ cmake -B build -DDRIP_BUILD_TESTS=ON
$ cmake --build build
$ cd build && ctest --output-on-failure --verbose
```

## Important

This is a read only mirror of the repository. Actual developing happens elsewhere.

# License

The MIT License (MIT). Please see [License File](LICENSE) for more information.
