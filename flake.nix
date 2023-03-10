{
  description = "Development dependencies";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let pkgs = import nixpkgs { inherit system; };
      in
      with pkgs; rec
      {
        devShell = mkShell rec {
          buildInputs = [
            cmake
            cppzmq
            gnumake
            protobuf
            protobufc
          ];
        };
      });
}
