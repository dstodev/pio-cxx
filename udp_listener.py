from datetime import datetime
from socket import socket, AF_INET, SOCK_DGRAM, IPPROTO_UDP


def main():
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)
	sock.bind(("0.0.0.0", 58400))

	while True:
		# https://docs.python.org/3/library/socket.html#socket.socket.recvfrom
		bytes, address = sock.recvfrom(128)
		timestamp = datetime.now().strftime("%I:%M:%S%p")  # Record time as soon as possible after it was received
		message = bytes.decode('ascii')
		ip = address[0]
		port = address[1]
		print(f'\n{ip}:{port} @ {timestamp} says: {message}')


if __name__ == '__main__':
	main()
