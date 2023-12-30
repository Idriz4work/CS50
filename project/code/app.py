from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import tkinter as tk
from project.code.helpers import apology, login_required
from datetime import datetime
import pytz  # Import the pytz module for timezone handling

# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///hustlerss.db")


@app.route("/")
@login_required
def index():
    """Show all tasks"""
    result = db.execute("SELECT date, task, body, timestap, finish FROM tasks")
    g = db.execute("SELECT date, task, body, timestap, finish FROM finished_task")
    finish = db.execute("SELECT date, task, body, timestap, finish FROM memory")

    # Show index page with tasks
    return render_template("portfolio.html", result=result, finish=finish, g=g)


@app.route("/planner", methods=["GET", "POST"])
@login_required
def tasks_planner():
    if request.method == "POST":
        task_header = request.form.get('taskHeader')
        selected_date = request.form.get('selectedDate')
        task_description = request.form.get('taskDescription')
        timestap = datetime.now(pytz.utc)
        finish = False
        result = db.execute("INSERT INTO tasks (task,date,body,timestap) VALUES (?,?,?,?)", task_header, selected_date, task_description,timestap)

        if result:
            return render_template('planned.html', task_header=task_header, selected_date=selected_date, task_description=task_description,timestap=timestap)
        else:
            return render_template('planned.html', error="There was an error saving your task.")

    else:  # GET request handling remains unchanged
        return render_template("planner.html")



@app.route("/finish", methods=["GET", "POST"])
@login_required
def finish():
    if request.method == "GET":
        user_tasks = db.execute("SELECT task FROM tasks")
        return render_template("finish.html", user_tasks=user_tasks)

    else:
        task_id = request.form.get("task_id")
        #re = db.execute("SELECT date, task, body, timestap, finish FROM tasks")
        query = db.execute("SELECT task, body, date, timestap FROM tasks")
        for q in query:
            task, date, body = q["task"],q["date"], q["body"]
            timestamp = datetime.now(pytz.utc)


            # deleting rows that are selected from the user
            db.execute("DELETE FROM tasks WHERE id = ?", task_id)

            db.execute("UPDATE tasks SET finish = ?",True)
            # Updating finish status for the task in finished_task table
            db.execute("INSERT INTO finished_task (task, date, finish, timestap,body) VALUES (?, ?, ?, ?, ?)",task, date, True, timestamp,body)

            db.execute("UPDATE finished_task SET finish = ?",True)


        return redirect("/")



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("fail")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("fail")

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("fail")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    session.clear()
    # when a new user get's registered he should'nt be a able to get information from others
    db.execute("DELETE FROM users")
    db.execute("DELETE FROM tasks")
    db.execute("DELETE FROM finished_task")
    db.execute("DELETE FROM memory")
    if request.method == "POST":
        # declaring variables
        register_committed = True
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # checking if the username is given
        if not username or not password or not confirmation:
            return apology("Please provide both username and password")

        if password != confirmation:
            return apology("Passwords do not match")

        # hash the password for security purposes
        hashed_password = generate_password_hash(password)

        # Insert username, password into "users" table
        row = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        # the len of row determines if there was something comted by the user via POST if not we know that there is not a username
        if len(row) != 0:
            return apology("empty")

        user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",username, hashed_password)

        session["user_id"] = user
        return render_template("portfolio.html", register_committed = register_committed)  # Return the rendered template

    else:
        return render_template("register.html")


@app.route("/logout")
@login_required
def logout():
    """Log user out"""
    if request.method == "GET":
        # Forget any user_id
        session.clear()

        # Redirect user to login form
        return redirect("/")


@app.route("/delete", methods=["GET", "POST"])
@login_required
def delete():
    """delete your tasks from planner"""
    if request.method == "GET":
        user_tasks = db.execute("SELECT task FROM tasks")
        return render_template("delete.html", user_tasks=user_tasks)

    else:
        task_id = request.form.get("task_id")
        query = db.execute("SELECT task, body, date, timestap FROM tasks")
        for q in query:
            task, date, body = q["task"],q["date"], q["body"]
            timestamp = datetime.now(pytz.utc)
            db.execute("DELETE FROM tasks")
            # remember to update otherwise user has still access to deleted data


        return render_template("deleted.html")


@app.route("/delete_finish", methods=["GET", "POST"])
@login_required
def delete_finish():
    if request.method == "GET":
        user_tasks = db.execute("SELECT id, task FROM finished_task")
        return render_template("delete_finish.html", user_tasks=user_tasks)
    else:
        query = db.execute("SELECT task, body, date, timestap FROM finished_task")
        for q in query:
            task, date, body = q["task"],q["date"], q["body"]
            timestamp = datetime.now(pytz.utc)
            db.execute("INSERT INTO memory (task,date,body,timestap) VALUES (?,?,?,?)", task, date, body,timestamp)
            db.execute("DELETE FROM finished_task")
            db.execute("UPDATE memory SET finish = ?",True)


        return render_template("deleted.html")


@app.route("/changepassword", methods=["GET", "POST"])
def change_password():
    # User reached route via GET (as by clicking a link or via redirect)
    if request.method == "GET":
        return render_template("change.html")

    # User reached route via POST (as by submitting a form via POST)
    else:
        current_pw = request.form.get("current_password")
        new_pw = request.form.get("new_password")
        confirm_new_pw = request.form.get("confirm_new_password")

        # Check whether the input box for the current password is empty or not
        if not current_pw:
            return apology("You should input your current password")

        # Check whether the current password is correct or not
        old_password = db.execute("SELECT hash FROM users WHERE id = ?", session["user_id"])
        if len(old_password) != 1 or not check_password_hash(old_password[0]["hash"], current_pw):
            return apology("Invalid username and/or password", 403)

        # New password and Confirm New Password Validation
        if not new_pw:
            return apology("You should input your new password")
        elif not confirm_new_pw:
            return apology("You should input your password in 'Confirmation New Password'")
        elif new_pw != confirm_new_pw:
            return apology("Password does not match")

        # Update the new password for that user in the database
        hashed_new_pw = generate_password_hash(new_pw)
        db.execute("UPDATE users SET hash = ? WHERE id = ?", hashed_new_pw, session["user_id"])

        # Redirect the user to the login form
        return redirect("/logout")

@app.route("/delete_memory", methods=["GET", "POST"])
@login_required
def delete_memory():
    """delete your tasks from planner"""
    if request.method == "GET":
        memory = db.execute("SELECT task FROM memory")
        return render_template("deletememory.html", memory=memory)

    else:
        query = db.execute("SELECT task, body, date, timestap FROM memory")
        for q in query:
            task, date, body = q["task"],q["date"], q["body"]
            timestamp = datetime.now(pytz.utc)
            db.execute("DELETE FROM memory")
            # remember to update otherwise user has still access to deleted data
            db.execute("UPDATE memory SET task = ?, date = ?, finish = ?, timestap = ?, body = ? WHERE task = ? AND date = ? AND finish = ? AND timestap = ? AND body = ?",
                   None, None, None, None, None, task, date, True, timestamp, body)
        return render_template("deleted.html")
