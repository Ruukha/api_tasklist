import os
import csv
from tasks.routes import PATH, COLUMNS, HEADERS

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

def rows_to_json(rows, simple=False):
    if not rows:
        return {}
    if not simple:
        tasks = {
                row[COLUMNS["id"]]: row_to_json(row)
                for row in rows
            }
    else:
        tasks = {
            row[COLUMNS["id"]]: row[COLUMNS["name"]]
            for row in rows
        }
    return tasks
