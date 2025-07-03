<?php

$_SERVER['REDIRECT_STATUS'] = '200';

http_response_code(200);
header('Content-Type: application/json');
header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Methods: POST');
header('Access-Control-Allow-Headers: Content-Type');

// Vérifier que c'est une requête POST
if ($_SERVER['REQUEST_METHOD'] !== 'POST')
{
	echo json_encode([
		'success' => false,
		'message' => 'Méthode non autorisee'
	]);
	exit;
}

$directory = '../files/';
$response = ['success' => false, 'message' => ''];

try
{
	$raw = file_get_contents('php://input');
	parse_str($raw, $parsed);

	$filename = $parsed['filename'] ?? null;
	$filename = basename($filename);

	if (!$filename)
	    throw new Exception('Nom du fichier non recu (fallback php://input)');

	$filePath = $directory . $filename;
	file_put_contents('/tmp/debug_delete.txt', "file path $filePath");

	// Tenter la suppression
	if (unlink($filePath))
	{
		$response = [
			'success' => true,
			'message' => 'Fichier supprime avec succes',
			'filename' => $filename
		];
		
		// Log de la suppression (optionnel)
		error_log("Fichier supprime: $filePath par " . ($_SERVER['REMOTE_ADDR'] ?? 'IP inconnue'));
		
	}
	else
	{
		throw new Exception('Impossible de supprimer le fichier');
	}
	
}
catch (Exception $e)
{
	$response = [
		'success' => false,
		'message' => $e->getMessage()
	];
	
	error_log("Erreur suppression fichier: " . $e->getMessage());
}

echo json_encode($response);
?>