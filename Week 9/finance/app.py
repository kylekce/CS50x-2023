import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Show user's portfolio
    rows = db.execute(
        "SELECT * FROM portfolio WHERE user_id = ?", session["user_id"])
    # Show user's cash
    cash = db.execute("SELECT cash FROM users WHERE id = ?",
                      session["user_id"])[0]["cash"]
    # Calculate total value of portfolio
    total = db.execute(
        "SELECT SUM(shares * price) FROM portfolio WHERE user_id = ?", session["user_id"])[0]["SUM(shares * price)"]
    if total == None:
        total = 0
    return render_template("index.html", rows=rows, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        user_cash = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"])
        # Ensure symbol is valid
        if quote == None:
            return apology("invalid symbol", 400)
        # Ensure number of shares is numeric
        elif not request.form.get("shares").isdigit():
            return apology("invalid number of shares", 400)
        # Ensure number of shares is more than zero
        elif int(request.form.get("shares")) <= 0:
            return apology("invalid number of shares", 400)
        # Ensure number of shares is valid
        elif quote["price"] > user_cash[0]["cash"]:
            return apology("cannot afford the number of shares", 400)
        else:
            # Update user's history
            db.execute("INSERT INTO history (user_id, symbol, name, shares, price) VALUES(?, ?, ?, +?, -?)",
                       session["user_id"], quote["symbol"], quote["name"], request.form.get("shares"), quote["price"])
            # Update user's portfolio
            # Check if user already owns the stock
            rows = db.execute(
                "SELECT * FROM portfolio WHERE user_id = ? AND symbol = ?", session["user_id"], quote["symbol"])
            if len(rows) == 1:
                db.execute("UPDATE portfolio SET shares = shares + ? WHERE user_id = ? AND symbol = ?",
                           request.form.get("shares"), session["user_id"], quote["symbol"])
            else:
                db.execute("INSERT INTO portfolio (user_id, symbol, name, shares, price) VALUES(?, ?, ?, ?, ?)",
                           session["user_id"], quote["symbol"], quote["name"], request.form.get("shares"), quote["price"])
            # Reduce user's cash
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?",
                       quote["price"] * int(request.form.get("shares")), session["user_id"])

            # Redirect user to index
            return redirect("/")
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Show user's history
    rows = db.execute("SELECT * FROM history WHERE user_id = ?",
                      session["user_id"])
    return render_template("history.html", rows=rows)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if quote == None:
            return apology("invalid symbol", 400)
        # Show quote
        else:
            return render_template("quoted.html", name=quote["name"], price=quote["price"], symbol=quote["symbol"])
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    if request.method == "POST":
        # Ensure fields were properly submitted
        if not username or not password or not confirmation:
            return apology("empty field", 400)
        # Ensure password and confirmation match
        elif password != confirmation:
            return apology("passwords do not match", 400)
        # Ensure username is not already taken
        elif db.execute("SELECT * FROM users WHERE username = ?", username):
            return apology("username already taken", 400)
        # Add user to database
        else:
            hash = generate_password_hash(password)
            db.execute(
                "INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
            return redirect("/")
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    rows = db.execute("SELECT symbol FROM portfolio WHERE user_id = ?",
                      session["user_id"])
    if request.method == "POST":
        # Ensure symbol is valid
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("must provide a symbol", 400)
        # Ensure number of shares is numeric
        elif not request.form.get("shares").isdigit():
            return apology("invalid number of shares", 400)
        # Ensure number of shares is more than zero
        elif int(request.form.get("shares")) <= 0:
            return apology("invalid number of shares", 400)
        # Ensure number of shares is valid
        elif int(request.form.get("shares")) > db.execute("SELECT shares FROM portfolio WHERE user_id = ? AND symbol = ?",
                                                          session["user_id"], request.form.get("symbol"))[0]["shares"]:
            return apology("invalid number of shares", 400)
        else:
            # Update user's history
            db.execute("INSERT INTO history (user_id, symbol, name, shares, price) VALUES(?, ?, ?, -?, +?)",
                       session["user_id"], quote["symbol"], quote["name"], request.form.get("shares"), quote["price"])

            # Update user's portfolio
            rows = db.execute(
                "SELECT * FROM portfolio WHERE user_id = ? AND symbol = ?", session["user_id"], quote["symbol"])
            if len(rows) == 1:
                db.execute("UPDATE portfolio SET shares = shares - ? WHERE user_id = ? AND symbol = ?",
                           request.form.get("shares"), session["user_id"], quote["symbol"])
            # If the stock have zero shares, remove it from the portfolio
            db.execute("DELETE FROM portfolio WHERE shares = 0 AND user_id = ? AND symbol = ?",
                       session["user_id"], quote["symbol"])

            # Increase user's cash
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                       quote["price"] * int(request.form.get("shares")), session["user_id"])

            # Redirect user to index
            return redirect("/")
    return render_template("sell.html", rows=rows)


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    """Add cash to user's account"""
    cash = db.execute("SELECT cash FROM users WHERE id = ?",
                      session["user_id"])[0]["cash"]
    if request.method == "POST":
        # Ensure amount is numeric
        if not request.form.get("amount").isdigit():
            return apology("invalid amount", 400)
        # Ensure amount is more than zero
        elif int(request.form.get("amount")) <= 0:
            return apology("invalid amount", 400)
        # Update user's cash
        else:
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                       request.form.get("amount"), session["user_id"])
            return redirect("/")
    return render_template("add.html", cash=cash)
