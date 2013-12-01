L1:	var_int(f) = var_int(const_i(10))
L3:	var_int(r) = var_int(const_i(1))
L4:	iffalse var_int(f) > var_int(const_i(1)) goto L2
L5:	var_int(r) = var_int(r) (i*) var_int(f)
L6:	var_int(f) = var_int(f) (i-) var_int(const_i(1))
	goto L4
L2: