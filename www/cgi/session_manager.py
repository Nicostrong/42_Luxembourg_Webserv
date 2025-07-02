# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    session_manager.py                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfordoxc <nfordoxc@42luxembourg.lu>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 09:06:53 by nfordoxc          #+#    #+#              #
#    Updated: 2025/07/02 16:11:26 by nfordoxc         ###   Luxembourg.lu      #
#                                                                              #
# **************************************************************************** #

#!/usr/bin/env python3
import os
import sys
import uuid
import json
from datetime import datetime
from pathlib import Path
from urllib.parse import unquote

# Configuration
SESSIONS_DIR = "sessions"
SESSION_DURATION = 30 * 60  # 30 minutes en secondes

# Déterminer le chemin absolu du répertoire sessions
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
SESSIONS_FULL_PATH = os.path.join(SCRIPT_DIR, "..", SESSIONS_DIR)

def debug_log(message):
    """Fonction de debug pour écrire dans les logs d'erreur"""
    sys.stderr.write(f"[DEBUG] {message}\n")
    sys.stderr.flush()

def ensure_sessions_directory():
    """Crée le répertoire sessions s'il n'existe pas"""
    try:
        sessions_path = Path(SESSIONS_FULL_PATH)
        sessions_path.mkdir(parents=True, exist_ok=True)
        debug_log(f"Repertoire sessions cree/verifie : {sessions_path.absolute()}")
        
        if not os.access(sessions_path, os.W_OK):
            debug_log(f"ERREUR: Pas de permission d'ecriture sur {sessions_path}")
            return False
        
        return True
    except Exception as e:
        debug_log(f"ERREUR lors de la creation du repertoire sessions: {e}")
        return False

def get_existing_session_id():
    """Récupère l'ID de session depuis les cookies"""
    http_cookie = os.environ.get('HTTP_COOKIE', '')
    debug_log(f"Cookies reçus: {http_cookie}")
    
    if not http_cookie:
        return None
    
    for cookie in http_cookie.split(';'):
        cookie = cookie.strip()
        if cookie.startswith('session_id='):
            session_id = cookie.split('=', 1)[1]
            debug_log(f"Session ID trouve: {session_id}")
            return session_id
    
    debug_log("Aucun session_id trouve dans les cookies")
    return None

def get_pseudo_from_cookies():
    """Récupère le pseudo depuis les cookies"""
    http_cookie = os.environ.get('HTTP_COOKIE', '')
    if not http_cookie:
        return 'Unknown'
    
    for cookie in http_cookie.split(';'):
        cookie = cookie.strip()
        if cookie.startswith('pseudo='):
            pseudo = cookie.split('=', 1)[1]
            decoded_pseudo = unquote(pseudo) if pseudo else 'Unknown'
            debug_log(f"Pseudo trouve: {decoded_pseudo}")
            return decoded_pseudo
    
    debug_log("Aucun pseudo trouve, utilisation de 'Unknown'")
    return 'Unknown'

def load_session(session_id):
    """Charge une session existante"""
    if not session_id:
        return None
    
    session_file = Path(SESSIONS_FULL_PATH) / f"{session_id}.json"
    debug_log(f"Tentative de chargement de session: {session_file}")
    
    if not session_file.exists():
        debug_log(f"Fichier de session n'existe pas: {session_file}")
        return None
    
    try:
        with open(session_file, 'r') as f:
            session_data = json.load(f)
        
        debug_log(f"Session chargee avec succes: {session_data.get('session_id', 'ID manquant')}")
        
        # Vérifier si la session n'a pas expiré
        last_access = datetime.fromisoformat(session_data.get('last_access', ''))
        if (datetime.utcnow() - last_access).total_seconds() > SESSION_DURATION:
            debug_log("Session expiree, suppression")
            session_file.unlink()
            return None
        
        return session_data
    except (json.JSONDecodeError, ValueError, KeyError) as e:
        debug_log(f"Erreur lors du chargement de session: {e}")
        # Fichier corrompu, le supprimer
        try:
            session_file.unlink()
            debug_log("Fichier de session corrompu supprime")
        except:
            pass
        return None

def create_new_session():
    """Crée une nouvelle session"""
    session_id = str(uuid.uuid4())
    debug_log(f"Creation d'une nouvelle session: {session_id}")
    
    session_data = {
        'session_id': session_id,
        'created_at': datetime.utcnow().isoformat(),
        'last_access': datetime.utcnow().isoformat(),
        'visited_pages': [],
        'total_visits': 0,
        'user_agent': os.environ.get('HTTP_USER_AGENT', ''),
        'ip_address': os.environ.get('REMOTE_ADDR', ''),
        'pseudo': get_pseudo_from_cookies()
    }
    
    debug_log(f"Donnees de session creees: {session_data}")
    return session_id, session_data

def add_page_visit(session_data, current_page):
    """Ajoute une visite de page à la session"""
    debug_log(f"Ajout de la page: {current_page}")
    
    if current_page not in session_data['visited_pages']:
        session_data['visited_pages'].append(current_page)
        debug_log(f"Nouvelle page ajoutee. Pages visitees: {session_data['visited_pages']}")
    else:
        debug_log(f"Page deja visitee: {current_page}")
    
    session_data['total_visits'] += 1
    session_data['last_access'] = datetime.utcnow().isoformat()
    session_data['pseudo'] = get_pseudo_from_cookies()
    
    debug_log(f"Total des visites: {session_data['total_visits']}")
    return session_data

def save_session(session_id, session_data):
    """Sauvegarde la session"""
    session_file = Path(SESSIONS_FULL_PATH) / f"{session_id}.json"
    debug_log(f"Sauvegarde de session dans: {session_file}")
    
    try:
        # S'assurer que le répertoire existe
        session_file.parent.mkdir(parents=True, exist_ok=True)
        
        with open(session_file, 'w') as f:
            json.dump(session_data, f, indent=2)
        
        debug_log(f"Session sauvegardee avec succes. Taille du fichier: {session_file.stat().st_size} bytes")
        return True
    except Exception as e:
        debug_log(f"ERREUR lors de la sauvegarde: {e}")
        debug_log(f"Repertoire parent: {session_file.parent}")
        debug_log(f"Repertoire parent existe: {session_file.parent.exists()}")
        debug_log(f"Permissions d'ecriture: {os.access(session_file.parent, os.W_OK)}")
        return False

def main():
    debug_log("=== DÉBUT DU SCRIPT SESSION_MANAGER ===")
    debug_log(f"Repertoire de travail: {os.getcwd()}")
    debug_log(f"Repertoire du script: {SCRIPT_DIR}")
    debug_log(f"Chemin complet sessions: {SESSIONS_FULL_PATH}")
    
    # Créer le répertoire sessions
    if not ensure_sessions_directory():
        debug_log("ERREUR: Impossible de creer le repertoire sessions")
        # Continuer quand même pour retourner une erreur JSON
    
    # Déterminer la page actuelle
    current_page = os.environ.get('REQUEST_URI', '/')
    if current_page == '/cgi/session_manager.py':
        current_page = '/'
    
    debug_log(f"Page actuelle: {current_page}")
    
    # Vérifier s'il y a une session existante
    existing_session_id = get_existing_session_id()
    session_data = None
    new_session = False
    
    if existing_session_id:
        session_data = load_session(existing_session_id)
    
    if session_data:
        # Session existante trouvée
        session_id = existing_session_id
        session_data = add_page_visit(session_data, current_page)
        debug_log("Utilisation de session existante")
    else:
        # Créer une nouvelle session
        session_id, session_data = create_new_session()
        session_data = add_page_visit(session_data, current_page)
        new_session = True
        debug_log("Creation d'une nouvelle session")
    
    # Sauvegarder la session
    save_success = save_session(session_id, session_data)
    debug_log(f"Sauvegarde reussie: {save_success}")
    
    if save_success:
        # Préparer la réponse
        response_data = {
            'success': True,
            'session_id': session_id,
            'new_session': new_session,
            'current_page': current_page,
            'visited_pages': session_data['visited_pages'],
            'total_visits': session_data['total_visits'],
            'session_duration': SESSION_DURATION,
            'current_user': session_data['pseudo'],
            'debug_info': {
                'sessions_dir': str(Path(SESSIONS_FULL_PATH).absolute()),
                'session_file': f"{session_id}.json"
            }
        }
        
        debug_log(f"Reponse preparee: {response_data}")
        
        # Envoyer les headers
        sys.stdout.write("Content-Type: application/json\r\n")
        
        if new_session:
            sys.stdout.write(f"Set-Cookie: session_id={session_id}; Path=/; Max-Age={SESSION_DURATION}; HttpOnly; SameSite=Lax\r\n")
            debug_log("Cookie session_id défini")
        
        sys.stdout.write("\r\n")
        
        # Envoyer la réponse JSON
        sys.stdout.write(json.dumps(response_data, indent=2))
    else:
        # Erreur de sauvegarde
        debug_log("ERREUR: Echec de la sauvegarde")
        
        error_response = {
            'success': False,
            'error': 'Unable to save session',
            'debug_info': {
                'sessions_dir': str(Path(SESSIONS_FULL_PATH).absolute()),
                'working_dir': os.getcwd(),
                'script_dir': SCRIPT_DIR
            }
        }
        
        sys.stdout.write("Content-Type: application/json\r\n")
        sys.stdout.write("\r\n")
        sys.stdout.write(json.dumps(error_response, indent=2))
    
    sys.stdout.flush()
    debug_log("=== FIN DU SCRIPT SESSION_MANAGER ===")

if __name__ == "__main__":
    main()