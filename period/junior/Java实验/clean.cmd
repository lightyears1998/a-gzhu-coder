@echo off
REM Execute this batch to clean up no-used file.

echo Cleaning temporary files:
del /S *.tmp

echo Cleaning compiled .class files:
del /S *.class

echo Cleaning javadoc:
del /S package-list
del /S script.js
del /S stylesheet.css
del /S *.html
