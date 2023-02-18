with import <nixpkgs> {};
{ release ? false }:

let
    cc="clang";
    ldflags="-lboost_program_options";
in
stdenv.mkDerivation {
    name = "snippet";
    src = ./.;

    nativeBuildInputs = [
        meson
        ninja
        clang
        pkg-config
    ];

    buildInputs = [ tomlplusplus boost ];

    configurePhase =
        if release then
            "CC='${cc}' LDFLAGS='${ldflags}' meson setup build --buildtype release"
        else
            "CC='${cc}' LDFLAGS='${ldflags}' meson setup build";

    buildPhase = "ninja -C build";

    installPhase = ''
        mkdir -p $out/bin
        cp build/snippet $out/bin/
    '';
}
