# Sparty-Gnome
I worked on this project alongside Lucas Wilkerson, Alhassan Diallo, Ravi Grewal, and Hunter Samoy.

This is a 2-D scrolling game where the user is able to control a sprite(sparty gnome) and traverse various levels. Each level has data stored in an XML file which is parsed whenever the player enters a level. The user must navigate walls, platforms, enemy sprites to reach a door at the end of each level. Along the way, a score is kept which can be influenced by items like in-game cash.

The project was developed in C++ using the wxWidgets GUI. CMAKE was used for cross-platform testing.

The game supports a simple Menu consisting of:
  - Exit Mechanic
  - Manual Level Selector
  - Help Button
  
Game Mechanics:
  Right Arrow Keydown --> Move right
  Left Arrow Keydown --> Move left
  Space Bar Keydown --> Jump(limit once, resets once back on ground)
