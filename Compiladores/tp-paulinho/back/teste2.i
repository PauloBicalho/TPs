L1:	var_int(n) = var_int(const_i(10))
L3:	var_int(r) = var_int(const_i(1))
L4:	iffalse var_int(n) > var_int(const_i(1)) goto L2
L5:	var_int(r) = var_int(r) (i*) var_int(n)
L6:	var_int(n) = var_int(n) (i-) var_int(const_i(1))
	goto L4
L2: