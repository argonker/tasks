# Task 9(3) - Game (Class Hierarchy)

Turn-based battle game demonstrating advanced C++ concepts: abstract classes, pure virtual functions, multiple inheritance, and polymorphism.

## Features

- **4 Character Classes**: Knight, Mage, Archer, Necromancer
- **Pure Virtual Functions**: `count_damage()` for damage calculation, `attack()` for combat
- **Multiple Inheritance**: `SkeletonKnight` inherits from both `Skeleton` and `Knight`
- **Necromancer Mechanics**: Summon a SkeletonKnight that blocks damage as a shield
- **Mana System**: Mages manage mana for special abilities
- **Polymorphic Combat**: All characters interact through base class pointers

## Class Hierarchy

```
Character (abstract)
├── Knight
├── Mage
│   └── Necromancer
├── Archer
└── Skeleton (virtual)
    └── SkeletonKnight : public Skeleton, public Knight
```

## Files

```
Character.h              # Abstract base class (header-only)
Knight.h / Knight.cpp    # Melee fighter
Mage.h / Mage.cpp        # Magic user with mana
Archer.h / Archer.cpp    # Ranged attacker
Skeleton.h / Skeleton.cpp # Base skeleton
SkeletonKnight.h / .cpp  # Multiple inheritance example
Necromancer.h / .cpp     # Summoner class
main.cpp                 # Game loop and UI
Makefile                 # Build configuration
README.md                # This file
```

## Build & Run

### Using Makefile
```bash
make          # Compile
make run      # Compile and run
make clean    # Remove build files
```

### Manual Compilation
```bash
g++ -std=c++23 Knight.cpp Mage.cpp Archer.cpp Skeleton.cpp SkeletonKnight.cpp Necromancer.cpp main.cpp -o game
./game
```

## 🎮 Controls

| Option | Description | Available For |
|--------|-------------|---------------|
| `1` | Basic attack | All characters |
| `2` | Restore mana | Mage, Necromancer |
| `3` | Summon SkeletonKnight | Necromancer (if no skeleton) |
| `4` | Attack with skeleton | Necromancer (if skeleton exists) |
