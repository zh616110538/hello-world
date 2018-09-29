function test(x)
    for i=1,1000 do
	if(z) then print(x,i,z) z = z + 1 end
    end
end
z = 5
mythread(test,"hello world")
test("goushi")
mythread(test,"heiheihei")
