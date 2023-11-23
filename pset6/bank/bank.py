

cash = input("Greeting: ").strip().lower()
    if cash.startswith("h"):
        print("$20")
    elif cash.startswith("Hello"):
        print("$0")
    else:
        print("$100")