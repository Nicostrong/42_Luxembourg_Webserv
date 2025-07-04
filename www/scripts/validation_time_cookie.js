function validateDuration()
{
    const durationInput = document.getElementById('duration');
    const value = parseInt(durationInput.value, 10);

    if (isNaN(value) || value < 60)
    {
        alert("La duree doit etre un nombre superieur a 60 secondes.");
        return false;
    }

    return true;
}