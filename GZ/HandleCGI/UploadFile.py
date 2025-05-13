import sys
import streamlit as st

st.write("File Uploader")

content = st.file_uploader("Upload file")

if len(sys.argv) == 2:
    filename = sys.argv[1]
    if content is not None and not os.path.isfile(filename):
        with open(filename, "w+") as file:
            file.write(content)