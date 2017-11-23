import android


app = android.Android()

msg = "Hello from Tiger K's second python scripts!"

app.makeToast(msg)

app.dialogCreateAlert("Select an athlete:")
app.dialogSetSingleChoiceItems(['Mikey','Sarah','James','Julie'])
app.dialogSetPositiveButtonText("Select")
app.dialogSetNegativeButtonText("Quit")
app.dialogShow()

resp = app.dialogGetResponse().result
