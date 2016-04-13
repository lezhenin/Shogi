#!/usr/bin/env bash
export PATH=$PATH:/opt/Qt5.5.0/5.5/gcc_64/bin/

build_release_version() {
	#TODO: можно использовать mkdir с ключом -p
	#-p, --parents     no error if existing, make parent directories as needed
	mkdir build 
	cd build
	mkdir release
	cd release
	cmake --version
    cmake -D CMAKE_BUILD_TYPE=Release –G "Unix Makefiles" ../../../workspace

	if [ -e "Makefile" ]; then
		cmake --build ../release --target APP --
		#TODO: не следует ли вынести эту строку за ветвление?
		cd ../..
	else
	#TODO: не следует ли вынести эту строку за ветвление?
	    cd ../..
		echo "Makefile does not exist"
		echo "Build release version failure!"
		#TODO: кажется слишком суровым вызывать здесь exit, разве return не достаточно?
		# и все остальные exit в этом скрипте аналогично
		exit 1
	fi
	ls
}

build_debug_version() {
    cd sources
    cloc --version
	cloc --by-file --exclude-dir=ShogiCore/SaveAndLoad/JSON/rapidjson --xml --out=../report/cloc_result *
	#TODO: можно использовать mkdir с ключом -p	
	cd ../build
	mkdir debug
	cd debug
	cmake --version
	cmake -D CMAKE_BUILD_TYPE=Debug –G "Unix Makefiles" ../../../workspace
	if [ -e "Makefile" ]; then
		cmake --build ../debug --clean-first --

		cd ../../sources
		../build/debug/sources/ShogiCoreTest/func_test -xml -o ../report/func_test_results || true
		../build/debug/sources/ShogiCoreTest/module_test -xml -o ../report/module_test_results || true

		cppcheck --version
		cppcheck --enable=all -v -iShogiCore/SaveAndLoad/JSON/rapidjson --xml  * 2> ../report/cppcheck_result

        ls

		#TODO: если это не работает в текущем способе сборки, то лучше удалить, 
		gcovr --version
		gcovr --object-directory=/opt/tomcat/.jenkins/jobs/Shogi/workspace/build/debug --root=/opt/tomcat/.jenkins/jobs/Shogi/workspace --xml -o ../report/gcovr_result

		valgrind --version
		valgrind --leak-check=full --xml=yes --xml-file=/opt/tomcat/.jenkins/jobs/Shogi/workspace/report/tst_func_test.%p.result /opt/tomcat/.jenkins/jobs/Shogi/workspace/build/debug/sources/ShogiCoreTest/func_test || true
		valgrind --leak-check=full --xml=yes --xml-file=/opt/tomcat/.jenkins/jobs/Shogi/workspace/report/tst_module_test.%p.result /opt/tomcat/.jenkins/jobs/Shogi/workspace/build/debug/sources/ShogiCoreTest/module_test || true
#TODO: не следует ли вынести эту строку за ветвление?
		cd ..
	else
#TODO: не следует ли вынести эту строку за ветвление?
	    cd ..
		echo "Makefile does not exist"
		echo "Build debug version failure!"
		exit 1
	fi
}

make_report() {
	cd report/doxygen/
	ls
	#TODO: предлагаю убрать эту проверку
	if [ -e "doxygenconfig.ini" ]; then
			doxygen --version
			doxygen doxygenconfig.ini
		else
			echo "Doxygen failed"
			echo "doxygen.ini does not exist"
	fi
	cd latex
	if [ -e "Makefile" ]; then
		make --version
		make
#TODO: не следует ли вынести эту строку за ветвление?
		cd ../../..
	else
		echo "Makefile does not exist"
		echo "Report failure!"
#TODO: не следует ли вынести эту строку за ветвление?
		cd ../../..
		exit 1
	fi
}

zip_files() {
    ls
	if [ -z ${JOB_NAME} ] || [ -z ${BUILD_NUMBER}]; then
		echo "Vars JOB_NAME/BUILD_NUMBER are unset"
		echo "Zip failure!"
		exit 1
	fi

	TITLE="${JOB_NAME}_v${BUILD_NUMBER}"
	mkdir "$TITLE"

	if [ -e "build/release/sources/ShogiConsoleAPP/APP" ]; then
		#TODO: предлагаю убрать номер сборки из названий файлов, поскольку он уже присутствует в названии архива
		cp build/release/sources/ShogiConsoleAPP/APP $TITLE/Shogi_v${BUILD_NUMBER}
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
