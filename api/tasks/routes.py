from flask import Blueprint, request
import csv
import os

PATH = os.path.join(os.path.dirname(__file__), "tasks.csv")
DELIMITER = ","

HEADERS = ["id", "name", "description", "date", "expiry"]
COLUMNS = {HEADERS[x]: x for x in range(len(HEADERS))}

tasks_bp = Blueprint("tasks", __name__, url_prefix="/tasks")

def get_last_id():
    if not os.path.exists(PATH):
        return 0
    with open(PATH, "r") as file:
        reader = csv.reader(file)
        next(reader, None)
        rows = list(reader)
    if not rows:
        return 0
    return int(rows[-1][COLUMNS["id"]])

last_id = get_last_id()

def find_row(id, pos=COLUMNS["id"], path=PATH):
    """
    Returns the index and row in which the first appeareance of id is found in column pos for the file path
    Returns -1 and empty list if not found, or -1 and a list with the error inside
    
    :param id: What you want to find
    :param pos: In which column you want to make the search (defaults to 0)
    :param path: Location of the file you want to search (defaults to PATH)
    """
    try:
        with open(path, "r") as file:
            reader = csv.reader(file)
            next(reader, None)
            nrow = 1
            for row in reader:
                if row[pos] == id:
                    return nrow, row
                nrow += 1

    except Exception as e:
        return -1, [e]

    return -1, []

def find(id=None, name=None):
    """
    Returns the index and row in which either the row id is or the first appeareance of name
    Returns -1 if not found
    Will prioritise id search over name
    
    :param id: The id of the task (unique)
    :param name: The name of the task (non-unique)
    """
    check_headers()
    if id is None and name is None:
        return -1, []
    elif id is not None:
        nrow, row = find_row(id)
    else:
        nrow, row = find_row(name, COLUMNS["name"])
    
    return nrow, row

def check_headers():
    if not os.path.exists(PATH):
        with open(PATH, 'w') as file:
            writer = csv.writer(file)
            writer.writerow(HEADERS)

def row_to_json(row):
    if not row:
        return {}
    task = {i: row[COLUMNS[i]] for i in HEADERS}
    return task

def rows_to_json(rows):
    if not rows:
        return {}
    tasks = {
            row[COLUMNS["id"]]: row_to_json(row)
            for row in rows
        }
    return tasks

@tasks_bp.route("/", methods=["GET"])
def get():
    name = request.args.get("name")
    if name is not None:
        return search(name, ["name"])

    try:
        with open(PATH, "r") as file:
            reader = csv.reader(file)
            next(reader, None)
            rows = list(reader)
            
    except Exception as e:
        return {"error": str(e)}, 500
    
    if rows != []:
        return rows_to_json(rows), 200
    return "", 204

@tasks_bp.route("/<id>", methods=["GET"])
def get_by_id(id):
    nrow, row = find(id)
    if nrow == -1:
        if row == []:
            return "", 404
        return "", 500
    
    return row_to_json(row), 200

@tasks_bp.route("/search", methods=["GET"])
def search(search = None, headers = None):
    if headers is None:
        headers = [request.args.get("search_by")]
        if headers[0] is None:
            headers = [x for x in HEADERS]
    if search is None:
        search = request.args.get("search")
        if search is None:
            return "search must be a valid string", 400

    try:
        rows = []
        search = search.lower()
        with open(PATH, "r") as file:
            reader = csv.reader(file)
            next(reader, None)
            for row in reader:
                for i in headers:
                    if search.lower() in row[COLUMNS[i]]:
                        rows.append(row)

    except Exception as e:
        return {"error": str(e)}, 500
    
    if rows != []:
        return rows_to_json(rows), 200
    return "", 404

@tasks_bp.route("/", methods=["POST"])
def add():
    global last_id
    check_headers()
    name = request.json.get("name")
    desc = request.json.get("description")
    date = request.json.get("date")
    expiry = request.json.get("expiry")
    
    if name is None or \
        desc is None or \
        date is None or \
        expiry is None:
        return "You need to pass the name, description, date and expiry date of the task.", 400
        
    try:
        with open(PATH, "a") as file:
            writer = csv.writer(file)
            writer.writerow([last_id+1, name, desc, date, expiry])
            last_id += 1
    
    except Exception as e:
        return {"error": str(e)}, 500
    
    return last_id, 201


@tasks_bp.route("/<id>", methods=["DELETE"])
def delete(id):
    nrow, _ = find(id)
    if nrow == -1:
        return "", 404

    try:
        with open(PATH, "r") as file: #file, aka. mosca
            reader = csv.reader(file)
            rows = list(reader)
            new = rows[:nrow] + rows[nrow+1:]
            
        with open(PATH, "w") as file:
            writer = csv.writer(file)
            writer.writerows(new)
        check_headers()

    except Exception as e:
        return {"error": str(e)}, 500

    return "", 204

@tasks_bp.route("/<id>", methods=["PATCH"])
def patch(id):
    name = request.json.get("name")
    desc = request.json.get("description")
    date = request.json.get("date")
    expiry = request.json.get("expiry")
    task = [id, name, desc, date, expiry]

    nrow, line = find(id, name)
    if nrow == -1:
        return "", 404

    for i in range(len(task)):
        if task[i] is None:
            continue
        line[i] = task[i]

    try:
        with open(PATH, "r") as file:
            reader = csv.reader(file)
            rows = list(reader)
            new = rows[:nrow] + [line] + rows[nrow+1:]

        with open(PATH, "w") as file:
            writer = csv.writer(file)
            writer.writerows(new)

    except Exception as e:
        return {"error": str(e)}, 500
    
    return "", 204
