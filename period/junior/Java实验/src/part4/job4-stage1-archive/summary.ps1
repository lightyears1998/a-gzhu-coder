# 统计代码行数
Get-Content *.java -Encoding UTF8 | Measure-Object -Line -Word -Character
