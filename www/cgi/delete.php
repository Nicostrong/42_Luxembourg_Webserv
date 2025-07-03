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

<!DOCTYPE html>
<html lang="fr">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<title>Gestionnaire de fichiers - Répertoire <?php echo htmlspecialchars($directory); ?></title>
	<script src="/scripts/cookie.js"></script>
	<style>
		body {
			font-family: Arial, sans-serif;
			max-width: 1200px;
			margin: 20px auto;
			padding: 20px;
			background-color: #f5f5f5;
		}
		
		.container {
			background: white;
			padding: 30px;
			border-radius: 8px;
			box-shadow: 0 2px 10px rgba(0,0,0,0.1);
		}
		
		h1 {
			color: #333;
			border-bottom: 2px solid #007cba;
			padding-bottom: 10px;
		}
		
		.alert {
			padding: 15px;
			margin: 20px 0;
			border-radius: 4px;
		}
		
		.alert-success {
			background-color: #d4edda;
			color: #155724;
			border: 1px solid #c3e6cb;
		}
		
		.alert-error {
			background-color: #f8d7da;
			color: #721c24;
			border: 1px solid #f5c6cb;
		}
		
		.file-list {
			margin-top: 30px;
		}
		
		table {
			width: 100%;
			border-collapse: collapse;
			margin-top: 20px;
		}
		
		th, td {
			padding: 12px;
			text-align: left;
			border-bottom: 1px solid #ddd;
		}
		
		th {
			background-color: #007cba;
			color: white;
			font-weight: bold;
		}
		
		tr:hover {
			background-color: #f8f9fa;
		}
		
		.btn {
			padding: 8px 16px;
			border: none;
			border-radius: 4px;
			cursor: pointer;
			text-decoration: none;
			display: inline-block;
			font-size: 14px;
		}
		
		.btn-danger {
			background-color: #dc3545;
			color: white;
		}
		
		.btn-danger:hover {
			background-color: #c82333;
		}
		
		.file-icon {
			margin-right: 8px;
		}
		
		.empty-directory {
			text-align: center;
			padding: 40px;
			color: #666;
			font-style: italic;
		}
		
		.directory-info {
			background-color: #e9ecef;
			padding: 15px;
			border-radius: 4px;
			margin-bottom: 20px;
		}
		
		.file-count {
			font-weight: bold;
			color: #007cba;
		}
	</style>
	<script>
		function confirmDelete(filename) {
			return confirm('Êtes-vous sûr de vouloir supprimer le fichier "' + filename + '" ?\n\nCette action est irréversible.');
		}
	</script>
</head>
<body>
	<header class="header">
			<a href="/index.html" class="banner-link">
				<h1>Welcome on the WebServer of GneugneuTeam.</h1>
			</a>
		</header>
		<nav class="navbar">
			<a	href="/upload.html">Upload</a>
			<a	href="/download.html">Download</a>
			<a	href="/delete.html">Delete</a>
			<a  href="/new.html">New</a>
			<a	href="../cgi/hello_world.py">Hello World Python</a>
			<a	href="../cgi/hello_world.php">Hello World PHP</a>
			<a	href="../cgi/timeout.py">Timeout</a>
		</nav>
	<div class="container">
		<h1>📁 Gestionnaire de fichiers</h1>
		
		<div class="directory-info">
			<strong>Répertoire :</strong> <?php echo htmlspecialchars($directory); ?><br>
			<strong>Nombre de fichiers :</strong> <span class="file-count"><?php echo count($files); ?></span>
		</div>
		
		<?php echo $message; ?>
		
		<div class="file-list">
			<?php if (empty($files)): ?>
				<div class="empty-directory">
					📂 Le répertoire est vide<br>
					<small>Aucun fichier à afficher</small>
				</div>
			<?php else: ?>
				<table>
					<thead>
						<tr>
							<th>📄 Nom du fichier</th>
							<th>📊 Taille</th>
							<th>📅 Modifié le</th>
							<th>🔧 Actions</th>
						</tr>
					</thead>
					<tbody>
						<?php foreach ($files as $file): ?>
							<tr>
								<td>
									<span class="file-icon">
										<?php
										// Icônes selon le type de fichier
										switch (strtolower($file['type'])) {
											case 'pdf': echo '📄'; break;
											case 'doc':
											case 'docx': echo '📝'; break;
											case 'xls':
											case 'xlsx': echo '📊'; break;
											case 'jpg':
											case 'jpeg':
											case 'png':
											case 'gif': echo '🖼️'; break;
											case 'mp3':
											case 'wav': echo '🎵'; break;
											case 'mp4':
											case 'avi': echo '🎬'; break;
											case 'zip':
											case 'rar': echo '🗜️'; break;
											case 'txt': echo '📋'; break;
											default: echo '📄'; break;
										}
										?>
									</span>
									<?php echo htmlspecialchars($file['name']); ?>
								</td>
								<td><?php echo formatBytes($file['size']); ?></td>
								<td><?php echo date('d/m/Y H:i:s', $file['modified']); ?></td>
								<td>
									<form method="post" style="display: inline;" onsubmit="return confirmDelete('<?php echo htmlspecialchars($file['name']); ?>')">
										<input type="hidden" name="file_to_delete" value="<?php echo htmlspecialchars($file['name']); ?>">
										<button type="submit" name="delete_file" class="btn btn-danger">
											🗑️ Supprimer
										</button>
									</form>
								</td>
							</tr>
						<?php endforeach; ?>
					</tbody>
				</table>
			<?php endif; ?>
		</div>
		
		<div style="margin-top: 30px; padding-top: 20px; border-top: 1px solid #ddd; color: #666; font-size: 12px;">
			<strong>⚠️ Attention :</strong> La suppression des fichiers est définitive et ne peut pas être annulée.
		</div>
	</div>
</body>
</html>