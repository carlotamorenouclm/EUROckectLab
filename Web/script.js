// ==========================================
// 1. TRADUCTION MULTILINGUE ET VOCALE
// ==========================================
const translations = {
    fr: { 
        subtitle: "Mission Control Center", connect: "Connecter USB", disconnect: "Déconnecter", mapTitle: "Suivi de Vol GPS", altTitle: "Altitude (m)", accelTitle: "Accélération (G)", tempTitle: "Température (°C)", pressTitle: "Pression (hPa)", humTitle: "Humidité (%)", terminalTitle: "Données Brutes du Capteur (Serial Log)", csvDownload: "Télécharger CSV",
        speedTitle: "Vitesse Verticale", phaseTitle: "Phase de vol", apogeeTitle: "Apogée (Max Alt)",
        phaseIdle: "Sur le pas de tir", phaseLaunch: "DÉCOLLAGE 🚀", phaseCoast: "Chute libre ascendante", phaseApogee: "APOGÉE ATTEINT 🎯", phaseDescent: "Descente sous parachute 🪂",
        audioEnable: "Activer Audio", audioDisable: "Couper Audio",
        voiceLiftoff: "Décollage détecté. Propulsion nominale.", voiceApogee: "Apogée atteint. Préparation du parachute.", voiceDescent: "Descente en cours.",
        erasmusTitle: "À propos du Projet Erasmus+ BIP", erasmusIntro: "Bienvenue sur la station sol du projet <strong>EU Rocket Lab</strong>, un programme Erasmus+ Blended Intensive Programme (BIP) 2026. Ce projet unique réunit des étudiants et des enseignants issus de plusieurs pays européens autour d'un défi d'ingénierie spatiale concret : concevoir, fabriquer et faire décoller une fusée expérimentale.", erasmusContext: "Au-delà de l'acquisition de compétences techniques en électronique (IoT, LoRa), en programmation C++ (Arduino/ESP32) et en analyses de données barométriques et inertielles (BME280/MPU-9250), ce BIP favorise l'échange interculturel, la collaboration internationale et l'esprit critique. Il prépare la prochaine génération d'ingénieurs à travailler dans un environnement collaboratif européen.", timelineTitle: "Timeline du Projet",
        timeFeb: "Février 2026", timeFebDesc: "Phase Virtuelle - Architecture logicielle et simulation.", timeMar: "Mars 2026", timeMarDesc: "Phase Physique à l'École - Fabrication et tests I2C.", timeLaunch: "Vendredi Lancement !", timeLaunchDesc: "Vol inaugural de la fusée \"Erasmus Star\"."
    },
    en: { 
        subtitle: "Mission Control Center", connect: "Connect USB", disconnect: "Disconnect", mapTitle: "GPS Flight Tracking", altTitle: "Altitude (m)", accelTitle: "Acceleration (G)", tempTitle: "Temperature (°C)", pressTitle: "Pressure (hPa)", humTitle: "Humidity (%)", terminalTitle: "Raw Sensor Data (Serial Log)", csvDownload: "Download CSV",
        speedTitle: "Vertical Speed", phaseTitle: "Flight Phase", apogeeTitle: "Apogee (Max Alt)",
        phaseIdle: "Standby on Pad", phaseLaunch: "LIFTOFF 🚀", phaseCoast: "Coasting ascent", phaseApogee: "APOGEE REACHED 🎯", phaseDescent: "Parachute descent 🪂",
        audioEnable: "Enable Audio", audioDisable: "Mute Audio",
        voiceLiftoff: "Liftoff detected. Propulsion nominal.", voiceApogee: "Apogee reached. Parachute deployment.", voiceDescent: "Descent nominal.",
        erasmusTitle: "About the Erasmus+ BIP Project", erasmusIntro: "Welcome to the ground station of the <strong>EU Rocket Lab</strong> project, an Erasmus+ Blended Intensive Programme (BIP) 2026. This unique project brings together students and teachers from several European countries around a practical aerospace engineering challenge: designing, manufacturing, and launching an experimental rocket.", erasmusContext: "Beyond acquiring technical skills in electronics (IoT, LoRa), C++ programming (Arduino/ESP32), and barometric and inertial data analysis (BME280/MPU-9250), this BIP fosters intercultural exchange, international collaboration, and critical thinking. It prepares the next generation of engineers to work in a collaborative European environment.", timelineTitle: "Project Timeline",
        timeFeb: "February 2026", timeFebDesc: "Virtual Phase - Software architecture and simulation.", timeMar: "March 2026", timeMarDesc: "Physical Phase at School - Manufacturing and I2C tests.", timeLaunch: "Friday Launch!", timeLaunchDesc: "Maiden flight of the \"Erasmus Star\" rocket."
    },
    es: { 
        subtitle: "Mission Control Center", connect: "Conectar USB", disconnect: "Desconectar", mapTitle: "Seguimiento de Vuelo GPS", altTitle: "Altitud (m)", accelTitle: "Aceleración (G)", tempTitle: "Temperatura (°C)", pressTitle: "Presión (hPa)", humTitle: "Humedad (%)", terminalTitle: "Datos reales (Serial Log)", csvDownload: "Descargar CSV",
        speedTitle: "Velocidad Vertical", phaseTitle: "Fase de vuelo", apogeeTitle: "Apogeo (Max Alt)",
        phaseIdle: "En plataforma de lanzamiento", phaseLaunch: "DESPEGUE 🚀", phaseCoast: "Ascenso por inercia", phaseApogee: "APOGEO ALCANZADO 🎯", phaseDescent: "Descenso con paracaídas 🪂",
        audioEnable: "Activar Audio", audioDisable: "Silenciar Audio",
        voiceLiftoff: "Despegue detectado. Propulsión nominal.", voiceApogee: "Apogeo alcanzado.", voiceDescent: "Descenso nominal.",
        erasmusTitle: "Sobre el Proyecto Erasmus+ BIP", erasmusIntro: "Bienvenido a la estación terrestre del proyecto <strong>EU Rocket Lab</strong>, un programa Erasmus+ Blended Intensive Programme (BIP) 2026. Este proyecto único reúne a estudiantes y profesores de varios países europeos en torno a un desafío concreto de ingeniería espacial: diseñar, fabricar y lanzar un cohete experimental.", erasmusContext: "Más allá de adquirir habilidades técnicas en electrónica (IoT, LoRa), programación C++ (Arduino/ESP32) y análisis de datos barométricos e inerciales (BME280/MPU-9250), este BIP fomenta el intercambio intercultural, la colaboración internacional y el espíritu crítico. Prepara a la próxima generación de ingenieros para trabajar en un entorno europeo colaborativo.", timelineTitle: "Línea de Tiempo del Proyecto",
        timeFeb: "Febrero 2026", timeFebDesc: "Fase Virtual - Arquitectura de software y simulación.", timeMar: "Marzo 2026", timeMarDesc: "Fase Física en la Escuela - Fabricación y pruebas I2C.", timeLaunch: "¡Viernes de Lanzamiento!", timeLaunchDesc: "Vuelo inaugural del cohete \"Erasmus Star\"."
    },
    lu: { 
        subtitle: "Mission Control Center", connect: "Antenn verbannen", disconnect: "Trennen", mapTitle: "GPS Verfollegung", altTitle: "Héicht (m)", accelTitle: "Beschleunegung (G)", tempTitle: "Temperatur (°C)", pressTitle: "Drock (hPa)", humTitle: "Fiichtegkeet (%)", terminalTitle: "Réi Daten (Serial Log)", csvDownload: "CSV eroflueden",
        speedTitle: "Vertikal Vitess", phaseTitle: "Fluchphas", apogeeTitle: "Apogeum (Max Alt)",
        phaseIdle: "Startbereet", phaseLaunch: "START 🚀", phaseCoast: "Steigfluch ouni Undriff", phaseApogee: "APOGEUM ERREESCHT 🎯", phaseDescent: "Fallschierm-Descente 🪂",
        audioEnable: "Audio un", audioDisable: "Audio aus",
        voiceLiftoff: "Start detektéiert.", voiceApogee: "Apogeum erreescht.", voiceDescent: "Descente ufänkt.",
        erasmusTitle: "Iwwer den Erasmus+ BIP Projet", erasmusIntro: "Wëllkomm op der Buedemstatioun vum Projet <strong>EU Rocket Lab</strong>, engem Erasmus+ Blended Intensive Programme (BIP) 2026. Dësen eenzegaartege Projet bréngt Studenten an Enseignanten aus verschiddenen europäesche Länner ronderëm en konkreten Weltraum-Ingenieur-Challenge zesummen: concevéieren, fabrizéieren an en experimentell Rakéit start loossen.", erasmusContext: "Niewent dem Acquérir vun technesche Kompetenzen an der Elektronik (IoT, LoRa), der C++ Programméierung (Arduino/ESP32) an der Analyse vun barometresche an inertiale Donnéeën (BME280/MPU-9250), fördert dësen BIP den interkulturellen Austausch, d'international Zesummenaarbecht an de kritesche Geescht. Hien preparéiert déi nächst Generatioun vun Ingenieuren op d'Aarbecht an engem kollaborativen europäeschen Emfeld.", timelineTitle: "Timeline vum Projet",
        timeFeb: "Februar 2026", timeFebDesc: "Virtuell Phas - Software-Architektur an Simulatioun.", timeMar: "Mäerz 2026", timeMarDesc: "Physikalesch Phas an der Schoul - Fabrikatioun an I2C Tester.", timeLaunch: "Freideg Start!", timeLaunchDesc: "Éischte Fluch vun der Rakéit \"Erasmus Star\"."
    }
};

let currentLang = 'fr';
let isConnected = false;

document.getElementById('langSelector').addEventListener('change', (e) => {
    currentLang = e.target.value;
    document.getElementById('langDisplay').innerText = currentLang.toUpperCase();

    document.querySelectorAll('[data-i18n]').forEach(el => {
        const key = el.getAttribute('data-i18n');
        if (key === 'connect') {
            el.innerHTML = isConnected ? translations[currentLang].disconnect : translations[currentLang].connect;
        } else if (key === 'phaseIdle' || key === 'phaseLaunch' || key === 'phaseCoast' || key === 'phaseApogee' || key === 'phaseDescent') {
            // On ne fait rien ici
        } else if (key === 'audioEnable') {
            el.innerHTML = audioEnabled ? translations[currentLang].audioDisable : translations[currentLang].audioEnable;
        } else {
            el.innerHTML = translations[currentLang][key];
        }
    });
    updateFlightPhaseUI();
});

// ==========================================
// 1.5. SYNTHÈSE VOCALE (Le Mac parle !)
// ==========================================
let audioEnabled = false;
let synth = window.speechSynthesis;

document.getElementById('audioBtn').addEventListener('click', () => {
    audioEnabled = !audioEnabled;
    const icon = document.getElementById('audioIcon');
    const btn = document.getElementById('audioBtn');
    const span = btn.querySelector('span');
    
    if(audioEnabled) {
        icon.classList.replace('fa-volume-xmark', 'fa-volume-high');
        icon.classList.replace('text-cyan-400', 'text-green-400');
        btn.classList.replace('border-cyan-500', 'border-green-500');
        btn.classList.replace('shadow-[0_0_15px_rgba(6,182,212,0.4)]', 'shadow-[0_0_15px_rgba(34,197,94,0.4)]');
        btn.classList.replace('hover:shadow-[0_0_25px_rgba(6,182,212,0.8)]', 'hover:shadow-[0_0_25px_rgba(34,197,94,0.8)]');
        span.innerText = "AUDIO ON";
        speakText("Système audio activé");
    } else {
        icon.classList.replace('fa-volume-high', 'fa-volume-xmark');
        icon.classList.replace('text-green-400', 'text-cyan-400');
        btn.classList.replace('border-green-500', 'border-cyan-500');
        btn.classList.replace('shadow-[0_0_15px_rgba(34,197,94,0.4)]', 'shadow-[0_0_15px_rgba(6,182,212,0.4)]');
        btn.classList.replace('hover:shadow-[0_0_25px_rgba(34,197,94,0.8)]', 'hover:shadow-[0_0_25px_rgba(6,182,212,0.8)]');
        span.innerText = "AUDIO OFF";
    }
});

function speakText(keyOrText, isTranslationKey = false) {
    if(!audioEnabled) return;
    synth.cancel(); 
    let textToSpeak = isTranslationKey ? translations[currentLang][keyOrText] : keyOrText;
    let utterance = new SpeechSynthesisUtterance(textToSpeak);
    if(currentLang === 'fr') utterance.lang = 'fr-FR';
    if(currentLang === 'en') utterance.lang = 'en-US';
    if(currentLang === 'es') utterance.lang = 'es-ES';
    if(currentLang === 'lu') utterance.lang = 'de-DE'; 
    synth.speak(utterance);
}


// ==========================================
// 2. INITIALISATION DE LA CARTE GPS (Leaflet)
// ==========================================
const launchLat = 49.110320; // NOUVELLE LATITUDE
const launchLon = 6.072202;  // NOUVELLE LONGITUDE

let map = L.map('map').setView([launchLat, launchLon], 16); 
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', { maxZoom: 19 }).addTo(map);

let rocketIcon = L.divIcon({ 
    html: '<i class="fa-solid fa-rocket text-yellow-erasmus text-2xl drop-shadow-[0_0_15px_rgba(241,196,15,0.9)]"></i>', 
    className: 'dummy', iconSize: [28, 28], iconAnchor: [14, 14] 
});
let rocketMarker = L.marker([launchLat, launchLon], {icon: rocketIcon}).addTo(map);
let flightPath = L.polyline([], {color: '#f1c40f', weight: 4, opacity: 0.8}).addTo(map);


// ==========================================
// 3. INITIALISATION DES GRAPHIQUES (Chart.js)
// ==========================================
Chart.defaults.color = '#94a3b8';
Chart.defaults.font.family = "'Montserrat', sans-serif";

function createChartConfig(color) {
    return {
        type: 'line',
        data: { labels: [], datasets: [{ data: [], borderColor: color, borderWidth: 2, pointRadius: 0, tension: 0.3, fill: false }] },
        options: { 
            responsive: true, maintainAspectRatio: false, animation: false, 
            plugins: { legend: { display: false } }, 
            scales: { x: { display: false }, y: { grid: { color: 'rgba(51, 65, 85, 0.4)' } } } 
        }
    };
}
const altChart = new Chart(document.getElementById('altChart'), createChartConfig('#3498db')); 
const accelChart = new Chart(document.getElementById('accelChart'), createChartConfig('#f1c40f')); 
const tempChart = new Chart(document.getElementById('tempChart'), createChartConfig('#e74c3c')); 
const pressChart = new Chart(document.getElementById('pressChart'), createChartConfig('#2ecc71')); 
const humChart = new Chart(document.getElementById('humChart'), createChartConfig('#8b5cf6')); // NOUVEAU GRAPHIQUE


// ==========================================
// 4. LOGIQUE DE VOL (Apogée, Vitesse, Phase)
// ==========================================
let maxAltitude = 0;
let lastAltitude = 0;
let lastTimeMs = Date.now();
let currentFlightPhase = 'IDLE'; 

function updateFlightDynamics(currentAlt, currentAccel) {
    let now = Date.now();
    let deltaTimeSec = (now - lastTimeMs) / 1000.0;
    
    let speed = 0;
    if (deltaTimeSec > 0) {
        speed = (currentAlt - lastAltitude) / deltaTimeSec;
    }
    document.getElementById('valSpeed').innerText = speed.toFixed(1);

    if (currentAlt > maxAltitude) {
        maxAltitude = currentAlt;
        document.getElementById('valApogee').innerText = maxAltitude.toFixed(1);
    }

    let maxG = parseFloat(document.getElementById('valMaxG').innerText);
    if (currentAccel > maxG) {
        document.getElementById('valMaxG').innerText = currentAccel.toFixed(2);
    }

    let previousPhase = currentFlightPhase;

    if (currentAccel >= 1.5) {
        currentFlightPhase = 'LAUNCH';
        startMissionTimer(); 
    }
    else if (currentFlightPhase === 'LAUNCH') {
        if (currentAccel < 1.5 && speed > 0) currentFlightPhase = 'COAST';
    } 
    else if (currentFlightPhase === 'COAST') {
        if (speed <= 0.5) currentFlightPhase = 'APOGEE';
    } 
    else if (currentFlightPhase === 'APOGEE') {
        if (speed < -2.0) currentFlightPhase = 'DESCENT';
    }

    if (previousPhase !== currentFlightPhase) {
        updateFlightPhaseUI();
        if(currentFlightPhase === 'LAUNCH') speakText('voiceLiftoff', true);
        if(currentFlightPhase === 'APOGEE') speakText('voiceApogee', true);
        if(currentFlightPhase === 'DESCENT') speakText('voiceDescent', true);
    }

    lastAltitude = currentAlt;
    lastTimeMs = now;
}

function updateFlightPhaseUI() {
    const box = document.getElementById('flightPhaseBox');
    const text = document.getElementById('valPhase');
    
    box.className = "glass-panel p-3 rounded-xl flex flex-col items-center justify-center border-b-4 bg-slate-800/80 transition-all duration-500 text-center col-span-2 md:col-span-4";
    
    if (currentFlightPhase === 'IDLE') {
        text.innerText = translations[currentLang].phaseIdle;
        box.classList.add('border-b-slate-500');
    } else if (currentFlightPhase === 'LAUNCH') {
        text.innerText = translations[currentLang].phaseLaunch;
        text.classList.add('text-white');
        box.classList.add('phase-launch', 'animate-launch');
    } else if (currentFlightPhase === 'COAST') {
        text.innerText = translations[currentLang].phaseCoast;
        box.classList.add('phase-coast');
    } else if (currentFlightPhase === 'APOGEE') {
        text.innerText = translations[currentLang].phaseApogee;
        box.classList.add('phase-apogee');
    } else if (currentFlightPhase === 'DESCENT') {
        text.innerText = translations[currentLang].phaseDescent;
        box.classList.add('phase-descent');
    }
}


// ==========================================
// 5. GESTION DU PORT USB & DATA (Web Serial)
// ==========================================
let port;
let reader;
let serialBuffer = "";
const consoleDiv = document.getElementById('serialConsole');

// NOUVEAU CSV : La colonne Humidité a été ajoutée
let flightDataLog = [["Heure", "Temperature_C", "Pression_hPa", "Altitude_m", "Humidite_%", "Acceleration_G", "Latitude", "Longitude", "Vitesse_m_s", "Phase"]];

function logTerminal(msg) {
    const div = document.createElement('div');
    div.innerText = `[${new Date().toLocaleTimeString()}] ${msg}`;
    consoleDiv.appendChild(div);
    consoleDiv.scrollTop = consoleDiv.scrollHeight;
}

document.getElementById('connectBtn').addEventListener('click', async () => {
    if (isConnected) {
        isConnected = false;
        if(reader) reader.cancel();
        document.getElementById('btnText').innerText = translations[currentLang].connect;
        connectBtn.classList.replace('bg-slate-700', 'bg-red-erasmus'); 
        port = null;
        logTerminal("Déconnecté.");
        return;
    }

    if (!("serial" in navigator)) { alert("Utilisez Google Chrome / Edge."); return; }

    try {
        port = await navigator.serial.requestPort();
        await port.open({ baudRate: 115200 });
        isConnected = true;
        
        maxAltitude = 0; document.getElementById('valApogee').innerText = "0.0";
        currentFlightPhase = 'IDLE'; updateFlightPhaseUI();

        document.getElementById('btnText').innerText = translations[currentLang].disconnect;
        connectBtn.classList.replace('bg-red-erasmus', 'bg-slate-700'); 
        document.getElementById('exportBtn').classList.remove('hidden'); 
        logTerminal("CONNECTÉ. En attente de la télémesure (Format: Temp,Press,Alt,Hum,Accel,Lat,Lon)...");
        readLoop();
    } catch (error) { logTerminal("Erreur USB."); }
});

async function readLoop() {
    const textDecoder = new TextDecoderStream();
    const readableStreamClosed = port.readable.pipeTo(textDecoder.writable);
    reader = textDecoder.readable.getReader();

    try {
        while (isConnected) {
            const { value, done } = await reader.read();
            if (done) { reader.releaseLock(); break; }
            if (value) {
                serialBuffer += value;
                let lines = serialBuffer.split('\n');
                serialBuffer = lines.pop(); 
                for (let line of lines) { line = line.trim(); if (line) processData(line); }
            }
        }
    } catch (error) { logTerminal("Connexion interrompue.", "error"); } finally { reader.releaseLock(); }
}

function processData(line) {
    // 1. On ignore le "bruit" visuel du moniteur série pour se concentrer sur la ligne de données
    if (line.includes("RAW: ")) {
        logTerminal("📡 " + line);

        // 2. On découpe la phrase "RAW: ID:47,T:21.28..."
        let dataPart = line.split("RAW: ")[1].trim(); // Récupère ce qu'il y a après "RAW: "
        let pairs = dataPart.split(','); // Sépare chaque bloc avec les virgules

        // 3. On crée un dictionnaire intelligent pour ranger chaque valeur avec son étiquette
        let dict = {};
        pairs.forEach(pair => {
            let parts = pair.split(':'); // Sépare "T" et "21.28"
            if (parts.length === 2) {
                dict[parts[0]] = parseFloat(parts[1]);
            }
        });

        // 4. Si la température et l'altitude existent, on met à jour l'interface
        if (dict["T"] !== undefined && dict["ALT"] !== undefined) {
            const temp = dict["T"];
            const press = dict["P"];
            const hum = dict["H"];
            const alt = dict["ALT"];
            // AT correspond à l'accélération totale (A_total) dans leur code
            const accel = dict["AT"] !== undefined ? dict["AT"] : 1.0; 
            
            // Pas de GPS dans la trame actuelle de la fusée, on utilise le pas de tir
            const lat = launchLat;
            const lon = launchLon;

            const timeStr = new Date().toLocaleTimeString();

            // Mise à jour des valeurs textuelles
            document.getElementById('liveAlt').innerText = alt.toFixed(1);
            document.getElementById('liveAccel').innerText = accel.toFixed(2);
            document.getElementById('liveTemp').innerText = temp.toFixed(1);
            document.getElementById('livePress').innerText = press.toFixed(0);
            document.getElementById('liveHum').innerText = hum.toFixed(1);

            // Mise à jour des graphiques
            updateChart(altChart, timeStr, alt);
            updateChart(accelChart, timeStr, accel);
            updateChart(tempChart, timeStr, temp);
            updateChart(pressChart, timeStr, press);
            updateChart(humChart, timeStr, hum);

            // Fait clignoter le voyant vert "LINK ACTIVE"
            blinkSignal();

            // Envoie à la Machine à États pour deviner la phase de vol
            updateFlightDynamics(alt, accel);

            // Sauvegarde pour le téléchargement CSV
            flightDataLog.push([timeStr, temp, press, alt, hum, accel, lat, lon, document.getElementById('valSpeed').innerText, currentFlightPhase]);
        }
    } 
    // Optionnel : On peut aussi afficher la force du signal dans le terminal
    else if (line.includes("Message received")) {
        logTerminal(line.trim());
    }
}

function updateChart(chart, label, data) {
    chart.data.labels.push(label);
    chart.data.datasets[0].data.push(data);
    if (chart.data.labels.length > 50) { 
        chart.data.labels.shift();
        chart.data.datasets[0].data.shift();
    }
    chart.update();
}

document.getElementById('exportBtn').addEventListener('click', () => {
    let csvContent = "data:text/csv;charset=utf-8," + flightDataLog.map(e => e.join(",")).join("\n");
    const encodedUri = encodeURI(csvContent);
    const link = document.createElement("a");
    link.setAttribute("href", encodedUri);
    link.setAttribute("download", "celestial_horizons_data.csv");
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
    logTerminal("Historique sauvegardé.");
});

// ==========================================
// 🚀 OUTILS PRO : HORLOGE, MET, PLEIN ÉCRAN, VOYANT
// ==========================================

setInterval(() => {
    const now = new Date();
    document.getElementById('liveClock').innerText = "LOCAL " + now.toLocaleTimeString('fr-FR');
}, 1000);

document.getElementById('fullscreenBtn').addEventListener('click', () => {
    if (!document.fullscreenElement) {
        document.documentElement.requestFullscreen();
        document.getElementById('fullscreenIcon').classList.replace('fa-expand', 'fa-compress');
    } else {
        if (document.exitFullscreen) {
            document.exitFullscreen();
            document.getElementById('fullscreenIcon').classList.replace('fa-compress', 'fa-expand');
        }
    }
});

let missionStartTime = null;
let metInterval = null;

function startMissionTimer() {
    if (missionStartTime !== null) return; 
    missionStartTime = Date.now();
    
    metInterval = setInterval(() => {
        let elapsedMs = Date.now() - missionStartTime;
        let totalSeconds = Math.floor(elapsedMs / 1000);
        let minutes = Math.floor(totalSeconds / 60);
        let seconds = totalSeconds % 60;
        
        let minStr = minutes < 10 ? "0" + minutes : minutes;
        let secStr = seconds < 10 ? "0" + seconds : seconds;
        
        document.getElementById('valMET').innerText = `T + ${minStr}:${secStr}`;
        document.getElementById('valMET').classList.replace('text-green-400', 'text-white');
    }, 1000);
}

let signalTimeout;
function blinkSignal() {
    const dot = document.getElementById('signalDot');
    const txt = document.getElementById('signalText');
    
    dot.classList.replace('bg-red-500', 'bg-green-400');
    dot.classList.replace('shadow-[0_0_10px_rgba(239,68,68,0.8)]', 'shadow-[0_0_10px_rgba(74,222,128,0.8)]');
    txt.classList.replace('text-red-400', 'text-green-400');
    txt.innerText = "LINK ACTIVE";
    
    clearTimeout(signalTimeout);
    signalTimeout = setTimeout(() => {
        dot.classList.replace('bg-green-400', 'bg-red-500');
        dot.classList.replace('shadow-[0_0_10px_rgba(74,222,128,0.8)]', 'shadow-[0_0_10px_rgba(239,68,68,0.8)]');
        txt.classList.replace('text-green-400', 'text-red-400');
        txt.innerText = "NO SIGNAL";
    }, 500);
}

// ==========================================
// 🛠️ MODE SIMULATEUR RÉALISTE (Vol Parabolique Complet)
// ==========================================
function startSimulator() {
    let simTemp = 25.0; let simPress = 1013.2; let simAlt = 0.0;
    let simHum = 50.0; 
    let simAccel = 1.0; 
    let simLat = 49.110320; // NOUVELLE LATITUDE ICI AUSSI
    let simLon = 6.072202;  // NOUVELLE LONGITUDE ICI AUSSI
    let simTime = 0;

    console.log("🚀 Lancement du simulateur de vol !");
    logTerminal("🛠️ MODE SIMULATEUR ACTIVÉ.");
    document.getElementById('exportBtn').classList.remove('hidden'); 

    setInterval(() => {
        simTime++;

        if (simTime < 5) {
            simAccel = 1.0 + (Math.random() * 0.1); 
        } 
        else if (simTime >= 5 && simTime < 10) {
            simAccel = 3.5 + (Math.random() * 0.5); 
            simAlt += 45 + (Math.random() * 5); 
            simTemp -= 0.5;
            simHum -= 0.8; // Plus on monte, plus l'air est sec
        } 
        else if (simTime >= 10 && simTime < 16) {
            simAccel = 0.1 + (Math.random() * 0.2); 
            simAlt += 15 - (simTime - 10)*2; 
            simTemp -= 0.2;
            simHum -= 0.2;
        } 
        else if (simTime >= 16 && simAlt > 0) {
            simAccel = 1.0 + (Math.random() * 0.1); 
            simAlt -= 10; 
            simTemp += 0.2; 
            simHum += 0.4; // On retrouve de l'humidité en descendant
        }

        if(simAlt < 0) simAlt = 0;
        if(simHum < 0) simHum = 0;

        simLat += 0.00005; simLon += 0.00005; 

        // NOUVEAU : La fausse trame génère 7 valeurs (avec simHum au milieu)
        let fakeTrame = `${simTemp.toFixed(1)},${simPress.toFixed(1)},${simAlt.toFixed(1)},${simHum.toFixed(1)},${simAccel.toFixed(2)},${simLat.toFixed(6)},${simLon.toFixed(6)}`;
        processData(fakeTrame);

    }, 1000);
}

// 👉 LE SIMULATEUR EST BIEN DÉSACTIVÉ POUR LE JOUR J :
//startSimulator();