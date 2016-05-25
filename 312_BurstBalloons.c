int maxCoins(int* nums, int numsSize) {
    if (numsSize == 0)
        return 0;
    int*** p;
    int limit, i, j, k;
    p = (int**)malloc(numsSize * sizeof(int**));
    for (i = 0; i < numsSize; i++) {
        p[i] = (int*)malloc(numsSize * sizeof(int*));
        for (j = 0; j < numsSize; j++)
            p[i][j] = (int)malloc(numsSize * sizeof(int));
    }
    build_cache(nums, numsSize, p);
    return find_solution(nums, numsSize, p);
}

int next_comb(int *i, int *j, int *k, int limit) {
    if (*i == *j - 1 && *j == *k - 1 && *k == limit - 1) {
        return 0;
    }
    if (*k < limit - 1) {
        *k = *k + 1;
        return 1;
    }
    if (*j < *k - 1) {
        *j = *j + 1;
        *k = *j + 1;
        return 1;
    }
    *i = *i + 1;
    *j = *i + 1;
    *k = *j + 1;
    return 1;
}

int map_value(int* nums, int numsSize, int i, int j, int k) {
    int v1 = i < 0? 1: nums[i];
    int v2 = nums[j];
    int v3 = k == numsSize? 1: nums[k];
    return v1 * v2 * v3;
}

void build_cache(int* nums, int numsSize, int*** p) {
    int limit, i, j, k;
    limit = numsSize + 1, i = -2, j = limit - 2, k = limit - 1;
    while (next_comb(&i, &j, &k, limit)) {
        p[i+1][j][k-1] = map_value(nums, numsSize, i, j, k);
    }
}

int next_lex_perm(int *a, int n) {
#	define swap(i, j) { a[i] ^= (a[j] ^ (a[j] ^= (a[i] ^ a[j]))); }
	int k, l, t, k1, l1;
	for (k = n - 1; k && a[k - 1] >= a[k]; k--);
	if (!k--) return 0;
	for (l = n - 1; a[l] <= a[k]; l--);
	swap(k, l);
	for (k1 = k + 1, l1 = n - 1; l1 > k1; l1--, k1++)
		swap(k1, l1);
	return 1;
#	undef swap
}

int find_solution(int* nums, int numsSize, int*** p) {
    int i, max = 0;
    int* iz = (int)malloc(numsSize * sizeof(int));
    int* op = (int)malloc(numsSize * sizeof(int));
    for (i = 0; i < numsSize; i++)
        iz[i] = i;
    do {
        int j, k, l, count = 0;
        for (i=0; i<numsSize; i++)
            op[i] = 0;
        for (i=0; i<numsSize; i++) {
            k = iz[i];
            op[k] = 1;
            for(j = k - 1; j > -1 && op[j] == 1; j--);
            for(l = k + 1; l < numsSize && op[l] == 1; l++);
            count += p[j+1][k][l-1];
        }
        if (count > max)
            max = count;
    } while (next_lex_perm(iz, numsSize));
    return max;
}
