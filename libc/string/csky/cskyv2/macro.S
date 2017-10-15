.macro M_BEZ rx, label
	bez   \rx, \label
.endm

.macro M_BNEZ rx, label
	bnez  \rx, \label
.endm

.macro M_BNE rx, ry, label
	cmpne \rx, \ry
	bt    \label
.endm

