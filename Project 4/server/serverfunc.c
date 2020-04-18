 #include <stdio.h>
 #include <ctype.h>
 #include <stdlib.h>
 #include <string.h>

// Global array
int char_count[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void add_count(int alphai, int add){
     char_count[alphai] += add;
 }

void count(char *file){
    FILE* fp = fopen(file,"r");
    char c;
    // Local array to store char count
    int char_count_local[26]; 
    for( int i = 0; i < 26; i++){
     char_count_local[i] = 0;
     }
    while ((c = fgetc(fp)) != EOF) {
		if(isalpha(c)){
            c = tolower(c);
            char_count_local[c-'a']++;
		}
     }
    fclose(fp);
    for(int i = 0; i<26; i++){
         add_count(i, char_count_local[i]);
         }
}


 int main() // main for test purpose. 
 {
    count("Makefile");
    for(int i1 = 0; i1 < 26; i1++){
       printf("%d# ", char_count[i1]);
       }
 }