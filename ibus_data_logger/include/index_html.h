#ifndef INDEX_HTML_H
#define INDEX_HTML_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>RC LIVE MONITOR</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background: #0f172a; color: #f8fafc; text-align: center; margin: 0; padding: 20px; }
        .container { max-width: 500px; margin: auto; }
        .card { background: #1e293b; padding: 20px; border-radius: 12px; margin: 15px 0; border: 1px solid #334155; box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1); }
        .bar-container { background: #334155; height: 12px; border-radius: 6px; margin-top: 10px; overflow: hidden; }
        .bar-fill { background: linear-gradient(90deg, #38bdf8, #818cf8); height: 100%; width: 50%; transition: width 0.05s ease-out; }
        .label-row { display: flex; justify-content: space-between; font-weight: 600; font-size: 0.9rem; }
        .value { color: #38bdf8; }
        h1 { font-size: 1.5rem; margin-bottom: 30px; letter-spacing: 1px; color: #f1f5f9; }
    </style>
</head>
<body>
    <div class="container">
        <h1>RC TELEMETRY HUB</h1>
        <div id="display">Connecting to ESP32...</div>
    </div>
    <script>
        var gateway = `ws://${window.location.hostname}/ws`;
        var websocket = new WebSocket(gateway);

        websocket.onmessage = function(event) {
            var data = JSON.parse(event.data);
            var html = "";
            var labels = ["ROLL (CH1)", "PITCH (CH2)", "THROTTLE (CH3)", "YAW (CH4)"];

            for(var i=0; i<4; i++) {
                var val = data["c" + i];
                var percent = ((val - 1000) / 10).toFixed(0);
                if(percent < 0) percent = 0; if(percent > 100) percent = 100;

                html += `
                <div class="card">
                    <div class="label-row">
                        <span>${labels[i]}</span>
                        <span class="value">${val}</span>
                    </div>
                    <div class="bar-container">
                        <div class="bar-fill" style="width:${percent}%"></div>
                    </div>
                </div>`;
            }
            document.getElementById('display').innerHTML = html;
        };
    </script>
</body>
</html>
)rawliteral";

#endif