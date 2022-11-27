# Using this file with platformio.ini extra_scripts field because it supports splitting flags between C & C++.
# The weird syntax is learned from: https://docs.platformio.org/en/stable/scripting/examples/split_build_flags.html
Import('env')

env.Append(CCFLAGS=[])  # C & C++
env.Append(CFLAGS=[])  # C only
env.Append(CXXFLAGS=['-std=c++17'])  # C++ only
