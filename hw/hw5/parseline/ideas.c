#define cd_limit() printf("command too long");
#define pipe_limit() printf("pipeline too deep");   
#define empty_stage() printf("invalid null command");  
#define many_arg(a) printf(#a": too many arguments");  
#define bad_input(a) printf(#a": bad input redirection");  
#define bad_output(a) printf(#a": bad output redirection");  
#define ambiguous_input(a) printf(#a": ambiguous input");}
#define ambiguous_output(a) printf(#a": ambiguous output");}
           
           
#define cd_limit() printf("command too long");
#define pipe_limit() printf("pipeline too deep");   
#define empty_stage() printf("invalid null command");  
#define many_arg(a) printf(#a": too many arguments");  
#define bad_input(a) printf(#a": bad input redirection");  
#define bad_output(a) printf(#a": bad output redirection");  
#define ambiguous_input(a) printf(#a": ambiguous input");
#define ambiguous_output(a) printf(#a": ambiguous output");


#define cd_limit() printf("command too long")
#define pipe_limit() printf("pipeline too deep")   
#define empty_stage() printf("invalid null command")
#define many_arg(str) printf("%s: too many arguments", str)   
#define empty_stage() printf("invalid null command")
           
            printf(" is");\ 
            printf(" %s number", str);\ 
            printf("\n");\ 
           while(0) 

void redirect_is_valid(char** cmd_line, stage_t* stage){ 
    /*pass in {"executable", "[flag|<|>|file|"*/
    /*check if the redirection is valid
    if valid: return TRUE 
    if not: print input| output redirect error message and return FALSE
    */ 
    char* str, skip = 0;
    int o = 0, i = 0; /* test if there is redundant redirection sign*/
    while(str = *cmd_line++){
        if(skip){
            skip = 0;
            continue;
        }
        else if(strcmp(str, ">")){
            printf(" this is a > ");
            if(*cmd_line == NULL){
                return FALSE;
                /* if > is the last arg - ERROR*/
            }
            /*if two redirect signs stack together* - ERROR*/
            if(strcmp(*cmd_line, ">") || strcmp(*cmd_line, "<")){
                return FALSE;
            }
            /*----- update Stage's outfile -------*/ 
            stage -> out_file = *cmd_line;
            skip = 1;
            o += 1;
        }
        else if(strcmp(str, "<")){
            printf(" this is a < ");
            if(*cmd_line == NULL){
                return FALSE;
                /* if > is the last arg - ERROR*/
            }
            /*if two redirect signs stack together* - ERROR*/
            if(strcmp(*cmd_line, ">") || strcmp(*cmd_line, "<")){
                return FALSE;
            }
             /*----- update Stage's infile -------*/ 
            stage -> in_file = *cmd_line;
            skip = 1;
            i += 1;
             
    }
    /*since we cant have two outfile*/
    if(i > 1){
        bad_input(cmd_line[0]);
        return FALSE;
    }
    if(o > 1){
        bad_output(cmd_line[0]);
        return FALSE;
    }
    return TRUE;
}

 if (next == NULL && !(*curr == '<' || *curr == '>')){
                strcpy(c->argv[c->argc++], curr);
                return 0;
            }
            else if (*curr == '>' || *curr == '<'){
                char f[CMDLINE_LEN];
                if (next == NULL){
                    return bad_redirect(curr);
                }
                direct = curr;
                curr = next+1;
                if (*curr == '\0'){
                    return bad_redirect(direct);
                }
                next = strpbrk(curr, whitespace);
                if (next){
                    strncpy(f, curr, next-curr);
                }
                else{
                    strncpy(f, curr, strlen(curr));
                }
                err = set_inoutname(c, direct, f);
                if (err < 0){
                    return err;
                }
                if (next){
                    curr = next+1;
                    next = NULL;
                }
                else{
                    return 0;
                }
            }
            else{
                strncpy(c->argv[c->argc++], curr, next-curr);
                curr = next+1;
                next = NULL;
            }
        }
        else{
            curr++;
        }
    