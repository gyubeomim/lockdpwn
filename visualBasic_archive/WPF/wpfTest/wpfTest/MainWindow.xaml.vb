Class MainWindow
    Sub New()
        ' This call is required by the designer.
        InitializeComponent()
        ' Add any initialization after the InitializeComponent() call.
        Dim brush As New LinearGradientBrush
        brush.GradientStops.Add(New GradientStop With {.Offset = 0, .Color = Colors.Black})
        brush.GradientStops.Add(New GradientStop With {.Offset = 0.6, .Color = Colors.White})
        grid1.Background = brush
        bedward.Background = brush
    End Sub

    Private Sub Button_Click(sender As Object, e As RoutedEventArgs)
        MessageBox.Show("Hello " & txtAnswer.Text & "!")
    End Sub
End Class