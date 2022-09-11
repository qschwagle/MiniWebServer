
.PHONY: setup-debug build-debug run-debug test-debug

setup-debug:
	cmake -DCMAKE_RELEASE_TYPE=Debug -Bdebug -DCMAKE_EXPORT_COMPILE_COMMANDS=Yes -S .

run-debug:
	./debug/mini_web_server

build-debug:
	cmake --build debug

test-debug:
	./debug/mini_web_server_test


