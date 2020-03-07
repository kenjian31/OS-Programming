 # CSCI4061 Project 2

 This first part of the project involved implementation of Unix commands: *cd*, *ls* and *wc*.  
 The second part provide a shell allows commands running, file redirection and pipes. 
 ## Unix commands
 
 To complie, do
 ```
 make
 ```
 
 ### cd
 
 Change directory to a given path. For example
 ```make
 ./cd <path>
 ./cd ..
 ./cd ~
 ./cd -  #only supported in shell
```

 ### ls
List files and directions. When used with the argument -R, it recursively displays the content of every subdirectory in the given path. If the path is not given, use the current working directory as the path.
For example, 
 ```
 ./ls <path>
 ./ls -R <path>
 ./ls
 ```
 
 ### wc
Find the line,word and character count of a file. *wc -l* print the number of lines, *wc -w* print the number of words and *wc -c* print the number of characters.  
If no file is specified, *wc* will take input from STDIN. 
For example,
```
./wc filename
./wc -l filename
./wc -w filename
./wc -c filename
./wc
```
## Implementation of Unix shell
The shell implementation supports all command listed, file redirection and pipes. 

To run, do
```
./shell
```
### File redirection
The ‘>' operator will truncate the old contents in the file if any. And the ‘>>’ operator will append the new contents to the old contents of the file if any. For example,
```
 ls > out.txt
```
will redirect the output of ls command to a file named out.txt.

### Pipes
Handle one pipe between two commands. For example,
```
cat data.txt | grep student
```
will search for the word ‘student’ in the output of ‘cat data.txt’, which is the content of the file ‘data.txt’.

### Work together
Count outputs of ls and append to result.
```
ls | wc >> result
```

### To exit the shell
```
exit
```

### Known Bugs
1. Do not support multiple pipes
2. ^D is not supported yet
3. ls -R will print an extra line at the bottom

### Contributor
Zhou Zhuang: shell.

Jian Wang: ls.  

Fei Gao: wc. 
  
