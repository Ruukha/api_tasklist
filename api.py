from flask import Flask, request
from flask_jwt_extended import JWTManager, jwt_required, create_access_token, get_jwt_identity
import csv

app = Flask(__name__)
app.config['JWT_SECRET_KEY'] = "key"
jwt = JWTManager(app)

PATH = "tasks.csv"
DELIMITER = ","

COLUMNS = {
    "id": 0,
    "name": 1,
    "desciption": 2,
    "date": 3,
    "expiry": 4
}

def find_row(id, pos=COLUMNS["id"], path=PATH):
    """
    Returns the index and row in which the first appeareance of id is found in column pos for the file path
    Returns -1 and empty list if not found
    
    :param id: What you want to find
    :param pos: In which column you want to make the search (defaults to 0)
    :param path: Location of the file you want to search (defaults to PATH)
    """
    with open(path, "r") as file:
        reader = csv.reader(file)
        nrow = 0
        for row in reader:
            if row[pos] == id:
                file.close()
                return nrow, row
            nrow += 1

        file.close()

    return -1, []

@app.route('/')
def home():
    return "Home", 200

class Tasklist:
    last_id = 0

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
                    ret += row[COLUMNS["name"]] + "<br>"
                    line_count += 1
                
                file.close()

        except Exception as e:
            return e, 500
            
        return ret, 200

    @app.route("/add", methods=["POST"])
    def add(self):
        name = request.json.get("name")
        desc = request.json.get("description")
        date = request.json.get("date")
        expiry = request.json.get("expiry")
            
        try:
            with open(PATH, "a") as file:
                writer = csv.writer(PATH)
                writer.writerow([self.last_id+1, name, desc, date, expiry])
                self.last_id += 1
                file.close()
        
        except Exception as e:
            return e, 500
        
        return 200


    @app.route("/delete", methods=["DELETE"])
    def delete():
        id = request.json.get("id")

        try:
            with open(PATH, '+') as file: #file, aka. mosca
                reader = csv.reader(file)
                writer = csv.writer(file)

                rows = list(reader)
                new = rows[:id] + rows[id+1:]

                writer.writerows(new)
                file.close()


        except Exception as e:
            return e, 500

        return 204

    @app.route("/update", methods=["UPDATE"])
    def update():
        id = request.json.get("id")
        name = request.json.get("name")
        desc = request.json.get("description")
        date = request.json.get("date")
        expiry = request.json.get("expiry")
        task = [id, name, desc, date, expiry]

        nrow, line = find_row(id)
        for i in task:
            if i is None:
                continue
            line[line.index(i)] = task[i]

        try:
            with open(PATH, '+') as file:
                reader = csv.reader(file)
                rows = list(reader)
                new = rows[:nrow] + line + rows[nrow+1:]

                writer = csv.writer(file)
                writer.writerows(new)

                file.close()

        except Exception as e:
            return e, 500
        
        return 205

if __name__ == '__main__':
    app.run(debug=False)