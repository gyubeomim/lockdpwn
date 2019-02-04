''
'' vba ==> 3DViewer 창을 연 다음 주어진 3점을 공간 상에 업로드하고 원하는 2점을 축을 그을 수 있는 코드
			Elastic Screw Axis용 코드
''
Dim classLib As New VBdotNet_3DView_for_excel.Class1

'----------------------------------------------------------------
' DECLARATION
Dim i As Integer

Dim x As Double
Dim y As Double
Dim z As Double
Dim rows As Integer

Dim pntNum As Integer ' hard point number!
Dim str As String ' for <-- used!


'----------------------------------------------------
' FUNCTIONS
' open 3D viewer Click!
Sub open3DViewer()
    classLib.open3DViwer
    i = 0
    rows = 4

End Sub

' Test #1, increase number btn
Sub IncreaseNumber()
    Dim stOut As String
    
    stOut = "Test Message from EXCEL .." + CStr(i)
    classLib.IncreaseNumber (stOut)
    i = i + 1
    
End Sub

' Test #2, add points btn
Sub addPoints()
    x = Cells(rows, 10).Value
    y = Cells(rows, 11).Value
    z = Cells(rows, 12).Value
    
    ' get point number data from classLib!
    pntNum = classLib.getPntNum()
    str = "<-- used!"
    
    Cells(rows, 13).Value = str
    Cells(rows, 14).Value = pntNum
    
    rows = rows + 1
    'MsgBox x & " " & y & " " & z & " " & rows
    
    classLib.addPointsUsingExcelData x, y, z

End Sub

' test #3, connect 2 hard points
Sub connectTwoPoints()
    Dim p1 As Integer ' for connecting hard points
    Dim p2 As Integer
    Dim color As Integer

    p1 = Cells(4, 17).Value
    p2 = Cells(5, 17).Value
    color = Cells(6, 17).Value
    
    'MsgBox p1 & " " & p2
    classLib.addModelUsingExcelData p1, p2, color

End Sub


' clear all btn
Sub clearAll()
    Dim rngList As Range
    Sheets("Sheet1").Activate
    Set rngList = ActiveSheet.Range("M4:M100, N4:N100")

    rngList.Value = ""
End Sub


