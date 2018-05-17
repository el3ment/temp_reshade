Recap
=====

Recap is a tool for collecting buffers from video game for training in machine learning. It is a fork of [ReShade](https://github.com/crosire/reshade) which is
an advanced, fully generic post-processing injector for games and video software. ReShade exposes an automated and generic way to access both frame color and 
depth information and all the tools to make it happen.

*NOTE:* This README.md document and [TECHNICAL_NOTES.md](./TECHNICAL_NOTES.md) are both focused on technical details. For a broader overview including game compatibility information see [this confluence document](https://confluence.nvidia.com/display/ADLR/Reshade%3A+Recap)

<<<<<<< HEAD
## Building

1. Clone this repository including all Git submodules
=======
You'll need both Git and Visual Studio 2017 or higher to build ReShade. Latter is required since the project makes use of some C++14 and C++17 features. Additionally a Python 2.7.9 or later (Python 3 is supported as well) installation is necessary for the `gl3w` dependency to build.

1. Clone this repository including all Git submodules
2. Open the Visual Studio solution
3. Select either the "32-bit" or "64-bit" target platform and build the solution (this will build ReShade and all dependencies)
>>>>>>> upstream/master

	```shell
	git clone ssh://git@yagr.nvidia.com:2200/ADLR/recap.git
	cd recap
	git submodule update --init --recursive
	git remote add upstream https://github.com/crosire/reshade
	```

2. Install [Visual Studio 2015](https://www.visualstudio.com/vs/older-downloads/), community edition is fine. The link may point to the latest (e.g. 2017) version, so make sure you download a 2015 version. You may also need to create an MSDN account to get download permissions. Once you download the right version, install with default options. 
3. Install [Python 3](https://www.python.org/downloads/), be sure to enable the option to include `python` in the PATH variables.
4. Install Windows 10 SDK 10.10586 ([direct link to download](https://go.microsoft.com/fwlink/p/?LinkID=698771)) from the [sdk archives](https://developer.microsoft.com/en-us/windows/downloads/sdk-archive).
5. Open the Visual Studio solution `ReShade.sln` using Visual Studio 2015
6. Visual Studio may ask you to install Common Tools for Visual C++ 2015 and Windows 8.1 SDK if you have not installed them before.
7. Select Project > ReShade Properties > Build-Events > Post-Build Event, and verify that the copy command is valid on your machine or blank. Read the section on debugging for more information.
8. Select either the "32-bit" or "64-bit" target platform and build the solution (the default is ReShade Setup)

*Note:* If you have never used Packman before, you will need to restart Visual Studio after trying to build the first time. Packman creates a few environment variables that are only loaded during Visual Studio's startup process. These variables aren't there when you first run build, but will be there after trying the first time. You will see a message in the build output that will tell you this if needed.

Lastly, consider installing the Python libraries.

## Installing Python Libraries

In addition to the capture tool, Reshade: Recap also provides a number of python functions for parsing and transcoding raw files, and a pytorch data loader. To use these in a project, you will need to first clone this repository, and follow the steps below
	```
	cd python
	pip install -e .
	```
If pip installing doesn't work or only want temporary access, you can alternatively add the `/python` folder to your `PYTHONPATH` environment variable like so:
	```
	PYTHONPATH=$PYTHONPATH:[... add your directory here]/recap/python
	```
Each of these will make the `nvrecap` python module avaliable to other scripts you run. Verify that it works properly by creating a `.py` file with:
	```
	import nvrecap
	```
For more details about the functions avaliable in `nvrecap`, look at the [README.md](/python/README.md) file present in the `python` directory. Reshade: Recap's python library was developed on Python 3, but has since been made compatible with Python 2. However any `metadata.pkl` files you create need to be read using the same python version with which they were created.


## Syncing with Upstream
This project is a fork of Reshade. You have a duty to posterity to keep it up to date with the current master branch! The instructions can be found [here](https://help.github.com/articles/syncing-a-fork/)

1. Commit your changes
2. `git fetch upstream`
3. `git checkout master`
4. `git merge upstream/master`

If you need to, you can always `git checkout` the commit before the `git merge`

You should do this after every big push (including merging local branches into master). Neglecting to do this is why the [Playing for Data](https://bitbucket.org/visinf/projects-2016-playing-for-data/) fork was so difficult to work with.


## Usage / Debugging

A detailed [USER_GUIDE.md](USER_GUIDE.md) is avaliable that explains how to use the tool itself.

Recap builds two DLLs ReShade.dll and ReShade64.dll. In order to be used by a game, these need to simply be copied into a folder with a game exe as `dxgi.dll` for DirectX 11 games or `opengl32.dll` for OpenGL games.
The best way to automate the setup of multiple games is to symlink the needed `dxgi.dll` to the build output. I've included [/debug_symlink_hook.cmd](/debug_symlink_hook.cmd) that shows the basics of this
for a large variety of games. It's easy to use:
1. Open [/debug_symlink_hook.cmd](/debug_symlink_hook.cmd) in a text editor
2. Change the source paths and target `ReShade64.dll`/`ReShade32.dll` paths to work on your system
3. Open a command prompt as an administrator
4. Run [/debug_symlink_hook.cmd](/debug_symlink_hook.cmd)
5. In Visual Studio, go to Build > Batch Build, to automatically build both the x86 and 64-bit configurations
6. Run a game.
7. In Visual Studio, got to Debug > Attach To Process and attach to the running exe.

 In addition you can modify the ReShade Properties > Debugging > Command to start / attach to your game's exe automatically. Be aware that some games won't allow you to debug.

 After a game has been successfully injected with the shim, a message will appear and hitting Shift + F2 will bring up the settings menu. 
 Capturing a sequence can be started using Shift + F11. Sequences will be saved in the game directory unless specified otherwise in the settings.

## Nvidia Notes

This tool was originally designed for use in the Applied Deep Learning Research (ADLR) group. Email Fitsum Reda ([freda@nvidia.com](mailto:freda@nvidia.com)) or
Bryan Catanzaro for more details ([bcatanzaro@nvidia.com](mailto:bcatanzaro@nvidia)).
Nvidia has a number of Steam accounts with access to games for use during testing. To get access follow the [instructions on nvinfo](https://wiki.nvidia.com/engwiki/index.php/Steam).
For more notes see [this confluence document](https://confluence.nvidia.com/display/ADLR/Reshade%3A+Recap)

## License

All the source code in ReShade is licensed under the conditions of the [BSD 3-clause license](LICENSE.md).

## File Overview

Path | Description
---- | -----------
[/deps](/deps) | Dependencies
[/res](/res) | Resources
[/setup](/setup) | Setup tool source code
[/source](/source) | ReShade source code
[/source/d3d9](/source/d3d9) | Direct3D 9 hooks and runtime implementation
[/source/d3d10](/source/d3d10) | Direct3D 10 hooks and runtime implementation
[/source/d3d11](/source/d3d11) | Direct3D 11 hooks and runtime implementation
[/source/dxgi](/source/dxgi) | DXGI hooks
[/source/opengl](/source/dxgi) | OpenGL hooks and runtime implementation
[/source/windows](/source/windows) | Network and window management hooks
[/source/constant_folding.cpp](/source/constant_folding.cpp) | Various rules that fold incoming constant abstract syntax tree expressions
[/source/directory_watcher.cpp](/source/directory_watcher.cpp) | Class which notifies on file modifications
[/source/filesystem.cpp](/source/filesystem.cpp) | Helper functions for file and path management
[/source/hook.cpp](/source/hook.cpp) | Function hooking
[/source/hook_manager.cpp](/source/hook_manager.cpp) | Management of the different hooking methods and automatic hooking based on DLL export matching
[/source/ini_file.cpp](/source/ini_file.cpp) | INI file format parser
[/source/input.cpp](/source/input.cpp) | Mouse and keyboard input management
[/source/image.cpp](/source/input.cpp) | Image and sequence utilities for saving frames and buffers
[/source/lexer.cpp](/source/lexer.cpp) | Hand-written tokenizer for ReShade FX code
[/source/log.cpp](/source/log.cpp) | Logging
[/source/main.cpp](/source/main.cpp) | DLL main entry point
[/source/parser.cpp](/source/parser.cpp) | Hand-written recursive descent parser for ReShade FX code
[/source/preprocessor.cpp](/source/preprocessor.cpp) | C-style preprocessor for ReShade FX code
[/source/recap.cpp](/source/recap.cpp) | Houses the bulk of the sequence capture logic and code
[/source/resource_loading.cpp](/source/resource_loading.cpp) | Win32 DLL resource loader
[/source/runtime.cpp](/source/runtime.cpp) | Main code interface managing the in-game user interface, effects etc.
[/source/runtime_objects.cpp](/source/runtime_objects.cpp) | Constant buffer read/write and data type conversion
[/source/symbol_table.cpp](/source/symbol_table.cpp) | Symbol table managing functions and variables while parsing ReShade FX code
[/tools](/tools) | Additional build tools
