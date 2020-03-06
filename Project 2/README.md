 #CSCI4061Project 2
 ##Contributor
 Zhou Zhuang: Shell, File redirection, Pipes, exit
 Jian Wang: ls
 Fei Gao: cd wc
 
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
 
