#include <stdio.h>
 #include <ctype.h>
 #include <stdlib.h>
 #include <string.h>

// Global array
int char_count[26]; 
for( x= 0; x < 26; x++)
{
    char_count[x] = 0;
}


void count_file(char* path){
    int char_count[26]; 
    for( x= 0; x < 26; x++){
     char_count[x] = 0;
     }
    char c;
    while((c = getchar()) != EOF){
       if(isalpha(c)){
           c = tolower(c);
            char_count[c-'a']++;
        }
     }
    //  for(i = 0; i<26; i++){
    //      addcount(i, char_count[i]);
    //  }
 }

 main() // main for test purpose. 
 {


 
  
 }