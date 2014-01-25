Public Class frmBoard1

    Dim intTurn As Integer = 0


    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        If intTurn = 1 Then
            intTurn = 0
            Button1.Text = "O"
            Button1.Enabled = False
        ElseIf intTurn = 0 Then
            Button1.Text = "X"
            intTurn = 1
            Button1.Enabled = False
        End If
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        If intTurn = 1 Then
            intTurn = 0
            Button2.Text = "O"
            Button2.Enabled = False
        ElseIf intTurn = 0 Then
            Button2.Text = "X"
            intTurn = 1
            Button2.Enabled = False
        End If
    End Sub

    Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button3.Click
        If intTurn = 1 Then
            intTurn = 0
            Button3.Text = "O"
            Button3.Enabled = False
        ElseIf intTurn = 0 Then
            Button3.Text = "X"
            intTurn = 1
            Button3.Enabled = False
        End If
    End Sub

    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        If intTurn = 1 Then
            intTurn = 0
            Button4.Text = "O"
            Button4.Enabled = False
        ElseIf intTurn = 0 Then
            Button4.Text = "X"
            intTurn = 1
            Button4.Enabled = False
        End If
    End Sub

    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        If intTurn = 1 Then
            intTurn = 0
            Button5.Text = "O"
            Button5.Enabled = False
        ElseIf intTurn = 0 Then
            Button5.Text = "X"
            intTurn = 1
            Button5.Enabled = False
        End If
    End Sub

    Private Sub Button6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button6.Click
        If intTurn = 1 Then
            intTurn = 0
            Button6.Text = "O"
            Button6.Enabled = False
        ElseIf intTurn = 0 Then
            Button6.Text = "X"
            intTurn = 1
            Button6.Enabled = False
        End If
    End Sub

    Private Sub Button7_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button7.Click
        If intTurn = 1 Then
            intTurn = 0
            Button7.Text = "O"
            Button7.Enabled = False
        ElseIf intTurn = 0 Then
            Button7.Text = "X"
            intTurn = 1
            Button7.Enabled = False
        End If
    End Sub

    Private Sub Button8_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button8.Click
        If intTurn = 1 Then
            intTurn = 0
            Button8.Text = "O"
            Button8.Enabled = False
        ElseIf intTurn = 0 Then
            Button8.Text = "X"
            intTurn = 1
            Button8.Enabled = False
        End If
    End Sub

    Private Sub Button9_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button9.Click
        If intTurn = 1 Then
            intTurn = 0
            Button9.Text = "O"
            Button9.Enabled = False
        ElseIf intTurn = 0 Then
            Button9.Text = "X"
            intTurn = 1
            Button9.Enabled = False
        End If
    End Sub
End Class
