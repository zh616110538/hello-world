function heavy_function(i)
	print("heavy_function start",i)
	if i < 1006 then 
		coroutine.yield(i+1)
	end
	print("heavy_function end",i)
end

