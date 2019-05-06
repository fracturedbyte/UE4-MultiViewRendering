# UE4 Multi View Rendering

## Disclaimer
This plugin and engine changes are considered experimental and may be modified in future releases. Use it at your own risk.

## Overview

Resizing window and increasing FOV in application leads to stretches/distortion on side monitors. This plugin solves this problem and brings triple screen rendering to Unreal Engine. It has functionality for determining and correctly setupping application in multi view environment.

## Getting Started

Just download UnrealEngine-4.22.0 folder from repository and move/replace its contents to your engine folder. MultiViewRendering folder move to plugins folder of your project. You will also have to recompile your engine and project afterwards.

### Prerequisites

You have to run you project on UE-4.22.0 compiled from sources. All prerequisites are the same as for running the usual engine. Merging and using this plugin with other versions of the engine was not tested, however may be possible. Please let us know about your experience in the comments.

### Using triple screen

- You need to setup MultiViewLocalPlayer to be able use MultiViewRenderingDevice in engine.
You can do this by adding that line
```
LocalPlayerClassName=/Script/MultiViewRendering.MultiViewLocalPlayer
```
to DefaultEngine.ini in section [/Script/Engine.Engine]

OR

you can open Edit -> Project Settings -> Engine - General Settings -> Local -> Default Classes -> Local Player Class and choose MultiViewLocalPlayer from drop-down menu.
- This plugin contains MultiViewFunctionLibrary that have functions for interacting with MultiViewRenderingDevice and monitor setup on current platform. You can use IsTripleScreenSetup to check if you have three monitors.
- Use SetupTripleScreenWindow function to resize window and occupy all monitor virtual space.
- You can switch between single and triple screen rendering in runtime. Just use EnableTripleScreenRendering function. By default triple screen rendering is enabled.

### General considerations/restrictions:
- For current moment this plugin is configured to work with three displays. Technically, it is possible to use from two to four displays (this is engine restriction, if you want more you need to update engine code)
- Monitors MUST have same physical size and resolution size otherwise you will have incorrect projection with some amount of stretches. Plugin checks resolution of monitors and will not allow switching to triple screen rendering if monitors have different resolution.
- You will HAVE problem with shadow!!! It is an architectural problem and you can not simply avoid it. All engine stereo code based on an idea that views look at the same point and shares shadow data between views. We added some engine code to fix it. But this shadow problem is still area when we can win some milliseconds by correctly sharing shadow data (future work, look roadmap).
- You need to disable/update vignette effect cause it will be applied for each monitor
- Screen space effects may have significant differences on adjacent sides of monitors
- You need adjust your UI

### Roadmap

- correct sharing shadow data between views (require engine changes)
- support for two, three and four monitors
- advanced options for correct monitor view matrices

## Contributing

Please read [CONTRIBUTING.md](Documentation/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/fracturedbyte/UE4-MaterialBlending/tags). 

## Authors

* **Gleb Bulgakov** - *Initial coding* - [FracturedByte](https://github.com/BulgakovGleb)
* **Roman Leshchenko** - *Vision and workflow* - [FracturedByte](https://github.com/mazatracker)

See also the list of [contributors](https://github.com/fracturedbyte/UE4-MultiViewRendering/contributors) who participated in this project.

## Acknowledgments

* Many thanks for [PurpleBooth](https://gist.github.com/PurpleBooth/) for making templates of [CONTRIBUTION.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) and [README.md](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2) that we've used for this repo
* Inspired by needs of UE4 developers
