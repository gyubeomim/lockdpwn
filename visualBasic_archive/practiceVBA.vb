
--------------------------------------------------------------------------------


--------------------------------------------------------------------------------


--------------------------------------------------------------------------------


--------------------------------------------------------------------------------


--------------------------------------------------------------------------------



--------------------------------------------------------------------------------


--------------------------------------------------------------------------------


--------------------------------------------------------------------------------


--------------------------------------------------------------------------------


--------------------------------------------------------------------------------


--------------------------------------------------------------------------------
'' vb.net ==> string 관련되서 여러가지 연습을 해본 코드
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




--------------------------------------------------------------------------------
''  VB.net ==> 처음 Visual Basic .net을 연습해본 코드
Module module1
	sub main()
		'' 여러 변수들을 선언한다 
		dim str1 as string = "he said ""hello"" to me"
		dim str2 as string = "hello"
		dim bell as string
		'' 
		dim dateyo as date
		dim array() as long = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}
		dim i as long

		bell = "hello world2"
		dateyo = "11/20/2014"
		dateyo = "05:25:00 pm"
		dateyo = "11/20/2014 05:45:00 pm"

		console.writeline(str1  & "!")
		console.writeline("tom said " &  """" & str2 & """" & " to me")
		console.writeline(str1.replace("hello", "go"))
		console.readline()

		console.writeline("hello world")
		console.writeline(bell)
		console.writeline(dateyo)

		for i = 0 to 17
			console.writeline(array(i))
			'msgbox(i)
		next
		console.write("len is :")
		console.writeline(len("123456"))

		call test()
	end sub

	sub test()
		dim sum as integer
		dim i as integer
		dim j as integer
		dim co as integer

		for i = 3 to 1 step -1
			for j = 10 to 1 step -1
				co += 1
			next
		next

		i = 0
		do
			console.writeline("hey loop!")
			i += 1
		loop until i > 6
	end sub
end module



