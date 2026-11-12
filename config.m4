PHP_ARG_WITH([vlc],
  [whether to enable libvlc support],
  [AS_HELP_STRING([[--with-vlc[=DIR]]], [Enable the libvlc 3.0 bindings; DIR is the prefix holding include/vlc/vlc.h])],
  [no])

PHP_ARG_ENABLE([vlc-probes],
  [whether to build the vlc probe switch],
  [AS_HELP_STRING([--enable-vlc-probes],
    [Build the VLC_PROBE_OFF switch that tests/Probes drives: env VLC_PROBE_OFF=<site id> turns that kept refusal off. Never for a release build])],
  [no],
  [no])

if test "$PHP_VLC" != "no"; then
  if test "$PHP_VLC_PROBES" != "no"; then
    AC_DEFINE([VLC_PROBES], [1], [Kept refusal sites can be turned off through env VLC_PROBE_OFF])
  fi

  dnl VLC.app ships headers and dylibs but no pkg-config file: find the prefix by its header.
  AC_MSG_CHECKING([for libvlc])
  VLC_DIR=
  for i in $PHP_VLC /Applications/VLC.app/Contents/MacOS /opt/homebrew /usr/local /usr; do
    if test "$i" != "yes" && test -r "$i/include/vlc/vlc.h"; then
      VLC_DIR=$i
      break
    fi
  done
  if test -z "$VLC_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([include/vlc/vlc.h not found: install VLC.app 3.0 (macOS) / apt install libvlc-dev (Debian) or pass --with-vlc=DIR])
  fi
  AC_MSG_RESULT([$VLC_DIR])

  dnl VLC.app keeps its dylibs in lib/ whatever PHP_LIBDIR is.
  VLC_LIBDIR=$VLC_DIR/$PHP_LIBDIR
  test -d "$VLC_DIR/lib" && test ! -d "$VLC_LIBDIR" && VLC_LIBDIR=$VLC_DIR/lib

  PHP_CHECK_LIBRARY([vlc], [libvlc_new],
    [
      PHP_ADD_INCLUDE([$VLC_DIR/include])
      PHP_ADD_LIBRARY_WITH_PATH([vlc], [$VLC_LIBDIR], [VLC_SHARED_LIBADD])
    ],
    [AC_MSG_ERROR([libvlc found at $VLC_DIR but libvlc_new does not link])],
    [-L$VLC_LIBDIR])
  PHP_SUBST([VLC_SHARED_LIBADD])

  PHP_NEW_EXTENSION([vlc],
    [src/vlc.c src/runtime.c src/types.c src/constants.c src/libvlc.c src/gen_player.c src/player.c src/gen_lists.c src/gen_discovery.c src/discovery.c src/gen_vlm.c src/vlm.c src/gen_dialog.c src/queue.c src/callbacks.c],
    [$ext_shared],, [-DZEND_ENABLE_STATIC_TSRMLS_CACHE=1])
  PHP_ADD_BUILD_DIR([$ext_builddir/src])
fi
