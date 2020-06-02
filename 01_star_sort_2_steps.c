#include <stdio.h>
#include <stdlib.h>

void Swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void Piramida_ocnova(int star_massiv[], int coren, int dno)
{
	int Maxheap;
	int complete = 0;
	while ((coren * 2 <= dno) && (!complete))
	{
		if (coren * 2 == dno)
		{
			Maxheap = coren * 2;
		}
		else if (star_massiv[coren * 2] > star_massiv[coren * 2 + 1])
		{
			Maxheap = coren * 2;
		}
		else
		{
			Maxheap = coren * 2 + 1;
		}
		if (star_massiv[coren] < star_massiv[Maxheap])
		{
			Swap(&star_massiv[coren], &star_massiv[Maxheap]);
			coren = Maxheap;
		}
		else
		{
			complete = 1;
		}
	}
}

void sort_piramida(int *star_massiv, int star_massiv_size, FILE *star_file)
{
	for (int i = (star_massiv_size / 2) - 1; i >= 0; i--)
	{
		for (int j = 0; j < star_massiv_size; j++)
			fprintf(star_file, "%d ", star_massiv[j]);
		fprintf(star_file, "\n");
		Piramida_ocnova(star_massiv, i, star_massiv_size - 1);
	}

	for (int i = star_massiv_size - 1; i >= 1; i--)
	{
		for (int j = 0; j < star_massiv_size; j++)
			fprintf(star_file, "%d ", star_massiv[j]);
		fprintf(star_file, "\n");
		Swap(&star_massiv[0], &star_massiv[i]);
		Piramida_ocnova(star_massiv, 0, i - 1);
	}
}

void sort_fast(int *star_massiv, int temp_left, int temp_right, int n, FILE *star_file)
{
	int i;
	if (temp_left < temp_right)
	{
		int left = temp_left, right = temp_right, middle = star_massiv[(left + right) / 2];
		do
		{
			while (star_massiv[left] < middle)
				left++;
			while (star_massiv[right] > middle)
				right--;
			if (left <= right)
			{
				for (i = 0; i < n; i++)
					fprintf(star_file, "%d ", star_massiv[i]);
				fprintf(star_file, "\n");
				int tmp = star_massiv[left];
				star_massiv[left] = star_massiv[right];
				star_massiv[right] = tmp;
				left++;
				right--;
			}
		} while (left <= right);

		sort_fast(star_massiv, temp_left, right, n, star_file);
		sort_fast(star_massiv, left, temp_right, n, star_file);
	}
}

int main()
{
	int i, n, vvod;

	scanf("%d", &n);

	int *sort_fast_massiv = (int *)malloc(n * sizeof(int));
	int *sort_piramida_massiv = (int *)malloc(n * sizeof(int));

	for (i = 0; i < n; i++)
	{
		scanf("%d", &vvod);
		sort_fast_massiv[i] = vvod;
		sort_piramida_massiv[i] = vvod;
	}

	FILE *star_file;

	star_file = fopen("sort_fast.log", "w");
	sort_fast(sort_fast_massiv, 0, n - 1, n, star_file);
	fclose(star_file);

	FILE *star_file2;

	star_file2 = fopen("sort_piramida.log", "w");
	sort_piramida(sort_piramida_massiv, n, star_file2);
	for (int j = 0; j < n; j++)
		fprintf(star_file, "%d ", sort_piramida_massiv[j]);
	fprintf(star_file, "\n");
	fclose(star_file2);

	for (i = 0; i < n; i++)
		printf("%d ", sort_piramida_massiv[i]);
	printf("\n");

	return 0;
}