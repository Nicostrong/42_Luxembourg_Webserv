The job here is to execute the requests received.
for that we analyze the content of several variables from the class HttpBase
I think we still need to fill in the values

For verifying, we use the class Server, which offers testing functions
So I either instantiate Server in my HandleRequests Class or I inherit Server in order to have the functions.
I think inheriting is the much smoother way as it means i don't need to create special constructors for the Server

Now I am inheriting Server, which means I don't need my trivial checking Functions anymore.
Now I just need to adjust the Server Class, get rid of my Constructors

Ok, now I am inheriting the Server and can use the Controller Functions directly
Now I just need to access the variables from Httpbase
Simple Getters should be enough

Now I need to make sure the variables got the right values.
Let's assume for now they have good content:
let's just make the executing logic

let's use pseudo code for this:
my main problem is I don't know the logic for sending the stuff,
I think flavian will handle that with HTTP Response
Let's just prepare the most simple possible Getter he could call to get the finished data.
Flavian's HTTPResponse receives a HTTPrequest reference, which is my class
yes he just uses my Getters to have a string, so let's create it
also it looks like he is just concat the different elements (method, uri, etc.) as strings
so my job could be really easy.

the hardest part is understanding what I need to deliver...
they also want to me respect the stuff in the webconfig

just use the permissions/denials from the config