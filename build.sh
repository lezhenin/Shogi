#!/usr/bin/env bash
export PATH=$PATH:/opt/Qt5.5.0/5.5/gcc_64/bin/

build_release_version() {
	mkdir build 
	cd build
	mkdir release
	cmake --version
    cmake –G "Unix Makefiles" ../../../ws

	if [ -e "Makefile" ]; then
		cmake --build ../build --target Release --
		cd ../..
	else
	    cd ../..
		echo "Makefile does not exist"
		echo "Build release version failure!"
		exit 1
	fi	
}

build_debug_version() {
    cd sources
    cloc --version
	cloc --by-file --xml --out=../report/cloc_result *
	cd ../build
	mkdir debug
	cd debug
	cmake --version
	cmake –G "Unix Makefiles" ../../../ws
	if [ -e "Makefile" ]; then
		cmake --build ../build --clean-first --

		cd ../../sources
		ShogiCoreTest/tst_ShogiCoreTest -xml -o test_results || true

		cppcheck --version
		cppcheck --enable=all -v  --xml  * 2> ../report/cppcheck_result

		gcovr --version
		gcovr -r . --xml --exclude='tst*' -o ../report/gcovr_result
		
		valgrind --version
		valgrind --leak-check=full --xml=yes --xml-file=/opt/tomcat/.jenkins/jobs/Shogi/workspace/report/tst_testcore.%p.result /opt/tomcat/.jenkins/jobs/FootballEditor16/workspace/sources/ShogiCoreTest/tst_ShogiCoreTest || true

        cd ../report
		if [ -e "doxygenconfig.ini" ]; then
			doxygen --version
			doxygen doxygenconfig.ini
		else
			echo "Doxygen failed"
			echo "doxygen.ini does not exist"
		fi

		cd ..
	else
	    cd ..
		echo "Makefile does not exist"
		echo "Build debug version failure!"
		exit 1
	fi
}

make_report() {
	cd report/doxygen/latex
	if [ -e "Makefile" ]; then
		make --version
		make
		cd ../../..
	else
		echo "Makefile does not exist"
		echo "Report failure!"
		cd ../../..
		exit 1
	fi
}

zip_files() {
	if [ -z ${JOB_NAME} ] || [ -z ${BUILD_NUMBER}]; then
		echo "Vars JOB_NAME/BUILD_NUMBER are unset"
		echo "Zip failure!"
		exit 1
	fi

	TITLE="${JOB_NAME}_v${BUILD_NUMBER}"
	mkdir "$TITLE"

	if [ -e "build/sources/ShogiConsoleAPP/APP" ]; then
		cp build/sources/ShogiConsoleAPP/APP $TITLE/Shogi_v${BUILD_NUMBER}
		if [ -e "report/doxygen/latex/refman.pdf" ]; then
			cp report/doxygen/latex/refman.pdf $TITLE/Shogi_v${BUILD_NUMBER}.pdf
		fi
		zip --version
		zip $TITLE.zip $TITLE/*
	else
		echo "ConsoleApp does not exist"
		echo "Zip failure!"
		exit 1
	fi

}

clean() {
	git clean -f -e *.zip *.pdf
}