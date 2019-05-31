# OUTLINE : parseline

## Support
	* both file redirection and pipes

## OBJECTIVE
	* prompts for and reads a single mush cmd line and parses it into a list of cmds showing the I/O and arguments of each.

## GRAMMAR

	* CMD : cmd [options] [arg1...[argn]]
	* < : std in redirection (file name has to be valid) (doesnt have to be at the end);
	* > : std out redirection (file name has to be valid)
	* | : connects std out => std in of eac program
		* assume each program sourounded  

