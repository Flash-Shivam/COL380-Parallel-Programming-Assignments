#include <stdio.h>
#include <stdlib.h>

void matrix_mult(int n, double A[n][n], double B[n][n],double result[n][n]);
void matrix_sub(int n, double A[n][n], double B[n][n],double result[n][n]);
void print_matrix(int n, double A[n][n]);

int main()
{
	int n;
	printf("Enter the size of the matrix: ");
	scanf("%d",&n);

	int no_threads;
	printf("Enter the no. of threads to be used: ");
	scanf("%d",&no_threads);

	double x;
  	struct drand48_data randBuffer;

  	srand48_r(time(NULL), &randBuffer);

	double a[n][n];

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			x=0;
			while(x==0)
			{
				drand48_r(&randBuffer, &x);
				a[i][j] = 100*x;	
			}
		}
	}

	print_matrix(n, a);
	printf("\n");

	double pi[n];
	for(int i=0;i<n;i++)
	{
		pi[i]=i;
	}

	double u[n][n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			u[i][j]=0;
		}
	}

	double l[n][n];
	for(int i=0;i<n;i++)
	{
		for (int j = 0; j < n; j++)
		{
			if(i==j)
				l[i][j]=1;
			else
				l[i][j]=0;
		}
	}

	for(int k=0;k<n;k++)
	{
		double max=0.1;
		int k_prime;
		for (int i = k; i < n; i++)
		{
			if(max<abs(a[i][k]))
			{
				max=abs(a[i][k]);
				k_prime=i;
			}
		}

		if(max==0)
		{
			//Throw error - Singular matrix
			printf("This is a singular matrix\n");
			// break;
		}

		//Swap pi
		double tmp=pi[k_prime];
		pi[k_prime]=pi[k];
		pi[k]=tmp;

		//Swap rows of a
		for (int i = 0; i < n; i++)
		{
			tmp=a[k][i];
			a[k][i]=a[k_prime][i];
			a[k_prime][i]=tmp;
		}

		for (int i = 0; i < k-1; i++)
		{
			tmp=l[k][i];
			l[k][i]=l[k_prime][i];
			l[k_prime][i]=tmp;
		}

		u[k][k]=a[k][k];

		for (int i = k+1; i < n; i++)
		{
			l[i][k]=a[i][k]/u[k][k];
			u[k][i]=a[k][i];
		}

		for (int i = k+1; i < n; i++)
		{
			for (int j = k+1; j < n; j++)
			{
				a[i][j]=a[i][j]-l[i][k]*u[k][j];
			}
		}
	}

	double P[n][n];

	for (int i = 0; i < n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(pi[i]==j)
				P[i][j]=1;
			else
				P[i][j]=0;
		}
	}

	double left[n][n];
	matrix_mult(n,P,a,left);
	double right[n][n];
	matrix_mult(n,l,u,right);
	double res[n][n];
	matrix_sub(n,left,right,res);

	print_matrix(n, res);

	

	return 0;
}

void matrix_mult(int n, double A[n][n], double B[n][n],double result[n][n])
{
	int i, j, k; 
	for (i = 0; i < n; i++) 
	{ 
		for (j = 0; j < n; j++) 
		{ 
			result[i][j] = 0; 
			for (k = 0; k < n; k++) 
			{
				result[i][j] += A[i][k]*B[k][j];
			} 
		} 
	}
}

void matrix_sub(int n, double A[n][n], double B[n][n],double result[n][n])
{
	int i, j; 
	for (i = 0; i < n; i++) 
	{ 
		for (j = 0; j < n; j++) 
		{ 
			result[i][j]=A[i][j]-B[i][j];
		} 
	}
}

void print_matrix(int n, double A[n][n])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
		    printf("%f\t", A[i][j]);
		}
		printf("\n");
	}

}