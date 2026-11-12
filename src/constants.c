/* The constants of the libvlc headers, as stubs/constants.stub.php (tools/constants.php) lists them. */
#include "runtime.h"
#include "../stubs/constants_arginfo.h"

void vlc_register_constants(int module_number)
{
	register_constants_symbols(module_number);
}
