# Honkai: Star Rail FPS Unlocker (Memory Patch)

This is a small tool that modifies the FPS value in the memory of Honkai: Star Rail. It allows you to change the FPS cap from 60 FPS to higher values.

Instead of editing the registry, this program directly works with the game's process memory, enabling you to unlock FPS limits.

## How it Works
The program locates the Honkai: Star Rail game process, finds the memory addresses that control FPS, and changes their values. This allows you to bypass the 60 FPS cap, provided the game supports higher FPS settings.

Unlike registry modifications, this approach works dynamically with the game’s memory.

### How to Use

1. **Launch the game** – Start **Honkai: Star Rail** (`Starrail.exe`) and make sure it’s running.
2. **Run the program** – After the game is launched, run this FPS Unlocker program. It will automatically detect the game process, find the necessary memory addresses, and change the FPS cap.

### Requirements

- The program is written in **C++**, so you need to have a compatible C++ environment for building or running the executable.
