


int strl(const char * s)
{
		char * base = s;

		while ((*s)++ != '\0')
			;
			return base - s;
}

