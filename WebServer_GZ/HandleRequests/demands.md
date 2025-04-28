The job here is to execute the requests received.
for that we analyze the content of several variables from the class HttpBase
I think we still need to fill in the values

For verifying, we use the class Server, which offers testing functions
So I either instantiate Server in my HandleRequests Class or I inherit Server in order to have the functions.
I think inheriting is the much smoother way as it means i don't need to create special constructors for the Server

Now I am inheriting Server, which means I don't need my trivial checking Functions anymore.
Now I just need to adjust the Server Class, get rid of my Constructors