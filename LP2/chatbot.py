from datetime import date, datetime, time
import webbrowser

print(date.today())
print(datetime.now().strftime("%H:%M:%S"))

webbrowser.open("https://www.google.com")

# disc = {
#     "hello": "hi there! how can i help you",
#     "what is your name?": "my name is chatbot",
#     "what is date today?": str(date.today()),
#     "what is time?": str(datetime.now().strftime("%H:%M:%S")),
#     "Please open google": ["https://www.google.com"],
# }
# to_con = ""

# while to_con.lower() != "bye":
#     to_con = input("YOU : ")
#     if to_con.lower() != "bye":
#         flag = False
#         for k in disc:
#             if k.lower() == to_con.lower():
#                 if isinstance(disc[k], str):  
#                     print("Bot: " + disc[k])
#                 else:
#                     webbrowser.open(disc[k][0])
#                 flag = True
#                 break
#         if not flag:
#             print("Bot: Sorry! I am a chatbot, not human.")

# print("Bot: Nice talking to you!!")