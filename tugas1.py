from flask import Flask, request, jsonify

app = Flask(_name_)

@app.route('/', methods=['POST'])
def receive_data():
    data = request.get_json()
    mq135 = data.get('mq135')
    
    # Cetak data ke konsol untuk verifikasi
    print(f"Received MQ135 value: {mq135}")
    
    # Kirim response
    return jsonify({"status": "success", "mq135": mq135}), 200

if _name_ == '_main_':
    app.run(host='0.0.0.0', port=5000)