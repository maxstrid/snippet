# snippet

- [Building](#building)
    - [With Nix](#with-nix)
    - [With Make](#with-make)  
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
