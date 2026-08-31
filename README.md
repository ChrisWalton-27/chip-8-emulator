# CHIP-8 Emulator

A fully functional CHIP-8 emulator built from scratch in C++ with SDL2 rendering and an integrated ImGui debugger. Implements the complete CHIP-8 instruction set (35 opcodes), a custom class-based architecture, real-time display and input handling, and a full-featured debugging suite.

![CHIP-8 Demo](CHIP-8%20Demo.gif)

---

## What is CHIP-8?

CHIP-8 is a virtual machine specification from the 1970s originally designed for the COSMAC VIP microcomputer. It features a 64×32 monochrome display, 16 general-purpose registers, 4KB of memory, a 16-level stack, and a 16-key hexadecimal keypad. Building an emulator for it is a foundational exercise in systems programming — you implement a real fetch-decode-execute CPU pipeline from scratch.

---

## Features

- Complete implementation of all 35 CHIP-8 opcodes
- Custom class-based architecture (CPU, Memory, Display, Keyboard, Stack, Platform, Debugger)
- Real-time SDL2 rendering at 640×320 (10x scaled from native 64×32)
- Full keyboard input mapped to the CHIP-8 hex keypad
- Delay and sound timer support running at 60Hz
- Configurable CPU cycle speed
- ROM loading from any `.ch8` file
- **Integrated ImGui debugger** with dockable panels, step-through execution, and live state inspection

---

## Debugger

The emulator includes a full real-time debugging suite built with Dear ImGui:

| Panel | Description |
|---|---|
| **Display** | Live CHIP-8 screen rendered inside a dockable ImGui window |
| **CHIP-8 Debugger** | Shows PC, current opcode, all 16 V registers (editable), I register, delay and sound timers |
| **Disassembly** | Scrollable instruction view centered on PC — current instruction highlighted in yellow, breakpoints shown in red |
| **Stack** | Live stack depth and all stored return addresses |
| **Memory Editor** | Full 4KB memory view, scrollable, every byte editable in hex |

**Debugger Controls:**
- **Run** — resume normal emulation
- **Pause** — freeze execution at the current instruction
- **Step** — execute exactly one instruction then pause
- **Breakpoints** — click any instruction in the Disassembly panel to toggle a breakpoint; execution pauses automatically when PC reaches it

---

## Architecture

The emulator is organized into eight classes, each with a single responsibility:

| Class | Responsibility |
|---|---|
| `Chip8` | Top-level orchestrator — owns all components, loads ROMs, drives the cycle |
| `CPU` | Fetch → Decode → Execute pipeline, all 35 opcodes, registers, timers |
| `Memory` | 4096-byte addressable memory with read/write interface |
| `Display` | 64×32 pixel grid with XOR sprite drawing and collision detection |
| `Keyboard` | 16-key state tracking |
| `Stack` | 16-level call stack with push/pop and overflow protection |
| `Platform` | SDL2 + ImGui wrapper — window, rendering, input, and all debug panel layout |
| `Debugger` | Execution controller — run/pause/step logic and breakpoint management |

CPU depends on Memory, Display, Keyboard, and Stack via references — it uses them without owning them. Chip8 owns everything.

---

## Build Instructions

### Prerequisites

- Windows 10/11
- [CLion](https://www.jetbrains.com/clion/) (or any C++17-compatible compiler)
- MinGW (bundled with CLion)
- [SDL2 development libraries for MinGW](https://github.com/libsdl-org/SDL/releases)
- [Dear ImGui](https://github.com/ocornut/imgui/tree/docking) — docking branch (included in repo under `imgui/`)

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

**ImGui docking layout** — the debugger uses ImGui's docking branch, allowing all panels to be freely repositioned, resized, and snapped into a custom workspace layout that persists between sessions.

**Step-through debugging** — the Debugger class sits between main and Chip8, intercepting the cycle loop. In step mode it allows exactly one instruction through then blocks, enabling instruction-level inspection of any program.

**Live memory editing** — all 4096 bytes of CHIP-8 RAM are displayed and editable in real time while the emulator runs, enabling on-the-fly state manipulation for testing and debugging.

---

## ROMs Tested

- IBM Logo — renders correctly, used to verify the core display pipeline
- Pong (1 player) — fully playable

---

## Built With

- C++17
- SDL2
- Dear ImGui (docking branch)
- CLion / MinGW
