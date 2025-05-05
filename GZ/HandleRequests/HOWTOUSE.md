Instructions on how to use the HandleRequests class:

Definition:
attributes: (method, uri, http, body)

Purpose:
check whether the attributes given in the Request (method, uri, http, body) are correct
IF YES:
return the values of (method, uri, http, body) via Getters.
IF NO:
return an error message

HOW IT WORKS:
Checks call Check Functions in the Server Class (Nico).
return a str/str map containing the attributes