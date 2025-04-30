import sys

if len(sys.argv) != 5:
	print("Must be 4 arguments")
	exit()

with open("showdata_base.html", "r") as file:
	content = file.read()

username = "Flavian"
useremail = "Flavian@email.com"

content = content.replace("DATA1", sys.argv[1])
content = content.replace("DATA2", sys.argv[2])
content = content.replace("DATA3", sys.argv[3])
content = content.replace("DYNSTR", sys.argv[4])

with open("showdata_userid.html", "w+") as file:
	file.write(content)

print("Finished Updating ShowData")