# Sistema de Control d'Accés (ACS)

Aquest projecte implementa un sistema de control d'accés per gestionar permisos d'usuaris en diferents espais i portes. El desenvolupament combina una part pròpia amb codi ja existent.

## 📌 Descripció del Projecte

L'ACS permet:

   - Gestionar usuaris i rols amb permisos diferenciats.

   - Controlar portes electrificades i accés a zones restringides.

   - Registrar logs d'accés per monitoritzar esdeveniments.

   - Proporcionar una interfície gràfica per a l'administració.

   - Implementar un sistema client-servidor per gestionar l'accés remot.

## 🛠️ Tecnologies Utilitzades

   - Java per a la lògica del servidor i gestió d'usuaris.

   - Spring Boot per a la creació de l'API REST.

   - HTML, CSS i JavaScript per a la interfície web del client.

   - Logging amb Log4j per registrar els esdeveniments del sistema.

## 📂 Estructura del Projecte

### 🔹 Backend (Servidor)

   - Gestió d'usuaris i rols (UserService.java, RoleService.java).

   - Control d'accés i permisos (AccessController.java).

   - Registre d'esdeveniments (LogService.java).

   - API REST per comunicar-se amb el client (AccessAPI.java).

   - Gestió d'espais i portes:

       - Area.java: Classe abstracta que defineix una àrea dins del sistema.

       - Partition.java: Contenidor que agrupa diverses àrees (Pattern Composite).

       - Space.java: Defineix un espai individual amb accés mitjançant portes.

       - DirectoryAreas.java: Gestiona totes les àrees i portes del sistema.

       - Door.java: Representa una porta amb identificador, estat i connexions entre àrees.

       - DoorState.java: Classe abstracta per al patró State, gestionant els diferents estats de la porta.

       - Locked.java: Estat de porta bloquejada, no permet l'obertura.

       - Unlocked.java: Estat de porta desbloquejada, permet l'obertura.

   - Gestió d'usuaris i permisos:

       - User.java: Representa un usuari amb credencials i assignació a un grup.

       - Group.java: Defineix els diferents rols d'usuaris i els seus permisos.

       - DirectoryGroup.java: Gestiona tots els grups i assigna usuaris amb els seus horaris.

       - Schedule.java: Controla els horaris d'accés per a cada grup, limitant l'entrada en funció del temps.

   - Servidor i Control del Sistema:

       - Main.java: Punt d'entrada del sistema, inicialitza les àrees, grups i engega el servidor. (No desenvolupat per aquest projecte.)

       - WebServer.java: Implementació del servidor HTTP que gestiona les peticions dels clients. (No desenvolupat per aquest projecte.)

       - States.java: Defineix els diferents estats d'una porta (LOCKED, UNLOCKED).

       - Actions.java: Gestiona les accions disponibles per a cada petició.

       - FakeFita2.java: Implementació de prova per simular el comportament del sistema.

### 🔹 Frontend (Interfície Web)

   - Interfície d'usuari (building.html) amb selecció de persona i acció.

   - Gestió d'interacció amb el servidor (building.js).

   - Visualització de l'estat de les portes (building.js).


