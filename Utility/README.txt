Lexer is "stupid", hence only knows how to parse a line, given specific defined strings,
 and return a queue of strings (parsed commands) based on the command given.

Should Lexer receive an unknown string, it will throw an execution error, returning to it's owner.
Thus, lexer's "parseLine" function usage should look like:
    try {
        lexer.parseLine(std::string someLine;
    } catch (std::exception& e) {
        std::cout << e.what(); // <--- example
    }

In this project, Lexer will be initialized in the client's main(), waiting to start server and connect client to the server.
 And then it will be used by the ClientHandler inside the server as well.

The ClientHandler will call lexer to parse lines and send back notifications to the user, that is
 to notify the client should his command received properly and were passed to the server for execution
 (execution will be done inside the server's Controller).

 the importance of the notifications are for situations such as (example): server opened on port 5054, and client
 is already connected, and the following line is parsed in the Lexer: "openDataServer 5400". The lexer should throw
 a runtime_error (since a server is already assigned) that will be caught be the ClientHandler and sent as an error
 to the user.


This structure allows us to continue reading from the client and handling both unknown strings and unknown commands.
 For more information regarding unknown commands, read the README.txt inside the Controller.