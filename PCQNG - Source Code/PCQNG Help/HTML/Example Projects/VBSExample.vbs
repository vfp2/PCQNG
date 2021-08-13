' Load PCQNG control
Dim xPCQNG
Set xPCQNG = CreateObject("QWPCQNG.PCQNG")

' Open PCQNG
xPCQNG.Open

' Get random numbers
Int32 = xPCQNG.RandInt32
Uniform = xPCQNG.RandUniform
Normal = xPCQNG.RandNormal
Bytes = xPCQNG.RandBytes(7)

' Convert Bytes array to an integer array:
Dim BInts(7)
For i = 1 To LenB(Bytes)
      BInts(i) = AscB(MidB(Bytes, i))
Next

' Convert BInts to a hex string for output
For i = 1 To UBound(BInts)
      STemp = CStr(Hex(BInts(i)))
      ' Prefixes "0" to a single digit hex number
      If Len(STemp) = 1 Then
            STemp = "0" & STemp
      End If
      SInts = SInts & STemp
Next

' Show results in popup
WScript.Echo("Int32: " & Int32 & vbCrLf & _ 
                            "Uniform: " & Uniform & vbCrLf & _
                            "Normal: " & Normal & vbCrLf & _
                            "7 Bytes: " & SInts)

' Close PCQNG
xPCQNG.Close