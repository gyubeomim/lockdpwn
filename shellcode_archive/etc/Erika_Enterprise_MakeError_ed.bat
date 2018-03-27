REM Erika Enterprise space --> tab 에러나면 사용하면 되는 스크립트
for /r %%A in (*.d) do vim -c ^"%%s/\ \/cyg/\t\/cyg/g" -c "wq" %%A
for /r %%A in (*.d) do vim -c ^"%%s/\ eec/\teec/g" -c "wq" %%A
