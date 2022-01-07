

## compile option for me
```
$ g++ -std=c++17 -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 main.cpp && aout

-F <value> Add directory to framework include search path
-I <dir> Add directory to include search path.
```
## Hints
SDL_Delay() prevent showing window, so use,

```cpp
// A basic main loop to prevent blocking
bool is_running = true;
SDL_Event event;
while (is_running) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            is_running = false;
        }
    }
    SDL_Delay(16);
}
```

