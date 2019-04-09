/* getFormat: 
return  0: if argc != 3 - more argument than needed
returns 1: if -d option is valid
return  2: argv[1] = SET1 and arv[2] = SET2
*/
int getFormat(int argc, const char *argv)
{

	if ( argc != 3)
		return 0;
	if ( *(argv) == '-' && *(argv+1) == 'd')
		return 1;
	else
		return 2; /*translation set1 -> set 2*/
}

int main(int argc, char *argv[])
{
	int num = getFormat(argc, argv[1]);
	printf("0: usage error\n 1: -d 'set'\n 2: 'set1' 'set2'\n : %d", num);

	return 0;
}
