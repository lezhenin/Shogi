#Shogi

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/report/latex)

set(LATEX_OPTIONS -include-directory=${SOURCE_DIR}
                  -output-directory=${SOURCE_DIR}
                  -job-name=report
                  -quiet)

add_custom_target(report COMMAND pdflatex ${LATEX_OPTIONS} main.tex
                         COMMAND pdflatex ${LATEX_OPTIONS} main.tex
                         COMMAND rm ${SOURCE_DIR}/*.aux ${SOURCE_DIR}/*.log ${SOURCE_DIR}/*.out ${SOURCE_DIR}/*.toc)