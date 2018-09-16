#include <Array.au3>
#include <Constants.au3>
#include <WinAPI.au3>

Global $avChildren

Run('D:\project\Sem5\QualityManagementSoftware\lab5\ahocorasick\ahocorasick.exe')
WinWaitActive('Calculator')

$hWnd = WinGetHandle('Calculator')
WinListChildren($hWnd, $avChildren)

_ArrayDisplay($avChildren)
Exit


Func WinListChildren($hWnd, ByRef $avArr)
    If UBound($avArr, 0) <> 2 Then
        Local $avTmp[10][2] = [[0]]
        $avArr = $avTmp
    EndIf
    
    Local $hChild = _WinAPI_GetWindow($hWnd, $GW_CHILD)
    
    While $hChild
        If $avArr[0][0]+1 > UBound($avArr, 1)-1 Then ReDim $avArr[$avArr[0][0]+10][2]
        $avArr[$avArr[0][0]+1][0] = $hChild
        $avArr[$avArr[0][0]+1][1] = _WinAPI_GetWindowText($hChild)
        $avArr[0][0] += 1
        WinListChildren($hChild, $avArr)
        $hChild = _WinAPI_GetWindow($hChild, $GW_HWNDNEXT)
    WEnd
    
    ReDim $avArr[$avArr[0][0]+1][2]
EndFunc