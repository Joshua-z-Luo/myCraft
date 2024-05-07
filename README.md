<!-- PROJECT LOGO 
<br />
<div align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>
-->
<!-- README TOP -->
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

![pic1](./images/image.png)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![OpenGL](https://img.shields.io/badge/OpenGL-FFFFFF?style=for-the-badge&logo=opengl)

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

To try it out for yourself, please download a zip file of your prefered version from the google drive below:
https://drive.google.com/drive/folders/1fvPoZl2YKkkZlZOwAT1dJBEqEvWAMplM?usp=sharing

Extract and run myCraft.exe located in the extracted folder.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

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

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- PATCH NOTES -->
## Patch Notes

<details>
<summary> 0.1 [LATEST PATCH] </summary>

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
  
<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact
Feel free to contact us at:

@Kevin Chen - kevinz.chen@mail.utoronto.ca\
@Joshua Luo - jla818@sfu.ca

<p align="right">(<a href="#readme-top">back to top</a>)</p>

