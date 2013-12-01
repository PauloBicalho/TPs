L1:	var_int(i) = var_int(const_i(0))
L3:	iffalse var_int(i) < var_int(const_i(10)) goto L4
L5:	var_int(j) = var_int(const_i(0))
L6:	iffalse var_int(j) < var_int(const_i(10)) goto L7
L8:	t1 = var_int(i) (i*) var_int(const_i(80))
	t2 = var_int(j) (i*) var_int(const_i(8))
	t3 = t1 (i+) t2
	var_[[float]](a)[t3] = var_int(const_i(0))
L9:	var_int(j) = var_int(j) (i+) var_int(const_i(1))
	goto L6
L7:	var_int(i) = var_int(i) (i+) var_int(const_i(1))
	goto L3
L4:	var_int(i) = var_int(const_i(0))
L10:	iffalse var_int(i) < var_int(const_i(10)) goto L2
L11:	t4 = var_int(i) (i*) var_int(const_i(80))
	t5 = var_int(i) (i*) var_int(const_i(8))
	t6 = t4 (i+) t5
	var_[[float]](a)[t6] = var_int(const_i(1))
L12:	var_int(i) = var_int(i) (i+) var_int(const_i(1))
	goto L10
L2: