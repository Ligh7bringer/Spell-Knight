# Spell Knight
Spell Knight is a run and gun platformer. The aim is to get to the portal at the end of the level as quickly as possible without dying.

![img](https://i.imgur.com/LMV3bIV.png)

![img](https://i.imgur.com/VXfrs2L.png)

## Controls
**A** - Move left.

**D** - Move right.

**W** - Jump.

**Space** - Shoot.

Controls are rebindable.


# Download 
## Builds
Builds for **Windows x64** (including an installer) and **Linux** can be found on the [Releases page](https://github.com/Ligh7bringer/SFML-Game/releases).

## Compile it yourself
1. Open a terminal and run 

    ```git clone https://github.com/Ligh7bringer/SFML-Game.git```

2. In the directory of the repository, run

    ```git submodule update --init --recursive```

3. Build a solution or generate makefiles using CMake.

# Troubleshooting
1. If **openal32.dll** is missing, [download](https://github.com/Ligh7bringer/SFML-Game/releases/download/0.3-play_test_alpha/openal32.dll) it and put in the folder where the executable is.
2. If you have openal32.dll but the game still doesn't start, run it as Administrator as it needs to create **settings.txt** and **score.txt**. 
If the files still can't be created, [download them](https://pastebin.com/LJUbtMCu).

# Continuous Integration builds status
| Windows build | Linux build |
| ------------- | ------------- |
| [![Windows status](https://ci.appveyor.com/api/projects/status/fatl1v01ymec32pk?svg=true)](https://ci.appveyor.com/project/Ligh7bringer/sfml-game) | [![Linux Status](https://travis-ci.org/Ligh7bringer/SFML-Game.svg?branch=master)](https://travis-ci.org/Ligh7bringer/SFML-Game) |
