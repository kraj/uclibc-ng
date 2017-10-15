.file  "initfini.c"

.section .init
	ldw	lr, (sp, 4)
	addi	sp, 8
	rts

.section .fini
	ldw	lr, (sp, 4)
	addi	sp, 8
	rts
