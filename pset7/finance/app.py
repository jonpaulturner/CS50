import os

#from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
#db = SQL("sqlite:///finance.db")
db=[]

@app.route("/")
@login_required
def index():
    portfolio = db.execute("SELECT * FROM Transactions WHERE user=:user", user = session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id=:user", user = session["user_id"])
    history = db.execute("SELECT * FROM history WHERE id=:user", user = session["user_id"])


    #Get a sum of all the stocks in the portfolio
    portfolioSum = 0
    for i in range(0, len(portfolio)):
        portfolioSum += portfolio[i]['price']

    #Return the page with the needd information for Jinja
    return(render_template("index.html", portfolio = portfolio, portfolioSum = portfolioSum, cash = cash[0]['cash'], history = history))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":

         #Check if the user typed in valid inputs
        if request.form.get("symbol") == "":
            return apology("Please type in a ticker symbol",400)

        #Make sure the quantity is an integer
        #if isinstance(request.form.get("shares"), int) == False:
        #    return apology("Please enter a valid quantity to buy", 400)

        if request.form.get("shares").isdigit() == False:
            return apology ("Please enter a valid quantity to buy", 400)
        #Make sure the quantity is a positive number
        if int(request.form.get("shares")) < 1:
            return apology("Please enter a valud quantity to buy", 400)


        #Look up the value of the quote and calculate the total cost
        quote = lookup(request.form.get("symbol"))

        if quote == None:
            return apology("Please enter a valid stock symbol",400)

        price = float(quote['price']) * int(request.form.get("shares"))
        priceusd = usd(int(price))

        #Retrive the amount of cash the user has:
        cash = db.execute("SELECT cash FROM users WHERE id=:user", user = session["user_id"])

        if price > float(cash[0]["cash"]):
            return apology("Not enough cash to execute order")

        cash[0]['cash'] -= price

        check = db.execute("SELECT * FROM Transactions WHERE user = :user AND symbol = :symbol", user = session["user_id"], symbol = request.form.get("symbol"))

        if check == []:
            result = db.execute("INSERT INTO Transactions (user, shares, symbol, price) VALUES(:user, :shares, :symbol, :price)", user = session["user_id"], shares = int(request.form.get("shares")), symbol = request.form.get("symbol"), price = price)

        else:
            shares = int(check[0]['shares']) + int(request.form.get("shares"))
            price = check[0]['price'] + price
            update = db.execute("UPDATE Transactions SET shares=:shares, price=:price WHERE id=:checkid", checkid = check[0]['id'], shares = shares, price = price)

        cashupdate = db.execute("UPDATE users SET cash=:cash WHERE id=:user", user = session["user_id"], cash = cash[0]['cash'])

        #Add the transaction to the history database
        boughtsold = "bought"
        historyupdate = db.execute("INSERT INTO history (user, symbol, shares, boughtsold, price) VALUES(:user, :symbol, :shares, :boughtsold, :price)", user=session["user_id"], symbol = request.form.get("symbol"), shares = int(request.form.get("shares")), price = float(quote['price']), boughtsold = "Bought")

        return render_template("buycomplete.html", cash = usd(cash[0]['cash']), shares = request.form.get("shares"), symbol = request.form.get("symbol"), priceusd = priceusd)

        # Redirect user to home page
        return redirect("/buycomplete")

    else:
        return(render_template("buy.html"))


@app.route("/history")
@login_required
def history():
    history = db.execute("SELECT * FROM history WHERE user=:user", user = session["user_id"])

    #Return the page with the needd information for Jinja
    return(render_template("history.html", history=history))
#https://ide50-jonpaulturner.legacy.cs50.io:8082/phpliteadmin.php?action=row_view&table=Transactions&PHPSESSID=0b0acfvipcb1efuh35vmj37jk7

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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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
    #Check if the the user typed something into symbol field:
    if request.method == "POST":

        if request.form.get("symbol") == "":

            return apology("Please type in a ticker symbol",400)

        #elif request.form.get("symbol")
        quote = lookup(request.form.get("symbol"))

        if quote == None:
            return apology("Please enter a valid stock symbol",400)
        price = usd(quote["price"])

        return render_template("quoted.html", quote = quote, price = price)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Registers user"""
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif request.form.get("username") == "" or request.form.get("password") == "" or request.form.get("confirmation") == "":
            return apology("Fill in blank fields", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must type password twice", 400)

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match", 400)

        #Still need to has password

        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :password)", username = request.form.get("username"), password = generate_password_hash(request.form.get("password")))
        if not result:
            return apology("User already exists", 400)


        user_id = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        session["user_id"] = user_id

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":

        #Check if the user typed in valid inputs
        if request.form.get("symbol") == "":
            return apology("Please type in a ticker symbol",400)

        #Check if the quantity is valid
        if request.form.get("shares").isdigit() == False:
            return apology ("Please enter a valid quantity to buy", 400)

        #Make sure the quantity is a positive number
        if int(request.form.get("shares")) < 1:
            return apology("Please enter a valud quantity to buy", 400)

        #Look up the value of the quote and calculate the total cost
        quote = lookup(request.form.get("symbol"))

        #Check if the quote is a valid stock
        if quote == None:
            return apology("Please enter a valid stock symbol",400)

        #Calculate the total cost of all the shares based on the current price.
        price = float(quote['price']) * int(request.form.get("shares"))
        priceusd = usd(int(price))

        #Retrive the amount of stock the user has
        check = db.execute("SELECT * FROM Transactions WHERE user = :user AND symbol = :symbol", user = session["user_id"], symbol = request.form.get("symbol"))

        if check == []:
            return apology("You don't have that stock")

        #Check if the user has enough of the stock specified to sell
        if int(check[0]['shares']) < int(request.form.get("shares")):
            return apology("You don't have that many shaares")


        #Retrive the amount of cash the user has:
        cash = db.execute("SELECT cash FROM users WHERE id=:user", user = session["user_id"])

        update = db.execute("UPDATE Transactions SET shares=shares-:soldshares, price=price-:price WHERE id=:checkid", checkid = check[0]['id'], soldshares = request.form.get("shares"), price = price)

        cashupdate = db.execute("UPDATE users SET cash=:cash WHERE id=:user", user = check[0]['user'], cash = cash[0]['cash'] + price)
        historyupdate = db.execute("INSERT INTO history (user, symbol, shares, boughtsold, price) VALUES(:user, :symbol, :shares, :boughtsold, :price)", user=session["user_id"], symbol = request.form.get("symbol"), shares = -1 * int(request.form.get("shares")), price = float(quote['price']), boughtsold = "Sold")

        #check if the quantity of stocks is zero
        qtycheck = db.execute("SELECT * FROM Transactions WHERE user=:user", user = session["user_id"])
        print(qtycheck)
        for i in range(0, len(qtycheck)):
            if qtycheck[i]['shares'] == 0:
                delete = db.execute("DELETE FROM Transactions WHERE symbol=:symbol", symbol = qtycheck[i]['symbol'])


        return render_template("salecomplete.html", cash = usd(cash[0]['cash']+price), shares = request.form.get("shares"), symbol = request.form.get("symbol"), priceusd = priceusd)

        # Redirect user to home page
        return redirect("/")

    else:
        portfolio = db.execute("SELECT * FROM Transactions WHERE user=:user", user = session["user_id"])
        return(render_template("sell.html", portfolio = portfolio))



def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
