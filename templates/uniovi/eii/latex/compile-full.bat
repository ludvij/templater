@REM compile
pdflatex main -output-directory pdf
@REM create bibliography
biber main -output-directory pdf
@REM compile again with all the stuff needed
pdflatex main -output-directory pdf