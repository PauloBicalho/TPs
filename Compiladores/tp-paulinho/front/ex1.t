{
  int i; int j; float v; float x; float[100] a;

  i = 0;
  j = 0;
  v = 0.0;
  x = 0.0;

  while( true ) {
    do i = i+1; while( a[i] < v);
    do j = j-1; while( a[j] > v);

    if( i >= j ) break;
    x = a[i]; a[i] = a[j]; a[j] = x;
  }
}

