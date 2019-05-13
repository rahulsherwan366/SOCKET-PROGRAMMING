All the theoritical parts of the question have been answered and commented at the top of that perticular source code.

How to execute:
(you can skip compiling statement step since executables are already there in the executable folder for each question)

#question1 :  compiling statement : gcc question1.c -o question1 
              running executable : ./question1 www.yahoo.com

#question2 :  First start the server by typing the following:
              compiling statement : gcc question2server.c -o question2server 
              running executable : ./question2server 

              Now run the client:
              compiling statement : gcc question2cli.c -o question2cli 
              running executable : ./question2cli localhost

#question3 : First start the server by typing the following:
              compiling statement : gcc question3tcpserv.c -o question3tcpserv 
              running executable : ./question3tcpserv 

              Now run the client:
              compiling statement : gcc question3cli.c -o question3cli
              running executable : ./question3cli helloserver 3993 helloservice
Note :- Its theoritical answer is in question3cli.c commented at the top.
#question4 : First start the server by typing the following:
              compiling statement : gcc question4udpserv.c -o question4udpserv 
              running executable : ./question4udpserv

              Now run the client:
              compiling statement : gcc question4cli.c -o question4cli
              running executable : ./question4cli helloserver 3993 helloservice

#question5 : First start the server by typing the following:
              compiling statement :  gcc question5serv.c -o question5serv
              running executable : ./question5serv 

              Now run the client:
              compiling statement : gcc question5cli.c -o question5cli
              running executable : ./question5cli localhost
Note : The netstat and other related commands which we have to run in question 5 has been done and i have put their screenshots
        in source code folder and its answers has been commented in the source code itself at the top. Its answer is in 
        question5cli.c.


#question6 : First start the server by typing the following:
              compiling statement :  gcc question6serv.c -o question6serv
              running executable : ./question6serv 

              Now run the client:
              compiling statement : gcc question6cli.c -o question6cli
              running executable : ./question6cli localhost

#question11 :  compiling statement :  gcc question11.c -o question11
              running executable : ./question11 www.cnn.com 80 GET index.html
