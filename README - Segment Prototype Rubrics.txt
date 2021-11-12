=================================
READ ME (INSTRUCTIONS FOR ENGINE)
=================================
Selected entity will be highlighted in green under the 'Hierarchy' tab.
All entities can add/remove components under the 'Inspector' tab when it is selected.

Entities can also be selected by clicking on the object in the scene window

Mouse wheel down in 'Scene Window' to zoom out.
Hold scroll wheel down in 'Scene Window' to move the scene camera

Assets can be found in folder: Dream-Studio\GAM200\Editor\Assets\


=================================
Changing of textures for entities
=================================
How to add/change texture to object?
Step 1: Ensure that there is a texture component for the selected object
Step 2: Click 'Change Texture' and navigate to 'Texture' inside 'Assets' folder
Step 3: Choose the texture that you want
Step 4: Do not tick 'Animation' under Texture Component if it is not a animated sprite sheet 


===============================
Rubrics Check; Open Scene Files
===============================
Step 1: Run in either Debug/Release in x64
Step 2: Click on 'Assets Manager' at the bottom of the Editor
Step 3: Double click on 'Scene' Folder in Asset Manager
Step 4: Drag and drop scene file into 'Scene' window to open the scene


===========================
Rubrics_CollisionTest Scene
===========================
- SAT collision
- Collider of individual objects can be adjusted according to designer needs.
- Collider can be scaled, moved and rotate. (Collider Component)
- Red lines on the scene window denotes the collider lines of the object

Step 1: Press the 'Play' button at the top of the Editor
Step 2: WASD to move, QE to rotate 'Player' object

Rigid Body:
When Player object collide with the Car's collider, both will move in the same direction as
both of them have Rigid Body component.

When Player collide with the Yellow quad's collider or the Circle's collider, both objects
will not move as they do not have the Rigid Body component.


============================
Rubrics_BatchRendering Scene
============================
Batch Rendering is done using GL_DYNAMIC_DRAW of buffer data inside "Mesh.cpp"
Run in Release mode

Step 1: Press the 'Play' button at the top of the Editor
Step 2: Hold 'C' to spawn entities (stable ~60fps)

Total Entities can be found under 'Engine Stats'


==============================
Rubrics_FontAndAnimation Scene
==============================
Scene Window only, zoom all the way out using mouse wheel!

Animated Sprite (Sprites Assets are placeholders from previous projects):
- Can be scaled and rotated (Transform Component)
- Sprites are displayed as their entire sprite sheet when scene is not running
(For designers to easily identify as animated sprites)

AnimatedSprite1: Looping, 4 frames, 0.5 second per frame
AnimatedSprite2: Looping, 4 frames, 1 second per frame
AnimatedSprite3: Not Looping, 2 frames, 4 seconds per frame

Fonts:
Loading of fonts is done under "ResourceManager.cpp" - LoadFont function

- Reads and loads .ttf files
- Can be scaled, rotated and moved
- Can change colour based on RGB
- Can change text during runtime

Step 1: Press the 'Play' button at the top of the Editor

- You should see the animated sprites moving at different speeds.
- 2 should be looping and 1 should not be looping