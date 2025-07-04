function validateLenght()
{
    const lenghtInput = document.getElementById('lenght');
    const value = parseInt(lenghtInput.value, 10);

    if (isNaN(value) || value <= 8 || value >= 501)
    {
        alert("Le mot de passe a generer doit avoir entre 8 et 500 caracteres");
        return false;
    }

    return true;
}