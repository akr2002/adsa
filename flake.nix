{
  description = "A build environment for C++ programs";

  inputs = {nixpkgs.url = "github:nixos/nixpkgs/master";};

  outputs = {
    self,
    nixpkgs,
  }: let
    pkgs = nixpkgs.legacyPackages.x86_64-linux.pkgs;
  in {
    devShell.x86_64-linux = pkgs.llvmPackages_19.libcxxStdenv.mkDerivation {
      name = "A build environment for C++ programs";
      buildInputs =
        (with pkgs; [
          clang_19
          clang-tools
          clang-analyzer
          lldb_19
        ])
        ++ (with pkgs.llvmPackages_19; [
          stdenv
          libcxxStdenv
          libcxxClang
          compiler-rt
          compiler-rt-libc
          bintools
          clangUseLLVM
          libcxxClang
          libcxx
          libllvm
          lld
          bintools
        ]);
      CPATH = builtins.concatStringsSep ":" [
        (pkgs.lib.makeSearchPathOutput "dev" "include" [pkgs.llvmPackages_19.libcxx])
        (pkgs.lib.makeSearchPath "resource-root/include" [pkgs.llvmPackages_19.clang])
      ];
      shellHook = ''
        echo "Usage: cxx -o bin source.cc"
        export CXX_MODULE_FLAGS='-fimplicit-modules -fimplicit-module-maps -fprebuilt-module-path=.'
        export CXX_SANITIZE_FLAGS='-fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=float-divide-by-zero -fsanitize=integer-divide-by-zero -fsanitize=nonnull-attribute -fsanitize=null -fsanitize=pointer-overflow -fsanitize=integer -fno-omit-frame-pointer'
        export CXX_WARNING_FLAGS='-Weverything -Wno-c++98-compat'
        alias cxx='clang++ -O1 -std=c++23 -stdlib=libc++ $(echo $CXX_MODULE_FLAGS $CXX_SANITIZE_FLAGS $CXX_WARNING_FLAGS) -g -fsafe-buffer-usage-suggestions'
      '';
    };
  };
}
