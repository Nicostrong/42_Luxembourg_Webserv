import sys
import streamlit as st
import os

"""

env_dict = dict(os.environ)

    Body> Stdinput



"""


st.write("File Uploader")

content = st.file_uploader("Upload file")



if content is not None:
    with open("userinput.txt", "w+") as file:
        file.write(content)