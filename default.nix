with import <nixpkgs> { };

let
  fm2gp = callPackage ./fm2gp.nix {};
in

stdenv.mkDerivation rec {
  name = "fm2gp-${version}";
  version = "0.0.1";

  buildInputs = [ fm2gp doxygen ];
}
