#ifndef SIDE_FUNCTIONS
#define SIDE_FUNCTIONS
long GCD(long a, long m){
	while(a!=m){
		if(a>m) a-=m;
		else m-=a;
	}
	return a;
}
#endif