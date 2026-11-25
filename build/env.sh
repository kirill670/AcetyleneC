if [ -z "$ACETYLENE_ROOT" ]; then
  _self="${BASH_SOURCE:-$0}"
  case "$_self" in
    /*|[A-Za-z]:*) : ;;
    *) _self="$(pwd)/$_self" ;;
  esac
  ACETYLENE_ROOT="$(cd "$(dirname "$_self")/.." && pwd)"
fi
export ACETYLENE_ROOT

if [ -z "${MINGW32_ROOT:-}" ]; then
  MINGW32_ROOT="$ACETYLENE_ROOT/.cache/tools/mingw32"
fi

if [ -x "$MINGW32_ROOT/bin/i686-w64-mingw32-gcc.exe" ] || [ -x "$MINGW32_ROOT/bin/i686-w64-mingw32-gcc" ]; then
  export MINGW32_ROOT
  export PATH="$MINGW32_ROOT/bin:$PATH"
else
  unset MINGW32_ROOT
fi

if [ -z "${CC:-}" ]; then
  export CC=i686-w64-mingw32-gcc
fi
export AR="${AR:-ar}"
export RANLIB="${RANLIB:-ranlib}"

if [ -n "${MINGW32_ROOT:-}" ] && [ -x "$MINGW32_ROOT/bin/mingw32-make.exe" ]; then
  export MAKE="$MINGW32_ROOT/bin/mingw32-make.exe"
elif command -v mingw32-make >/dev/null 2>&1; then
  export MAKE=mingw32-make
else
  export MAKE=make
fi
