# 2d-game
mds d game sfml cpp something idk #let me use sfml 2 #let me use cs

## VScode installation
- Download the **Visual C++ 17** thing from [here](https://www.sfml-dev.org/download/sfml/3.0.0/#windows) (top left option)
- Put all the dlls in `./Debug`
- Put `include` and `lib` directories in `./2DGame`

---

# Checklist
## Basic Features
- [x] Player can move left/right with Arrow keys **and** A/D keys  
- [x] Player can jump with Space / W / Up Arrow  
- [ ] Player can drop through certain platforms with S / Down Arrow  
- [ ] At least **two types of platforms** (e.g., ground + moving/fall-through)  
- [ ] At least **two enemies/obstacles**:
  - [ ] One that damages the player  
  - [ ] One that blocks progress (e.g., door needing key)  
- [ ] Collision system prevents falling through world and triggers damage/restart  
- [ ] Debug window toggled by a key (e.g., `~` or `Esc`) to edit properties at runtime  
- [ ] Game has both **win** and **lose** states

## Advanced Features
- [ ] Level loader using text files (multiple levels, consistent format)  
- [ ] Interactable objects (switches, plates, breakables, etc.)  
- [ ] Physics-based interactions (pushing, gravity toggle, scaling objects, etc.)  