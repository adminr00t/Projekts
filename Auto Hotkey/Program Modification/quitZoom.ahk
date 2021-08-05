#SingleInstance, Force
SendMode Input
SetWorkingDir, %A_ScriptDir%

^Q::
run, taskkill /f /im /zoom.exe
Process, Close, Zoom.exe
Return