#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "Galaxy M31A7A6";
const char* password = "idkbruhh";

ESP8266WebServer server(80);

const char mainPage[] PROGMEM = R"MAIN(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sakhi - Smart Assistance</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { 
            font-family: 'Poppins', 'Segoe UI', sans-serif;
            background: linear-gradient(135deg, #0f2027 0%, #203a43 50%, #2c5364 100%);
            min-height: 100vh;
            color: #fff;
            overflow-x: hidden;
        }
        .face-screen {
            display: flex;
            align-items: center;
            justify-content: center;
            min-height: 100vh;
            width: 100vw;
            position: fixed;
            top: 0;
            left: 0;
            background: linear-gradient(135deg, #FFE5F1 0%, #FFD4E5 50%, #FFC4DD 100%);
            animation: fadeIn 0.6s ease;
            cursor: pointer;
            overflow: hidden;
            padding: 0;
            margin: 0;
        }
        .robot-face {
            width: 100vw;
            height: 100vh;
            position: relative;
            display: flex;
            align-items: center;
            justify-content: center;
            transition: all 0.3s ease;
        }
        .robot-face:hover .face-content {
            transform: scale(1.01);
        }
        @keyframes float {
            0%, 100% { transform: translateY(0px); }
            50% { transform: translateY(-15px); }
        }
        .face-content {
            position: relative;
            width: 100%;
            height: 100%;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            transition: all 0.3s ease;
        }
        .eyes-container {
            display: flex;
            gap: 180px;
            margin-bottom: 120px;
            animation: float 3s ease-in-out infinite;
        }
        .eye {
            width: 200px;
            height: 200px;
            background: white;
            border-radius: 50%;
            position: relative;
            box-shadow: 0 15px 40px rgba(255, 105, 180, 0.3);
            display: flex;
            align-items: center;
            justify-content: center;
            border: 8px solid #FF69B4;
        }
        .pupil {
            width: 80px;
            height: 80px;
            background: linear-gradient(135deg, #FF1493, #FF69B4);
            border-radius: 50%;
            position: relative;
            animation: blink 4s ease-in-out infinite;
            box-shadow: 0 6px 15px rgba(255, 20, 147, 0.4);
        }
        .pupil::after {
            content: '';
            width: 35px;
            height: 35px;
            background: white;
            border-radius: 50%;
            position: absolute;
            top: 15px;
            left: 15px;
            animation: sparkle 2s ease-in-out infinite;
        }
        @keyframes sparkle {
            0%, 100% { opacity: 1; transform: scale(1); }
            50% { opacity: 0.7; transform: scale(0.9); }
        }
        @keyframes blink {
            0%, 90%, 100% { 
                transform: scaleY(1);
                opacity: 1;
            }
            93%, 97% { 
                transform: scaleY(0.1);
                opacity: 0.5;
            }
        }
        .mouth {
            width: 200px;
            height: 100px;
            border: 10px solid #FF69B4;
            border-top: none;
            border-radius: 0 0 200px 200px;
            position: relative;
            background: linear-gradient(to bottom, rgba(255, 192, 203, 0.3) 0%, rgba(255, 182, 193, 0.5) 100%);
            box-shadow: inset 0 -10px 20px rgba(255, 105, 180, 0.2);
        }
        .cheeks {
            position: absolute;
            width: 80px;
            height: 80px;
            background: radial-gradient(circle, rgba(255, 182, 193, 0.8), transparent);
            border-radius: 50%;
            top: 50%;
            transform: translateY(-50%);
            animation: blush 3s ease-in-out infinite;
        }
        .cheek-left {
            left: 15%;
        }
        .cheek-right {
            right: 15%;
        }
        @keyframes blush {
            0%, 100% { opacity: 0.6; }
            50% { opacity: 0.9; }
        }
        @keyframes pulse {
            0%, 100% { opacity: 0.9; }
            50% { opacity: 1; }
        }
        @keyframes fadeIn {
            from { opacity: 0; transform: scale(0.9); }
            to { opacity: 1; transform: scale(1); }
        }
        .container { 
            max-width: 1200px; 
            margin: 0 auto; 
            display: flex; 
            flex-direction: column; 
            align-items: center;
            width: 100%;
            padding: 30px 20px;
        }
        .header { 
            text-align: center; 
            margin-bottom: 80px; 
            animation: fadeInDown 0.8s ease;
            width: 100%;
        }
        .logo { 
            font-size: 4em; 
            margin-bottom: 15px; 
            display: inline-block; 
            animation: float 3s ease-in-out infinite; 
        }
        @keyframes fadeInDown { 
            from { opacity: 0; transform: translateY(-30px); } 
            to { opacity: 1; transform: translateY(0); } 
        }
        @keyframes fadeInUp { 
            from { opacity: 0; transform: translateY(30px); } 
            to { opacity: 1; transform: translateY(0); } 
        }
        h1 {
            font-size: 4.5em;
            font-weight: 900;
            background: linear-gradient(135deg, #00d4ff, #0099ff, #00d4ff);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            background-clip: text;
            margin-bottom: 20px;
            letter-spacing: -2px;
            text-shadow: 0 10px 30px rgba(0, 212, 255, 0.2);
        }
        .tagline { 
            font-size: 1.3em; 
            color: rgba(255, 255, 255, 0.9);
            font-weight: 500;
            background: linear-gradient(135deg, #ffb347, #ff6b6b);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            background-clip: text;
            letter-spacing: 1px;
        }
        .button-grid { 
            display: grid; 
            grid-template-columns: repeat(auto-fit, minmax(220px, 1fr)); 
            gap: 25px; 
            margin-bottom: 60px; 
            animation: fadeInUp 0.8s ease 0.2s both;
            width: 100%;
        }
        .btn {
            padding: 40px 25px;
            border: none;
            border-radius: 25px;
            font-size: 16px;
            font-weight: 700;
            cursor: pointer;
            transition: all 0.4s cubic-bezier(0.23, 1, 0.320, 1);
            position: relative;
            overflow: hidden;
            backdrop-filter: blur(15px);
            border: 2px solid rgba(255, 255, 255, 0.3);
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            gap: 15px;
            color: white;
            box-shadow: 0 8px 32px rgba(0, 212, 255, 0.1);
            min-height: 200px;
        }
        .btn .emoji { 
            font-size: 3em; 
            filter: drop-shadow(0 4px 8px rgba(0, 0, 0, 0.2)); 
        }
        .btn .text { 
            font-size: 1em; 
            letter-spacing: 0.5px; 
        }
        .btn:nth-child(1) { background: linear-gradient(135deg, rgba(255, 107, 107, 0.3), rgba(255, 107, 107, 0.1)); border-color: rgba(255, 107, 107, 0.4); }
        .btn:nth-child(2) { background: linear-gradient(135deg, rgba(106, 17, 203, 0.3), rgba(106, 17, 203, 0.1)); border-color: rgba(106, 17, 203, 0.4); }
        .btn:nth-child(3) { background: linear-gradient(135deg, rgba(255, 154, 0, 0.3), rgba(255, 154, 0, 0.1)); border-color: rgba(255, 154, 0, 0.4); }
        .btn:nth-child(4) { background: linear-gradient(135deg, rgba(0, 200, 255, 0.3), rgba(0, 200, 255, 0.1)); border-color: rgba(0, 200, 255, 0.4); }
        .btn:nth-child(5) { background: linear-gradient(135deg, rgba(76, 175, 80, 0.3), rgba(76, 175, 80, 0.1)); border-color: rgba(76, 175, 80, 0.4); }
        .btn:nth-child(6) { background: linear-gradient(135deg, rgba(255, 193, 7, 0.3), rgba(255, 193, 7, 0.1)); border-color: rgba(255, 193, 7, 0.4); }
        .btn:nth-child(7) { background: linear-gradient(135deg, rgba(63, 81, 181, 0.3), rgba(63, 81, 181, 0.1)); border-color: rgba(63, 81, 181, 0.4); }
        .btn:nth-child(8) { background: linear-gradient(135deg, rgba(233, 30, 99, 0.3), rgba(233, 30, 99, 0.1)); border-color: rgba(233, 30, 99, 0.4); }
        .btn::after { 
            content: ''; 
            position: absolute; 
            top: 50%; 
            left: 50%; 
            width: 0; 
            height: 0; 
            border-radius: 50%; 
            background: rgba(255, 255, 255, 0.1); 
            transform: translate(-50%, -50%); 
            transition: width 0.6s, height 0.6s; 
        }
        .btn:hover::after { 
            width: 300px; 
            height: 300px; 
        }
        .btn:hover { 
            transform: translateY(-15px) scale(1.05); 
            box-shadow: 0 30px 60px rgba(0, 212, 255, 0.3), 0 0 30px rgba(0, 212, 255, 0.2), inset 0 0 20px rgba(255, 255, 255, 0.1); 
            border-color: rgba(255, 255, 255, 0.8); 
        }
        .dashboard-screen {
            display: none;
            width: 100%;
        }
        .video-section { 
            text-align: center; 
            margin-top: 60px; 
            animation: fadeInUp 0.8s ease 0.4s both;
            width: 100%;
        }
        .video-btn { 
            background: linear-gradient(135deg, #00d4ff 0%, #0099ff 100%); 
            color: white; 
            padding: 18px 50px; 
            border: none; 
            border-radius: 50px; 
            font-size: 1.1em; 
            font-weight: 700; 
            cursor: pointer; 
            transition: all 0.4s ease; 
            box-shadow: 0 15px 40px rgba(0, 212, 255, 0.4); 
            display: inline-block; 
            letter-spacing: 1px; 
            margin: 10px;
        }
        .video-btn:hover { 
            transform: translateY(-8px) scale(1.08); 
            box-shadow: 0 25px 60px rgba(0, 212, 255, 0.6); 
        }
        .exit-section {
            margin-top: 40px;
            text-align: center;
            animation: fadeInUp 0.8s ease 0.6s both;
        }
        .exit-btn {
            background: linear-gradient(135deg, #ff6b6b 0%, #ff4444 100%);
            color: white;
            padding: 16px 50px;
            border: none;
            border-radius: 50px;
            font-size: 1.1em;
            font-weight: 700;
            cursor: pointer;
            transition: all 0.3s ease;
            box-shadow: 0 10px 30px rgba(255, 107, 107, 0.3);
            letter-spacing: 1px;
        }
        .exit-btn:hover {
            transform: translateY(-5px) scale(1.05);
            box-shadow: 0 15px 40px rgba(255, 107, 107, 0.5);
        }
        .modal { 
            display: none; 
            position: fixed; 
            z-index: 1000; 
            left: 0; 
            top: 0; 
            width: 100%; 
            height: 100%; 
            background: rgba(0, 0, 0, 0.7); 
            backdrop-filter: blur(5px); 
            animation: fadeIn 0.3s ease; 
        }
        .modal-content {
            background: linear-gradient(135deg, #1a1a2e 0%, #16213e 100%);
            margin: 5% auto;
            padding: 50px 40px;
            border-radius: 25px;
            width: 90%;
            max-width: 600px;
            color: white;
            box-shadow: 0 25px 60px rgba(0, 0, 0, 0.5);
            animation: slideUp 0.4s cubic-bezier(0.34, 1.56, 0.64, 1);
            border: 1px solid rgba(0, 212, 255, 0.2);
        }
        @keyframes slideUp { 
            from { transform: translateY(100px); opacity: 0; } 
            to { transform: translateY(0); opacity: 1; } 
        }
        .modal-header { 
            font-size: 2.2em; 
            margin-bottom: 25px; 
            border-bottom: 2px solid #00d4ff; 
            padding-bottom: 20px; 
            display: flex; 
            align-items: center; 
            gap: 15px; 
        }
        .modal-header-emoji { font-size: 2em; }
        .modal-body { 
            font-size: 1.05em; 
            line-height: 1.8; 
            margin-bottom: 30px; 
            color: rgba(255, 255, 255, 0.85); 
        }
        .visual { 
            text-align: center; 
            font-size: 5em; 
            margin: 40px 0; 
            animation: pulse 2s ease-in-out infinite; 
        }
        .close-btn { 
            background: linear-gradient(135deg, #00d4ff, #0099ff); 
            color: white; 
            padding: 14px 35px; 
            border: none; 
            border-radius: 25px; 
            cursor: pointer; 
            font-size: 1em; 
            font-weight: 600; 
            transition: all 0.3s ease; 
            margin: 8px; 
            box-shadow: 0 5px 15px rgba(0, 212, 255, 0.2); 
        }
        .close-btn:hover { 
            background: linear-gradient(135deg, #0099ff, #0066cc); 
            transform: translateY(-3px); 
            box-shadow: 0 10px 25px rgba(0, 212, 255, 0.4); 
        }
        .sub-buttons { 
            display: grid; 
            grid-template-columns: 1fr 1fr; 
            gap: 15px; 
            margin-top: 30px; 
        }
        .sub-buttons .close-btn { 
            width: 100%; 
            margin: 0; 
        }
        .full-width-btn { 
            width: 100% !important; 
            margin-top: 20px; 
        }
    </style>
</head>
<body>
    <div class="face-screen" id="faceScreen" onclick="openDashboard()">
        <div class="robot-face">
            <div class="face-content">
                <div class="cheeks cheek-left"></div>
                <div class="cheeks cheek-right"></div>
                <div class="eyes-container">
                    <div class="eye">
                        <div class="pupil"></div>
                    </div>
                    <div class="eye">
                        <div class="pupil"></div>
                    </div>
                </div>
                <div class="mouth"></div>
            </div>
        </div>
    </div>

    <div class="dashboard-screen" id="dashboardScreen">
        <div class="container">
            <div class="header">
                <div class="logo">🤖</div>
                <h1>Sakhi</h1>
                <p class="tagline">Sakhi Layegi Sukhi 💕</p>
            </div>
            <div class="button-grid">
                <button class="btn" onclick="showModal('shakehand')"><span class="emoji">👋</span><span class="text">Shake Hand</span></button>
                <button class="btn" onclick="showModal('alzheimer')"><span class="emoji">🧠</span><span class="text">Alzheimer's</span></button>
                <button class="btn" onclick="showModal('burgler')"><span class="emoji">🚨</span><span class="text">Burgler Alarm</span></button>
                <button class="btn" onclick="showModal('blind')"><span class="emoji">👁️</span><span class="text">Blind Assist</span></button>
                <button class="btn" onclick="showModal('locker')"><span class="emoji">🔐</span><span class="text">Safety Locker</span></button>
                <button class="btn" onclick="showModal('chatbot')"><span class="emoji">💬</span><span class="text">Chatbot</span></button>
                <button class="btn" onclick="showModal('server')"><span class="emoji">🍽️</span><span class="text">Restaurant Waiter</span></button>
                <button class="btn" onclick="showModal('joystick')"><span class="emoji">🕹️</span><span class="text">Joystick Control</span></button>
            </div>
            <div class="video-section">
                <button class="video-btn" onclick="window.open('https://youtu.be/9qRvcFxtc6I?si=_jwGv_cEP9RtRQdo', '_blank')">🎥 Watch Full Video</button>
            </div>
            <div class="exit-section">
                <button class="exit-btn" onclick="exitDashboard()">← EXIT</button>
            </div>
        </div>
    </div>

    <div id="shakehandModal" class="modal">
        <div class="modal-content">
            <div class="modal-header"><span class="modal-header-emoji">👋</span><span>Shake Hand</span></div>
            <div class="visual">🤝</div>
            <div class="modal-body">Gesture-based control through hand shake detection. Perfect for contactless interaction and accessibility.</div>
            <button class="close-btn" onclick="closeModal('shakehandModal')">Close</button>
        </div>
    </div>

    <div id="alzheimerModal" class="modal">
        <div class="modal-content">
            <div class="modal-header"><span class="modal-header-emoji">🧠</span><span>Alzheimer's Assistance</span></div>
            <div class="modal-body">Comprehensive care system with advanced features for daily health and safety.</div>
            <div class="sub-buttons">
                <button class="close-btn" onclick="showSubModal('facerecognition')">👤 Face Recognition</button>
                <button class="close-btn" onclick="showSubModal('tabletwater')">💊 Tablet/Water</button>
            </div>
            <button class="close-btn full-width-btn" onclick="closeModal('alzheimerModal')">Close</button>
        </div>
    </div>

    <div id="facerecognitionSubModal" class="modal">
        <div class="modal-content">
            <div class="modal-header"><span class="modal-header-emoji">👤</span><span>Face Recognition</span></div>
            <div class="visual">🔍👤</div>
            <div class="modal-body">Advanced facial recognition. Identifies family members and caregivers for personalized greetings and security.</div>
            <button class="close-btn" onclick="closeModal('facerecognitionSubModal')">Close</button>
        </div>
    </div>

    <div id="tabletwaterSubModal" class="modal">
        <div class="modal-content">
            <div class="modal-header"><span class="modal-header-emoji">💊</span><span>Tablet/Water Reminder</span></div>
            <div class="modal-body">
                <div style="margin-bottom: 25px;">
                    <label style="display: block; margin-bottom: 10px; font-size: 1.1em; color: #00d4ff;">
                        💊 Tablet Time (24-hour format):
                    </label>
                    <input type="time" id="tabletTimeInput" style="width: 100%; padding: 12px; border-radius: 10px; border: 2px solid #00d4ff; background: rgba(255, 255, 255, 0.1); color: white; font-size: 1.1em;">
                </div>
                <div style="margin-bottom: 25px;">
                    <label style="display: block; margin-bottom: 10px; font-size: 1.1em; color: #00d4ff;">
                        💧 Water Interval (minutes):
                    </label>
                    <input type="number" id="waterIntervalInput" placeholder="e.g., 30" min="1" style="width: 100%; padding: 12px; border-radius: 10px; border: 2px solid #00d4ff; background: rgba(255, 255, 255, 0.1); color: white; font-size: 1.1em;">
                </div>
                <button class="close-btn" style="width: 100%; margin-top: 10px; padding: 16px;" onclick="activateTabletWater()">✓ Activate</button>
                <button class="close-btn" style="width: 100%; background: linear-gradient(135deg, #ff6b6b, #ff4444);" onclick="stopTabletWater()">✕ Stop & Close</button>
            </div>
        </div>
    </div>

    <div id="burglerModal" class="modal">
        <div class="modal-content">
            <div class="modal-header"><span class="modal-header-emoji">🚨</span><span>Burgler Alarm</span></div>
            <div class="visual">🔔</div>
            <div class="modal-body">Motion and intrusion detection. Monitors your space 24/7 and triggers alerts on unauthorized activity.</div>
            <button class="close-btn" onclick="closeModal('burglerModal')">Close</button>
        </div>
    </div>

    <div id="blindModal" class="modal">
        <div class="modal-content">
            <div class="modal-header"><span class="modal-header-emoji">👁️</span><span>Blind Assist</span></div>
            <div class="visual">🦯</div>
            <div class="modal-body">AI-powered navigation and obstacle detection. Real-time audio feedback for safe navigation.</div>
            <button class="close-btn" onclick="closeModal('blindModal')">Close</button>
        </div>
    </div>

    <div id="lockerModal" class="modal">
        <div class="modal-content">
            <div class="modal-header"><span class="modal-header-emoji">🔐</span><span>Safety Locker</span></div>
            <div class="visual">🔒</div>
            <div class="modal-body">Secure storage with smart locking. Biometric and PIN access control for valuables.</div>
            <button class="close-btn" onclick="closeModal('lockerModal')">Close</button>
        </div>
    </div>

    <div id="chatbotModal" class="modal">
        <div class="modal-content">
            <div class="modal-header"><span class="modal-header-emoji">💬</span><span>Chatbot</span></div>
            <div class="visual">🤖</div>
            <div class="modal-body">Conversational AI assistant. Ask questions and control devices through natural language.</div>
            <button class="close-btn" onclick="closeModal('chatbotModal')">Close</button>
        </div>
    </div>

    <div id="serverModal" class="modal">
        <div class="modal-content">
            <div class="modal-header"><span class="modal-header-emoji">🍽️</span><span>Restaurant Waiter</span></div>
            <div class="visual">👨‍🍳</div>
            <div class="modal-body">Intelligent restaurant service robot. Takes orders, serves food, and provides exceptional dining experience with voice interaction and autonomous navigation.</div>
            <button class="close-btn" onclick="closeModal('serverModal')">Close</button>
        </div>
    </div>

    <div id="joystickModal" class="modal">
        <div class="modal-content">
            <div class="modal-header"><span class="modal-header-emoji">🕹️</span><span>Joystick Control</span></div>
            <div class="visual">🎮</div>
            <div class="modal-body">Real-time device control with analog joystick. Smooth, responsive control for robotics.</div>
            <button class="close-btn" onclick="closeModal('joystickModal')">Close</button>
        </div>
    </div>

    <script>
        let tabletWaterInterval = null;
        
        function openDashboard() {
            document.getElementById('faceScreen').style.display = 'none';
            document.getElementById('dashboardScreen').style.display = 'block';
        }
        
        function exitDashboard() {
            document.getElementById('dashboardScreen').style.display = 'none';
            document.getElementById('faceScreen').style.display = 'flex';
        }
        
        function showModal(feature) {
            const modalId = feature + 'Modal';
            document.getElementById(modalId).style.display = 'block';
            fetch('/' + feature);
        }
        
        function showSubModal(feature) {
            const subModalId = feature + 'SubModal';
            document.getElementById(subModalId).style.display = 'block';
            if (feature !== 'tabletwater') {
                fetch('/' + feature);
            }
        }
        
        function closeModal(modalId) {
            document.getElementById(modalId).style.display = 'none';
            if (modalId === 'tabletwaterSubModal') {
                stopTabletWater();
            }
        }
        
        function activateTabletWater() {
            const tabletTime = document.getElementById('tabletTimeInput').value;
            const waterInterval = document.getElementById('waterIntervalInput').value;
            
            if (!tabletTime || !waterInterval) {
                alert('Please enter both tablet time and water interval!');
                return;
            }
            
            fetch('/tabletwater?tablet_time=' + encodeURIComponent(tabletTime) + '&water_interval=' + encodeURIComponent(waterInterval))
                .then(response => response.text())
                .then(data => {
                    alert('Activated! Tablet: ' + tabletTime + ', Water: every ' + waterInterval + ' min');
                    startTabletWaterMonitoring(tabletTime, waterInterval);
                });
        }
        
        function startTabletWaterMonitoring(tabletTime, waterInterval) {
            if (tabletWaterInterval) {
                clearInterval(tabletWaterInterval);
            }
            
            tabletWaterInterval = setInterval(() => {
                fetch('/tabletwater/ping?tablet_time=' + encodeURIComponent(tabletTime) + '&water_interval=' + encodeURIComponent(waterInterval));
            }, 5000);
        }
        
        function stopTabletWater() {
            if (tabletWaterInterval) {
                clearInterval(tabletWaterInterval);
                tabletWaterInterval = null;
                fetch('/tabletwater/stop');
            }
        }
        
        window.onclick = function(event) {
            if (event.target.classList.contains('modal')) {
                event.target.style.display = 'none';
                if (event.target.id === 'tabletwaterSubModal') {
                    stopTabletWater();
                }
            }
        }
    </script>
</body>
</html>
)MAIN";

const char alzheimerPage[] PROGMEM = R"ALZI(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Alzheimer's Controls</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { 
            font-family: 'Poppins', 'Segoe UI', sans-serif;
            background: linear-gradient(135deg, #FFE5F1 0%, #FFD4E5 50%, #FFC4DD 100%);
            min-height: 100vh;
            padding: 30px 20px;
            color: #333;
        }
        .container { max-width: 900px; margin: 0 auto; }
        .header { text-align: center; margin-bottom: 60px; }
        h1 {
            font-size: 2.8em;
            font-weight: 800;
            background: linear-gradient(135deg, #FF69B4, #FF1493);
            -webkit-background-clip: text;
            -webkit-text-fill-color: transparent;
            background-clip: text;
            margin-bottom: 10px;
        }
        .subtitle { color: rgba(255, 20, 147, 0.8); }
        .button-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(220px, 1fr)); gap: 25px; margin-bottom: 40px; }
        .btn {
            padding: 35px 20px;
            border: none;
            border-radius: 20px;
            font-size: 16px;
            font-weight: 600;
            cursor: pointer;
            transition: all 0.4s ease;
            backdrop-filter: blur(10px);
            border: 1px solid rgba(255, 255, 255, 0.2);
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 12px;
            color: white;
        }
        .btn .emoji { font-size: 2.5em; }
        .btn .text { font-size: 0.95em; }
        .btn:nth-child(1) { background: linear-gradient(135deg, rgba(255, 105, 180, 0.3), rgba(255, 105, 180, 0.1)); border-color: rgba(255, 105, 180, 0.4); }
        .btn:nth-child(2) { background: linear-gradient(135deg, rgba(138, 43, 226, 0.3), rgba(138, 43, 226, 0.1)); border-color: rgba(138, 43, 226, 0.4); }
        .btn:hover { transform: translateY(-12px) scale(1.02); box-shadow: 0 20px 40px rgba(255, 105, 180, 0.3); border-color: rgba(255, 105, 180, 0.6); }
        .back-btn { background: linear-gradient(135deg, #FF69B4, #FF1493); color: white; padding: 16px 40px; border: none; border-radius: 50px; cursor: pointer; font-size: 1em; font-weight: 600; transition: all 0.3s ease; width: 100%; box-shadow: 0 10px 30px rgba(255, 105, 180, 0.3); }
        .back-btn:hover { background: linear-gradient(135deg, #FF1493, #C71585); transform: translateY(-5px); box-shadow: 0 15px 40px rgba(255, 105, 180, 0.4); }
        .modal { display: none; position: fixed; z-index: 1000; left: 0; top: 0; width: 100%; height: 100%; background: rgba(0, 0, 0, 0.7); backdrop-filter: blur(5px); }
        .modal-content {
            background: linear-gradient(135deg, #FFE5F1 0%, #FFD4E5 100%);
            margin: 5% auto;
            padding: 50px 40px;
            border-radius: 25px;
            width: 90%;
            max-width: 600px;
            color: #333;
            box-shadow: 0 25px 60px rgba(255, 105, 180, 0.4);
            border: 3px solid #FF69B4;
        }
        .modal-header { font-size: 2.2em; margin-bottom: 25px; border-bottom: 3px solid #FF69B4; padding-bottom: 20px; display: flex; align-items: center; gap: 15px; color: #FF1493; }
        .modal-header-emoji { font-size: 2em; }
        .modal-body { font-size: 1.05em; line-height: 1.8; margin-bottom: 30px; color: rgba(51, 51, 51, 0.9); }
        .visual { text-align: center; font-size: 5em; margin: 40px 0; }
        .close-btn { background: linear-gradient(135deg, #FF69B4, #FF1493); color: white; padding: 14px 35px; border: none; border-radius: 25px; cursor: pointer; font-size: 1em; font-weight: 600; transition: all 0.3s ease; margin: 8px; box-shadow: 0 5px 15px rgba(255, 105, 180, 0.3); }
        .close-btn:hover { background: linear-gradient(135deg, #FF1493, #C71585); transform: translateY(-3px); box-shadow: 0 10px 25px rgba(255, 105, 180, 0.5); }0099ff, #0066cc); transform: translateY(-3px); box-shadow: 0 10px 25px rgba(0, 212, 255, 0.4); }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>🏥 Alzheimer's Assistance</h1>
            <p class="subtitle">Specialized Care Support</p>
        </div>
        <div class="button-grid">
            <button class="btn" onclick="showModal('facerecognition')"><span class="emoji">👤</span><span class="text">Face Recognition</span></button>
            <button class="btn" onclick="showModal('tabletwater')"><span class="emoji">💊</span><span class="text">Tablet/Water</span></button>
        </div>
        <button class="back-btn" onclick="window.location.href='/'">← Back to Dashboard</button>
    </div>

    <div id="facerecognitionModal" class="modal">
        <div class="modal-content">
            <div class="modal-header"><span class="modal-header-emoji">👤</span><span>Face Recognition</span></div>
            <div class="visual">🔍👤</div>
            <div class="modal-body">Advanced facial recognition system. Identifies family and caregivers for personalized greetings and security.</div>
            <button class="close-btn" onclick="closeModal('facerecognitionModal')">Close</button>
        </div>
    </div>

    <div id="tabletwaterModal" class="modal">
        <div class="modal-content">
            <div class="modal-header"><span class="modal-header-emoji">💊</span><span>Tablet/Water Reminder</span></div>
            <div class="visual">💊💧</div>
            <div class="modal-body">Intelligent reminder system for medications and hydration. Audio and visual alerts at scheduled times.</div>
            <button class="close-btn" onclick="closeModal('tabletwaterModal')">Close</button>
        </div>
    </div>

    <script>
        function showModal(feature) {
            const modalId = feature + 'Modal';
            document.getElementById(modalId).style.display = 'block';
            fetch('/' + feature);
        }
        function closeModal(modalId) {
            document.getElementById(modalId).style.display = 'none';
        }
        window.onclick = function(event) {
            if (event.target.classList.contains('modal')) {
                event.target.style.display = 'none';
            }
        }
    </script>
</body>
</html>
)ALZI";

void shakeHandFeature() {
  Serial.println("Shake Hand Feature Activated!");
  server.send(200, "text/plain", "Shake Hand Activated");
}

void alzheimerFeature() {
  Serial.println("Alzheimer's Feature Activated!");
  server.send_P(200, "text/html", alzheimerPage);
}

void burglerAlarmFeature() {
  Serial.println("Burgler Alarm Feature Activated!");
  server.send(200, "text/plain", "Burgler Alarm Activated");
}

void blindAssistFeature() {
  Serial.println("Blind Assist Feature Activated!");
  server.send(200, "text/plain", "Blind Assist Activated");
}

void safetyLockerFeature() {
  Serial.println("Safety Locker Feature Activated!");
  server.send(200, "text/plain", "Safety Locker Activated");
}

void chatbotFeature() {
  Serial.println("Chatbot Feature Activated!");
  server.send(200, "text/plain", "Chatbot Activated");
}

void serverFeature() {
  Serial.println("Server Feature Activated!");
  server.send(200, "text/plain", "Server Activated");
}

void joystickControlFeature() {
  Serial.println("Joystick Control Feature Activated!");
  server.send(200, "text/plain", "Joystick Control Activated");
}

void faceRecognitionFeature() {
  Serial.println("Face Recognition Activated!");
  server.send(200, "text/plain", "Face Recognition Activated");
}

void tabletWaterFeature() {
  if (server.hasArg("tablet_time") && server.hasArg("water_interval")) {
    String tablet_time = server.arg("tablet_time");
    String water_interval = server.arg("water_interval");
    
    Serial.println("=== TABLET/WATER REMINDER ACTIVATED ===");
    Serial.print("Tablet Time: ");
    Serial.println(tablet_time);
    Serial.print("Water Interval: ");
    Serial.print(water_interval);
    Serial.println(" minutes");
    Serial.println("========================================");
    
    server.send(200, "text/plain", "Tablet/Water Reminder Activated");
  } else if (server.uri() == "/tabletwater/ping") {
    String tablet_time = server.arg("tablet_time");
    String water_interval = server.arg("water_interval");
    
    Serial.println("Monitoring: Tablet at " + tablet_time + ", Water every " + water_interval + " min");
    server.send(200, "text/plain", "Monitoring active");
  } else if (server.uri() == "/tabletwater/stop") {
    Serial.println("=== TABLET/WATER REMINDER STOPPED ===");
    server.send(200, "text/plain", "Stopped");
  } else {
    server.send(200, "text/plain", "Tablet/Water Page Opened");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", [](){ 
    server.send_P(200, "text/html", mainPage); 
  });
  
  server.on("/alzheimer", alzheimerFeature);
  server.on("/shakehand", shakeHandFeature);
  server.on("/burgler", burglerAlarmFeature);
  server.on("/blind", blindAssistFeature);
  server.on("/locker", safetyLockerFeature);
  server.on("/chatbot", chatbotFeature);
  server.on("/server", serverFeature);
  server.on("/joystick", joystickControlFeature);
  server.on("/facerecognition", faceRecognitionFeature);
  server.on("/tabletwater", tabletWaterFeature);
  server.on("/tabletwater/ping", tabletWaterFeature);
  server.on("/tabletwater/stop", tabletWaterFeature);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}