# OUTLINE : parseline

## Support
	* both file redirection and pipes

## OBJECTIVE
	* prompts for and reads a single mush cmd line and parses it into a list of cmds showing the I/O and arguments of each.

## GRAMMAR

	* CMD : cmd [options] [arg1...[argn]]
	* < : std in redirection
	* > : std out redirection
	*
