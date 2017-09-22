VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSComm32.ocx"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   6150
   ClientLeft      =   120
   ClientTop       =   450
   ClientWidth     =   9735
   LinkTopic       =   "Form1"
   ScaleHeight     =   6150
   ScaleWidth      =   9735
   StartUpPosition =   3  '窗口缺省
   Begin VB.ComboBox comStop 
      Height          =   300
      ItemData        =   "串口打印1.frx":0000
      Left            =   1320
      List            =   "串口打印1.frx":000A
      TabIndex        =   15
      Text            =   "1"
      Top             =   2040
      Width           =   1095
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   0
      Top             =   2520
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.TextBox txtMsg 
      Height          =   735
      Left            =   360
      TabIndex        =   10
      Text            =   "消息："
      Top             =   3360
      Width           =   2175
   End
   Begin VB.TextBox txtSend 
      Height          =   1095
      Left            =   360
      TabIndex        =   9
      Text            =   "发送区："
      Top             =   4320
      Width           =   2055
   End
   Begin VB.TextBox txtReceive 
      Height          =   5415
      Left            =   2880
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   8
      Text            =   "串口打印1.frx":0014
      Top             =   120
      Width           =   6495
   End
   Begin VB.CommandButton btnClearMsg 
      Caption         =   "清空消息"
      Height          =   375
      Left            =   2880
      TabIndex        =   7
      Top             =   5640
      Width           =   975
   End
   Begin VB.CommandButton btnClearSend 
      Caption         =   "清空发送区"
      Height          =   375
      Left            =   1560
      TabIndex        =   6
      Top             =   5640
      Width           =   1095
   End
   Begin VB.CommandButton btnClearReceive 
      Caption         =   "清空接收"
      Height          =   375
      Left            =   360
      TabIndex        =   5
      Top             =   5640
      Width           =   975
   End
   Begin VB.ComboBox comNumBit 
      Height          =   300
      ItemData        =   "串口打印1.frx":001D
      Left            =   1320
      List            =   "串口打印1.frx":0027
      TabIndex        =   4
      Text            =   "8"
      Top             =   1560
      Width           =   1095
   End
   Begin VB.ComboBox comVerify 
      Height          =   300
      ItemData        =   "串口打印1.frx":0031
      Left            =   1320
      List            =   "串口打印1.frx":003E
      TabIndex        =   3
      Text            =   "无校验"
      Top             =   1080
      Width           =   1095
   End
   Begin VB.ComboBox comBaud 
      Height          =   300
      ItemData        =   "串口打印1.frx":004B
      Left            =   1320
      List            =   "串口打印1.frx":005E
      TabIndex        =   2
      Text            =   "38400"
      Top             =   600
      Width           =   1095
   End
   Begin VB.ComboBox comPort 
      Height          =   300
      ItemData        =   "串口打印1.frx":0084
      Left            =   1320
      List            =   "串口打印1.frx":0086
      TabIndex        =   1
      Top             =   240
      Width           =   1095
   End
   Begin VB.CommandButton btnOpenSerial 
      Caption         =   "打开串口"
      Height          =   375
      Left            =   1440
      TabIndex        =   0
      Top             =   2520
      Width           =   975
   End
   Begin VB.Label Label5 
      Caption         =   "停止位"
      Height          =   255
      Left            =   240
      TabIndex        =   16
      Top             =   2040
      Width           =   615
   End
   Begin VB.Label Label4 
      Caption         =   "数据位"
      Height          =   375
      Left            =   240
      TabIndex        =   14
      Top             =   1560
      Width           =   615
   End
   Begin VB.Label Label3 
      Caption         =   "校验位"
      Height          =   255
      Left            =   240
      TabIndex        =   13
      Top             =   1080
      Width           =   735
   End
   Begin VB.Label Label2 
      Caption         =   "波特率"
      Height          =   255
      Left            =   240
      TabIndex        =   12
      Top             =   720
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "串口选择"
      Height          =   255
      Left            =   240
      TabIndex        =   11
      Top             =   240
      Width           =   855
   End
   Begin VB.Shape shpSerial 
      FillColor       =   &H000000FF&
      FillStyle       =   0  'Solid
      Height          =   375
      Left            =   840
      Shape           =   3  'Circle
      Top             =   2520
      Width           =   375
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False





Private Sub btnClearMsg_Click()
    txtMsg.Text = "消息区：" & Chr(13) & Chr(10)
End Sub
Private Sub btnClearReceive_Click()
    txtReceive.Text = "接收区：" & Chr(13) & Chr(10)
End Sub
Private Sub btnClearSend_Click()
    txtSend.Text = "发送区：" & Chr(13) & Chr(10)
End Sub
Private Sub testComPortNum()
'检测系统存在的串口，并设置到下拉列表框
Dim a  As Integer
For a = 1 To 16
    '判断添加被占用的串口到列表
    If Err.Number = 8005 Then                              '如果错误号为8005(端口已经打开),则添加到列表
        comPort.AddItem ("COM" & a - 1)
        comPort.ItemData(comPort.NewIndex) = a - 1
    End If
    Err.Clear                                                          '清除错误信息

    '判断添加可用的串口到列表
    MSComm1.CommPort = a
    If MSComm1.PortOpen = True Then                   '如果串口处于打开状态说明，此串口存在，添加到列表
        comPort.AddItem ("COM" & a)
        comPort.ItemData(comPort.NewIndex) = a
    Else                                                                   '如串口未处于打开状态，进行串口检测操作
        On Error Resume Next                                   '下一句操作出现错误，说明这个串口号不存在，进入下一个串口号的检测
        MSComm1.PortOpen = True                           '打开这个串口，如果出现错误则说明这个串口不存在
        If MSComm1.PortOpen = True Then               '如果串口处于打开状态说明，此串口存在，添加到列表，并关闭该串口,恢复初始的串口状态
            comPort.AddItem ("COM" & a)
            comPort.ItemData(comPort.NewIndex) = a
            MSComm1.PortOpen = False
        End If
    End If
    
    
    
    
Next
End Sub
Private Sub btnOpenSerial_Click()
On Error Resume Next
    Dim baud As String, parity As String, stopbit As String, numBit, comPortNum As Integer
    If btnOpenSerial.Caption = "打开串口" Then
        '串口选择
        Select Case comPort.ListIndex
            Case -1
                comPortNum = 0
            Case Else
                comPortNum = comPort.ItemData(comPort.ListIndex)
        End Select
        '波特率选择
        Select Case comBaud.ListIndex
            Case 0
                baud = "4800"
            Case 1
                baud = "9600"
            Case 2
                baud = "19200"
            Case 3
                baud = "38400"
            Case 4
                baud = "115200"
            Case Else
                baud = ""
        End Select
        '校验方式选择
        Select Case comVerify.ListIndex
            Case 0
                parity = "N"
            Case 1
                parity = "O"
            Case 2
                parity = "E"
            Case Else
                parity = ""
        End Select
        '停止位选择
        Select Case comStop.ListIndex
            Case 0
                stopbit = "1"
            Case 1
                stopbit = "2"
            Case Else
                stopbit = ""
        End Select
        '数据位选择
        Select Case comNumBit.ListIndex
            Case 0
                numBit = "7"
            Case 1
                numBit = "8"
        End Select
        '检查输入是否有误
        If comPortNum = 0 Then
            txtMsg.Text = txtMsg.Text + "请选择串口  " + Chr(13) + Chr(10)
        End If
        If baud = "" Then
            txtMsg.Text = txtMsg.Text + "请选择波特率  " + Chr(13) + Chr(10)
        End If
        If parity = "" Then
            txtMsg.Text = txtMsg.Text + "请选择校验位  " + Chr(13) + Chr(10)
        End If
        If stopbit = "" Then
            txtMsg.Text = txtMsg.Text + "请选择停止位  " + Chr(13) + Chr(10)
        End If
        If numBit = "" Then
            txtMsg.Text = txtMsg.Text + "请选择数据位  " + Chr(13) + Chr(10)
        End If
        
 'txtReceive.Text = comPortNum & baud & parity & stopbit & numBit
        
        
        If comPortNum <> 0 And baud <> "" And parity <> "" And stopbit <> "" And numBit <> "" Then
            MSComm1.CommPort = comPortNum
            MSComm1.Settings = baud & "," & parity & "," & numBit & "," & stopbit
           ' MSComm1.InputMode = comInputModeText
            MSComm1.InputMode = comInputModeBinary  '二进制接收
            MSComm1.RThreshold = 5  '接收缓冲区每收到一个字符触发事件onComm()
            MSComm1.PortOpen = True
            
            MSComm1.RTSEnable = True '转为接收状态
            
            If Err.Number = 8002 Then
                txtMsg.Text = txtMsg.Text + "端口不存在" + Chr(13) + Chr(10)
                MsgBox "无效的端口号", vbOKOnly, "信息"
                GoTo Label
            ElseIf Err.Number = 8005 Then
                txtMsg.Text = txtMsg.Text + "端口被占用" + Chr(13) + Chr(10)
                MsgBox "端口被占用", vbOKOnly, "信息"
                GoTo Label
            Else
                txtMsg.Text = txtMsg.Text + comPort.Text + "端口已打开" + Chr(13) + Chr(10)
                txtMsg.Text = txtMsg.Text + "通信参数为：" + Chr(13) + Chr(10)
                txtMsg.Text = txtMsg.Text + baud & "," & parity & "," & numBit & "," & stopbit + Chr(13) + Chr(10)
                btnOpenSerial.Caption = "关闭串口"
                shpSerial.FillColor = &HFF00&
            End If
        Else
            txtMsg.Text = txtMsg.Text + "通信参数不完整" + Chr(13) + Chr(10)
            MsgBox "通信参数不完整", vbOKOnly, "信息"
            GoTo Label
        End If
    '关闭串口
    ElseIf btnOpenSerial.Caption = "关闭串口" Then
        MSComm1.PortOpen = False
        shpSerial.FillColor = &HFF&
        txtMsg.Text = txtMsg.Text + "端口已关闭" + Chr(13) + Chr(10)
        btnOpenSerial.Caption = "打开串口"
    End If
Label:
End Sub
Private Sub btnSend_Click()
On Error Resume Next
    If Trim(txtSend.Text) = "" Or Trim(txtSend.Text) = "发送区：" + Chr(13) + Chr(10) Then
        txtMsg.Text = txtMsg.Text + "请输入发送内容" + Chr(13) + Chr(10)
        MsgBox "请输入发送内容", vbOKOnly, "信息"
        Exit Sub
    End If
    MSComm1.Output = txtSend.Text
    If Err.Number = 8018 Then
        txtMsg.Text = txtMsg.Text & "串口未打开" & Chr(13) & Chr(10)
    End If
End Sub



Private Sub Form_Load()
    'comPort.ListIndex = 0
    comBaud.ListIndex = 1
    comVerify.ListIndex = 0
    comStop.ListIndex = 0
    comNumBit.ListIndex = 1
    '
    txtMsg.Text = "消息区：" & Chr(13) & Chr(10)
    txtReceive.Text = "接收区：" & Chr(13) & Chr(10)
    txtSend.Text = "发送区：" & Chr(13) & Chr(10)
    '
    Call testComPortNum
    'comPort.ListIndex = 0 '0  '在自动寻找到的串口中默认选择第一个
  ' txtReceive.Text = comPort.ListCount
    
End Sub
Private Sub Form_Unload(Cancel As Integer)
On Error Resume Next
    MSComm1.PortOpen = False
End Sub
Private Sub MSComm1_OnComm()
    Dim PA() As Byte
    Dim PB As String
    Dim strdata  As String
    
    Dim vol_b1 As Integer
    Dim vol_b2 As Integer
    Dim vol_b3 As Integer
    Dim temp As Long
    Dim temp1 As Long
    Dim temp3 As Double
    
    
    
    Select Case MSComm1.CommEvent
        Case comEvCD
        Case comEvCTS
        Case comEvDSR
        Case comEvReceive
            MSComm1.InputLen = 0 '读取接收缓冲区的所有字符
            PB = MSComm1.Input
            PA() = PB
                  
            '*************************在此处处理串口读回的数据 ****************************************
                  
            If CLng("&H" & Hex(PA(0))) = &HAA Then
                If UBound(PA()) = 4 Then
                    vol_b1 = CLng("&H" & Hex(PA(1))) * 256 + CLng("&H" & Hex(PA(2)))
                    vol_b2 = CLng("&H" & Hex(PA(3))) * 256 + CLng("&H" & Hex(PA(4)))
                    
                   ' temp3 = vol_b2 / 320
                   ' temp = temp3 * 800
                   ' temp1 = temp / 799
                   temp = vol_b2
                    
                    txtReceive.Text = txtReceive.Text & vbCrLf & "B1电压 " & Hex(PA(1)) & Hex(PA(2)) & " " & vol_b1 & "mV" & " B1电流 " & Hex(PA(3)) & Hex(PA(4)) & " " & temp & "mA"
                  '  txtReceive.Text = txtReceive.Text & vbCrLf & "第二节电池电压 " & Hex(PA(3)) & Hex(PA(4)) & " " & vol_b2 & "mV"
                    txtReceive.SelStart = Len(txtReceive.Text)
                    
                End If
            Else
                 For i = 0 To UBound(PA())
                    'Print "PA(" & i & ")"; PA(i)
                    If Len(Hex(PA(i))) = 1 Then
                        strdata = strdata & " " & Hex(PA(i))
                    Else
                        strdata = strdata & " " & Hex(PA(i))
                    End If
                Next
                    txtReceive.Text = txtReceive.Text & vbCrLf & strdata
                    txtReceive.SelStart = Len(txtReceive.Text)
            End If
            
            '*****************************************************************************************
            
            
        Case comEvSend
    End Select
End Sub
Private Sub txtMsg_Change()
    txtMsg.SelStart = Len(txtMsg.Text)
End Sub
Private Sub txtSend_GotFocus()
    If txtSend.Text = "发送区：" & Chr(13) & Chr(10) Then
        txtSend.Text = ""
    End If
End Sub



   
