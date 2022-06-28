int main(int argc, char **argv)
{
	int a = 5;
	int b = 4;

	int *pa = &a;
	int *pb = &b;

	(void)argc;
	(void)argv;

	++pa, ++pb;

	return (0);
}

