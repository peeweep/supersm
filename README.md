# supersm
Super Symlink Manager.

| LICENSE                                                                    | Activities                                                                       |
|----------------------------------------------------------------------------|----------------------------------------------------------------------------------|
| [![GitHub license](https://img.shields.io/github/license/peeweep/supersm)] | ![GitHub last commit](https://img.shields.io/github/last-commit/peeweep/supersm) |

### Build

Required:
* boost-libs (libboost_program_options, libboost_filesystem)


```
$ git clone https://github.com/peeweep/supersm
$ cd supersm
$ cmake -Bbuild
$ cd build && make
```

[AUR](https://aur.archlinux.org/packages/supersm)

### Features

This software looks like [GNU Stow](https://www.gnu.org/software/stow/), but something different:

1. Don't need `--no-folding` anymore.
    Only symlink files, not folder.
2. Don't need `--adopt`anymore.
    If symlink's path already exist file, we will force delete it.

OPTIONS:

```text
Super Symlinks Manager.
Allowed options:
  -v [ --version ]                      version message
  -h [ --help ]                         help message
  -s [ --supersm ] arg                  supersm project
  -u [ --undo ] arg                     undo supersm
  -t [ --target ] arg                   set target
```

* `--target` will use current path's parent directory if not specified.(absolute path)
