# COMP-2113-group-project

# Nuclear Ashes: Space Trader🛸

## 1. Team Members

Han Jiale Jonathan (3036390279)   
Ding Yushan (3036453124)  
Li Yukit (3036392497)  
Liao Ruochen （3036260589）

## 2. Game Description

**Nuclear Ashes: Space Trader** is a text-based strategy game that blends immersive narrative with strategic decision-making, set in a post-nuclear galaxy where civilizations cling to survival amid star-system ruins. With text interaction at its core, it crafts an immersive interstellar trade adventure: the embers of nuclear war have soaked the stars, and remaining societies are reconstructing trade routes in the ruins. You will transform into an interstellar merchant, piloting a spaceship to carve your fortune across the cosmos.

Your journey starts on a stable habitable planet, armed with a basic spaceship and limited resources. Your goal is clear: claim victory by either 🎯**collecting 3 Oasis Map Fragments** or 💰**hitting a money target** (to become a galactic tycoon). You can select one of three difficulty levels (Easy/Medium/Hard) that tailors the money target, available turns, and random event intensity.

Travel between three distinct planet types, each with unique trade opportunities:
- 🌍 **Habitable Colonies**: Safe hubs to buy low-cost basic commodities (food, water).
- ☢️ **Nuclear Wastelands**: High-risk black markets where rare goods (nuclear alloy, rare metal) fetch massive profits. While random crises (pirate raids, radiation storms) lurk around every jump.
- 🏜️ **The Oasis**: A scarce resource paradise (unlocked by 2 fragments) where you can acquire the final map piece or sell goods for unrivaled gains.

Interstellar travel is never smooth: random crises are full of hidden dangers, and every choice is tied to survival and profit. Upgrading your spaceship’s armor, engine, or cargo hold with trade profits will be the key to breaking through dangerous situations. The game revolves around a core cycle: **planetary trade → interstellar navigation → crisis response → spaceship upgrade → goal achievement**.

You’ll have a **fixed number of turns** to achieve your goal: fail to collect all fragments or hit the money target before turns run out, and the game ends. Balance smart trading (buy low, sell high), strategic spaceship upgrades 🚀, and careful resource management (durability, fuel) to outlast the turns. Through pure text narrative, the game sketches a vast interstellar picture and ultimately guiding you toward the peak of wealth or a mysterious ultimate ending. Will you survive the nuclear ashes to claim your victory?

## 3. Core Features

1. **Random event mechanism**: During the journey, events such as pirate attacks, friendly merchant transactions, and radiation storms are triggered. The results are random and affect players' resources (money, fuel, and spaceship durability).  
   *Requirement 1: Generation of random events*

2. **Multi-dimensional planet system**: Three types of planets (habitable/nuclear waste/Oasis), with significant price differences for goods on each planet, supporting dynamic price adjustment and simulating real trade logic. Data is stored via `std::map` and custom `Commodity` objects to organize planet-specific commodities and prices.  
   *Requirement 2: Data structures for storing data*

3. **Deep Spacecraft Management**: It can upgrade cargo hold capacity, fuel limit, and radiation shield, support maintenance and fuel replenishment, and the status of the spacecraft directly affects travel safety. Implemented as a separate `Spaceship` class with dynamic memory management for upgrade components (e.g., dynamically allocating upgraded parts at runtime).  
   *Requirement 3: Dynamic memory management*

4. **Complete player progress**: Record money, product inventory, current planet, and spaceship status, and support new games/loading games via file input/output (reads/writes progress to `save_game.txt`).  
   *Requirement 4: File input/output (e.g., for loading/saving data)*

5. **Modular code structure**: The project is split into multiple independent files following object-oriented principles, ensuring maintainability and scalability. Key files include `Game.h`/`Game.cpp`, `Player.h`/`Player.cpp`, `Spaceship.h`/`Spaceship.cpp`, `Planet.h`/`Planet.cpp`, `Event.h`/`Event.cpp`, `Utils.h`/`Utils.cpp`.  
   *Requirement 5: Program codes in multiple files*

6. **Selectable difficulty**: Players can choose the difficulty level (Easy/Medium/Hard) to play the game, with variations in the money target, available turns, and random event intensity—allowing everyone to have a different gaming experience.  
   *Requirement 6: Multiple Difficulty Levels*

## 4. Dependency on Non-standard Libraries

This project has no dependencies on any non-standard libraries and only uses the C++11 standard library

## 5. Compilation and Execution Instructions
In the terminal, please first run the command "make" and then "./space_trader" to start the game!
