{
  description = "A code snippet helper";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }: 
    flake-utils.lib.eachDefaultSystem (system: 
      let
        pkgs = import nixpkgs { inherit system; };
        inherit (pkgs) lib;
        
        nativeBuildInputs = with pkgs; [
          meson
          ninja
          clang
          pkg-config
        ];
        
        buildInputs = with pkgs; [
          tomlplusplus
          boost
        ];

        cc = "clang";
        ldflags = "-lboost_program_options";
      in {
        packages.default =
          pkgs.stdenv.mkDerivation {
            name = "snippet";
            src = ./.;

            nativeBuildInputs = nativeBuildInputs;
            buildInputs = buildInputs;

            configurePhase = "CC='${cc}' LDFLAGS='${ldflags}' meson setup build";

            buildPhase = "ninja -C build";

            installPhase = ''
              mkdir -p $out/bin
              cp build/snippet $out/bin/
            '';
          };

        devShells.default = 
          pkgs.mkShell {
            nativeBuildInputs = nativeBuildInputs;
            buildInputs = buildInputs;
          };
      } 
    );
}
