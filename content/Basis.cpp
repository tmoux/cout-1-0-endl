const int D; //length of masks

ll basis[D]; // basis[i] keeps the mask of the vector whose f value is i

int bs = 0; //basis size

void insertVector(ll mask) {
	for (int i = 0; i < D; i++) {
		if ((mask & 1ll << i) == 0) continue; 

		if (!basis[i]) { 
			basis[i] = mask;
			++bs;
			return;
		}

		mask ^= basis[i]; 
	}
}

bool inSpan(ll mask) {
	for (int i = 0; i < D; i++) {
		if ((mask & 1ll << i) == 0) continue;
		mask ^= basis[i];
	}
  return mask == 0;
}
