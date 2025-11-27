The API is the middleman between the database and the end user, so only from here can tasks be created, added, etc.
So far, the database is only a csv file with information about each task (each row representing one task).
This could be made into a proper database if needed, and it would be ideal for the future with users and more stuff.

The API so far only has the task register part, but I made it so that more functionality can be easily added.
The api.py only starts the API, but the functionality is in other files, such as tasks/routes.py. All functionality
will come in routes.py folder in the subfolder titled with the function it fulfills.
These are the endpoints of the API:
    1. GET tasks/get: returns the names of the tasks
    2. GET tasks/get_id: returns the id of a task by its name
    3. POST tasks/add: adds a task to the list. You must give the name, description, date and expiry date of the tasks
    4. DELETE tasks/delete: deletes a task by id or name (prioritises id if both are passed)
    5. PATCH tasks/update: updates the info of a task if given. Will only change the info passed, the rest will stay the same.

    POST, DELETE or PATCH calls all require the id or name of a task. The update endpoint will only change the name of a task if its id is passed.