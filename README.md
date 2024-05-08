<!-- PROJECT LOGO 
<br />
<div align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>
-->

<h3 align="center">myCraft</h3>

  <p align="center">
    Minecraft style game built using C++ and OpenGL
    <br />


<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
    </li>
    <li>
      <a href="#controls">Controls</a>
    </li>
    <li>
      <a href="#patch-notes">Patch Notes</a>
    </li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

This is an ongoing personal learning project to help us familiarize ourselves with GPU API's such as OpenGL and continue to further our skill as game developers.

The game is a Minecraft style, procedurally generated voxel sandbox.

![Example](images/hi.gif)

https://github.com/Joshua-z-Luo/myCraft/assets/109507575/139c614b-c45f-463c-a878-c66004fecc69


### Built With

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-5586A4.svg?style=for-the-badge&logo=OpenGL&logoColor=white)

Used Dear ImGui to develop GUI: https://github.com/ocornut/imgui

<!-- GETTING STARTED -->
## Getting Started

To try it out for yourself, 
please clone the project and run it in Visual Studio,

OR

please download a zip file of your prefered version from the google drive below:
https://drive.google.com/drive/folders/1fvPoZl2YKkkZlZOwAT1dJBEqEvWAMplM?usp=sharing

Extract and run myCraft.exe located in the extracted folder.


<!-- Controls -->
## Controls
The basic control layout is:

W, A, S, D - Forward, Left, Backwards, Right

SPACEBAR - Jump

ESC - Menu

TAB - Inventory

Left click - Destroy block from inventory

Right click - Place block from inventory

Note that the controls are displayed in-game in the menu!


<!-- PATCH NOTES -->
## Patch Notes

<details open>
<summary> Update 0.2 [LATEST PATCH] </summary>

### Basic GUI and Inventory Update!

Added the nessecary core functionality and a proper HUD to make MyCraft feel more like a real game!

## Camera
- Player camera is now locked to follow the cursor, similar to most FPS games.
- Added a crosshair to represent the center of the screen and the player cursor.

## Breaking and Placing Blocks
- Improved upon from the previous patch, player can now place and break blocks using mouse left click and right click. 
- Breaking a block adds it to your invetory.
- To place a block, the player must select a block from their inventory by clicking on a non-empty slot in the inventory interface.
- The selected block is displayed in the bottom right of the players HUD.


https://github.com/Joshua-z-Luo/myCraft/assets/109507575/b6b0341c-bbb2-4d6f-a049-9ea0197b0022


## Inventory
- Added an inventory that can be accessed when player hits TAB. Allows the player to store destroyed blocks.
- Inventory has 20 slots, which each can hold up to 16 blocks of the same type.
- Player can select a slot by clicking on the slot.
  
![inventory1](https://github.com/Joshua-z-Luo/myCraft/assets/109507575/31ecae05-4e66-4493-a48d-55f27415ffda)

In the future, I plan to add an information section in the inventory that provides valuable information about the item in the currently selected slot.

![inventory2](https://github.com/Joshua-z-Luo/myCraft/assets/109507575/fbddfd0c-add1-41cc-acb9-e98169b86d7a)

## Menu
- Player can hit ESC to access a basic menu interface.
- Option to exit the game.
- Quick access to control scheme guide.

![menu](https://github.com/Joshua-z-Luo/myCraft/assets/109507575/fc290e56-a480-41df-afe0-9ce8551d0750)


</details>

<details>
<summary> Update 0.1 </summary>

### Release Patch!

Hi! Here is some stuff we added.

## Basic Procedural Generation via Simplex Noise
- Map is generated in chunks, 32 x 32 x 32 blocks in size.
- The blocks in each chunk are all drawn as one mesh to reduce the number of draw calls sent to the GPU per frame. I started by rendering each block as an individual mesh, and this caused SIGNIFICANT performance issues. By switching to rendering chunks, performance has greatly increased, as we are only sending 9 draw calls, as only 9 chunks are ever loaded at the same time.

## General Collision Detection using Swept AABB
- Initially started with basic AABB for collision detection but could not create smooth 3D collision reactions with so many different possible collision objects in the gamespace.
- Swept AABB instead calculates the future position of an entity and sees if it collides with any block. If it does, it stops the object just before touching the block. This greatly reduces clipping and allows our reactions to be more seamless.

## [EXPERIMENTAL] Block Destruction
- Player can press P to cast a ray; if the ray finds a block, that block is deleted.
- Very janky right now, as while the ray casting works well, the way we get the possible blocks for the ray to collide with is by getting all loaded blocks and checking if the ray collides with each one. There is currently no check to see which block the ray should remove in the list of blocks, so it removes the first one it finds in the list. This means it will not necessarily remove the block that the player intends to remove but rather the first block along the ray that it encounters within the list of all blocks. So it could remove a block on the far side of the hill, instead of the block the player is staring at.

</details>


<!-- CONTACT -->
## Contact
Feel free to contact us at:

@Kevin Chen - kevinz.chen@mail.utoronto.ca\
@Joshua Luo - jla818@sfu.ca


