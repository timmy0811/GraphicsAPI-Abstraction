<img align="left" src="https://github.com/timmy0811/GraphicsAPI-Abstraction/blob/Projects/logo0.png" width="200" height="200">

# GraphicsAPIAbstraction
A wrapper library for abstracting the most common graphics-APIs like OpenGL, Vulkan, Direct3D. This Library will grow with time...

## What it offers
Implementations of the most basic objects in graphics-applications (Textures, Buffers, Arrays, ...) for OpenGL. Implementations for Vulkan, etc. are not provided but can easily be added by yourself!

## How to use
This repository provides a ```premake5.lua``` which is part of bigger premake-project and gets included by it. As this library links to external dependencies that are not contained in this directory, it is neccessary to write a dedicated ```premake5.lua``` for your own needs. You can find all of the information about building this project in the existing ```premake5.lua```.
