# create buffer with length MAXCHARS as its length
	* IF in the program the buffer length exceeds MAXCHAR
		Create a ptr_buffer = malloc(2*MAXCHAR);
	* ELSE
		put chars in the buffer;
	* ENDIF
# Check to see if buffer line == heap_line (need a ptr to to start of the prev word and one to the end of the line in head )
	* every new line clear the buffer`(that is when input '\n') clear
	
