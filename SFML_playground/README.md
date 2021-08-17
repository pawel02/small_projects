# This is an example SFML project used to learn more about SFML

## Prerequisites
Make sure that you have [cmake](https://cmake.org/download/) installed as well as [visual studio](https://visualstudio.microsoft.com/downloads/) if you are on windows or g++ on linux (**Build not tested on linux**)

## Building
Before building the project you will need to make sure that you have all of the necessary submodules so run the command
`git submodule update --init --recursive`\
\
You will then need to build the SFML library which you can do by following the [link](https://www.sfml-dev.org/tutorials/2.5/compile-with-cmake.php)\
**After doing so make sure that you have the correct paths set in the CMakeLists.txt you shouldn't need to make changes on windows but you might need to on Linux**\
\

Then you can run the following command\
`cmake -S . -B ./build`
\
This should build the project into the build directory. You can then open it in visual studio on windows and build using the start button.