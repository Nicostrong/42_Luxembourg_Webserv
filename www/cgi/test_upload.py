# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_upload.py                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/25 09:31:34 by nfordoxc          #+#    #+#              #
#    Updated: 2025/06/25 10:00:23 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import io
import sys
import os
from upload import get_boundary, parse_multipart, main, UPLOAD_DIR

class FakeStdin:
    def __init__(self, data: bytes):
        self.buffer = io.BytesIO(data)
    def read(self, *args, **kwargs):
        # Pour content_length = 0, .read() peut être appelée
        return self.buffer.read(*args, **kwargs)

def make_multipart_data(boundary, files):
    """
    Génère un body multipart/form-data pour tests.
    files: liste de tuples (fieldname, filename, bytesdata)
    """
    lines = []
    for fieldname, filename, filedata in files:
        lines.append(f"--{boundary}")
        lines.append(f'Content-Disposition: form-data; name="{fieldname}"; filename="{filename}"')
        lines.append("Content-Type: application/octet-stream")
        lines.append("")
        lines.append(filedata.decode('utf-8') if isinstance(filedata, bytes) else filedata)
    lines.append(f"--{boundary}--")
    lines.append("")
    return "\r\n".join(lines).encode("utf-8")
    
def test_main():
    # ... (préparation multipart identique à avant)
    boundary = "----WebKitFormBoundary7MA4YWxkTrZu0gW"
    files = [
        ("file1", "test1.txt", b"Hello 1"),
        ("file2", "test2.txt", b"Hello 2"),
    ]
    from test_upload import make_multipart_data  # ou recopie l'ancienne fonction ici
    multipart_data = make_multipart_data(boundary, files)

    os.environ["CONTENT_TYPE"] = f"multipart/form-data; boundary={boundary}"
    os.environ["CONTENT_LENGTH"] = str(len(multipart_data))

    # Remplacer sys.stdin par un faux stdin avec .buffer
    sys.stdin = FakeStdin(multipart_data)

    # Nettoyage dossier uploads...
    if os.path.exists(UPLOAD_DIR):
        for f in os.listdir(UPLOAD_DIR):
            os.remove(os.path.join(UPLOAD_DIR, f))
    else:
        os.makedirs(UPLOAD_DIR)

    # Exécute
    main()

    # Vérification identique...
    uploaded_files = set(os.listdir(UPLOAD_DIR))
    assert "test1.txt" in uploaded_files
    assert "test2.txt" in uploaded_files
    with open(os.path.join(UPLOAD_DIR, "test1.txt"), "rb") as f:
        assert f.read() == b"Hello 1"
    with open(os.path.join(UPLOAD_DIR, "test2.txt"), "rb") as f:
        assert f.read() == b"Hello 2"

if __name__ == "__main__":
    test_main()
    print("Test terminé avec succès !")