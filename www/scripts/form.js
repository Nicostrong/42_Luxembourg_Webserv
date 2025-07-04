let fileInputCounter = 1;

// Fonction pour ajouter un input de fichier
function addFileInput() {
	fileInputCounter++;
	const fileInputs = document.getElementById('fileInputs');
	const newInputGroup = document.createElement('div');
	newInputGroup.className = 'file-input-group';
	newInputGroup.innerHTML = `
		<input type="file" name="file${fileInputCounter}" id="file${fileInputCounter}">
		<button type="button" class="remove-file-btn" onclick="removeFileInput(this)">
			(-) Remove
		</button>
	`;
	fileInputs.appendChild(newInputGroup);
}

// Fonction pour supprimer un input de fichier
function removeFileInput(button) {
	const inputGroup = button.parentElement;
	inputGroup.remove();
}

// Gestion de la sélection multiple
const multipleFilesInput = document.getElementById('multipleFiles');
const selectedFilesDiv = document.getElementById('selectedFiles');
const fileListUl = document.getElementById('fileList');
const multipleSelectDiv = document.querySelector('.multiple-select');

multipleFilesInput.addEventListener('change', function() {
	displaySelectedFiles(this.files);
});

// Fonction pour afficher les fichiers sélectionnés
function displaySelectedFiles(files) {
	fileListUl.innerHTML = '';
	
	if (files.length > 0) {
		selectedFilesDiv.style.display = 'block';
		
		Array.from(files).forEach((file, index) => {
			const li = document.createElement('li');
			li.innerHTML = `
				<span>${file.name}</span>
				<span class="file-size">${formatFileSize(file.size)}</span>
			`;
			fileListUl.appendChild(li);
		});
	} else {
		selectedFilesDiv.style.display = 'none';
	}
}

// Fonction pour formater la taille des fichiers
function formatFileSize(bytes) {
	if (bytes === 0) return '0 Bytes';
	const k = 1024;
	const sizes = ['Bytes', 'KB', 'MB', 'GB'];
	const i = Math.floor(Math.log(bytes) / Math.log(k));
	return parseFloat((bytes / Math.pow(k, i)).toFixed(2)) + ' ' + sizes[i];
}

// Gestion du drag and drop
multipleSelectDiv.addEventListener('dragover', function(e) {
	e.preventDefault();
	this.classList.add('dragover');
});

multipleSelectDiv.addEventListener('dragleave', function(e) {
	e.preventDefault();
	this.classList.remove('dragover');
});

multipleSelectDiv.addEventListener('drop', function(e) {
	e.preventDefault();
	this.classList.remove('dragover');
	
	const files = e.dataTransfer.files;
	multipleFilesInput.files = files;
	displaySelectedFiles(files);
});

// Validation avant soumission
document.getElementById('uploadForm').addEventListener('submit', function(e) {
	const allInputs = document.querySelectorAll('input[type="file"]');
	let hasFiles = false;
	
	for (let input of allInputs) {
		if (input.files && input.files.length > 0) {
			hasFiles = true;
			break;
		}
	}
	
	if (!hasFiles) {
		e.preventDefault();
		alert('Please select at least one file to upload.');
		return false;
	}
	
	// Vérifier la taille des fichiers
	for (let input of allInputs) {
		if (input.files) {
			for (let file of input.files) {
				if (file.size > 10 * 1024 * 1024) { // 10MB
					e.preventDefault();
					alert(`File "${file.name}" is too large. Maximum size is 10MB.`);
					return false;
				}
			}
		}
	}
});