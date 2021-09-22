struct Compress {//Uses all 8 bits
	static unsigned char data[];
	int pos = 0, curr = -1;
	uint64_t Data(int bits, uint64_t x = 0) {
		assert(1 <= bits and bits <= 64);
		for (int i = 0; i < bits; i++) {
			if (++curr == 8) { pos++; curr = 0; }
			if (((x >> i) ^ (data[pos] >> curr)) & 1) {
				data[pos] ^= 1 << curr;
				x ^= 1llu << i;
			}
		}
		return x;
	}
	void Print() {
		FILE *fp = fopen("compressed.cpp", "w");
		fprintf(fp, "unsigned char Compress::data[] = \"");
		for (int i = 0; i <= pos; ++i) {
			unsigned char x = data[i];
			if (x == '\n') fprintf(fp, "\\n");
			else if (x == '\r') fprintf(fp, "\\r");
			else if (x == '\\' || x == '\"') fprintf(fp, "\\%c", x);
			// else if (x == '\?') fprintf(fp, "\\%c", x); //required only if online judge still uses trigraphs
			else putc(x, fp);
		}
		fprintf(fp, "\";\n");
		fclose(fp);
	}
};
unsigned char Compress::data[2 * 128 * 1024 /* More than will be written. */];
