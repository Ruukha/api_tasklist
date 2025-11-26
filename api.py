from flask import Flask, request
from flask_jwt_extended import JWTManager, jwt_required, create_access_token, get_jwt_identity
import csv

app = Flask(__name__)
app.config['JWT_SECRET_KEY'] = "key"
jwt = JWTManager(app)

PATH = "tasks.csv"
DELIMITER = ","

@app.route('/')
def home():
    return "Home", 200

class Task:
    @app.route("/get", methods=["GET"])
    def get():
        try:
            ret = ""
            with open(PATH, "r") as file:
                reader = csv.reader(file)
                line_count = 0
                for row in reader:
                    if line_count == 0:
                        line_count += 1
                        continue
                    ret += row[0] + "<br>"
                    line_count += 1
                
                file.close()
            return ret, 200
        except Exception as e:
            return e, 500

    @app.route("/add", methods=["POST"])
    def add():
        name = request.json.get("name")
        desc = request.json.get("description")
        date = request.json.get("date")
        expiry = request.json.get("expiry")
            
        try:
            with open(PATH, "a") as file:
                last_id = ""
                for c in file.readlines()[-1]:
                    if c == DELIMITER:
                        break
                    last_id += c

                last_id = int(last_id)
                writer = csv.writer(PATH)
                writer.writerow([last_id+1, name, desc, date, expiry])
                file.close()
            return 200
        
        except Exception as e:
            return e, 500


    @app.route("/delete", methods=["DELETE"])
    def delete():
        id = request.json.get("id")

        try:
            with open(PATH, '+') as file: #file, aka. mosca
                reader = csv.reader(file)
                writer = csv.writer(file)

                for row in reader:
                    if row[0] == id:
                        pass

        except Exception as e:
            return e, 500


    @app.route("/update", methods=["UPDATE"])
    def update():
        pass

if __name__ == '__main__':
    app.run(debug=False)