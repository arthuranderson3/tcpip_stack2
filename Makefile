.PHONY: build run
build:
	docker build -t tcpip-stack2 .

run:
	docker run -it tcpip-stack2

format:
	git clang-format
