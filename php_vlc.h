#ifndef PHP_VLC_H
#define PHP_VLC_H

extern zend_module_entry vlc_module_entry;
#define phpext_vlc_ptr &vlc_module_entry

#define PHP_VLC_VERSION "0.11.0"

#if defined(ZTS) && defined(COMPILE_DL_VLC)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif
