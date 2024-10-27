Rollerball Chess Bot as part of Artificial Intelligence course, IIT Delhi (2023-24 Semester I) 

## Objective

The goal of the project is to develop a bot that competes in the game of Rollerball across three different board configurations for an in-class tournament. Rollerball is a turn-based game similar to chess, where the objective is to checkmate the opponent's king. The bot must efficiently handle game strategies for three distinct board setups and compete against other bots in a tournament format. 
Rollerball's GUI is implemented in JavaScript, and the core engine is written in C++. 

## Game Overview

Rollerball features three board types with different starting positions:
1. **7x3 Rollerball Board**: Standard configuration with regular pieces.
2. **8x4 Rollerball Board**: Larger board with more pieces and complex strategies.
3. **8x2 Rollerball Board**: A unique board that includes the knight piece and introduces additional complexity.

The bot needs to:
- Make efficient and strategic moves.
- Maximize its chances of checkmating the opponent's king.
- Minimize the number of moves taken to win (or survive).
- Manage time across moves as the total time per match is fixed.

## Approach

### 1. **State Representation and Board Evaluation**

The key to developing an effective bot is a proper representation of the board state and the ability to evaluate each state to determine the optimal move. Our approach involves:
- **Board Representation**: Each board state is represented as a data structure that keeps track of all pieces, their positions, and potential moves.
- **Piece Movement**: We adhere to the movement rules for each piece (similar to chess), including specific logic for pawns and knights. For example, the knight moves in an "L" shape, while pawns promote when they reach specific squares.
- **Four-fold Symmetry**: We take advantage of the symmetry of the board to reduce redundant calculations.

### 2. **Minimax Algorithm with Alpha-Beta Pruning**

To decide on the best move, we implement a **Minimax** algorithm with **Alpha-Beta Pruning**. This allows the bot to simulate possible moves and evaluate their outcomes to choose the best course of action:
- **Minimax**: This algorithm recursively evaluates the game tree, assuming both players play optimally. It minimizes the possible loss for a worst-case scenario.
- **Alpha-Beta Pruning**: To optimize the search, we prune branches of the game tree that are unlikely to yield a better result, thus reducing the number of states we need to evaluate.

### 3. **Heuristic Evaluation Function**

At the core of the Minimax algorithm is a **heuristic evaluation function**. This function evaluates the board state and assigns a score based on:
- **Material Advantage**: The value of the pieces on the board (e.g., knights, rooks, bishops, pawns) and the difference in value between the player's pieces and the opponent's.
- **Positional Advantage**: The positioning of pieces on the board, especially control of key squares and proximity to checkmate.

### 4. **Handling Time Limits**

Since each player has a limited time pool for the entire match, our bot carefully manages its time allocation:
- **Move Complexity**: We estimate the complexity of each move and adjust the depth of our search accordingly.
- **Time Management**: As the game progresses, we prioritize faster moves, reserving more time for critical decision points (e.g., when a king is under threat).

### 5. **Iterative Deepening**

To ensure that we can make a decision within the time limit, we use **iterative deepening**. This allows the bot to start with a shallow search and progressively deepen the search until the time runs out. This ensures that we always have a move ready, even if the deeper search hasn’t completed.

### 6. **Move Ordering**

We improve the efficiency of the Minimax algorithm by **move ordering**. By evaluating promising moves first (such as captures and checks), we increase the chances of pruning irrelevant branches early, speeding up the search process.

### 7. **Endgame Strategy**

In the endgame, when fewer pieces remain on the board, we employ specialized strategies:
- **Aggressive King Attack**: If the opponent's king is vulnerable, we aggressively search for checkmate opportunities.
- **Piece Preservation**: If winning is not possible, we focus on preserving valuable pieces to maximize our margin score.

# Using the BOT
To run the GUI, launch a web server from the `web` directory.

```bash
cd web
python3 -m http.server 8080
```

You can then open [localhost:8080](http://localhost:8080) on your browser to view the GUI. Here you can select one of the three board types. 

To launch the bots (assuming you're in the directory)

```bash
./bin/rollerball -p 8181
```
You can then connect the GUI to the bots. You would also need to start another bot for black on port 8182 to join and start the game.
