#include <sysdep.h>
.file  "initfini.c"

.section .init
ENTRY(_init)
	subi	sp, 8
	stw	lr, (sp, 4)

.section .fini
ENTRY(_fini)
	subi	sp, 8
	stw	lr, (sp, 4)

