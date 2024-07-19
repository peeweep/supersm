# supersm
Super Symlink Manager. 

![build status badge](https://code.0x0.ee/peeweep/supersm/actions/workflows/build.yml/badge.svg)

### Features

This software looks like [GNU Stow](https://www.gnu.org/software/stow/), but something different:

1. Don't need `--no-folding` anymore.
    Only symlink files, not folder.
2. Don't need `--adopt`anymore.
    If symlink's path already exist file, we will force delete it.

OPTIONS:

```text
Super Symlinks Manager
Allowed options:
  -V [ --version ]                      version message
  -H [ --help ]                         help message
  -T [ --target ] arg                   set target
  -A [ --add ] arg                      Add links
  -D [ --delete ] arg                   Remove links
```

* `--target` will use current path's parent directory if not specified.(absolute path)
* For Windows user: Create symlink on Windows needing to elevate the cmd console as admin.

### Build

Depends: boost-libs

For Debian user:
```
$ sudo apt install libboost-filesystem-dev libboost-program-options-dev
$ cmake -B build && cmake --build build
```

For macOS user:
```
$ brew install boost
$ cmake -B build && cmake --build build
```

For Windows user:

Install [msys2](https://www.msys2.org/), then add the absolute path of `msys64\mingw64\bin` and `msys64\mingw64\include` to PATH.

```
$ pacman -S mingw-w64-x86_64-boost mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc
$ cmake -G "MinGW Makefiles" -B build
$ cmake --build build
```

For Arch user:

[AUR](https://aur.archlinux.org/packages/supersm)
