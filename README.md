# Deadlocked Chaos Mod
this mod is not working and is in the very early stages, but I wanted to share what I have done already.

I am taking advantage of the patch.bin file that Ratchet: Deadlocked uses.  I've known how to use the patch file for a while now, and i decided to take my knowledge and learning farthur.  I am using the patch.bin file to hook into the kernel of te PS2, so that i can then have my own codes run in the kernael and create a Chaos mod for campaign.

Why not just use a cheat device?  This is more fun.  And this way I can just share a save file with an edited patch.bin file for others to play right away.

# Notes
 1. CODE NO WORK :(  Still in progress
 2. Kernel Address: `0x80047010`
 3. Codes Address: `0x80050000`

# The Plan
 2. Load all codes.c into kernel and run
 2. sounds easier than said.
 3. DONE --convert codes.c to codes.S via bin2s--.
 4. do more magic.
 5. hope it works.


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
