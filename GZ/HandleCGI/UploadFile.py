import streamlit as st

st.write("File Uploader")

content = st.file_uploader("Upload file")

if content is not None and not os.path.isfile("userinput.txt"):
    with open("userinput.txt", "w+") as file:
        file.write(content)