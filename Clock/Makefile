clock.exe: main.cpp lib/Capsule.h lib/CapsuleRunner.h lib/CapsuleRunner.cpp lib/TimerThread.h lib/TimerThread.cpp lib/MessageHandler.h lib/MessageHandler.tpp lib/Message.h caps/Main_Capsule.h caps/Main_Capsule.cpp caps/Clock_Capsule.h caps/Clock_Capsule.cpp caps/Digit_Capsule.h caps/Digit_Capsule.cpp
	g++ main.cpp lib/CapsuleRunner.cpp lib/TimerThread.cpp caps/Main_Capsule.cpp caps/Clock_Capsule.cpp caps/Digit_Capsule.cpp -std=c++20 -g -o clock.exe
clean:
	rm -f clock.exe