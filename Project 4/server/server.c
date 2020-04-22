#include "server.h"

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


# Not tested
# Assume First arg is an array of file path, second arg is number of threads
int main(int argc, char *argv[]){
  # Create c threads
  int num_threads = atoi(argv[2]);
  p_thread threads[num_threads];
  for (int i = 0; i < num_threads; i++){
    pthread_create(&threads[i], NULL, (void *)count, NULL);
  }

  # Create Mutex 
  pthread_mutex_t mut;

  # for each thread
   for (int i = 0; i < num_threads; i++){
      pthread_mutex_lock(&mut);

      # receive a file path
      # count and update thread
      count(argv[1][i]);

      # loop until receive END ??


      pthread_mutex_unlock(&mut);
  }

    # Wait all thread to finish
   for (int i = 0; i < num_threads; i++){
     pthread_join(threads[i],NULL);
  }

  # send final result



}