#!/usr/bin/env bash
export PATH=$PATH:/opt/Qt5.5.0/5.5/gcc_64/bin/

build_release_version()
{
	mkdir -p build/release
	cd build/release
	cmake --version
    cmake -D CMAKE_BUILD_TYPE=Release –G "Unix Makefiles" ../../../workspace

	if [ -e "Makefile" ]; then

		cmake --build ../release --target APP --
		cmake --build ../release --target GUIApp --

	else

		echo "Makefile does not exist"
		echo "Build release version failure!"
		return 1

	fi
	cd ../..
}

build_debug_version()
{
    cd sources
    cloc --version
	cloc --by-file --exclude-dir=ShogiCore/SaveAndLoad/JSON/rapidjson --xml --out=../report/cloc_result *

	mkdir -p ../build/debug
	cd ../build/debug
	cmake --version
	cmake -D CMAKE_BUILD_TYPE=Debug –G "Unix Makefiles" ../../../workspace

	if [ -e "Makefile" ]; then

        cd ../../sources
        cppcheck --version
		cppcheck --enable=all -v -iShogiCore/SaveAndLoad/JSON/rapidjson -iShogiCoreTest -i*/qrc_resources.cpp --xml  * 2> ../report/cppcheck_result
        cd ../build/debug

		cmake --build ../debug --clean-first --

		cd ../../sources
		../build/debug/sources/ShogiCoreTest/func_test -xml -o ../report/func_test_results || true
		../build/debug/sources/ShogiCoreTest/module_test -xml -o ../report/module_test_results || true

		valgrind --version
		valgrind --leak-check=full --xml=yes --xml-file=/opt/tomcat/.jenkins/jobs/Shogi/workspace/report/tst_func_test.%p.result /opt/tomcat/.jenkins/jobs/Shogi/workspace/build/debug/sources/ShogiCoreTest/func_test || true
		valgrind --leak-check=full --xml=yes --xml-file=/opt/tomcat/.jenkins/jobs/Shogi/workspace/report/tst_module_test.%p.result /opt/tomcat/.jenkins/jobs/Shogi/workspace/build/debug/sources/ShogiCoreTest/module_test || true

	else

		echo "Makefile does not exist"
		echo "Build debug version failure!"
		return 1

	fi
	cd ..
}

make_report()
{
	cd report/doxygen/
	doxygen --version
	doxygen doxygenconfig.ini

	cd latex
	if [ -e "Makefile" ]; then

		make --version
		make

	else

		echo "Makefile does not exist"
		echo "Report failure!"
		return 1
	fi
	cd ../../..
}

zip_files()
{
    ls
	if [ -z ${JOB_NAME} ] || [ -z ${BUILD_NUMBER}]; then
		echo "Vars JOB_NAME/BUILD_NUMBER are unset"
		echo "Zip failure!"
		return 1
	fi

	TITLE="${JOB_NAME}_v${BUILD_NUMBER}"
	mkdir "$TITLE"

	if [ -e "build/release/sources/ShogiConsoleAPP/APP" ]; then

		cp build/release/sources/ShogiConsoleAPP/APP $TITLE/Shogi


		if [ -e "build/release/sources/ShogiGUI/GUIApp" ]; then

		    cp build/release/sources/ShogiGUI/GUIApp $TITLE/ShogiGUI
	    fi

	    if [ -e "report/doxygen/latex/refman.pdf" ]; then

		    cp report/doxygen/latex/refman.pdf $TITLE/Shogi.pdf
	    fi

		zip --version
		zip $TITLE.zip $TITLE/*

	else

		echo "ConsoleApp does not exist"
		echo "Zip failure!"
		return 1
	fi

}

clean() {
	git clean -f -e *.zip *.pdf
}
