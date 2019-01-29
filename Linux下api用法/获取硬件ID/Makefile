build :
	g++ -o get_cpu_id get_cpu_id.cpp
	g++ -o get_mac_address get_mac_address.cpp
	g++ -o get_disk_serial_number get_disk_serial_number.cpp
	g++ -o get_board_serial_number get_board_serial_number.cpp

run   :
	@echo "--------------------"
	@- ./get_cpu_id
	@echo "--------------------"
	@- ./get_mac_address
	@echo "--------------------"
	@- ./get_disk_serial_number
	@echo "--------------------"
	@- ./get_board_serial_number
	@echo "--------------------"

clean : 
	-rm get_cpu_id
	-rm get_mac_address
	-rm get_disk_serial_number
	-rm get_board_serial_number

rebuild : clean build
