# DBMS for Players and Games

This project is a console-based database management system (DBMS) for managing players and games using a binary search tree (BST). The system allows searching, deleting, editing, and viewing entries of players and games, as well as displaying top players and saving data.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
  1. [Search Player and Game](#1-search-player-and-game)
  2. [Delete Player and Game](#2-delete-player-and-game)
  3. [Save Player and Game Data](#3-save-player-and-game-data)
  4. [Show Layers of Player and Game Trees](#4-show-layers-of-player-and-game-trees)
  5. [Get Player and Game Layer by ID](#5-get-player-and-game-layer-by-id)
  6. [Show Search Path for Player and Game](#6-show-search-path-for-player-and-game)
  7. [Edit Player Entry](#7-edit-player-entry)
  8. [Edit Game Entry](#8-edit-game-entry)
  9. [Show Player Details and Their Games](#9-show-player-details-and-their-games)
- [Function Details and Time Complexity](#function-details-and-time-complexity)

## Project Overview

This DBMS allows users to:

- Manage player and game data efficiently.
- Perform operations like searching, deleting, editing, and displaying data.
- Traverse BST layers and save data to files.
- Search for top players based on the number of games played.

## Features

### 1. Search Player and Game

Searches for a player or a game by their unique IDs and displays their basic details.

**Time Complexity:** 
- \(O(\log n)\) in the average case for BST search.

### 2. Delete Player and Game

Deletes a player or a game entry from memory, freeing all associated memory resources to avoid memory leaks.

**Time Complexity:** 
- \(O(\log n)\) for BST deletion.

### 3. Save Player and Game Data

Saves the current state of player and game data from memory to CSV files using preorder traversal, maintaining the tree structure for easy restoration.

**Time Complexity:** 
- \(O(n)\) since it traverses all nodes.

### 4. Show Layers of Player and Game Trees

Displays nodes up to a specified number of layers in the BST structure for both players and games.

**Time Complexity:** 
- \(O(N)\) for \(N\) layers, as each layer involves visiting each node in that layer.

### 5. Get Player and Game Layer by ID

Finds the layer in which a specific player or game node resides based on their ID.

**Time Complexity:** 
- \(O(\log n)\) in the average case.

### 6. Show Search Path for Player and Game

Displays the search path taken to locate a player or game node in the tree, based on their ID. This helps visualize the traversal path in the BST.

**Time Complexity:** 
- \(O(\log n)\) in the average case.

### 7. Edit Player Entry

Allows users to edit player details, including the primary key (Player ID). If the ID is changed, the node is removed and reinserted to maintain BST properties.

**Time Complexity:** 
- \(O(\log n)\) for deletion and reinsertion if ID is changed; otherwise \(O(1)\) for direct field updates.

### 8. Edit Game Entry

Similar to editing a player entry, users can modify game details, including the primary key (Game ID). The node is repositioned if the ID changes.

**Time Complexity:** 
- \(O(\log n)\) for deletion and reinsertion if ID is changed; otherwise \(O(1)\) for direct field updates.

### 9. Show Player Details and Their Games

Searches for a player by ID and displays detailed information about the player along with the details of all games they have played.

**Time Complexity:** 
- \(O(\log n)\) for player search, plus \(O(m)\) where \(m\) is the number of games played by that player.