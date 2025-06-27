# 2D Grid-Based Terminal Game

## Menu

1. **For Player**  
   i. [Team Members](#team-members)  
   ii. [How to Play](#how-to-play)  
   iii. [Features & Mechanics](#features--mechanics)  
   iv. [Non-Standard Libraries](#non-standard-libraries)  
   v. [Compilation & Execution](#compilation--execution)  

2. **For Developer**  
   i. [Technical Architecture](#technical-architecture)  
   ii. [Code Implementation](#code-implementation)  

---

# For Player

## Team Members
| Name             | Student ID   | 
|------------------|--------------|
| Guan Tik Sha     | 3036387856   |
| Huang Jiangzixuan| 3036289298   | 
| Luo Jiafan       | 3036292867   | 
| Shen Hongshan    | 3036290936   | 

---

## How to Play 🕹️
###quick demo

Link to our video: https://drive.google.com/file/d/1fGwllfDpfVFAFEk-RiDhS_xqEQ8MCO9W/view?usp=sharing

### Controls
- **W**: Move Up | **S**: Move Down | **A**: Move Left | **D**: Move Right | **Q**: Quit

### Core Mechanics
| Item/Mode        | Effect                                                                 |
|------------------|-----------------------------------------------------------------------|
| **Coins ($)**    | +1 Point (Normal) / +2 Points (Special Modes)                        |
| **Bombs (*)**    | -1 Point (Normal) / -2 Points (Special Modes)                        |
| **Magnet (&)**   | Auto-collects coins in 3 closest rows (Once per game)                |
| **Flow Modes**   | `U` (Upflow), `L` (Leftflow), `R` (Rightflow) - Double points mode   |
| **Vision Block** | Hides peripheral cells (`X`) after 5 bomb hits                       |

---

## Features & Mechanics 🚀

### Magnetic Effect 🧲 
```diff
+----------------------------------------------+
|  Magnet grabbed!                             |
| 2 coins collected from the first three rows! |
+----------------------------------------------+
```
- **Activation**: Collect the `&` symbol
- **Rules**:
  - Collects **all coins** in 3 adjacent rows (current + above + below)
  - One-time use per game
- **Scoring**:  
  - Double points during Special Modes (`+2/coin`)

### Special Flow Modes 🔄
| Mode      | Visual | Rules                                                                 |
|-----------|--------|-----------------------------------------------------------------------|
| **Upflow**| ↑      | Grid shifts upward<br>Restrict vertical movement                     |
| **Leftflow**| ←  | Grid shifts leftward<br>Prioritize horizontal navigation            |
| **Rightflow**| → | Grid shifts rightward<br>Increased bomb spawn rate                  |

**Exit Condition**: Collect **5 coins** to return to normal mode.

### Vision-Blocked Mode ⚠️
```diff
- - - - X X X X X X - - - -
- X X P . $ * X X X X X X -
- - - X X X X X X - - - - -
```
- **Trigger**: 5 bomb collisions
- **Effects**:
  - Masks peripheral cells with `X`
  - Hidden items still affect gameplay
- **Recovery**: Collect coins to remove bombs (1 coin = 1 bomb)

### Advanced Features
- **Procedural Generation**: Mersenne Twister RNG for item spawns
- **High Scores**: Top 10 saved in `history.txt`

---

## Non-Standard Libraries 🗂️
| Library          | Purpose                          | Example Usage           |
|------------------|----------------------------------|-------------------------|
| `<termios.h>`    | Non-blocking terminal input      | `input.cpp` (Line 15-30)|
| `<atomic>`       | Thread-safe state management     | `game_state.h` (Global) |
| `<chrono>`       | Precise timing control           | Main game loop          |

---

## Compilation & Execution
```bash
# Compile & Run
make clean && make && ./game

# Difficulty Options
1. Easy (600ms)  2. Medium (400ms)  3. Hard (300ms)
```

---

# For Developer

## Technical Architecture
### Multi-Threaded Design
```
+-------------------+     +-------------------+
|  Input Thread     | --> |  Atomic Input Key  |
| (Non-blocking I/O)|     +-------------------+
+-------------------+           |
                                v
+-------------------+     +-------------------+
| Main Game Loop    | <-> |  Game State       |
| (Logic+Rendering) |     | (Shared Memory)   |
+-------------------+     +-------------------+
```

### Key Systems
1. **Grid Management**  
   - Circular buffer for row shifting (`shiftRowsDown()`)
2. **Collision Detection**  
   - Immediate response system (`checkCollisions()`)

---

## Code Implementation

### Requirement Mapping
| Code Requirement       | Implementation                         | File Reference       |
|------------------------|----------------------------------------|----------------------|
| **Random Events**      | Mersenne Twister RNG for item spawn    | `grid.cpp` (L32-58) |
| **Data Structures**    | 2D char array + `vector<int>`          | `game_state.h`       |
| **Dynamic Memory**     | Atomic variables for thread safety     | `game_state.h`       |
| **File I/O**           | FIFO buffer for score history          | `utils.cpp` (L25-37)|
| **Multi-File Code**    | 12 modular files                       | All `.h`/`.cpp`     |
| **Multi-Difficulty**   | Configurable update intervals          | `ui.cpp` (L28-42)   |

<sub>_High scores persist across sessions in `history.txt`_</sub>

Enjoy the game!
```
