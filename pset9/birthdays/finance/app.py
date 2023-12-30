import os
import sqlite3
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
import tkinter as tk
from helpers import apology, login_required, lookup, usd

REGISTRANTS = []  # storing registrats in this array


# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        price = request.form.get("price")
        shares_str = request.form.get("shares")
        # if shares is empty
        if shares_str is None:
            return apology("Shares must be provided")
        try:
            shares = int(shares_str)
        # if shares is a negative number
        except ValueError:
            return apology("Shares must be a valid integer")

        if shares <= 0:
            return apology("Shares must be a positive integer")

        stock = lookup(symbol)
        # selecting data we need to put information inn portfolio
        base = db.execute(
            "SELECT u.id AS user_id, u.username, u.hash, u.cash, s.id AS stock_id, s.symbol, s.sharesFROM users u LEFT JOIN stocks s ON u.id = s.user_id GROUP BY u.id;"
        )
        # check if stock exists
        if stock is not None:
            price = stock.get("price")
            info = [
                {
                    "symbol": symbol,
                    "name": symbol,
                    "shares": shares,
                    "price": price,
                    "total": 10.000,
                }
            ]
            # insert into users the information of info
            db.execute("INSERT INTO users = ?", info)
            cash = db.execute("SELECT cash from users")
            total = db.execute("SELECT cash from users")

            balance = [{"cash": cash, "total": total}]

            # Pass data to template
            return render_template("portfolio.html", info=info, balance=balance)
    else:
        return render_template("portfolio.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_str = request.form.get("shares")
        # if shares is empty
        if shares_str is None:
            return apology("Shares must be provided")
        try:
            shares = int(shares_str)
        # if shares is a negative number
        except ValueError:
            return apology("Shares must be a valid integer")

        if shares <= 0:
            return apology("Shares must be a positive integer")

        # Assuming 'user_id' is available through session or some other means
        user_id = session[
            "user_id"
        ]  # Replace 'session["user_id"]' with actual user ID retrieval method
#
        # Select the cash of logged-in user only
        bank_balance_row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        if not bank_balance_row:
            return apology("User not found")  # Handle case where user is not found

        bank_balance = float(bank_balance_row[0]["cash"])

        stock = lookup(symbol)
        # if stock isnt valid return apology
        if stock is None:
            return apology("invalid symbol")
        # if stock is valid continue
        if stock is not None:
            price = float(stock.get("price"))
            purchase = (
                shares * price
            )  # No need to cast to float again as price is already a float

            if bank_balance >= purchase:
                # put data in stocks
                db.execute(
                    "INSERT INTO stocks (symbol, shares, price) VALUES (?, ?, ?)",
                    symbol,
                    shares,
                    price,
                )
                # update users data to current events
                db.execute(
                    "UPDATE users SET cash = cash - ? WHERE id = ?", purchase, user_id
                )
                return render_template("portfolio.html", buy_committed=True)
            else:
                return apology("You don't have enough money for your purchase")

    else:  # GET request handling remains unchanged
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    hist = request.form.get("history")

    return render_template("history.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

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
        row = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )
        # the len of row determines if there was something comted by the user via POST if not we know that there is not a username
        if len(row) != 0:
            return apology("empty")

        user = db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)",
            username,
            hashed_password,
        )

        session["user_id"] = user
        return render_template(
            "portfolio.html", register_committed=register_committed
        )  # Return the rendered template

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


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        price = request.form.get("price")
        stock = lookup(symbol)
        # check if stock exists
        if stock is not None:
            price = stock.get("price")
            return render_template(
                "qouted.html", symbol=symbol, price=price, stock=stock
            )
        # if stock is not valid return apology
        if stock is None:
            return apology("invalid symbol")
        else:
            return apology("Not found")
    # if get is requested go to qoute template
    else:
        return render_template("qoute.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        shares_str = request.form.get("shares")
        # to inform the user if he succesfully sold his stock
        sell_committed = True
        if shares_str is None:
            return apology("Shares must be provided")
        try:
            shares = int(shares_str)
        # if shares is a negative number
        except ValueError:
            return apology("Shares must be a valid integer")

        if shares <= 0:
            return apology("Shares must be a positive integer")

        # Assuming 'user_id' is available through session or some other means
        user_id = session[
            "user_id"
        ]  # Replace 'session["user_id"]' with actual user ID retrieval method

        # Select the cash of logged-in user only
        bank_balance_row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)

        bank_balance = float(bank_balance_row[0]["cash"])

        if not bank_balance_row:
            return apology("User not found")  # Handle case where user is not found

        if stock is not None:
            price = float(stock.get("price"))
            money = (
                shares * price
            )  # No need to cast to float again as price is already a float

            if bank_balance >= money:
                # put data in stocks
                db.execute(
                    "INSERT INTO sold_stocks (symbol, shares, price) VALUES (?, ?, ?)",
                    symbol,
                    shares,
                    price,
                )
                # update users data to current events
                db.execute(
                    "UPDATE users SET cash = cash - ? WHERE id = ?", money, user_id
                )
                return render_template("portfolio.html", sell_committed=True)
            else:
                return apology("You don't have enough money for your purchase")

        if symbol:
            return render_template("portfolio.html", sell_committed=sell_committed)
        else:
            return apology("you don't have so much stocks")
    # if get is requested return sell page
    else:
        return render_template("sell.html")


# bonus work
@app.route("/password_change", methods=["POST"])
@login_required
def password_change():
    # Forget registrant
    id = request.form.get("id")
    if request.method == "POST":
        db.execute("DELETE password FROM users WHERE id = ?", id)
        return redirect("/")


def is_logged_in():
    return "user_id" in session
