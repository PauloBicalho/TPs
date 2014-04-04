L1:	var_bool(r) = var_bool(true)
L3:	var_bool(r) = var_bool(false)
L4:	iffalse var_int(a) < var_int(b) goto L6
	t1 = true
	goto L7
L6:	t1 = false
L7:	var_bool(r) = t1
L5:	iffalse var_int(x) <= var_int(y) goto L9
	t2 = true
	goto L10
L9:	t2 = false
L10:	var_bool(r) = t2
L8:	iffalse var_int(a) == var_int(b) goto L12
	t3 = true
	goto L13
L12:	t3 = false
L13:	var_bool(r) = t3
L11:	iffalse var_int(x) != var_int(y) goto L15
	t4 = true
	goto L16
L15:	t4 = false
L16:	var_bool(r) = t4
L14:	iffalse var_int(a) >= var_int(b) goto L18
	t5 = true
	goto L19
L18:	t5 = false
L19:	var_bool(r) = t5
L17:	iffalse var_int(x) > var_int(y) goto L21
	t6 = true
	goto L22
L21:	t6 = false
L22:	var_bool(r) = t6
L20:	if var_int(x) < var_int(const_i(100)) goto L26
	iffalse var_int(x) > var_int(const_i(200)) goto L24
L26:	t7 = true
	goto L25
L24:	t7 = false
L25:	var_bool(r) = t7
L23:	iffalse var_int(a) < var_int(const_i(100)) goto L28
	iffalse var_int(a) > var_int(const_i(200)) goto L28
	t8 = true
	goto L29
L28:	t8 = false
L29:	var_bool(r) = t8
L27:	if var_int(x) < var_int(const_i(100)) goto L33
	iffalse var_int(x) > var_int(const_i(200)) goto L31
	iffalse var_int(x) != var_int(y) goto L31
L33:	t9 = true
	goto L32
L31:	t9 = false
L32:	var_bool(r) = t9
L30:	if var_int(a) < var_int(const_i(100)) goto L37
	iffalse var_int(a) > var_int(const_i(200)) goto L38
	if var_int(a) != var_int(const_i(150)) goto L37
L38:	iffalse var_int(a) != var_int(const_i(0)) goto L35
L37:	t10 = true
	goto L36
L35:	t10 = false
L36:	var_bool(r) = t10
L34:	iffalse var_int(x) > var_int(const_i(200)) goto L43
	if var_int(x) != var_int(b) goto L42
L43:	iffalse var_int(x) < var_int(const_i(100)) goto L40
L42:	t11 = true
	goto L41
L40:	t11 = false
L41:	var_bool(r) = t11
L39:	if var_int(a) < var_int(const_i(100)) goto L46
	iffalse var_int(a) > var_int(const_i(200)) goto L44
	iffalse var_int(a) != var_int(b) goto L44
L46:	t12 = true
	goto L45
L44:	t12 = false
L45:	var_bool(r) = t12
L2: