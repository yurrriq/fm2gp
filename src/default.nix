{ lib, stdenv, doxygen, gcc, texlive, makeFontsConf,  }:

stdenv.mkDerivation rec {
  pname = "fm2gp";
  name = "${pname}-${version}";
  version = builtins.readFile ../VERSION;

  src = ./.;

  outputs = [ "out" "doc" ];

  makeFlags = [
    "prefix=$(out)"
  ];

  nativeBuildInputs = [
    doxygen
    gcc
    (texlive.combine {
      inherit (texlive) scheme-basic
        adjustbox
        caption
        collectbox
        ec
        float
        helvetic
        metrix
        tabu
        multirow
        courier
        sectsty
        tocloft
        varwidth
        xcolor
        xkeyval
        wasysym
        wasy
       ;
    })
  ];

  meta = with stdenv.lib; {
    description = "From Mathematics to Generic Programming";
    homepage = https://github.com/yurrriq/fm2gp;
    license = licenses.mit;
    maintainers = with maintainers; [ yurrriq ];
  };
}
