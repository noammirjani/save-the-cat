# Circle the Cat Game

## Description
This is a puzzle game where the player is presented with a tile board. The player needs to surround the cat from all sides, by "filling the tiles", so it has nowhere to go.

## Design
- **Controller class**: This is the main class that manages the game.
- **Board class**: This class manages the game board.
- **Resources class**: This class is intended for external aids related to the game: loading images, sounds and fonts.
- **GameScreen class**: Manages the screen, for example prints the number of steps and prints the transition screens required in the game.
- **Enemy class**: The enemy class, in our case – the cat. It contains calculations related to the cat and its animation.
- **levelHandler class**: This class manages the game stages by creating a stage and drawing tiles for scattering on the board.
- **Button class**: This class holds the game buttons (undo, reset) and manages them in the different classes.
- **Stack class**: A template class that manages the stacks in the game.

## Additional Notes
- We used a rich animation of the cat so that the jumps and movements look similar to the original and so that the gameplay is richer and more interesting.
- We created a template class "stack.h".
- We implemented the bfs algorithm so that the cat escapes in the most efficient way.
- We also implemented a reset button that takes us back to the beginning of the stage.
- The game has three stages (possibility to add more in the future), the first stage has 11-14 tiles (the easiest) and in the next stages the difficulty level rises by reducing the number of tiles.
- We implemented that when the cat wins and reaches one of the ends of the board it also escapes through the animation.