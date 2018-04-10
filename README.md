# nodejs_game_server
CS460 Final Project. Nodejs server that interacts with a C++ program



# Playing Rock Paper Scissors
This is what you should use to test the project

First, clone the repository.
Second, run npm install
Third, run `node node_modules/websockify/websockify.js localhost:7777 localhost:6789` to start the middle-man.
Fourth, Compile and run `rps_demo/rpsServer.c`. Or type `g++ rps_demo/rpsServer.c` followed by `a.out 6789`
Finally, open two instances of `rps_demo/rpsClient.html` so that two separate connections are established to the game. Alternatively, you could compile and run the rpsClient.c program and one instance of the rps_demo/rpsClient.html together.

# Playing Scrabble
This is a lot of unfinished pieces for something that was big in scope.
The Scrabble project is written in Microsoft Visual C++ and can be downloaded at https://github.com/keanedawg/ScrabblePlusPlus.

It does attempt to set up a TCP Stream using Winsocks but I haven't been able to get it to communicate with an html client. 
