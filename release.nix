with import <nixpkgs> {};

stdenv.mkDerivation {
    name = "snippet";
    src = ./.;
    
    buildInputs = [ gcc tomlplusplus boost ];

    buildPhase = "make release";

    installPhase = ''
        mkdir -p $out/bin/release/
        cp snippet $out/bin/release/
    '';
}
