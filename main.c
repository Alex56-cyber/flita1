#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_ONE 9
#define LEN_INPUT 1+1

int if_exist=0;
void guide()
{
    printf("\n______MENU______\n");
    printf("This is a program for setting two sets.\n");
    printf("The set is filled with DECIMAL integers.\n");
    printf("The second one, with binary numbers, is built automatically\n");
}
void help()
{
    printf("\n______HELP______\n");
    printf("Enter the letter and click on the enter if you want:\n");
    printf("A or a -To fill in the set\n");
    printf("B or b -To output a set in binary form\n");
    printf("D or d -To output a set in decimal form\n");
    printf("H or h -To call for help\n");
    printf("E or e -To exit the program\n");
}
int checking_n(char array[], int array_size)
{
    int flag=0;
    for (int i= array_size; i!= 0l; i--)
    {
        if (array[i]=='\n')
        {
            flag=1;
            break;
        }
    }
    return flag;
}
int checking_uniq(int element,int control_set[], int len_conrtol_set)
{
    int flag=1;
    for (int i=0;i!=len_conrtol_set;i++)
    {
        if (control_set[i]==element)
        {
            flag=0;
            break;
        }
    }
    return flag;
}
char menu_input()
{
    char stdinput[(LEN_INPUT+1)]="";
    fgets(stdinput, (LEN_INPUT+1), stdin);
    for(;;){
        if (checking_n(stdinput, strlen(stdinput))==0)
        {
            memset(stdinput, 0,(LEN_INPUT + 1));
            fflush(stdin);
            puts("More than one symbol has been entered, write -H or h for help\n");
            fgets(stdinput, LEN_INPUT + 1, stdin);
        }
        else
            break;
    }
    return stdinput[0];
}
void dec_to_bin(int dec)
{
    if (dec>=2){
        dec_to_bin(dec/2);
    }
    printf("%d",dec%2);
}

int is_number(char array[], int len)
{
    int flag=1;
    char alf_array[10]="1234567890";
    if (array[0]=='-'||array[0]=='+')
    {
        int counter=0;
        for (int i=1; i!=len; i++)
        {
            for (int j=0; j!=10;j++)
            {
                if (array[i]==alf_array[j])
                {
                    counter++;
                    break;
                }
            }
            if (counter!=i)
            {
                flag=0;
                break;
            }
        }
    }
    else{
        int counter=0;
        for (int i=0; i!=len; i++)
        {
            for (int j=0; j!=10;j++)
            {
                if (array[i]==alf_array[j])
                {
                    counter++;
                    break;
                }
            }
            if (counter!=(i+1))
            {
                flag=0;
                break;
            }
        }
    }
    return flag;
}
int line_len(char enter[])
{
    int i=0;
    while (enter[i]!='\n')
    {
        i++;
    }
    return i;
}


void enter_element(char array[]) {
    char  input_string[(LEN_ONE + 1)]="";
    memset(input_string, 0, (LEN_ONE + 1));
    fgets(input_string, LEN_ONE + 1, stdin);
    for(;;){
        if (checking_n(input_string, strlen(input_string)) == 0)
        {
            memset(input_string, 0, (LEN_ONE + 1));
            fflush(stdin);// чистим буфер
            printf("The length is exceeded, enter no more %d\n", LEN_ONE);
        }
        else
            break;
        fgets(input_string, LEN_ONE + 1, stdin);
    }
    for (int i=0; i!=strlen(input_string); i++)
    {
        array[i]=input_string[i];
    }
}
void rewrite(char array[],char result[], int len)
{
    for (int i=0; i!=len;i++)
    {
        result[i]=array[i];
    }
}
int* make_dec_set(int len_set)
{
    int *resulted= (int*) malloc(sizeof (int) * len_set);
    char input_line[(LEN_ONE + 1)] = "";
    for (int i=1; i<=len_set;i++)
    {
        for(;;)
        {
            printf("Enter %d element of the set: ", i);
            enter_element(input_line);
            int new_size= line_len(input_line);
            char first_pre[new_size];
            rewrite(input_line, first_pre, new_size);
            if (is_number(first_pre,new_size))
            {
                int element=atoi(input_line);
                if (element>=0 && checking_uniq(element, resulted, i - 1))
                {
                    resulted[i - 1]= element;
                    printf("%d successfully written to %d element of the set \n", element, i);
                    break;
                } else if (element>=0 && checking_uniq(element, resulted, i - 1) == 0){
                    printf("The element is already in the set\n");
                } else{
                    printf("The element cannot be negative");
                }

            }
            else printf("Incorrect input, repeat input\n");
        }
    }
    printf("The set was successfully written\n");
    if_exist=1;
    return &resulted[0];
}
void print_dec_array(int array[], int len)
{
    for (int i=0; i!=len;i++){
        printf("%d element=%d\n",(i+1),array[i]);
    }

}
void print_bin_array(int array[], int len)
{
    for (int i=0; i!=len;i++){
        printf("%d element=", i+1);
        dec_to_bin(array[i]);
        printf("\n");
    }

}
void main()
{
    char result_input=' ';
    char input_string[(LEN_ONE + 1)] = "";
    int* dec_array;
    guide();
    help();
    for(;;){
        result_input=menu_input();
        if (result_input == 'A' || result_input == 'a')
        {
            if (if_exist==0)
            {
                printf("Enter the number of set elements: ");
                enter_element(input_string);
                int new_size= line_len(input_string);
                char first_pre[new_size];
                rewrite(input_string, first_pre, new_size);
                if (is_number(first_pre,new_size))
                {
                    if (atoi(input_string) >= 0)
                    {
                        dec_array= make_dec_set(atoi(input_string));
                    }
                    else{
                        printf("The number cannot be negative\n");
                        printf("repeat the set input_string operation\n");
                    }
                } else
                {
                    printf("The entered string is not a number\n");
                    printf("repeat the set input_string operation\n");
                }

            } else printf("The array has already been set\n");

        }else if (result_input == 'B' || result_input == 'b')
        {
            if (if_exist)
            {
                printf("Array in binary format:\n");
                print_bin_array(dec_array, atoi(input_string));
            }
            else printf("First create an array");
        } else if (result_input == 'D' || result_input == 'd')
        {
            if (if_exist)
            {
                printf("Array in decimal format:\n");
                print_dec_array(dec_array, atoi(input_string));
            }
            else printf("First create an array");
        }
        else if (result_input == 'H' || result_input == 'h')
        {
            help();
        }
        else if (result_input == 'E' || result_input == 'e')
        {
            exit(1);
        }
        else {
            printf("The wrong symbol\n");
            printf("H or h -To call for help\n");
        }
    }

}