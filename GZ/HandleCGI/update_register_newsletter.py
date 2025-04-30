with open("register_newsletter_base.html", "r") as file:
	content = file.read()

username = "Flavian"
useremail = "Flavian@email.com"

content = content.replace("GREETING", "Hello World, CGI is working!")
content = content.replace("USERNAME", username)
content = content.replace("USEREMAIL", useremail)

with open("register_newsletter.html", "w+") as file:
	file.write(content)

print("Finished Updating Newsletter")