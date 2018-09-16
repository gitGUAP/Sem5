#include <Array.au3>
#include <Date.au3>                   ;For use with the Time of Day gui
#include <GUIConstantsEx.au3>
#include <GuiDateTimePicker.au3>                  ;For use with the Time of Day gui
#include <GuiEdit.au3>                   ;For use with the Input Controls
#include <GuiStatusBar.au3>                 ;For use with the Status Bar
#include <WindowsConstants.au3>
Opt("GUIOnEventMode", 1)
; #MAIN GUI# ====================================================================================================================
#Region
$gMain = GUICreate("Test Command Builder", 651, 451, 232, 191, BitOR($WS_MAXIMIZEBOX,$WS_MINIMIZEBOX,$WS_SIZEBOX,$WS_THICKFRAME,$WS_SYSMENU,$WS_CAPTION,$WS_OVERLAPPEDWINDOW,$WS_TILEDWINDOW,$WS_POPUP,$WS_POPUPWINDOW,$WS_GROUP,$WS_TABSTOP,$WS_BORDER,$WS_CLIPSIBLINGS))
GUISetOnEvent($GUI_EVENT_CLOSE, "wClose")
$mFile = GUICtrlCreateMenu("&File")
$mFileExit = GUICtrlCreateMenuItem("&Exit" & @TAB & "         Esc", $mFile)
GUICtrlSetOnEvent(-1, "wClose")
$mOptions = GUICtrlCreateMenu("&Options")
$mProgram = GUICtrlCreateMenu("&Program Commands")
$mProgramAccess = GUICtrlCreateMenuItem("Test" & @TAB & "         Ctrl+Alt+X", $mProgram)
GUICtrlSetOnEvent(-1, "mProgram")
$mWindow = GUICtrlCreateMenu("&Window")
$mWindowCascade = GUICtrlCreateMenuItem("&Cascade" & @TAB & "         F3", $mWindow)
GUICtrlSetOnEvent(-1, "mWindow")
        GUICtrlSetState(-1, $GUI_DISABLE)
$mWindowCloseAll = GUICtrlCreateMenuItem("Close All" & @TAB & "       F4", $mWindow)
GUICtrlSetOnEvent(-1, "mWindow")
        GUICtrlSetState(-1, $GUI_DISABLE)
$mHelp = GUICtrlCreateMenu("&Help")
$mHelpAbout = GUICtrlCreateMenuItem("About" & @TAB & "        F2", $mHelp)
GUICtrlSetOnEvent(-1, "mHelp")
        GUICtrlSetState(-1, $GUI_DISABLE)
$mHelpHelp = GUICtrlCreateMenuItem("Help" & @TAB & "          F1", $mHelp)
GUICtrlSetOnEvent(-1, "mHelp")
        GUICtrlSetState(-1, $GUI_DISABLE)
Dim $gMain_AccelTable[47][2] = [["!+{BS}", $mFileExit],["^!x", $mProgramAccess]]
GUISetAccelerators($gMain_AccelTable)
$sbMain = _GUICtrlStatusBar_Create($gMain, -1, "", $SBARS_SIZEGRIP)
Dim $sbMain_PartsWidth[3] = [120, 240, -1]
_GUICtrlStatusBar_SetParts($sbMain, $sbMain_PartsWidth)
_GUICtrlStatusBar_SetText($sbMain, @TAB & "9/15/2011 1:39 PM", 0)
  _GUICtrlStatusBar_SetText($sbMain, @TAB & "Current Window", 1)
   _GUICtrlStatusBar_SetText($sbMain, "Not Connected", 2)
GUIRegisterMsg($WM_SIZE, "wSize")                 ;Set the windows message "WM_SIZE" to trigger the function "WM_SIZE"
GUISetState(@SW_SHOW)
#EndRegion
; ===============================================================================================================================
; #TIME OF DAY GUI# =============================================================================================================
#Region
$gTime = GUICreate("Time of Day", 385, 170, 2, 2, BitOR($WS_CAPTION,$WS_CHILD,$WS_MINIMIZEBOX,$WS_SYSMENU), "", $gMain)
GUISetOnEvent($GUI_EVENT_CLOSE, "wClose")
$gTimeString = GUICtrlCreateGroup("Command String", 8, 8, 137, 41)
$Label1 = GUICtrlCreateLabel("'proprietary'", 23, 25, 109, 17)
$gTimeTime = GUICtrlCreateGroup("Date and Time", 152, 8, 225, 89)
$dtDateTime = _GUICtrlDTP_Create($gTime, 168, 32, 193, 21)
  _GUICtrlDTP_SetFormat($dtDateTime, "ddd MMM dd, yyyy hh:mm:ss ttt")
$lTimeGMT = GUICtrlCreateLabel("Hours after GMT:", 168, 64, 86, 17)
$cbTimeGMT = GUICtrlCreateCombo("00", 320, 61, 41, 25)
GUICtrlSetData(-1, "01|02|03|04|05|06|07|08|09|10|11|12|13|14|15|16|17|18|19|20|21|22|23")
$bTimeGetTime = GUICtrlCreateButton("Create Command String", 8, 64, 137, 25, $WS_GROUP)
GUICtrlSetOnEvent(-1, "bCmd")
$iTimeCmd = GUICtrlCreateInput("", 8, 104, 369, 21)
$bTimeCmd = GUICtrlCreateButton("Send Command", 8, 136, 369, 25)
GUICtrlSetOnEvent(-1, "bCmd")
#EndRegion
; ===============================================================================================================================
While 1
Sleep(1000)
WEnd

Func bCmd()
If @GUI_CtrlId = $bTimeGetTime Then
  GUICtrlSetData($iTimeCmd, "Proprietary String Goes Here")
EndIf
EndFunc
Func mHelp()
EndFunc
Func mOptions()
EndFunc
Func mPanel()
EndFunc
Func mProgram()
If @GUI_CtrlId = $mProgramAccess Then GUISetState(@SW_SHOW, $gTime)
EndFunc
Func mWindow()
EndFunc
Func wClose()
Switch @GUI_WINHANDLE ; See which GUI sent the CLOSE message
        Case $gTime
            GUISetState(@SW_HIDE, $gTime)
  Case $gMain
   _GUICtrlDTP_Destroy($dtDateTime)
   Exit
    EndSwitch
EndFunc
Func wSize($hWnd, $iMsg, $iwParam, $ilParam)
$aSizes = WinGetPos("Test Command Builder","")            ;Get the size of the program window
If $aSizes[2] < 659 Then $aSizes[2] = 659              ;If just the width is smaller than allowed, then set the minimum size for width
If $aSizes[3] < 485 Then $aSizes[3] = 485              ;If just the height is smaller than allowed, then set the minimum size for height
WinMove("Test Command Builder","", $aSizes[0], $aSizes[1], $aSizes[2], $aSizes[3])   ;Move the window to the new settings
  _GUICtrlStatusBar_Resize($sbMain)              ;Resize the Status Bar
    Return $GUI_RUNDEFMSG                   ;Returns $GUI_RUNDEFMSG
EndFunc   ;==>wSize