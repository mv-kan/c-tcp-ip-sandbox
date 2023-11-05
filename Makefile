debug:
	mkdir -p debug
	cd debug
	cmake -Bdebug -DCMAKE_BUILD_TYPE=Debug

release:
	mkdir -p release
	cd release
	cmake -Brelease -DCMAKE_BUILD_TYPE=Release

clear:
	rm -rf release
	rm -rf debug
	rm -rf build
	rm -rf main.dSYM