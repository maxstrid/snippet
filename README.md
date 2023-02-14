# snippet

- [Building](#building)
    - [With Nix](#with-nix)
    - [With Make](#with-make)
- [Configuration](#configuration)
- [TODO](TODO.md)

## Building

### With Nix

Building with nix can be done by running

```bash
nix-build
```

Building for release requires

```bash
nix-build release.nix
```

### With Make

Building with make requires

* Boost
* Toml++

Both installed to your include path. Then

```bash
make
```

or 

```bash
make release
```

can be ran depending on your needs.

## Configuration

An example for configuration can be found in `config.toml`.

A config.toml file can be set explicitly with `snippet -c/--config /path/to/config.toml`.

The defualt configuration is in `$XDG_CONFIG_HOME/snippet/config.toml` on *nix and `%APPDATA%\Snippet\config.toml` on windows.
