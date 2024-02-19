void * __cdecl memset(void* dst, int ch, unsigned long long count) {
	unsigned char C = *(unsigned char *)&ch;
	unsigned char *Dst = (unsigned char *)dst;
	while (count) {
		*Dst++ = C;
		count -= 1;
	}
	return dst;
}
