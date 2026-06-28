# Qt-Snake-Game
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge)
![Qt](https://img.shields.io/badge/Qt-6.x-41CD52?style=for-the-badge&logo=qt&logoColor=white)
![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B)
![Game](https://img.shields.io/badge/Genre-Arcade-orange?style=for-the-badge)
[![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)](LICENSE)
[![Download](https://img.shields.io/badge/Download-Release-blue?style=for-the-badge&logo=github)](../../releases)

A polished recreation of the classic **Snake** game built with **C++** and the **Qt Framework**.

This project was created as a learning exercise to explore **Qt's Graphics Framework**, **event-driven programming**, **collision detection**, and **object-oriented game architecture**. It also helped me understand the basics of 2D game development before moving on to a dedicated game engine.

---

<p align="center">
<img width="788" height="792" alt="gameplay" src="https://github.com/user-attachments/assets/ee80784a-df2b-42a8-ade0-5480f4422ee0" />


</p>

---

# Features

## Interactive Main Menu

The game starts with a custom animated menu instead of a static screen.

### Highlights

* Mouse-tracking mascot eyes
* Hover sound effects
* Dedicated menu scene
* Credits dialog

<p align="center">

<img width="804" height="812" alt="menu" src="https://github.com/user-attachments/assets/ddb5a135-7977-4446-bcad-575e73f9d536" />

</p>

---

## Classic Snake Gameplay

The core gameplay stays faithful to the original Snake formula while keeping the controls responsive and clean.

* Grid-based movement
* Snake growth after eating food
* Real-time score tracking
* Boundary and self-collision detection
* Random food spawning
* Instant restart support

<p align="center">

<img width="788" height="792" alt="gameplay" src="https://github.com/user-attachments/assets/be385f08-bd9a-41dd-a458-2bb1c895857b" />

</p>

---

## Speed Boost

Holding a movement key temporarily increases the snake's speed, making the game feel a little more dynamic without changing the basic rules.

<p align="center">

<img width="750" height="742" alt="fast" src="https://github.com/user-attachments/assets/64c4032a-deb8-473c-a540-a6509427ea73" />


</p>

---

## Visual Feedback

The snake updates its appearance while moving so the motion feels more natural.

* Rotating head
* Corner-aware body sprites
* Tail orientation updates
* Custom pixel-art assets

---

## Audio Feedback

Small sound effects are used to make the game feel more responsive.

* Eating food
* Menu hover
* Game over

---

# Technical Highlights

## Scene-Based Architecture

The game is built on **QGraphicsScene** and **QGraphicsView**, so each object exists as an independent graphical item.

This keeps rendering, layering, and object management modular and easy to follow.

---

## Custom Collision Geometry

Instead of relying only on Qt's default rectangular collision boxes, the project overrides `shape()` with `QPainterPath`.

This makes collision areas closer to the actual sprite shapes.

* Circular hitbox for food
* Tighter hitbox for snake segments

---

## Object Recycling

Snake body segments are reused during movement instead of being recreated every frame.

This keeps the movement logic efficient and avoids unnecessary object creation.

```id="ieeqic"
Tail
 ↓
takeLast()
 ↓
Move to previous position
 ↓
Update sprite
 ↓
prepend()
```

---

## Dynamic Sprite System

Every body segment updates its appearance according to the snake's movement.

* Straight body sprite
* Left corner sprite
* Right corner sprite
* Tail sprite

This creates smooth visual transitions without requiring complex animation systems.

---

## Food Spawn Validation

Food is generated randomly across the map while ensuring it never appears inside the snake.

Before placing a new apple, the scene checks whether the selected grid cell is already occupied.

---

## Event-Driven Design

The project heavily utilizes Qt's event system.

* Keyboard events
* Event Filters
* Mouse tracking
* Signal-Slot communication
* QTimer-based game loop

Keeping gameplay logic separated from UI interactions results in a clean and maintainable architecture.

---

# Learning Objectives

This project focuses on learning several important software engineering and game development concepts, including:

* Object-Oriented Programming
* Qt Graphics Framework
* Scene-based rendering
* Event-driven programming
* Collision detection
* Sprite management
* Game loop implementation
* Interactive desktop UI development

The project is intentionally small and self-contained, and it is not planned to receive major new feature updates.

---

# Project Structure

| File             | Description                                                  |
| ---------------- | ------------------------------------------------------------ |
| `main.cpp`       | Application entry point                                      |
| `mainwindow.cpp` | Main game logic, UI management, menu interactions, game loop |
| `mainwindow.h`   | MainWindow declarations                                      |
| `mainwindow.ui`  | Interface designed with Qt Designer                          |
| `snakehead.cpp`  | Snake movement, input handling, collision detection          |
| `snakehead.h`    | Snake head declarations                                      |
| `snakebody.cpp`  | Snake body rendering and collision geometry                  |
| `snakebody.h`    | Snake body declarations                                      |
| `food.cpp`       | Food rendering and collision shape                           |
| `food.h`         | Food declarations                                            |
| `resources.qrc`  | Sprites and sound resources                                  |

---

# Build & Run

## Requirements

* Qt Creator (Latest Version)
* Qt 6.x
* C++17 compatible compiler
* CMake

## Build

```bash
git clone https://github.com/Fatih-Sahinoglu/Qt-Snake-Game.git
```

Open the project using **Qt Creator**, configure the CMake project, then simply press **Run**.

---

# Releases

Prebuilt Windows releases will be provided as **.zip** or **.rar** archives in the [Releases](../../releases) section.

Download the archive, extract it, and run the executable directly.

---

# Why This Project Matters

Although it is based on the classic Snake game, the main goal of this project was to learn how **Qt** can be used for real-time gameplay systems.

It covers scene management, object-oriented design, collision handling, event-driven programming, reusable game objects, and interactive UI design.

Even though the project is now essentially complete, the concepts used here form a solid foundation for future 2D game development with dedicated engines.

---

# Developer

**Fatih Şahinoğlu**

GitHub: https://github.com/Fatih-Sahinoglu

LinkedIn: https://www.linkedin.com/in/fatih-şahinoğlu/

---

# License

This project is licensed under the  [MIT License](LICENSE).
