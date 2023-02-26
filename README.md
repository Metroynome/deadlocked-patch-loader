# deadlocked-patch-loader
I am taking advantage of the patch.bin file that Ratchet: Deadlocked uses.  I've known how to use the patch file for a while now, and i decided to take my knowledge and learning farthur.  I am using the patch.bin file to hook into the kernel of te PS2, then it copies the needed Deadlocked-Chaos codes into EE memory and runs via a second hook.

Why not just use a cheat device?  This is more fun.  And this way I can just share a save file with an edited patch.bin file for others to play right away.

## Current Progress
1. Current code in `Codes/main.c` is Infinite Health/Moon Jump.  It works in Single Player only.

# How To Use
0. Obtain a copy of the mod.  Whether you compile it or get a shared save, you're choice.
1. Once the file/save is in the correct spot, start the game.
2. Once loaded, Go to "Mulitplayer".  The mod will automatically load.
3. Once on the multiplayer menu, Press Circle to Enable/Disable the mod.
4. Once Enabled, Exit by pressing triangle and then choose single player and choose a new save (or a current save...?).
4. Enjoy the mod!

## Build with docker
Clone Repo:
```sh
git clone https://github.com/Metroynome/deadlocked-patch-loader.git
cd deadlocked-patch-loader
```

Get PS2SDK via docker:
```sh
docker pull ps2dev/ps2dev:v1.2.0
docker run -it --rm -v "$PWD\:/src" ps2dev/ps2dev:v1.2.0
cd src
./docker-init.sh
```

Make it:
```sh
make clean && make
```

When building, it also creates a `codes.pnach` cheat file in `Codes/`.  This is so you can test the mod with PCSX2, without the need of loading into the Multiplayer Menu.

## How it Compiles Currently:
1. Compile `Codes/` directory
    This holds all the Chaos-Mod codes/timers
    1. Compile `codes.bin` and `codes.elf` (stripped .elf)
    2. Convert `codes.elf` to `codes.s`
    3. copy `codes.s` to `/../Kernel`
2. Compile `Kernel/` directory
    This is where the code can hook into the kernel via the `patch.bin`
    1. Compile `kernel.bin` and `kernel.elf`with an added `codes.s` added to the `EE_OBJ` line. 
    2. copy `kernel.bin` to `/../bin`
3. Compile `bin/` directory
    This is where the new `patch.bin` file is created.
    1. Copy `patch-template.bin` from `template/` to `bin/` as `patch.bin`
    2. Write `kernel.bin` file into `patch.bin` at offset `0x100`, or `256` bytes

# Table of Address'!
|       Module      | Kernel Address |  EE Address  |
| ----------------- | -------------- | ------------ |
| Kernel Engine     | `0x80047010`   |     N/A      |
| Exception Display | `0x80079000`   | `0x000C8000` |
| Codes.bin         | `0x80050000`   | `0x000F0000` |
