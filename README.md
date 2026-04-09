# Voice-controlled-ESP-Project

Approach 1:- ESP will communicate with phone via Wifi(Vol_1 & Vol_2)(Vol_6 -> mDNS):-
    Phone will work as access point(AP/hotspot) and ESP will work as station point(SP/will connect to hotspot)
    Problems faced:-
    a) To create a http request(http:/a.b.c.d/ledon) local IP is need to be known. a.b.c.d is assigned by AP and I could not set it for any randome phone where my application is running.
    b) Another one approach is to use mDNS, but android does not support .local calls
    Solution is to show its IP and the IP should be entered at phone for further communication. But adding a display is not fisable.

    Hence, solution is to shift to next approach
    
Approach 2:- ESP will communicate with phone via Wifi(Vol_3):-
    ESP will work as access point(AP/hotspot) and Phone will work as station point(SP/will connect to hotspot)
    Problem faced:- 
    The voice detection will run on phone which need internet and whenever connected to hotspot it's net connection get shut down so voice detection does not work.

    Hence, solution is to shift to next approach.

Approach 3:- Use bluetooth to communicate with phone(Vol_4):-
    ESP will be connected to phone via bluetooth. Which is currently in use.

Vol_5 -> Requirement specific adaptations.
