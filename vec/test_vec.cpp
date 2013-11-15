#include <iostream>
#include <cstdio>
#include <string.h>
#include <string>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;

template <class T> T sqr(T x) { return x * x; }

const int maxT = 100000 + 10;
const int maxn = 100 + 10;
const int maxl = 30 + 2;
char keyword[maxn][maxl];
char divide_st[30][1024];

struct Vector
{
    int id;
	int vx[maxn];
	double vy[30];
} vec[maxT], myvec;
int nT, nvx, nvy;
int n_word;

bool isNum(char x) { return '0' <= x && x <= '9'; }
bool isChr(char x) { return ('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z'); }

char toHchr(char x)
{
    if ('a' <= x && x <= 'z') return x - 'a' + 'A';
    return x;
}

double st2r(char * s)
{
	double dr = 10.0, e = 1.0, ans = 0.0;
	for (int i = 0; i < strlen(s); i++)
		if (s[i] == '.') {
			dr = 1.0, e = 0.1;
		} else
		if (isNum(s[i])) {
			ans = ans * dr + e * (s[i] - '0');
			if (dr < 5.0) e = e * 0.1;
		}
	return ans;
}

void divide(char * s)
{
	int id = 0, len = 0;
	for (int i = 0; i < strlen(s) - 3; i++)
	if (s[i] == '"' && s[i + 1] == ',' && s[i + 2] == '"') {
		i += 2;
		divide_st[id][len++] = '\0';
		id ++;
		len = 0;
	} else {
		if (isNum(s[i]) || isChr(s[i]) || (id>=4 && s[i]=='.')) {
            if (isChr(s[i])) s[i] = tolower(s[i]);
            divide_st[id][len++] = s[i];
		} else {
		    divide_st[id][len++] = ' ';
		}
	}
	divide_st[id][len++] = '\0';
}

void calc(char * st, Vector * vec)
{
    for (int i = 0; i != n_word; i++)
    if (strcmp(keyword[i], st) == 0) {
        vec->vx[i]++;
    }
}

void Output(FILE * output_file, int id, Vector * vec)
{
    fprintf(output_file, "%d", id);
    for (int i = 0; i != 5 + 4 + 15; i++)
        fprintf(output_file, ",%.3lf", vec->vy[i]);
    fprintf(output_file, "\n");
}

double dis(Vector * x, Vector * y)
{
    double ans = 0;
    for (int i = 0; i != nvx; i++)
        ans += sqr(x->vx[i] - y->vx[i]);
    return ans;
}

int getmin(Vector * myvec)
{
    double min_d = 1e+10, tmp;
    int min_index = 0;
    for (int i = 0; i != nT; i++) {
        tmp = dis(myvec, vec + i);
        if (tmp < min_d) {
            min_index = i;
            min_d = tmp;
            if (min_d < 1e-6) break;
        }
    }
    // printf("%d %.2lf\n", min_index, min_d);
    return min_index;
}

int main()
{
	char x[2000 + 10];

    FILE * fp = fopen("important_word.csv_dm", "r");
	for (n_word = 0; fscanf(fp, "%s", keyword[n_word]) != EOF; n_word++) {
        printf("%s\n", keyword[n_word]);
	}
	fclose(fp);

    FILE * input_vec_file = fopen("train_word_vec.out", "r");
    fscanf(input_vec_file, "%d%d", &nvx, &nvy);
    while (fscanf(input_vec_file, "%d", &vec[nT].id) != EOF) {
        for (int i = 0; i != nvx; i++)
            fscanf(input_vec_file, "%d", &vec[nT].vx[i]);
        for (int i = 0; i != nvy; i++)
            fscanf(input_vec_file, "%lf", &vec[nT].vy[i]);
        nT++;
    }
    fclose(input_vec_file);

    FILE * input_file = fopen("test.csv", "r");
    FILE * output_file = fopen("test_vec.out", "w");

    int m = 0;
	while (fgets(x, 2000, input_file)) {
		divide(x);
		memset(&myvec, 0, sizeof(myvec));
		int j = 0;
		for (int i = 0; i < strlen(divide_st[1]); i++) {
			if (isNum(divide_st[1][i]) || isChr(divide_st[1][i])) {
                x[j++] = divide_st[1][i];
			} else {
			    x[j++] = '\0';
			    calc(x, &myvec);
                j = 0;
			}
		}
		Output(output_file, st2r(divide_st[0]), &vec[getmin(&myvec)]);
		m ++;
	}
    divide(x);


    fclose(input_file);
    fclose(output_file);

    return 0;
}

