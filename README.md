# TomoyoAfter_Dungeons_and_Takafumi
A Reimplementation of Dungeons and Takafumi for Win32 and Linux

# Discontinued
I have decided to stop working on this project as I have been finding myself not understanding the rest of original disassembly of the original game. 
You may fork this repo and continue working on it if you like. Besides that you may use this project to get information about how the game works. Just keep in mind that the battling code does not work at all and is completely incorrect.

Keep in mind when looking or working on the code it is a mess and almost all the methods starting with sub_ are either un-named, stubbed or just me messing around trying to see if anything will happen.


## Compiling
The following are required to compile TomoyoAfter_Dungeons_and_Takafumi:
- [Premake5][premake5_url] for generating building configurations.
- build-essential or [Visual Studio 2017][vs_url] or newer with C++ Development Tools for building the project.

[premake5_url]: https://premake.github.io/Premake5
[vs_url]: https://visualstudio.microsoft.com/downloads/

## Compiling under Linux
Before you can compile the project you will first need to generate the build scripts, This can be easilly done by running:

    $ premake5 gmake2

This will generate a configured GNU Make workspace so we can start building the project.
Once it completes, You can now start building the project by running:

    $ make config=release

Once this completes you should have a shared object file in `./bin/Release` called `libdt00.so`
This file can be loaded as an extension with a modified version of rlvm to allow some playthrough of the mini game in TomoyoAfter. 
 
You can take a look at my version of rlvm which is designed to load the shared object into the game which you can get it her at [thesupersonic16/rlvm][rlvm_url]

[rlvm_url]: https://github.com/thesupersonic16/rlvm

## Compiling under Windows
Before you can compile the project you will first need to generate a solution and project for Visual Studio, This can be easilly done by running: (Change vs2017 to the version of VS you are using to build this project)

    .\premake5 vs2017

Once it has completed creating the solution, you can now open the solution file at `.\TomoyoAfter_Dungeons_and_Takafumi.sln`
Once the solution has been loaded, you can start building it by right clicking the project and click on Build, when this completes you should have a DLL file at `./bin/Debug/dt00.dll`
You can load this library as an extension in the Windows version of Tomoyo After.
