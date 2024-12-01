#SingleInstance, Force
SendMode Input
SetWorkingDir, %A_ScriptDir%

^XButton1:: ; ctrl+mouseBackButton
Send, {Delete}