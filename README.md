A set of routines for running kernel-based filters on images. They convolve an arbitrary image of an arbitrary pixel type with an arbitrary kernel and kernel anchor point, allowing to choose between different policies for handling the borders of the image.

The functionality is similar to OpenCV's filter2D (see http://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html); the focus here is on a polymorphic object-oriented approach designed to maximize extensibility with new edge-handling policies.

Currently, three policies are implemented: _wrap_, _extend_ and _crop_. _Wrap_ and _extend_ are analogous to OpenCV's _BORDER\_WRAP_ and _BORDER\_REPLICATE_. _Crop_ simply crops out the borders.

This code relies on OpenCV2 for input/output and basic structures and functions for handling images.

- Go to build/
- Run cmake . to create Makefile
- Run make to create executables
- Executables are placed in bin/

Examples of usage can be found in example/example.cpp. After building, executing bin/example will run different filters on a given input image and write the results in a given location. For instance, the images in example/output were obtained by running _./bin/example example/input/messi.jpg example/output/_.
