# Deadlocked Chaos Mod
this mod is not working and is in the very early stages, but I wanted to share what I have done already.

I am taking advantage of the patch.bin file that Ratchet: Deadlocked uses.  I've known how to use the patch file for a while now, and i decided to take my knowledge and learning farthur.  I am using the patch.bin file to hook into the kernel of te PS2, so that i can then have my own codes run in the kernael and create a Chaos mod for campaign.

Why not just use a cheat device?  This is more fun.  And this way I can just share a save file with an edited patch.bin file for others to play right away.

# Notes
 1. CODE NO WORK :(  Still in progress
 2. Kernel Engine Address: `0x80047010`
 3. Codes Address: `0x80050000`


## Build with docker
Clone Repo:
```sh
git clone https://github.com/Metroynome/Deadlocked-Chaos.git
cd Deadlocked-Chaos
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
make
```
## How it Compiles Currently:
1. Compile `Codes/` directory
    This holds all the Chaos-Mod codes/timers
    1. compile `codes.bin` and `codes.elf` (stripped .elf)
    2. Convert `codes.elf` to `codes.s`
    3. copy `codes.s` to `/../Kernel`
2. Compile `Kernel/` directory
    This is where the code can hook into the kernel via the `patch.bin`
    1. Comple `kernel.bin` and `kernel.elf`with an added `codes.s` added to the `EE_OBJ` line. 
    2. copy `kernel.bin` to `/../bin`
3. Compile `bin/` directory
    This is where the new `patch.bin` file is created.
    1. Copy `patch-template.bin` from `template/` to `bin/` as `patch.bin`
    2. Write `kernel.bin` file into `patch.bin` at offset `0x100`, or `256` bytes