# NavMesh Generator in Vulkan Engine

## Overview

This project is a **C++ NavMesh Generator** built inside of my own **Vulkan Engine**. It uses a **voxel-based** technique to create a navigation mesh for pathfinding. 

To test the generated navmesh, a simple **A\* pathfinding algorithm** has been implemented. The pathfinding currently takes a random start and end point to calculate the path.

The project uses my own Vulkan-Engine to handle rendering, camera movement and objects. The repository on which I built this project can be found <a href="https://github.com/RobbeHijzen/Collision-Generation-Vulkan" target="_blank">here</a>.

## Features

- **Voxel-based NavMesh Generation**: A voxel grid is used to generate the navigation mesh, allowing pathfinding across simple 3D environments.
- **A\* Pathfinding**: grid-based pathfinding using the A\* algorithm, which allows for testing the accuracy of the generated navmesh.
- All the features that are also in the original <a href="https://github.com/RobbeHijzen/Collision-Generation-Vulkan" target="_blank">repository</a>.
  
## Controls

**WASD**: Move camera forward, left, backwards and right respectively.

**Mouse**: rotate camera.

**R**: Regenerate random pathfinding points.

## Dependencies
- C++ 20 or later
- <a href="https://vulkan.lunarg.com/sdk/home" target="_blank">Vulkan SDK</a>
- CMake (for building)


## Future Improvements
- Dynamic obstacle handling
- Better navmesh customizability using agent radius, step height, slope angles etc.
- Use of multithreading
