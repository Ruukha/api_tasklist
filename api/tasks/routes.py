from flask import Blueprint, request
import csv
import os
from datetime import datetime

PATH = os.path.join(os.path.dirname(__file__), "tasks.csv")
DELIMITER = ","
NEWLINE = ""

HEADERS = ["id", "name", "description", "date", "expiry"]
COLUMNS = {HEADERS[x]: x for x in range(len(HEADERS))}
from tasks.helpers import *
last_id = get_last_id()
last_update = datetime.now()
unix_last_update = last_update.timestamp()

tasks_bp = Blueprint("tasks", __name__, url_prefix="/tasks")

def update():
    global last_update, unix_last_update
    last_update = datetime.now()
    unix_last_update = last_update.timestamp()

@tasks_bp.route("", methods=["GET"])
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
        return rows_to_json(rows, simple=True), 200
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
    
    if name is None:
        return "You need to pass the name of the task.", 400
    if desc is None:
        desc = ""
    if date is None:
        date = datetime.today()
        
    try:
        with open(PATH, "a", newline=NEWLINE) as file:
            writer = csv.writer(file)
            writer.writerow([last_id+1, name, desc, date, expiry])
            last_id += 1
    
    except Exception as e:
        return {"error": str(e)}, 500
    
    update()
    return {"id": last_id}, 201

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
            
        with open(PATH, "w", newline=NEWLINE) as file:
            writer = csv.writer(file)
            writer.writerows(new)
        check_headers()

    except Exception as e:
        return {"error": str(e)}, 500

    update()
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

        with open(PATH, "w", newline=NEWLINE) as file:
            writer = csv.writer(file)
            writer.writerows(new)

    except Exception as e:
        return {"error": str(e)}, 500
    
    update()
    return "", 204

@tasks_bp.route("/last_update", methods=["GET"])
def last_upd():
    global last_update
    return {
        "last_update": str(last_update),
        "unix_last_update": unix_last_update
        }