<?php

$directory = '../files/';

if (!isset($_GET['filename']) || empty($_GET['filename']))
{
    http_response_code(400);
    echo "";
    echo "Nom du fichier manquant";
    exit;
}

$filename = basename($_GET['filename']);
$filePath = $directory . $filename;

if (!file_exists($filePath) || !is_file($filePath))
{
    http_response_code(404);
    echo "";
    echo "Fichier introuvable";
    exit;
}

http_response_code(200);
header('Content-Description: File Transfer');
header('Content-Type: application/octet-stream');
header('Content-Disposition: attachment; filename="' . $filename . '"');
header('Cache-Control: must-revalidate');
header('Pragma: public');
header('Expires: 0');
echo "";
readfile($filePath);
exit;

?>