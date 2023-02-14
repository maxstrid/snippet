with import <nixpkgs> {};

let
    pkgName = "snippet";
    linkerLibs = "-lboost_program_options -lboost_filesystem";
in
stdenv.mkDerivation {
    name = "${pkgName}";
    src = ./.;
    
    buildInputs = [ clang tomlplusplus boost ];

    buildPhase = "EXE=${pkgName} LDLIBS=\"${linkerLibs}\" make";

    installPhase = ''
        mkdir -p $out/bin
        cp ${pkgName} $out/bin/
    '';
}
