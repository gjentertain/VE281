# Benchmark of sorting algorithms

## Introduction

The benchmark is under node, with node-gyp to build the cpp addon,
which receives test-cases and return each sorting algorithm's running time.

## Configuration

If you are testing your own cpp source, you may need to edit `sort_wrapper.h` and `binding.gyp`.

Make sure to have `node` installed, and then run

```
npm install -g node-gyp
npm install
node-gyp configure build
```

## Benchmarking

If no error occurs in configuration, run this

```
node benchmark.js
```

Then you can use the MATLAB script `benchmark.m` to plot figures.


