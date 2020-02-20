// If the first char is an ! 
if(scanned_input[0] == '!')
{
    if(arg_count == 0)
    {
        printf("No recent arguments to execute"); 
        continue; 
    }

    // Check for the second character 
    if(s[1] == '!')
    {
        // Command in case of two consequetive !! commands: add_into_array(past_com[0])
        char com[MAX_LINE] = past_com[0]; 
        char *curr_arr[]; 
        tokenize(com, curr_arr); 
    }
    else
    {
        int n = s[1] - 48; 
        if(n >= 11 || x <= 0)
            printf("Error Capacity only for 10 commands\n"); 
        
        // add_to_array(past_com[n]); 
        char com[MAX_LINE] = past_com[n]; 
        char *curr_arr[]; 
        tokenize(com, curr_arr); 
    }
}else 
{
    add_to_array(scanned_input); 
    tokenize(scanned_input, args); 
}