Public Class Form1
    Inherits System.Windows.Forms.Form

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents AxPCQNG1 As AxQWPCQNGLib.AxPCQNG
    Friend WithEvents Go As System.Windows.Forms.Button
    Friend WithEvents Out As System.Windows.Forms.Label
    Friend WithEvents label1 As System.Windows.Forms.Label
    Friend WithEvents Selection As System.Windows.Forms.GroupBox
    Friend WithEvents Int32 As System.Windows.Forms.RadioButton
    Friend WithEvents Normal As System.Windows.Forms.RadioButton
    Friend WithEvents Uniform As System.Windows.Forms.RadioButton
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(Form1))
        Me.AxPCQNG1 = New AxQWPCQNGLib.AxPCQNG()
        Me.Go = New System.Windows.Forms.Button()
        Me.Out = New System.Windows.Forms.Label()
        Me.label1 = New System.Windows.Forms.Label()
        Me.Selection = New System.Windows.Forms.GroupBox()
        Me.Int32 = New System.Windows.Forms.RadioButton()
        Me.Normal = New System.Windows.Forms.RadioButton()
        Me.Uniform = New System.Windows.Forms.RadioButton()
        CType(Me.AxPCQNG1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.Selection.SuspendLayout()
        Me.SuspendLayout()
        '
        'AxPCQNG1
        '
        Me.AxPCQNG1.Enabled = True
        Me.AxPCQNG1.Location = New System.Drawing.Point(8, 8)
        Me.AxPCQNG1.Name = "AxPCQNG1"
        Me.AxPCQNG1.OcxState = CType(resources.GetObject("AxPCQNG1.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxPCQNG1.Size = New System.Drawing.Size(32, 32)
        Me.AxPCQNG1.TabIndex = 0
        '
        'Go
        '
        Me.Go.Location = New System.Drawing.Point(176, 40)
        Me.Go.Name = "Go"
        Me.Go.TabIndex = 9
        Me.Go.Text = "Go"
        '
        'Out
        '
        Me.Out.Location = New System.Drawing.Point(168, 136)
        Me.Out.Name = "Out"
        Me.Out.TabIndex = 8
        Me.Out.Text = "Out"
        '
        'label1
        '
        Me.label1.Location = New System.Drawing.Point(168, 112)
        Me.label1.Name = "label1"
        Me.label1.TabIndex = 7
        Me.label1.Text = "Random Value:"
        '
        'Selection
        '
        Me.Selection.Controls.AddRange(New System.Windows.Forms.Control() {Me.Int32, Me.Normal, Me.Uniform})
        Me.Selection.Location = New System.Drawing.Point(16, 80)
        Me.Selection.Name = "Selection"
        Me.Selection.Size = New System.Drawing.Size(128, 120)
        Me.Selection.TabIndex = 6
        Me.Selection.TabStop = False
        Me.Selection.Text = "Selection"
        '
        'Int32
        '
        Me.Int32.Location = New System.Drawing.Point(16, 88)
        Me.Int32.Name = "Int32"
        Me.Int32.TabIndex = 2
        Me.Int32.Text = "Int32"
        '
        'Normal
        '
        Me.Normal.Location = New System.Drawing.Point(16, 56)
        Me.Normal.Name = "Normal"
        Me.Normal.TabIndex = 1
        Me.Normal.Text = "Normal"
        '
        'Uniform
        '
        Me.Uniform.Location = New System.Drawing.Point(16, 24)
        Me.Uniform.Name = "Uniform"
        Me.Uniform.TabIndex = 0
        Me.Uniform.Text = "Uniform"
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(292, 273)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.Go, Me.Out, Me.label1, Me.Selection, Me.AxPCQNG1})
        Me.Name = "Form1"
        Me.Text = "Form1"
        CType(Me.AxPCQNG1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.Selection.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub Go_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Go.Click

        AxPCQNG1.Open()

        If Int32.Checked Then
            Out.Text = AxPCQNG1.RandInt32.ToString
        End If

        If Uniform.Checked Then
            Out.Text = AxPCQNG1.RandUniform.ToString
        End If

        If Normal.Checked Then
            Out.Text = AxPCQNG1.RandNormal.ToString
        End If

        AxPCQNG1.Close()

    End Sub

End Class
