L1:L3:	var_int(i) = var_int(i) (i+) var_int(const_i(1))
L5:	t1 = var_int(i) (i*) var_int(const_i(8))
	t2 = var_[float](a)[t1]
	if t2 < var_float(v) goto L3
L4:	var_int(j) = var_int(j) (i-) var_int(const_i(1))
L7:	t3 = var_int(j) (i*) var_int(const_i(8))
	t4 = var_[float](a)[t3]
	if t4 > var_float(v) goto L4
L6:	iffalse var_int(i) >= var_int(j) goto L8
L9:	goto L2
L8:	t5 = var_int(i) (i*) var_int(const_i(8))
	var_float(x) = var_[float](a)[t5]
L10:	t6 = var_int(i) (i*) var_int(const_i(8))
	t7 = var_int(j) (i*) var_int(const_i(8))
	t8 = var_[float](a)[t7]
	var_[float](a)[t6] = t8
L11:	t9 = var_int(j) (i*) var_int(const_i(8))
	var_[float](a)[t9] = var_float(x)
	goto L1
L2: