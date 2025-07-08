function validateLength()
{
    const lenghtInput = document.getElementById('length');
    const value = parseInt(lenghtInput.value, 10);

    if (isNaN(value) || value < 8 || value >= 251)
    {
        alert("Le mot de passe a generer doit avoir entre 8 et 250 caracteres");
        return false;
    }

    return true;
}