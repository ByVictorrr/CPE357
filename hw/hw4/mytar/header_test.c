
/*has to be recursive*/
void transverse_dir(uint8 *path, int outFd, int flags)
{
}


void transverse(uint8 *path, int outFd, int options[])
{
	struct dirent *entry;
	struct stat file_info;
	DIR *directory;
	int i;

	/*step 1 - open current directory */
	if((directory = opendir(path)) == NULL)
		print_error("opendir err")

	/*Step 2 - perform a transversal with each entry*/
	for(;dirent=readdir(directory) != NULL;)
	{

	/*Step 3 - get information associated with that directory entry*/
	if(lstat(path, &file_info) == -1)
		print_error("lstat err");
	/*step 4 - look out for the .. and . case which are not extending directories*/
	if (strcmp(dirent, ".") != 0 || strcmp(dirent, "..") != 0)
	{

		/*step 5.1 - is the entry a directory that isnt  . or ..*/
		if (S_ISDIR(file_info.st_mode))
		{
			/*Print because of verbosity*/
			if(option[4] == TRUE)
			{
                /*print file*/
			}
			/*step 6.1 - add entry*/
			writeFileEntry(pathname, name_parsed, outFd)

		
		}
		/*Step 5.2 - reg file*/
		else if(S_ISREG(file_info.st_mode))
		{
			writeFileEntry(pathname, name_parsed_outFd)

		}
		/*step 5.3 - symbolic link*/
		else if (S_ISLNK(file_info.st_mode))
		{

		}else{ /*accepting no other file types*/
			print_error("not accepting type of files");
		}




		/*step 5.3 - is the entry a link*/
	}
	
	}

}
