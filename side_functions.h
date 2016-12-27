#ifndef SIDE_FUNCTIONS
#define SIDE_FUNCTIONS
long GCD(long a, long m){
	while(a!=m){
		if(a>m) a-=m;
		else m-=a;
	}
	return a;
}

int mod_inv(int a, int b)
{
	int b0 = b, t, q;
	int x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}
#endif