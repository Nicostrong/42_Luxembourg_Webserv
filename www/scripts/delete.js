// Charger la liste des fichiers au démarrage
document.addEventListener('DOMContentLoaded', function() {
	loadFiles();
});

// Fonction pour charger la liste des fichiers
function loadFiles()
{
	showLoading(true);
	hideMessage();
	
	fetch('/cgi/get_files.php')
		.then(response => response.json())
		.then(data => {
			showLoading(false);
			if (data.success)
			{
				displayFiles(data.files);
				updateFileCount(data.files.length);
			}
			else
			{
				showMessage('Erreur lors du chargement des fichiers: ' + data.message, 'error');
			}
		})
		.catch(error => {
			showLoading(false);
			showMessage('Erreur de communication avec le serveur', 'error');
			console.error('Erreur:', error);
		});
}

// Fonction pour afficher les fichiers
function displayFiles(files)
{
	const fileListDiv = document.getElementById('fileList');
	
	if (files.length === 0)
	{
		fileListDiv.innerHTML = `
			<div class="empty-directory">
				Le repertoire est vide<br>
				<small>Aucun fichier a afficher</small>
			</div>
		`;
		return;
	}

	let html = `
		<table>
			<thead>
				<tr>
					<th>Nom du fichier</th>
					<th>Taille</th>
					<th>Modifie le</th>
					<th>Actions</th>
				</tr>
			</thead>
			<tbody>
	`;

	files.forEach(file =>
	{
		html += `
			<tr>
				<td>${escapeHtml(file.name)}</td>
				<td>${formatBytes(file.size)}</td>
				<td>${formatDate(file.modified)}</td>
				<td>
					<button class="btn-danger" onclick="deleteFile('${escapeForAttribute(file.name)}')">
						Supprimer
					</button>
				</td>
			</tr>
		`;
	});

	html += `
			</tbody>
		</table>
	`;

	fileListDiv.innerHTML = html;
}

// Fonction pour supprimer un fichier
function deleteFile(filename)
{
	if (!confirm(`Etes-vous sur de vouloir supprimer le fichier "${filename}" ?\n\nCette action est irreversible.`))
	{
		return;
	}

	showLoading(true);
	hideMessage();

	const formData = new FormData();
	formData.append('filename', filename);

	fetch('/cgi/delete_file.php', {
    	method: 'POST',
    	headers: {
    	    'Content-Type': 'application/x-www-form-urlencoded'
    	},
    	body: 'filename=' + encodeURIComponent(filename)
	})
	.then(response => response.json())
	.then(data => {
		showLoading(false);
		if (data.success)
		{
			showMessage(`Fichier "${filename}" supprime avec succes`, 'success');
			loadFiles();
		}
		else
		{
			showMessage('Erreur lors de la suppression: ' + data.message, 'error');
		}
	})
	.catch(error => {
		showLoading(false);
		showMessage('Erreur de communication avec le serveur', 'error');
		console.error('Erreur:', error);
	});
}

// Fonctions utilitaires
function showMessage(message, type)
{
	const messageDiv = document.getElementById('message');
	messageDiv.textContent = message;
	messageDiv.className = `alert alert-${type}`;
	messageDiv.style.display = 'block';
	
	// Masquer le message après 5 secondes
	setTimeout(() => { hideMessage(); }, 5000);
}

function hideMessage()
{
	document.getElementById('message').style.display = 'none';
}

function showLoading(show)
{
	document.getElementById('loading').style.display = show ? 'block' : 'none';
}

function updateFileCount(count)
{
	document.getElementById('fileCount').textContent = count;
}

function formatBytes(bytes)
{
	if (bytes === 0) return '0 B';
	const units = ['B', 'KB', 'MB', 'GB'];
	const i = Math.floor(Math.log(bytes) / Math.log(1024));
	return Math.round(bytes / Math.pow(1024, i) * 100) / 100 + ' ' + units[i];
}

function formatDate(timestamp)
{
	const date = new Date(timestamp * 1000);
	return date.toLocaleString('fr-FR');
}

// Fonction pour échapper le HTML
function escapeHtml(text)
{
	const map = {
		'&': '&amp;',
		'<': '&lt;',
		'>': '&gt;',
		'"': '&quot;',
		"'": '&#039;'
	};
	return text.replace(/[&<>"']/g, function(m) { return map[m]; });
}

// Fonction pour échapper les attributs
function escapeForAttribute(text)
{
	return text.replace(/'/g, "\\'").replace(/"/g, '\\"');
}