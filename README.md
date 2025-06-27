# Assets required for operation:
- Name: Adventure Character
- User: Bugrimov Maksim
- Link: https://www.fab.com/listings/deecb264-3b8e-47f1-b4a1-563865f5cd88
- Ruta: /All/Game/Main/Assets/Man
---
- Name: Modular SciFi Season 1 Starter Bundle
- User: Jonathon Frederick
- Link: https://www.fab.com/es-es/listings/86913335-3c75-42bf-8404-54fe9d9d7396
- Ruta: /All/Game/Main/Assets/StarterBundle
---
- Name: Lyra Starter Game
- User: Epic Games
- Link: https://www.fab.com/listings/93faede1-4434-47c0-85f1-bf27c0820ad0
- Ruta: /All/Game/Main/Characters   /All/Game/Main/Weapons
- Note: Export the animations only to the Characters , Weapons folder of the Lyra project, once exported they must be moved to the main folder. And in the Content folder, leave the Audio and Effects folder.
---
- Name: Polar Sci-Fi Facility
- User: 3DBrushwork
- Link: https://www.fab.com/listings/58f90d16-1b28-420c-a4bd-2833fee73554
- Ruta: /All/Game/Main/Polar
---
- Name: SoundMorph MetaSounds
- User: SoundMorph
- Link: https://www.fab.com/listings/21c75bfa-5ee7-4b4d-9499-4c9c8345e658
- Ruta: /All/Game/Main/SoundMorphMetaSounds
---

## NOTES
- Note 1: settings used for the use of some options disabled in the editor. Build lighting only: To use “Build lighting only” you have to activate “Allow Static Lighting” in Project Settings>Engine>Rendering.

### Error skydome mesh solutions
- Note 2: The following options are changed to cast only the shadows of a mesh that is required to be invisible but with shadows.
Go to Details in the mesh
Hidden Shadow = true 
Hidden in Game = true 
At startup these will be set to false, they should be changed to true, this fixes the error “your scene contains a skydome mesh with a sky material but it does not cover that part of the screen” along with the mesh remaining solid black.

- Note 3: To solve the error “your scene contains a skydome mesh with a sky material but it does not cover that part of the screen” you must use Render in Depth Pass = false, Render in main pass = false, as additional you must rebuild the whole Env. Light.
---