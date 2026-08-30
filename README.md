# CHIP-8 Emulator

A fully functional CHIP-8 emulator built from scratch in C++ with SDL2 rendering. Implements the complete CHIP-8 instruction set (35 opcodes), a custom class-based architecture, and real-time display and input handling.

![CHIP-8 Demo](CHIP-8%20Demo.gif)

---

## What is CHIP-8?

CHIP-8 is a virtual machine specification from the 1970s originally designed for the COSMAC VIP microcomputer. It features a 64×32 monochrome display, 16 general-purpose registers, 4KB of memory, a 16-level stack, and a 16-key hexadecimal keypad. Building an emulator for it is a foundational exercise in systems programming — you implement a real fetch-decode-execute CPU pipeline from scratch.

---

## Features

- Complete implementation of all 35 CHIP-8 opcodes
- Custom class-based architecture (CPU, Memory, Display, Keyboard, Stack, Platform)
- Real-time SDL2 rendering at 640×320 (10x scaled from native 64×32)
- Full keyboard input mapped to the CHIP-8 hex keypad
- Delay and sound timer support running at 60Hz
- Configurable CPU cycle speed
- ROM loading from any `.ch8` file

---

## Architecture

The emulator is organized into seven classes, each with a single responsibility:

| Class | Responsibility |
|---|---|
| `Chip8` | Top-level orchestrator — owns all components, loads ROMs, drives the cycle |
| `CPU` | Fetch → Decode → Execute pipeline, all 35 opcodes, registers, timers |
| `Memory` | 4096-byte addressable memory with read/write interface |
| `Display` | 64×32 pixel grid with XOR sprite drawing and collision detection |
| `Keyboard` | 16-key state tracking |
| `Stack` | 16-level call stack with push/pop and overflow protection |
| `Platform` | SDL2 wrapper — window creation, pixel rendering, keyboard event handling |

CPU depends on Memory, Display, Keyboard, and Stack via references — it uses them without owning them. Chip8 owns everything.

---

## Build Instructions

### Prerequisites

- Windows 10/11
- [CLion](https://www.jetbrains.com/clion/) (or any C++17-compatible compiler)
- MinGW (bundled with CLion)
- [SDL2 development libraries for MinGW](https://github.com/libsdl-org/SDL/releases)

### SDL2 Setup

1. Download `SDL2-devel-2.x.x-mingw.zip` from the SDL2 releases page
2. Extract to `C:\SDL2\`
3. The `CMakeLists.txt` in this repo already points to `C:/SDL2/SDL2-devel-2.32.0-mingw/SDL2-2.32.0/x86_64-w64-mingw32` — update the path if your version differs

### Build

1. Clone the repository
2. Open in CLion
3. Click **Sync CMake Changes** if prompted
4. Build with **Ctrl+F9**

### Run

Update the ROM path in `main.cpp`:

```cpp
chip8.loadROM("C:/path/to/your/rom.ch8");
```

Then run with **Shift+F10**. CHIP-8 ROMs can be found at [dmatlack's chip8-roms collection](https://github.com/dmatlack/chip8/tree/master/roms).

---

## Controls

The CHIP-8 hex keypad maps to the following keys:

```
CHIP-8 Key    Keyboard
----------    --------
1 2 3 C  →   1 2 3 4
4 5 6 D  →   Q W E R
7 8 9 E  →   A S D F
A 0 B F  →   Z X C V
```

Press **Escape** to quit.

---

## Technical Highlights

**Fetch-Decode-Execute cycle** — each CPU cycle reads two bytes from memory at the program counter, combines them into a 16-bit opcode using bit shifting and OR, decodes via a nested switch on the opcode's nibbles, and dispatches to the corresponding handler.

**XOR sprite drawing** — CHIP-8 sprites are drawn by XOR-ing each bit against the existing pixel state. A pixel turning off signals a collision, which sets register VF — the mechanism games use for hit detection.

**VF flag safety** — arithmetic opcodes that set VF as a carry or borrow flag save the flag value to a temporary variable before writing the result, preventing corruption when the destination register is VF itself.

**Timer decoupling** — delay and sound timers decrement at 60Hz independently of CPU speed, controlled by a cycle counter in the main loop.

---

## ROMs Tested

- IBM Logo — renders correctly, used to verify the core display pipeline
- Pong (1 player) — fully playable

---

## Built With

- C++17
- SDL2
- CLion / MinGW
