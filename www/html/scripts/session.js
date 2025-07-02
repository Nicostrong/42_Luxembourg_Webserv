// === GESTION DES SESSIONS ===
class SessionManager
{
    constructor()
    {
        this.sessionData = null;
        this.isInitialized = false;
    }
    
    // Obtenir le pseudo depuis le cookie (méthode utilitaire)
    getCurrentUser()
    {
        // Vérifier si CookieManager est disponible
        if (typeof CookieManager !== 'undefined')
            return CookieManager.getCookie('pseudo') || 'Unknown';
        
        // Fallback si CookieManager n'est pas chargé
        const value = `; ${document.cookie}`;
        const parts = value.split(`; pseudo=`);
        if (parts.length === 2)
            return decodeURIComponent(parts.pop().split(';').shift()) || 'Unknown';
        return 'Unknown';
    }
    
    async initSession()
    {
        try
        {
            console.log('Initialisation de la session...');
            const response = await fetch('/cgi/session_manager.py');
            
            if (!response.ok)
                throw new Error(`HTTP ${response.status}: ${response.statusText}`);
            
            this.sessionData = await response.json();
            
            if (this.sessionData.success)
            {
                console.log(' Session initialisee:', this.sessionData);
                this.isInitialized = true;
                this.updateSessionDisplay();
                this.attachEventListeners();
                return true;
            }
            else
            {
                console.error('Erreur session:', this.sessionData.error);
                return false;
            }
        }
        catch (error)
        {
            console.error('Erreur lors de l\'initialisation de session:', error);
            this.handleSessionError(error);
            return false;
        }
    }
    
    handleSessionError(error)
    {
        // Session de secours côté client
        this.sessionData =
        {
            success: true,
            session_id: `fallback_${Date.now()}`,
            new_session: true,
            current_page: window.location.pathname,
            visited_pages: [window.location.pathname],
            total_visits: 1,
            fallback: true
        };
        
        console.log('Session de secours creee:', this.sessionData);
        this.updateSessionDisplay();
    }
    
    updateSessionDisplay()
    {
        if (!this.sessionData)
            return;
        
        // Créer ou mettre à jour la section d'informations de session
        this.createSessionInfoSection();
        
        // Émettre un événement pour notifier les autres composants
        window.dispatchEvent(new CustomEvent('sessionUpdated',
        { 
            detail: this.sessionData 
        }));
    }
    
    createSessionInfoSection()
    {
        let sessionInfo = document.getElementById('session-info');
        
        if (!sessionInfo)
        {
            sessionInfo = document.createElement('div');
            sessionInfo.id = 'session-info';
            sessionInfo.style.cssText = `
                margin-top: 15px; 
                padding: 12px; 
                background: #f8f9fa; 
                border: 1px solid #dee2e6;
                border-radius: 8px; 
                font-size: 13px; 
                color: #495057;
                font-family: 'Courier New', monospace;
            `;
            
            const container = document.querySelector('.container');
            if (container)
                container.appendChild(sessionInfo);
        }
        
        const currentUser = this.getCurrentUser();
        const userDisplay = currentUser === 'Unknown' ? 
            '<span style="color: #6c757d; font-style: italic;">Anonyme</span>' : 
            `<span style="color: #28a745; font-weight: bold;">${currentUser}</span>`;
        
        const fallbackText = this.sessionData.fallback ? ' (Mode secours)' : '';
        const newSessionText = this.sessionData.new_session ? 'Nouvelle' : 'Existante';
        
        sessionInfo.innerHTML = `
            <div style="border-bottom: 1px solid #dee2e6; padding-bottom: 8px; margin-bottom: 8px;">
                <strong>Session WebServ${fallbackText}</strong>
            </div>
            <div style="display: grid; grid-template-columns: auto 1fr; gap: 8px; font-size: 12px;">
                <strong>ID:</strong> <code>${this.sessionData.session_id}</code>
                <strong>Type:</strong> <span>${newSessionText}</span>
                <strong>Page actuelle:</strong> <code>${this.sessionData.current_page}</code>
                <strong>Pages visitees:</strong> <span>${this.sessionData.visited_pages.join(', ')}</span>
                <strong>Visites totales:</strong> <span>${this.sessionData.total_visits}</span>
                <strong>Utilisateur:</strong> ${userDisplay}
                <strong>Timestamp:</strong> <span>${new Date().toLocaleString()}</span>
            </div>
        `;
    }
    
    async trackPageVisit(page = null) {
        if (!this.isInitialized)
            {
            console.warn('Session non initialisee, impossible de tracker la page');
            return;
        }
        
        const currentPage = page || window.location.pathname;
        
        try
        {
            const response = await fetch(`/cgi/session_manager.py`,
            {
                method: 'GET',
                headers:
                {
                    'X-Current-Page': currentPage
                }
            });
            
            if (response.ok)
            {
                const updatedSessionData = await response.json();
                if (updatedSessionData.success)
                {
                    this.sessionData = updatedSessionData;
                    this.updateSessionDisplay();
                    console.log('Page trackee:', currentPage);
                }
            }
        }
        catch (error)
        {
            console.error('Erreur lors du tracking de page:', error);
        }
    }
    
    attachEventListeners()
    {
        window.addEventListener('pseudoChanged', (event) =>
        {
            console.log('Session informee du changement de pseudo:', event.detail.pseudo);
            this.updateSessionDisplay();
        });
        
        let currentPath = window.location.pathname;
        setInterval(() =>
        {
            if (window.location.pathname !== currentPath)
            {
                currentPath = window.location.pathname;
                this.trackPageVisit(currentPath);
            }
        }, 1000);
    }
    
    getSessionInfo()
    {
        return {
            ...this.sessionData,
            currentUser: this.getCurrentUser()
        };
    }
    
    isSessionActive()
    {
        return this.isInitialized && this.sessionData && this.sessionData.success;
    }
    
    destroy()
    {
        this.sessionData = null;
        this.isInitialized = false;
        
        const sessionInfo = document.getElementById('session-info');
        if (sessionInfo)
            sessionInfo.remove();
        
        console.log('Session détruite');
    }
}

// === INSTANCE GLOBALE ===
const sessionManager = new SessionManager();

// === INITIALISATION ===
document.addEventListener('DOMContentLoaded', async function()
{
    console.log('Initialisation du SessionManager...');
    await sessionManager.initSession();
});

// === FONCTIONS GLOBALES POUR ACCÈS EXTERNE ===
window.getSessionInfo = () => sessionManager.getSessionInfo();
window.isSessionActive = () => sessionManager.isSessionActive();
window.trackPageVisit = (page) => sessionManager.trackPageVisit(page);
window.getCurrentUser = () => sessionManager.getCurrentUser();

// === DEBUG ===
window.debugSession = () =>
{
    console.log('=== DEBUG SESSION ===');
    console.log('Initialisée:', sessionManager.isInitialized);
    console.log('Active:', sessionManager.isSessionActive());
    console.log('Utilisateur actuel:', sessionManager.getCurrentUser());
    console.log('Données:', sessionManager.sessionData);
};