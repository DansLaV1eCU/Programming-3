#include <stdio.h>

int	horn()
{
	int		res;
	int		negative;
	char	chr;

	negative = 1;
	res = 0;
	chr = getchar();
	if (chr == '-')
	{
		negative = -1;
		chr = getchar();
	}
	while (chr != '\n' && chr != ' ')
	{
		res = res * 10 + (chr - 48);
		chr = getchar();
	}
	return (res * negative);
}

void towerOfHanoi(int n, int from_rod, int to_rod,
                  int aux_rod)
{
    if (n == 0) {
        return;
    }
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    printf("Kotouc %d z %d na %d\n", n, from_rod, to_rod);
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main()
{
    int N;

	N = horn();
    towerOfHanoi(N, 1, 2, 3);
    return 0;
}