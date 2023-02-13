with import <nixpkgs> {};

let
    pkgName = "snippet";
in
stdenv.mkDerivation {
    name = "${pkgName}";
    src = ./.;
    
    buildInputs = [ clang ];

    buildPhase = "EXE=${pkgName} make";

    installPhase = ''
        mkdir -p $out/bin
        cp ${pkgName} $out/bin/
    '';
}
