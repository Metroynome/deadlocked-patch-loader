# Deadlocked Chaos Mod
I am taking advantage of the patch.bin file that Ratchet: Deadlocked uses.  I've known how to use the patch file for a while now, and i decided to take my knowledge and learning farthur.  I am using the patch.bin file to hook into the kernel of te PS2, then it copies the needed Deadlocked-Chaos codes into EE memory and runs via a second hook.

Why not just use a cheat device?  This is more fun.  And this way I can just share a save file with an edited patch.bin file for others to play right away.

## Current Progress
1. Current code in `Codes/main.c` is Infinite Health/Moon Jump.  It does work in Local play and in campaign.
2. I am going to add an option to the Online/Local Play screen so you can turn on/off the mod.
3. Will add actual codes that contribute to the Chaos mod as time continues.

# Notes
 1. Kernel Engine Address: `0x80047010`
 2. Codes Address: `0x80050000`

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