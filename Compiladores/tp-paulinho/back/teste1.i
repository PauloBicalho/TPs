L1:	var_int(i) = var_int(const_i(10))
L3:	var_int(j) = var_int(const_i(0))
L4:	var_float(v) = var_float(const_f(0.000000))
L5:	var_float(x) = var_float(const_f(0.000000))
L6:L7:	var_int(i) = var_int(i) (i+) var_int(const_i(1))
L9:	t1 = var_int(i) (i*) var_int(const_i(8))
	t2 = var_[float](a)[t1]
	if t2 < var_float(v) goto L7
L8:	var_int(j) = var_int(j) (i-) var_int(const_i(1))
L11:	t3 = var_int(j) (i*) var_int(const_i(8))
	t4 = var_[float](a)[t3]
	if t4 > var_float(v) goto L8
L10:	iffalse var_int(i) >= var_int(j) goto L12
L13:	goto L2
L12:	t5 = var_int(i) (i*) var_int(const_i(8))
	var_float(x) = var_[float](a)[t5]
L14:	t6 = var_int(i) (i*) var_int(const_i(8))
	t7 = var_int(j) (i*) var_int(const_i(8))
	t8 = var_[float](a)[t7]
	var_[float](a) [ t6 ] = t8
L15:	t9 = var_int(j) (i*) var_int(const_i(8))
	var_[float](a) [ t9 ] = var_float(x)
	goto L6
L2: