# Benchmark of priority queues

## Introduction

The benchmark is under node, with node-gyp to build the cpp addon,
which receives test-cases and return each sorting algorithm's running time.

## Configuration

If you are testing your own cpp source, you may need to edit `queue_wrapper.h` and `binding.gyp`.

Make sure to have `node` installed, and then run

```
npm install -g node-gyp
npm install
CXXFLAGS='-std=c++14' node-gyp configure build
```

## Benchmarking

If no error occurs in configuration, run this

```
node benchmark.js
```

Then you can use the MATLAB script `benchmark.m` to plot figures.


