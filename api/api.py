from flask import Flask, request
from flask_jwt_extended import JWTManager, jwt_required, create_access_token, get_jwt_identity
from tasks.routes import tasks_bp, check_headers

app = Flask(__name__)
app.config['JWT_SECRET_KEY'] = "key"
jwt = JWTManager(app)

check_headers()

@app.route('/')
def home():
    return "Home", 200

app.register_blueprint(tasks_bp)

if __name__ == '__main__':
    app.run(debug=False)