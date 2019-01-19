let

  fetchTarballFromGitHub =
    { owner, repo, rev, sha256, ... }:
    builtins.fetchTarball {
      url = "https://github.com/${owner}/${repo}/tarball/${rev}";
      inherit sha256;
    };

  fromJSONFile = f: builtins.fromJSON (builtins.readFile f);

in

{ nixpkgs ? fetchTarballFromGitHub (fromJSONFile ./nixpkgs-src.json) }:

with import nixpkgs {
  overlays = [
    (self: super: {
      fm2gp = super.callPackage ./src {};
    })
  ];
};


if lib.inNixShell then
  mkShell {
    buildInputs = fm2gp.nativeBuildInputs;
  }
else
  fm2gp
