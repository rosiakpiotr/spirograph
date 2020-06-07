# spirograph
Toy we know from childhood.
Entirely written in C++ as side project.

## How to run
You can download binaries from [/bin](/bin) folder, choosing your platform, OR compile project yourself from sources located in [/src](/src) and [/include](/include).

### Compilation
You can create new project on your C++ IDE and add all files from /src and /include to it or compile from command line. Don't forget to link ```-ltgui -lsfml-graphics -lsfml-window -lsfml-system```
Compilation won't suceed if you don't link [TGUI](https://tgui.eu/) and [SFML](https://www.sfml-dev.org/) libraries. To make sure everything goes right use ```-std=c++14``` (or higher) compiler flag.

On linux you can download TGUI and SFML by typing
```
sudo apt-get install libsfml-dev
sudo add-apt-repository ppa:texus/tgui-0.8
sudo apt-get update
sudo apt-get install libtgui-dev
```
in your terminal.
