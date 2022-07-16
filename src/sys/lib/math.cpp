#include <sys/lib/math.h>

int abs(int i)
{
    return i < 0 ? -i : i;
}

int Clamp(int value, int min, int max)
{
	if (min > max)
	{
		return 0;
	}
	if (value < min)
	{
		return min;
	}
	else if (value > max)
	{
		return max;
	}
	return value;
}

double floor(double num) {
    if (num >= 9223372036854775807 || num <= -9223372036854775807 || num != num)
     {
        return num;
    }
    long long n = (long long)num;
    double d = (double)n;
    if (d == num || num >= 0)
        return d;
    else
        return d - 1;
}

float sin(float x)
{
  float res=0, pow=x, fact=1;
  for(int i=0; i<5; ++i)
  {
    res+=pow/fact;
    pow*=-1*x*x;
    fact*=(2*(i+1))*(2*(i+1)+1);
  }

  return res;
}

double cos(double x) {
	x = modd(x, PI);
    char sign = 1;
    if (x > PI)
    {
        x -= PI;
        sign = -1;
    }
    double xx = x * x;

    return sign * (1 - ((xx) / (2)) + ((xx * xx) / (24)) - ((xx * xx * xx) / (720)) + ((xx * xx * xx * xx) / (40320)) - ((xx * xx * xx * xx * xx) / (3628800)) + ((xx * xx * xx * xx * xx * xx) / (479001600)) - ((xx * xx * xx * xx * xx * xx * xx) / (87178291200)) + ((xx * xx * xx * xx * xx * xx * xx * xx) / (20922789888000)) - ((xx * xx * xx * xx * xx * xx * xx * xx * xx) / (6402373705728000)) + ((xx * xx * xx * xx * xx * xx * xx * xx * xx * xx) / (2432902008176640000)));
}