# Aseprite Thumbnails for KDE

Shows previews of Ase files in Dolphin and KDE desktop.
Uses Aseprite cli for generating previews, Aseprite installation is required.

Compatible with new KDE 5 and KDE 6.

## Build

Build dependencies:
- cmake
- qt6-base
- kio

1. First need to install [Aseprite](https://aseprite.org/)
2. Build the plugin
   ```sh
   mkdir build
   cd build
   cmake -DCMAKE_BUILD_TYPE=Release ..
   make
   ```
3. Install it for testing
   ```sh
   sudo make install
   ```
4. Enable "Aseprite Pixel Art" in Configure Dolphin > Interface > Previews
