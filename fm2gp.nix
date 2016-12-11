{ stdenv }:

stdenv.mkDerivation rec {
  name = "fm2gp-1.0.0";

  src = ./src;

  installPhase = ''
    pwd
    ls -la
    prefix=$out make install
  '';

  meta = with stdenv.lib; {
    description = "From Mathematics to Generic Programming";
    homepage = "https://github.com/yurrriq/fm2gp";
    license = licenses.mit;
    maintainers = with maintainers; [ yurrriq ];
  };
}
