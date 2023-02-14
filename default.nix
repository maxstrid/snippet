with import <nixpkgs> {};
{ release ? false }:

stdenv.mkDerivation {
    name = "snippet";
    src = ./.;
    
    buildInputs = [ gcc tomlplusplus boost ];

    buildPhase = if release then "make release" else "make";

    installPhase = ''
        mkdir -p $out/bin
        cp snippet $out/bin/
    '';
}
