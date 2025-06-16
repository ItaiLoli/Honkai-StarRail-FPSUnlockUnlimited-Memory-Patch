# ✨ Honkai: Star Rail FPS Unlocker Unlimited (Memory Patch)

A lightweight tool that removes the built-in FPS cap in **Honkai: Star Rail** by patching its memory in real-time.

---

## 🚀 Features

- Removes FPS limit (bypasses the 60-120 FPS cap)
- Works dynamically at runtime (no registry tweaks needed)
- Automatically detects the game process and patches the required memory

---

## ⚙️ How It Works

This tool locates the **Honkai: Star Rail** process (`StarRail.exe`), identifies memory addresses responsible for the FPS limit, and sets their values to `0` (unlimited).

Unlike registry-based methods, which increase the cap only up to 120 FPS, this approach removes the limit entirely by modifying the game's memory at runtime.

---

## 📝 Usage

1. **Launch the game**  
   Start **Honkai: Star Rail** and wait until it is fully loaded.

2. **Run the HSR: FPS Unlocker**  
   Launch [Honkai FPS Unlocker](https://github.com/ItaiLoli/Honkai-StarRail-FPSUnlockUnlimited-Memory-Patch/releases/latest) after the game is running. It will automatically:
   - Detect the game process
   - Locate relevant memory addresses
   - Patch the FPS limit

---

## 📦 Requirements

- The tool is written in **C++**
- You’ll need a compatible runtime or development environment to build or execute it
