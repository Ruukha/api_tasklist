from flask import Blueprint, request
import csv
import os

PATH = "tasks.csv"
DELIMITER = ","

COLUMNS = {
    "id": 0,
    "name": 1,
    "desciption": 2,
    "date": 3,
    "expiry": 4
}
HEADERS = [x for x in COLUMNS.keys()]

tasks_bp = Blueprint("tasks", __name__, url_prefix="/tasks")

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

def check_headers():
    if not os.path.exists(PATH):
        with open(PATH, 'w') as file:
            writer = csv.writer(file)
            writer.writerow(COLUMNS)

@tasks_bp.route('/')
def home():
    return "Home", 200

class Tasklist:
    last_id = 0

    @tasks_bp.route("/get", methods=["GET"])
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
        
        return ret, 200 if ret else 204

    @tasks_bp.route("/add", methods=["POST"])
    def add(self):
        check_headers()
        name = request.json.get("name")
        desc = request.json.get("description")
        date = request.json.get("date")
        expiry = request.json.get("expiry")
            
        try:
            with open(PATH, "a") as file:
                writer = csv.writer(file)
                writer.writerow([self.last_id+1, name, desc, date, expiry])
                self.last_id += 1
                file.close()
        
        except Exception as e:
            return e, 500
        
        return 201


    @tasks_bp.route("/delete", methods=["DELETE"])
    def delete():
        id = request.json.get("id")
        if id is None:
            return "id required", 400
        nrow = find_row(id)
        id = int(id)

        try:
            with open(PATH, "r") as file: #file, aka. mosca
                reader = csv.reader(file)
                rows = list(reader)
                new = rows[:nrow] + rows[nrow+1:]
             
            with open(PATH, "w") as file:
                writer = csv.writer(file)
                writer.writerow(HEADERS)
                writer.writerows(new)


        except Exception as e:
            return e, 500

        return 204

    @tasks_bp.route("/update", methods=["UPDATE"])
    def update():
        id = request.json.get("id")
        name = request.json.get("name")
        desc = request.json.get("description")
        date = request.json.get("date")
        expiry = request.json.get("expiry")
        task = [id, name, desc, date, expiry]

        nrow, line = find_row(id)
        for i in range(len(task)):
            if task[i] is None:
                continue
            line[i] = task[i]

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
