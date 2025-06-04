<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST')
{
	if (isset($_FILES['file']) && $_FILES['file']['error'] == 0)
	{
		$upload_dir = '../uploads/';
		$file_name = basename($_FILES['file']['name']);
		$upload_file = $upload_dir . $file_name;

		$file_type = pathinfo($upload_file, PATHINFO_EXTENSION);

		if (move_uploaded_file($_FILES['file']['tmp_name'], $upload_file))
		{
			echo "Upload succes : " . $upload_file;
		}
		else
		{
			echo "Error uploading.";
		}
	}
	else
	{
		echo "Error no file received";
	}
}
?>