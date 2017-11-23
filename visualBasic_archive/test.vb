''
'' vb.net ==> string 관련되서 여러가지 연습을 해본 코드
''

sub main()
	'' strTest를 string 형식으로 선언한다
	dim strTest as string = "this is a sample"
	
	'' 단어 교체
	console.writeline("replace ==> " & strTest.replace("sample", "sex"))

	'' 단위를 나타내는 format 함수
	console.writeline("format ==> currency " & format(100000, "C") &
	" Percent ==> " & format(0.23,"p"))

	'' strTest를 공백 단위로 자릅니다
	console.writeline("split ==> " & strTest.split(" "c).length)

	'' strTest에 공백을 _로 치환합니다
	console.writeline("join ==> " & string.join("_"c, strTest.split(" "c)))
	
	'' is라는 단어가 들어간 부분의 인덱스를 구합니다
	console.writeline("indexof ==> " & strTest.indexof("is") & " lastindexof ==> " & strTest.lastindexof("is"))

end sub

