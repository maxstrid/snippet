# snippet

- [Building](#building)
- [Configuration](#configuration)
- [TODO](TODO.md)

## Building

Building requires
* boost
* toml++

and can be built with
```bash
$ meson setup build
$ ninja -C build
```

Alternatively [nix](https://nixos.org/) can be used.
`nix-build` can be ran to auto-download dependancies and build.
`nix-build --arg release true` can be ran to build with release optimizations.

## Configuration

An example for configuration can be found in `config.toml`.

A config.toml file can be set explicitly with `snippet -c/--config /path/to/config.toml`.

The defualt configuration is in `$XDG_CONFIG_HOME/snippet/config.toml` on *nix and `%APPDATA%\Snippet\config.toml` on windows.
