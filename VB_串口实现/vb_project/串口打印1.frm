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
   StartUpPosition =   3  '����ȱʡ
   Begin VB.ComboBox comStop 
      Height          =   300
      ItemData        =   "���ڴ�ӡ1.frx":0000
      Left            =   1320
      List            =   "���ڴ�ӡ1.frx":000A
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
      Text            =   "��Ϣ��"
      Top             =   3360
      Width           =   2175
   End
   Begin VB.TextBox txtSend 
      Height          =   1095
      Left            =   360
      TabIndex        =   9
      Text            =   "��������"
      Top             =   4320
      Width           =   2055
   End
   Begin VB.TextBox txtReceive 
      Height          =   5415
      Left            =   2880
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   8
      Text            =   "���ڴ�ӡ1.frx":0014
      Top             =   120
      Width           =   6495
   End
   Begin VB.CommandButton btnClearMsg 
      Caption         =   "�����Ϣ"
      Height          =   375
      Left            =   2880
      TabIndex        =   7
      Top             =   5640
      Width           =   975
   End
   Begin VB.CommandButton btnClearSend 
      Caption         =   "��շ�����"
      Height          =   375
      Left            =   1560
      TabIndex        =   6
      Top             =   5640
      Width           =   1095
   End
   Begin VB.CommandButton btnClearReceive 
      Caption         =   "��ս���"
      Height          =   375
      Left            =   360
      TabIndex        =   5
      Top             =   5640
      Width           =   975
   End
   Begin VB.ComboBox comNumBit 
      Height          =   300
      ItemData        =   "���ڴ�ӡ1.frx":001D
      Left            =   1320
      List            =   "���ڴ�ӡ1.frx":0027
      TabIndex        =   4
      Text            =   "8"
      Top             =   1560
      Width           =   1095
   End
   Begin VB.ComboBox comVerify 
      Height          =   300
      ItemData        =   "���ڴ�ӡ1.frx":0031
      Left            =   1320
      List            =   "���ڴ�ӡ1.frx":003E
      TabIndex        =   3
      Text            =   "��У��"
      Top             =   1080
      Width           =   1095
   End
   Begin VB.ComboBox comBaud 
      Height          =   300
      ItemData        =   "���ڴ�ӡ1.frx":004B
      Left            =   1320
      List            =   "���ڴ�ӡ1.frx":005E
      TabIndex        =   2
      Text            =   "38400"
      Top             =   600
      Width           =   1095
   End
   Begin VB.ComboBox comPort 
      Height          =   300
      ItemData        =   "���ڴ�ӡ1.frx":0084
      Left            =   1320
      List            =   "���ڴ�ӡ1.frx":0086
      TabIndex        =   1
      Top             =   240
      Width           =   1095
   End
   Begin VB.CommandButton btnOpenSerial 
      Caption         =   "�򿪴���"
      Height          =   375
      Left            =   1440
      TabIndex        =   0
      Top             =   2520
      Width           =   975
   End
   Begin VB.Label Label5 
      Caption         =   "ֹͣλ"
      Height          =   255
      Left            =   240
      TabIndex        =   16
      Top             =   2040
      Width           =   615
   End
   Begin VB.Label Label4 
      Caption         =   "����λ"
      Height          =   375
      Left            =   240
      TabIndex        =   14
      Top             =   1560
      Width           =   615
   End
   Begin VB.Label Label3 
      Caption         =   "У��λ"
      Height          =   255
      Left            =   240
      TabIndex        =   13
      Top             =   1080
      Width           =   735
   End
   Begin VB.Label Label2 
      Caption         =   "������"
      Height          =   255
      Left            =   240
      TabIndex        =   12
      Top             =   720
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "����ѡ��"
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
    txtMsg.Text = "��Ϣ����" & Chr(13) & Chr(10)
End Sub
Private Sub btnClearReceive_Click()
    txtReceive.Text = "��������" & Chr(13) & Chr(10)
End Sub
Private Sub btnClearSend_Click()
    txtSend.Text = "��������" & Chr(13) & Chr(10)
End Sub
Private Sub testComPortNum()
'���ϵͳ���ڵĴ��ڣ������õ������б��
Dim a  As Integer
For a = 1 To 16
    '�ж���ӱ�ռ�õĴ��ڵ��б�
    If Err.Number = 8005 Then                              '��������Ϊ8005(�˿��Ѿ���),����ӵ��б�
        comPort.AddItem ("COM" & a - 1)
        comPort.ItemData(comPort.NewIndex) = a - 1
    End If
    Err.Clear                                                          '���������Ϣ

    '�ж���ӿ��õĴ��ڵ��б�
    MSComm1.CommPort = a
    If MSComm1.PortOpen = True Then                   '������ڴ��ڴ�״̬˵�����˴��ڴ��ڣ���ӵ��б�
        comPort.AddItem ("COM" & a)
        comPort.ItemData(comPort.NewIndex) = a
    Else                                                                   '�紮��δ���ڴ�״̬�����д��ڼ�����
        On Error Resume Next                                   '��һ��������ִ���˵��������ںŲ����ڣ�������һ�����ںŵļ��
        MSComm1.PortOpen = True                           '��������ڣ�������ִ�����˵��������ڲ�����
        If MSComm1.PortOpen = True Then               '������ڴ��ڴ�״̬˵�����˴��ڴ��ڣ���ӵ��б����رոô���,�ָ���ʼ�Ĵ���״̬
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
    If btnOpenSerial.Caption = "�򿪴���" Then
        '����ѡ��
        Select Case comPort.ListIndex
            Case -1
                comPortNum = 0
            Case Else
                comPortNum = comPort.ItemData(comPort.ListIndex)
        End Select
        '������ѡ��
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
        'У�鷽ʽѡ��
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
        'ֹͣλѡ��
        Select Case comStop.ListIndex
            Case 0
                stopbit = "1"
            Case 1
                stopbit = "2"
            Case Else
                stopbit = ""
        End Select
        '����λѡ��
        Select Case comNumBit.ListIndex
            Case 0
                numBit = "7"
            Case 1
                numBit = "8"
        End Select
        '��������Ƿ�����
        If comPortNum = 0 Then
            txtMsg.Text = txtMsg.Text + "��ѡ�񴮿�  " + Chr(13) + Chr(10)
        End If
        If baud = "" Then
            txtMsg.Text = txtMsg.Text + "��ѡ������  " + Chr(13) + Chr(10)
        End If
        If parity = "" Then
            txtMsg.Text = txtMsg.Text + "��ѡ��У��λ  " + Chr(13) + Chr(10)
        End If
        If stopbit = "" Then
            txtMsg.Text = txtMsg.Text + "��ѡ��ֹͣλ  " + Chr(13) + Chr(10)
        End If
        If numBit = "" Then
            txtMsg.Text = txtMsg.Text + "��ѡ������λ  " + Chr(13) + Chr(10)
        End If
        
 'txtReceive.Text = comPortNum & baud & parity & stopbit & numBit
        
        
        If comPortNum <> 0 And baud <> "" And parity <> "" And stopbit <> "" And numBit <> "" Then
            MSComm1.CommPort = comPortNum
            MSComm1.Settings = baud & "," & parity & "," & numBit & "," & stopbit
           ' MSComm1.InputMode = comInputModeText
            MSComm1.InputMode = comInputModeBinary  '�����ƽ���
            MSComm1.RThreshold = 5  '���ջ�����ÿ�յ�һ���ַ������¼�onComm()
            MSComm1.PortOpen = True
            
            MSComm1.RTSEnable = True 'תΪ����״̬
            
            If Err.Number = 8002 Then
                txtMsg.Text = txtMsg.Text + "�˿ڲ�����" + Chr(13) + Chr(10)
                MsgBox "��Ч�Ķ˿ں�", vbOKOnly, "��Ϣ"
                GoTo Label
            ElseIf Err.Number = 8005 Then
                txtMsg.Text = txtMsg.Text + "�˿ڱ�ռ��" + Chr(13) + Chr(10)
                MsgBox "�˿ڱ�ռ��", vbOKOnly, "��Ϣ"
                GoTo Label
            Else
                txtMsg.Text = txtMsg.Text + comPort.Text + "�˿��Ѵ�" + Chr(13) + Chr(10)
                txtMsg.Text = txtMsg.Text + "ͨ�Ų���Ϊ��" + Chr(13) + Chr(10)
                txtMsg.Text = txtMsg.Text + baud & "," & parity & "," & numBit & "," & stopbit + Chr(13) + Chr(10)
                btnOpenSerial.Caption = "�رմ���"
                shpSerial.FillColor = &HFF00&
            End If
        Else
            txtMsg.Text = txtMsg.Text + "ͨ�Ų���������" + Chr(13) + Chr(10)
            MsgBox "ͨ�Ų���������", vbOKOnly, "��Ϣ"
            GoTo Label
        End If
    '�رմ���
    ElseIf btnOpenSerial.Caption = "�رմ���" Then
        MSComm1.PortOpen = False
        shpSerial.FillColor = &HFF&
        txtMsg.Text = txtMsg.Text + "�˿��ѹر�" + Chr(13) + Chr(10)
        btnOpenSerial.Caption = "�򿪴���"
    End If
Label:
End Sub
Private Sub btnSend_Click()
On Error Resume Next
    If Trim(txtSend.Text) = "" Or Trim(txtSend.Text) = "��������" + Chr(13) + Chr(10) Then
        txtMsg.Text = txtMsg.Text + "�����뷢������" + Chr(13) + Chr(10)
        MsgBox "�����뷢������", vbOKOnly, "��Ϣ"
        Exit Sub
    End If
    MSComm1.Output = txtSend.Text
    If Err.Number = 8018 Then
        txtMsg.Text = txtMsg.Text & "����δ��" & Chr(13) & Chr(10)
    End If
End Sub



Private Sub Form_Load()
    'comPort.ListIndex = 0
    comBaud.ListIndex = 1
    comVerify.ListIndex = 0
    comStop.ListIndex = 0
    comNumBit.ListIndex = 1
    '
    txtMsg.Text = "��Ϣ����" & Chr(13) & Chr(10)
    txtReceive.Text = "��������" & Chr(13) & Chr(10)
    txtSend.Text = "��������" & Chr(13) & Chr(10)
    '
    Call testComPortNum
    'comPort.ListIndex = 0 '0  '���Զ�Ѱ�ҵ��Ĵ�����Ĭ��ѡ���һ��
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
            MSComm1.InputLen = 0 '��ȡ���ջ������������ַ�
            PB = MSComm1.Input
            PA() = PB
                  
            '*************************�ڴ˴������ڶ��ص����� ****************************************
                  
            If CLng("&H" & Hex(PA(0))) = &HAA Then
                If UBound(PA()) = 4 Then
                    vol_b1 = CLng("&H" & Hex(PA(1))) * 256 + CLng("&H" & Hex(PA(2)))
                    vol_b2 = CLng("&H" & Hex(PA(3))) * 256 + CLng("&H" & Hex(PA(4)))
                    
                   ' temp3 = vol_b2 / 320
                   ' temp = temp3 * 800
                   ' temp1 = temp / 799
                   temp = vol_b2
                    
                    txtReceive.Text = txtReceive.Text & vbCrLf & "B1��ѹ " & Hex(PA(1)) & Hex(PA(2)) & " " & vol_b1 & "mV" & " B1���� " & Hex(PA(3)) & Hex(PA(4)) & " " & temp & "mA"
                  '  txtReceive.Text = txtReceive.Text & vbCrLf & "�ڶ��ڵ�ص�ѹ " & Hex(PA(3)) & Hex(PA(4)) & " " & vol_b2 & "mV"
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
    If txtSend.Text = "��������" & Chr(13) & Chr(10) Then
        txtSend.Text = ""
    End If
End Sub



   
