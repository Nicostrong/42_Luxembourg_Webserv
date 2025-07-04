<?php
// Configuration
$directory = 'files';
$message = '';

// Créer le répertoire s'il n'existe pas
if (!file_exists($directory)) {
	mkdir($directory, 0755, true);
}

// Traitement de la suppression
if (isset($_POST['delete_file']) && !empty($_POST['file_to_delete'])) {
	$fileToDelete = $_POST['file_to_delete'];
	$fullPath = $directory . '/' . $fileToDelete;
	
	// Vérification de sécurité : s'assurer que le fichier est dans le bon répertoire
	if (strpos(realpath($fullPath), realpath($directory)) === 0 && file_exists($fullPath)) {
		if (unlink($fullPath)) {
			$message = "<div class='alert alert-success'>Fichier '$fileToDelete' supprimé avec succès.</div>";
		} else {
			$message = "<div class='alert alert-error'>Erreur lors de la suppression du fichier '$fileToDelete'.</div>";
		}
	} else {
		$message = "<div class='alert alert-error'>Fichier non trouvé ou accès non autorisé.</div>";
	}
}

// Récupérer la liste des fichiers
function getFiles($dir) {
	$files = [];
	if (is_dir($dir)) {
		$items = scandir($dir);
		foreach ($items as $item) {
			if ($item != '.' && $item != '..' && is_file($dir . '/' . $item)) {
				$filePath = $dir . '/' . $item;
				$files[] = [
					'name' => $item,
					'size' => filesize($filePath),
					'modified' => filemtime($filePath),
					'type' => pathinfo($item, PATHINFO_EXTENSION)
				];
			}
		}
	}
	return $files;
}

$files = getFiles($directory);

// Fonction pour formater la taille
function formatBytes($size, $precision = 2) {
	$units = array('B', 'KB', 'MB', 'GB', 'TB');
	for ($i = 0; $size > 1024 && $i < count($units) - 1; $i++) {
		$size /= 1024;
	}
	return round($size, $precision) . ' ' . $units[$i];
}
?>