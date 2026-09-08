{
  description = "shared library learning project flake";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:
    flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        nativeBuildInputs = with pkgs; [
          pkg-config
        ];
        buildInputs = with pkgs; [
          gcc
          clang-tools
          cmake
          ninja
          pkg-config
          lazygit
          cloc
          abseil-cpp
        ];
      in
      {
        devShell = pkgs.mkShell {
          inherit buildInputs;
          shellHook = ''
            alias la="eza -lA"
          '';
        };
      }
    );
}
